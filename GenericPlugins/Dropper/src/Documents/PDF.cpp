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
                size_t searchBackOffset = (i > 200) ? i - 200 : 0;
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