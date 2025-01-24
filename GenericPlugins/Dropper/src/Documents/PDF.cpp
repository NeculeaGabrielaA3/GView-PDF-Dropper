#include "Documents.hpp"

namespace GView::GenericPlugins::Droppper::Documents
{
//https://en.wikipedia.org/wiki/PDF#File_format
constexpr uint64 IMAGE_PDF_MAGIC = 0x46445025;

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

// bool PDF::Check(uint64 offset, DataCache& file, BufferView precachedBuffer, Finding& finding)
// {
//     CHECK(IsMagicU32(precachedBuffer, IMAGE_PDF_MAGIC), false, "");

//     auto buffer = file.Get(offset, 0x400, true); // Citim primii 1KB
//     CHECK(buffer.IsValid(), false, "");

//    // Verificăm dacă versiunea PDF este validă (e.g., "%PDF-1.x")
//     const char* header = reinterpret_cast<const char*>(buffer.GetData());
//     CHECK(header != nullptr, false, "");
//     CHECK(strncmp(header, "%PDF-1.", 7) == 0, false, "Invalid PDF version");

//     // Căutăm marker-ul "%%EOF"
//     uint64 fileSize = file.GetSize();
//     auto eofBuffer  = file.Get(fileSize - 0x100, 0x100, true); // Ultimii 256 bytes
//     CHECK(eofBuffer.IsValid(), false, "");

//     bool foundEOF = false;
//     const char* eofData = reinterpret_cast<const char*>(eofBuffer.GetData());
//     CHECK(eofData != nullptr, false, "");
//     for (size_t i = 0; i < eofBuffer.GetLength() - 5; i++) {
//         if (strncmp(eofData + i, "%%EOF", 5) == 0) {
//             foundEOF = true;
//             break;
//         }
//     }
//     CHECK(foundEOF, false, "Missing %%EOF marker");

//     // Căutăm secțiunea "xref" în buffer-ul principal
//     bool foundXRef = false;
//     const char* bufferData = reinterpret_cast<const char*>(buffer.GetData());
//     CHECK(bufferData != nullptr, false, "");
//     for (size_t i = 0; i < buffer.GetLength() - 4; i++) {
//         if (strncmp(bufferData + i, "xref", 4) == 0) {
//             foundXRef = true;
//             break;
//         }
//     }
//     CHECK(foundXRef, false, "Missing xref section");

//     // Căutăm secțiunea "trailer" în buffer-ul principal
//     bool foundTrailer = false;
//     for (size_t i = 0; i < buffer.GetLength() - 7; i++) {
//         if (strncmp(bufferData + i, "trailer", 7) == 0) {
//             foundTrailer = true;
//             break;
//         }
//     }
//     CHECK(foundTrailer, false, "Missing trailer section");

//     // Stabilim limitele fișierului
//     finding.start = offset;
//     finding.end   = fileSize;
//     finding.result = Result::Buffer;

//     return true;
// }

bool PDF::Check(uint64 offset, DataCache& file, BufferView precachedBuffer, Finding& finding)
{
    // Verificăm dacă header-ul fișierului este "%PDF"
    CHECK(IsMagicU32(precachedBuffer, IMAGE_PDF_MAGIC), false, "");

    // Dimensiunea fișierului
    uint64 fileSize = file.GetSize();
    CHECK(fileSize > 0x100, false, "File too small to be a valid PDF");

    // Cautăm "%%EOF" la finalul fișierului, citind în blocuri
    constexpr size_t blockSize = 0x100; // 256 bytes per block
    uint64 currentOffset = fileSize - blockSize;
    bool foundEOF = false;

    while (currentOffset >= offset && !foundEOF) {
        auto buffer = file.Get(currentOffset, blockSize, true);
        CHECK(buffer.IsValid(), false, "Failed to read block");

        const char* data = reinterpret_cast<const char*>(buffer.GetData());
        for (int64 i = buffer.GetLength() - 5; i >= 0; i--) {
            if (strncmp(data + i, "%%EOF", 5) == 0) {
                foundEOF = true;
                currentOffset += i; // Poziția markerului %%EOF
                break;
            }
        }

        if (!foundEOF) {
            if (currentOffset < blockSize) {
                break;
            }
            currentOffset -= blockSize;
        }
    }
    CHECK(foundEOF, false, "Missing %%EOF marker");

    // Cautăm "startxref" înainte de %%EOF
    currentOffset -= blockSize;
    bool foundStartXRef = false;
    uint64 xrefOffset = 0;

    while (currentOffset >= offset && !foundStartXRef) {
        auto buffer = file.Get(currentOffset, blockSize, true);
        CHECK(buffer.IsValid(), false, "Failed to read block");

        const char* data = reinterpret_cast<const char*>(buffer.GetData());
        for (int64 i = buffer.GetLength() - 9; i >= 0; i--) {
            if (strncmp(data + i, "startxref", 9) == 0) {
                foundStartXRef = true;
                xrefOffset = static_cast<uint64>(std::stoull(std::string(data + i + 10)));
                break;
            }
        }

        if (!foundStartXRef) {
            if (currentOffset < blockSize) {
                break;
            }
            currentOffset -= blockSize;
        }
    }
    CHECK(foundStartXRef, false, "Missing startxref marker");

    // Validăm secțiunea xref de la poziția determinată
    auto xrefBuffer = file.Get(xrefOffset, blockSize, true);
    CHECK(xrefBuffer.IsValid(), false, "Failed to read xref section");

    const char* xrefData = reinterpret_cast<const char*>(xrefBuffer.GetData());
    CHECK(strncmp(xrefData, "xref", 4) == 0, false, "Invalid xref section");

    // Stabilim limitele fișierului
    finding.start = offset;
    finding.end   = fileSize;
    finding.result = Result::Buffer;

    return true;
}

} // namespace GView::GenericPlugins::Droppper::Documents