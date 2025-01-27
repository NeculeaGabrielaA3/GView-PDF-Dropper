#include "Documents.hpp"

namespace GView::GenericPlugins::Droppper::Documents
{

//https://en.wikipedia.org/wiki/PDF#File_format
constexpr uint64 IMAGE_PDF_MAGIC       = 0x46445025;
constexpr std::string_view PDF_EOF     = "%%EOF";
constexpr size_t SEARCH_BACK_OFFSET    = 200;   // Number of bytes to search back before EOF

const std::string_view PDF::GetName() const
{
    return "PDF";
}

Category PDF::GetCategory() const
{
    return Category::Documents;
}

Subcategory PDF::GetSubcategory() const
{   
    return Subcategory::PDF;
}

const std::string_view PDF::GetOutputExtension() const
{
    return "pdf";
}

Priority PDF::GetPriority() const
{
    return Priority::Binary;
}

bool PDF::ShouldGroupInOneFile() const
{
    return false;
}

size_t FindObjectEnd(BufferView& buffer, size_t objectStart)
{
    for (size_t i = objectStart; i < buffer.GetLength(); i++) {
        // Look for end of object marker ("endobj")
        if (memcmp(buffer.GetData() + i, "endobj", 6) == 0) {
            return i + 6; 
        }
    }

    return 0; 
}

bool ValidateObjectStructure(BufferView& buffer, size_t objectStart, size_t objectEnd)
{
    // Parse and validate the object structure between objectStart and objectEnd

    bool inDictionary = false;
    bool hasStream    = false;
    bool hasStreamEnd = false;
    bool hasLength    = false;
    size_t i;
    for (i = objectStart; i < objectEnd; i++) {
        if (!inDictionary && memcmp(buffer.GetData() + i, "<<", 2) == 0) {
            inDictionary = true;
        } else if (inDictionary && memcmp(buffer.GetData() + i, ">>", 2) == 0) {
            inDictionary = false;
        } else if (memcmp(buffer.GetData() + i, "stream", 6) == 0) {
            hasStream = true;
        } else if (memcmp(buffer.GetData() + i, "endstream", 9) == 0) {
            if (!hasStream) {
                CHECK(false, false, "Stream object missing 'stream' marker");
            }
            hasStreamEnd = true;
        } else if (inDictionary && memcmp(buffer.GetData() + i, "/Length", 7) == 0) {
            hasLength = true;
        }
    }

    if (hasStream && hasStreamEnd) {
        CHECK(hasLength, false, "Stream object missing '/Length' entry");
    }
    
    CHECK(!inDictionary, false, "Unterminated dictionary");

    return true;
}

bool ValidatePDFObjects(DataCache& file, uint64 startOffset, uint64 endOffset)
{
    uint64 currentOffset = startOffset;
    auto buffer          = file.Get(currentOffset, file.GetCacheSize() / 8, false);

    while (currentOffset < endOffset && buffer.GetLength() > 0) {
        for (size_t i = 0; i < buffer.GetLength(); i++) {
            // Look for object start pattern (e.g., "n 0 obj")
            if (isdigit(buffer.GetData()[i]) && memcmp(buffer.GetData() + i + 2, " 0 obj", 6) == 0) {
                // Object found, validate its structure
                size_t objectStart = i;
                size_t objectEnd   = FindObjectEnd(buffer, objectStart);
                CHECK(objectEnd != 0, false, "Invalid object structure");

                // Validate object content
                CHECK(ValidateObjectStructure(buffer, objectStart, objectEnd), false, "Malformed object content");

                // Update the offset to continue searching
                i = objectEnd;
            }
        }

        currentOffset += buffer.GetLength();
        buffer = file.Get(currentOffset, file.GetCacheSize() / 8, false);
    }

    return true;
}

bool PDF::Check(uint64 offset, DataCache& file, BufferView precachedBuffer, Finding& finding)
{
    CHECK(precachedBuffer.GetLength() >= sizeof(IMAGE_PDF_MAGIC), false, "Precached buffer too small");

    // Check for the PDF magic number (%PDF-)
    CHECK(IsMagicU32(precachedBuffer, IMAGE_PDF_MAGIC), false, "");

    finding.start = offset;
    finding.end   = offset + sizeof(IMAGE_PDF_MAGIC);

    // Additional validation: Verify that the version number is valid (e.g., %PDF-1.x or %PDF-2.x)
    if (precachedBuffer.GetLength() > 7) // Minimum length for %PDF-x.x
    {
        char version = precachedBuffer.GetData()[5];
        CHECK(version >= '1' && version <= '2', false, "Invalid PDF version");
        char subversion = precachedBuffer.GetData()[7];
        CHECK(subversion >= '0' && subversion <= '9', false, "Invalid PDF subversion");
    }

    // Start searching for the end-of-file marker (%%EOF)
    uint64 currentOffset = offset;
    auto buffer          = file.Get(currentOffset, file.GetCacheSize() / 8, false);
    bool xrefFound       = false;
    bool trailerFound    = false;
    bool startxrefFound  = false;

    while (buffer.GetLength() > 0) {
        for (size_t i = 0; i < buffer.GetLength() - PDF_EOF.size() + 1; i++) {
            if (memcmp(buffer.GetData() + i, PDF_EOF.data(), PDF_EOF.size()) == 0) {
                // Validate the presence of "xref" and "trailer" markers before EOF
                size_t searchBackOffset = (i > SEARCH_BACK_OFFSET) ? i - SEARCH_BACK_OFFSET : 0;
                for (size_t j = searchBackOffset; j < i; j++) {
                    if (!xrefFound && memcmp(buffer.GetData() + j, "xref", 4) == 0) {
                        xrefFound = true;
                    }
                    if (!trailerFound && memcmp(buffer.GetData() + j, "trailer", 7) == 0) {
                        trailerFound = true;
                    }
                    if (!startxrefFound && memcmp(buffer.GetData() + j, "startxref", 9) == 0) {
                        startxrefFound = true;
                    }
                }

                // Ensure all critical markers are found
                CHECK(xrefFound, false, "xref marker not found");
                CHECK(trailerFound, false, "trailer marker not found");
                CHECK(startxrefFound, false, "startxref marker not found");

                // Calculate the exact position of the EOF marker
                uint64 eofOffset = currentOffset + i;
                // Validate PDF objects
                CHECK(ValidatePDFObjects(file, offset, eofOffset), false, "Invalid PDF objects");
                finding.end      = eofOffset + PDF_EOF.size();
                finding.result   = Result::Buffer;

                return true;
            }
        }

        // Move to the next chunk of the file
        currentOffset += buffer.GetLength() - PDF_EOF.size();
        buffer = file.Get(currentOffset, file.GetCacheSize() / 8, false);
    }

    return false;
}


} // namespace GView::GenericPlugins::Droppper::Documents