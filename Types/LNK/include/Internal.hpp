#pragma once

#include <GView.hpp>

// https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-shllink/16cb4ca1-9339-4d0c-a68d-bf1d6cc0f943?redirectedfrom=MSDN

namespace GView::Type::LNK
{
#define GET_PAIR_FROM_ENUM(x)                                                                                                              \
    {                                                                                                                                      \
        x, (std::string_view(#x).substr(std::string_view(#x).find_last_of(":") + 1))                                                       \
    }

constexpr uint32 SIGNATURE           = 0x0000004C;
constexpr uint8 CLASS_IDENTIFIER[16] = { 0x01, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

enum class FileAttributeFlags : uint32
{
    ReadOnly            = 0x00000001,
    Hidden              = 0x00000002,
    System              = 0x00000004,
    VolumeLabel         = 0x00000008,
    Directory           = 0x00000010,
    Archive             = 0x00000020,
    Device              = 0x00000040,
    Normal              = 0x00000080,
    Temporary           = 0x00000100,
    SparseFile          = 0x00000200,
    ReparsePoint        = 0x00000400,
    Compressed          = 0x00000800,
    Offline             = 0x00001000,
    NotContentIndexed   = 0x00002000,
    Encrypted           = 0x00004000,
    UnknownWindows95FAT = 0x00008000,
    Virtual             = 0x00010000,
};

static const std::map<FileAttributeFlags, std::string_view> FileAttributeFlagsNames{
    GET_PAIR_FROM_ENUM(FileAttributeFlags::ReadOnly),     GET_PAIR_FROM_ENUM(FileAttributeFlags::Hidden),
    GET_PAIR_FROM_ENUM(FileAttributeFlags::System),       GET_PAIR_FROM_ENUM(FileAttributeFlags::VolumeLabel),
    GET_PAIR_FROM_ENUM(FileAttributeFlags::Directory),    GET_PAIR_FROM_ENUM(FileAttributeFlags::Archive),
    GET_PAIR_FROM_ENUM(FileAttributeFlags::Device),       GET_PAIR_FROM_ENUM(FileAttributeFlags::Normal),
    GET_PAIR_FROM_ENUM(FileAttributeFlags::Temporary),    GET_PAIR_FROM_ENUM(FileAttributeFlags::SparseFile),
    GET_PAIR_FROM_ENUM(FileAttributeFlags::ReparsePoint), GET_PAIR_FROM_ENUM(FileAttributeFlags::Compressed),
    GET_PAIR_FROM_ENUM(FileAttributeFlags::Offline),      GET_PAIR_FROM_ENUM(FileAttributeFlags::NotContentIndexed),
    GET_PAIR_FROM_ENUM(FileAttributeFlags::Encrypted),    GET_PAIR_FROM_ENUM(FileAttributeFlags::UnknownWindows95FAT),
    GET_PAIR_FROM_ENUM(FileAttributeFlags::Virtual)
};

static const std::map<FileAttributeFlags, std::string_view> FileAttributeFlagsDescriptions{
    { FileAttributeFlags::ReadOnly,
      "The file or directory is read-only. For a file, if this bit is set, applications can read the file but cannot write to it or delete "
      "it.For a directory, if this bit is set, applications cannot delete the directory" },
    { FileAttributeFlags::Hidden,
      "The file or directory is hidden. If this bit is set, the file or folder is not included in an ordinary directory listing." },
    { FileAttributeFlags::System, "The file or directory is part of the operating system or is used exclusively by the operating system." },
    { FileAttributeFlags::VolumeLabel, "A bit that MUST be zero. Is a volume label." },
    { FileAttributeFlags::Directory, "The link target is a directory instead of a file." },
    { FileAttributeFlags::Archive,
      "The file or directory is an archive file. Applications use this flag to mark files for backup or removal." },
    { FileAttributeFlags::Device, "A bit that MUST be zero. Is a device." },
    { FileAttributeFlags::Normal,
      "The file or directory has no other flags set. If this bit is 1, all other bits in this structure MUST be clear." },
    { FileAttributeFlags::Temporary, "The file is being used for temporary storage." },
    { FileAttributeFlags::SparseFile, "The file is a sparse file." },
    { FileAttributeFlags::ReparsePoint, "The file or directory has an associated reparse point." },
    { FileAttributeFlags::Compressed,
      "The file or directory is compressed. For a file, this means that all data in the file is compressed.For a directory, this means "
      "that compression is the default for newly created files and subdirectories." },
    { FileAttributeFlags::Offline, "The data of the file is not immediately available. It is stored on an offline storage." },
    { FileAttributeFlags::NotContentIndexed, "The contents of the file need to be indexed." },
    { FileAttributeFlags::Encrypted,
      "The file or directory is encrypted. For a file, this means that all data in the file is encrypted.For a directory, this means that "
      "encryption is the default for newly created files and subdirectories." },
    { FileAttributeFlags::UnknownWindows95FAT, "Unknown (seen on Windows 95 FAT)." },
    { FileAttributeFlags::Virtual, "Is virtual. Currently reserved for future use, not used by the LNK format." },
};

static const std::vector<FileAttributeFlags> GetFileAttributeFlags(uint32 flags)
{
    std::vector<FileAttributeFlags> output;

    for (const auto& data : FileAttributeFlagsNames)
    {
        const auto flag = static_cast<FileAttributeFlags>(static_cast<decltype(flags)>(data.first) & flags);
        if (flag == data.first)
        {
            output.emplace_back(flag);
        }
    }

    return output;
}

enum class ShowWindow : uint32
{
    Hide            = 0,
    Normal          = 1,
    ShowMinimized   = 2,
    Maximize        = 3,
    ShowNoActivate  = 4,
    Show            = 5,
    Minimize        = 6,
    ShowMinNoActive = 7,
    ShowNA          = 8,
    Restore         = 9,
    ShowDefault     = 10,
    ForceMinimize   = 11,
    NormalNA        = 12
};

static const std::map<ShowWindow, std::string_view> ShowWindowNames{
    GET_PAIR_FROM_ENUM(ShowWindow::Hide),           GET_PAIR_FROM_ENUM(ShowWindow::Normal),
    GET_PAIR_FROM_ENUM(ShowWindow::ShowMinimized),  GET_PAIR_FROM_ENUM(ShowWindow::Maximize),
    GET_PAIR_FROM_ENUM(ShowWindow::ShowNoActivate), GET_PAIR_FROM_ENUM(ShowWindow::Show),
    GET_PAIR_FROM_ENUM(ShowWindow::Minimize),       GET_PAIR_FROM_ENUM(ShowWindow::ShowMinNoActive),
    GET_PAIR_FROM_ENUM(ShowWindow::ShowNA),         GET_PAIR_FROM_ENUM(ShowWindow::Restore),
    GET_PAIR_FROM_ENUM(ShowWindow::ShowDefault),    GET_PAIR_FROM_ENUM(ShowWindow::ForceMinimize),
    GET_PAIR_FROM_ENUM(ShowWindow::NormalNA)
};

static const std::map<ShowWindow, std::string_view> ShowWindowDescriptions{
    { ShowWindow::Hide, "Hides the window and activates another window." },
    { ShowWindow::Normal,
      "Activates and displays the window. The window is restored to its original size and position if the window is minimized or "
      "maximized." },
    { ShowWindow::ShowMinimized, "Activates and minimizes the window." },
    { ShowWindow::Maximize, "Activates and maximizes the window" },
    { ShowWindow::ShowNoActivate, "Display the window in its most recent position and size without activating it." },
    { ShowWindow::Show, "Activates the window and displays it in its current size and position." },
    { ShowWindow::Minimize, "Minimizes the window and activates the next top-level windows (in order of depth (Z order))." },
    { ShowWindow::ShowMinNoActive, "Display the window as minimized without activating it." },
    { ShowWindow::ShowNA, "Display the window in its current size and position without activating it." },
    { ShowWindow::Restore,
      "Activates and displays the window. The window is restored to its original size and position if the window is minimized or "
      "maximized." },
    { ShowWindow::ShowDefault, "Set the show state based on the ShowWindow values specified during the creation of the process." },
    { ShowWindow::ForceMinimize, "Minimizes a window, even if the thread that owns the window is not responding." },
    { ShowWindow::NormalNA, "Undocumented according to wine project." },
};

enum class HotKeyHigh : uint8
{
    NONE    = 0x00,
    SHIFT   = 0x01,
    CONTROL = 0x02,
    ALT     = 0x04,
};

static const std::map<HotKeyHigh, std::string_view> HotKeyHighNames{ GET_PAIR_FROM_ENUM(HotKeyHigh::NONE),
                                                                     GET_PAIR_FROM_ENUM(HotKeyHigh::SHIFT),
                                                                     GET_PAIR_FROM_ENUM(HotKeyHigh::CONTROL),
                                                                     GET_PAIR_FROM_ENUM(HotKeyHigh::ALT) };

static const std::string GetHotKeyHighFromFlags(uint8 flags)
{
    static const std::initializer_list<HotKeyHigh> types{ HotKeyHigh::NONE, HotKeyHigh::SHIFT, HotKeyHigh::CONTROL, HotKeyHigh::ALT };

    std::string high;
    for (const auto& t : types)
    {
        if ((flags & static_cast<uint8>(t)) == static_cast<uint8>(t))
        {
            if (high.empty())
            {
                high += HotKeyHighNames.at(t);
            }
            else
            {
                high += " | ";
                high += HotKeyHighNames.at(t);
            }
        }
    }

    if (high.empty())
    {
        high = "NONE";
    }

    return high;
};

enum class HotKeyLow : uint8
{
    NONE    = 0x00,
    _0      = 0x30,
    _1      = 0x31,
    _2      = 0x32,
    _3      = 0x33,
    _4      = 0x34,
    _5      = 0x35,
    _6      = 0x36,
    _7      = 0x37,
    _8      = 0x38,
    _9      = 0x39,
    A       = 0x41,
    B       = 0x42,
    C       = 0x43,
    D       = 0x44,
    E       = 0x45,
    F       = 0x46,
    G       = 0x47,
    H       = 0x48,
    I       = 0x49,
    J       = 0x4A,
    K       = 0x4B,
    L       = 0x4C,
    M       = 0x4D,
    N       = 0x4E,
    O       = 0x4F,
    P       = 0x50,
    Q       = 0x51,
    R       = 0x52,
    S       = 0x53,
    T       = 0x54,
    U       = 0x55,
    V       = 0x56,
    W       = 0x57,
    X       = 0x58,
    Y       = 0x59,
    Z       = 0x5A,
    F1      = 0x70,
    F2      = 0x71,
    F3      = 0x72,
    F4      = 0x73,
    F5      = 0x74,
    F6      = 0x75,
    F7      = 0x76,
    F8      = 0x77,
    F9      = 0x78,
    F10     = 0x79,
    F11     = 0x7A,
    F12     = 0x7B,
    F13     = 0x7C,
    F14     = 0x7D,
    F15     = 0x7E,
    F16     = 0x7F,
    F17     = 0x80,
    F18     = 0x81,
    F19     = 0x82,
    F20     = 0x83,
    F21     = 0x84,
    F22     = 0x85,
    F23     = 0x86,
    F24     = 0x87,
    NumLock = 0x90,
    Scroll  = 0x91,
};

static const std::map<HotKeyLow, std::string_view> HotKeyLowNames{
    GET_PAIR_FROM_ENUM(HotKeyLow::NONE), GET_PAIR_FROM_ENUM(HotKeyLow::_0),      GET_PAIR_FROM_ENUM(HotKeyLow::_1),
    GET_PAIR_FROM_ENUM(HotKeyLow::_2),   GET_PAIR_FROM_ENUM(HotKeyLow::_3),      GET_PAIR_FROM_ENUM(HotKeyLow::_4),
    GET_PAIR_FROM_ENUM(HotKeyLow::_5),   GET_PAIR_FROM_ENUM(HotKeyLow::_6),      GET_PAIR_FROM_ENUM(HotKeyLow::_7),
    GET_PAIR_FROM_ENUM(HotKeyLow::_8),   GET_PAIR_FROM_ENUM(HotKeyLow::_9),      GET_PAIR_FROM_ENUM(HotKeyLow::A),
    GET_PAIR_FROM_ENUM(HotKeyLow::B),    GET_PAIR_FROM_ENUM(HotKeyLow::C),       GET_PAIR_FROM_ENUM(HotKeyLow::D),
    GET_PAIR_FROM_ENUM(HotKeyLow::E),    GET_PAIR_FROM_ENUM(HotKeyLow::F),       GET_PAIR_FROM_ENUM(HotKeyLow::G),
    GET_PAIR_FROM_ENUM(HotKeyLow::H),    GET_PAIR_FROM_ENUM(HotKeyLow::I),       GET_PAIR_FROM_ENUM(HotKeyLow::J),
    GET_PAIR_FROM_ENUM(HotKeyLow::K),    GET_PAIR_FROM_ENUM(HotKeyLow::L),       GET_PAIR_FROM_ENUM(HotKeyLow::M),
    GET_PAIR_FROM_ENUM(HotKeyLow::N),    GET_PAIR_FROM_ENUM(HotKeyLow::O),       GET_PAIR_FROM_ENUM(HotKeyLow::P),
    GET_PAIR_FROM_ENUM(HotKeyLow::Q),    GET_PAIR_FROM_ENUM(HotKeyLow::R),       GET_PAIR_FROM_ENUM(HotKeyLow::S),
    GET_PAIR_FROM_ENUM(HotKeyLow::T),    GET_PAIR_FROM_ENUM(HotKeyLow::U),       GET_PAIR_FROM_ENUM(HotKeyLow::V),
    GET_PAIR_FROM_ENUM(HotKeyLow::W),    GET_PAIR_FROM_ENUM(HotKeyLow::X),       GET_PAIR_FROM_ENUM(HotKeyLow::Y),
    GET_PAIR_FROM_ENUM(HotKeyLow::Z),    GET_PAIR_FROM_ENUM(HotKeyLow::F1),      GET_PAIR_FROM_ENUM(HotKeyLow::F2),
    GET_PAIR_FROM_ENUM(HotKeyLow::F3),   GET_PAIR_FROM_ENUM(HotKeyLow::F4),      GET_PAIR_FROM_ENUM(HotKeyLow::F5),
    GET_PAIR_FROM_ENUM(HotKeyLow::F6),   GET_PAIR_FROM_ENUM(HotKeyLow::F7),      GET_PAIR_FROM_ENUM(HotKeyLow::F8),
    GET_PAIR_FROM_ENUM(HotKeyLow::F9),   GET_PAIR_FROM_ENUM(HotKeyLow::F10),     GET_PAIR_FROM_ENUM(HotKeyLow::F11),
    GET_PAIR_FROM_ENUM(HotKeyLow::F12),  GET_PAIR_FROM_ENUM(HotKeyLow::F13),     GET_PAIR_FROM_ENUM(HotKeyLow::F14),
    GET_PAIR_FROM_ENUM(HotKeyLow::F15),  GET_PAIR_FROM_ENUM(HotKeyLow::F16),     GET_PAIR_FROM_ENUM(HotKeyLow::F17),
    GET_PAIR_FROM_ENUM(HotKeyLow::F18),  GET_PAIR_FROM_ENUM(HotKeyLow::F19),     GET_PAIR_FROM_ENUM(HotKeyLow::F20),
    GET_PAIR_FROM_ENUM(HotKeyLow::F21),  GET_PAIR_FROM_ENUM(HotKeyLow::F22),     GET_PAIR_FROM_ENUM(HotKeyLow::F23),
    GET_PAIR_FROM_ENUM(HotKeyLow::F24),  GET_PAIR_FROM_ENUM(HotKeyLow::NumLock), GET_PAIR_FROM_ENUM(HotKeyLow::Scroll)
};

struct HotKey
{
    uint8 high;
    HotKeyLow low;
};

enum class LinkFlags : uint32
{
    HasTargetIDList             = 0x00000001,
    HasLinkInfo                 = 0x00000002,
    HasName                     = 0x00000004,
    HasRelativePath             = 0x00000008,
    HasWorkingDir               = 0x00000010,
    HasArguments                = 0x00000020,
    HasIconLocation             = 0x00000040,
    IsUnicode                   = 0x00000080,
    ForceNoLinkInfo             = 0x00000100,
    HasExpString                = 0x00000200,
    RunInSeparateProcess        = 0x00000400,
    Unknown0                    = 0x00000800,
    HasDarwinID                 = 0x00001000,
    RunAsUser                   = 0x00002000,
    HasExpIcon                  = 0x00004000,
    NoPidlAlias                 = 0x00008000,
    Unknown1                    = 0x00010000,
    RunWithShimLayer            = 0x00020000,
    ForceNoLinkTrack            = 0x00040000,
    EnableTargetMetadata        = 0x00080000,
    DisableLinkPathTracking     = 0x00100000,
    DisableKnownFolderTracking  = 0x00200000,
    DisableKnownFolderAlias     = 0x00400000,
    AllowLinkToLink             = 0x00800000,
    UnaliasOnSave               = 0x01000000,
    PreferEnvironmentPath       = 0x02000000,
    KeepLocalIDListForUNCTarget = 0x04000000,
};

static const std::map<LinkFlags, std::string_view> LinkFlagsNames{ GET_PAIR_FROM_ENUM(LinkFlags::HasTargetIDList),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::HasLinkInfo),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::HasName),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::HasRelativePath),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::HasWorkingDir),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::HasArguments),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::HasIconLocation),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::IsUnicode),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::ForceNoLinkInfo),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::HasExpString),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::RunInSeparateProcess),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::Unknown0),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::HasDarwinID),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::RunAsUser),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::HasExpIcon),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::NoPidlAlias),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::Unknown1),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::RunWithShimLayer),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::ForceNoLinkTrack),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::EnableTargetMetadata),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::DisableLinkPathTracking),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::DisableKnownFolderTracking),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::DisableKnownFolderAlias),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::AllowLinkToLink),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::UnaliasOnSave),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::PreferEnvironmentPath),
                                                                   GET_PAIR_FROM_ENUM(LinkFlags::KeepLocalIDListForUNCTarget) };

static const std::map<LinkFlags, std::string_view> LinkFlagsDescriptions{
    { LinkFlags::HasTargetIDList,
      "The shell link is saved with an item ID list (IDList). If this bit is set, a LinkTargetIDList structure MUST follow the "
      "ShellLinkHeader. If this bit is not set, this structure MUST NOT be present." },
    { LinkFlags::HasLinkInfo,
      "The shell link is saved with link information. If this bit is set, a LinkInfo structure MUST be present.If this bit is not "
      "set, "
      "this structure MUST NOT be present." },
    { LinkFlags::HasName,
      "The shell link is saved with a name string. If this bit is set, a NAME_STRING StringData structure MUST be present.If this "
      "bit is "
      "not set, this structure MUST NOT be present" },
    { LinkFlags::HasRelativePath,
      "The shell link is saved with a relative path string. If this bit is set, a RELATIVE_PATH StringData structure MUST be "
      "present.If "
      "this bit is not set, this structure MUST NOT be present." },
    { LinkFlags::HasWorkingDir,
      "The shell link is saved with a working directory string. If this bit is set, a WORKING_DIR StringData structure MUST be "
      "present.If "
      "this bit is not set, this structure MUST NOT be present." },
    { LinkFlags::HasArguments,
      "The shell link is saved with command line arguments. If this bit is set, a COMMAND_LINE_ARGUMENTS StringData structure MUST "
      "be "
      "present.If this bit is not set, this structure MUST NOT be present." },
    { LinkFlags::HasIconLocation,
      "The shell link is saved with an icon location string. If this bit is set, an ICON_LOCATION StringData structure MUST be "
      "present.If "
      "this bit is not set, this structure MUST NOT be present." },
    { LinkFlags::IsUnicode,
      "The shell link contains Unicode encoded strings. This bit SHOULD be set. If this bit is set, the StringData section contains "
      "Unicode - encoded strings; otherwise, it contains strings that are encoded using the system default code page." },
    { LinkFlags::ForceNoLinkInfo, "The LinkInfo structure is ignored." },
    { LinkFlags::HasExpString, "The shell link is saved with an EnvironmentVariableDataBlock." },
    { LinkFlags::RunInSeparateProcess,
      "The target is run in a separate virtual machine when launching a link target that is a 16 - bit application." },
    { LinkFlags::Unknown0, "A bit that is undefined and MUST be ignored." },
    { LinkFlags::HasDarwinID, "The shell link is saved with a DarwinDataBlock." },
    { LinkFlags::RunAsUser, "The application is run as a different user when the target of the shell link is activated." },
    { LinkFlags::HasExpIcon, "The shell link is saved with an IconEnvironmentDataBlock." },
    { LinkFlags::NoPidlAlias,
      "The file system location is represented in the shell namespace when the path to an item is parsed into an IDList." },
    { LinkFlags::Unknown1, "A bit that is undefined and MUST be ignored." },
    { LinkFlags::RunWithShimLayer, "The shell link is saved with a ShimDataBlock." },
    { LinkFlags::ForceNoLinkTrack, "The TrackerDataBlock is ignored." },
    { LinkFlags::EnableTargetMetadata,
      "The shell link attempts to collect target properties and store them in the PropertyStoreDataBlock when the link target is set." },
    { LinkFlags::DisableLinkPathTracking, "The EnvironmentVariableDataBlock is ignored." },
    { LinkFlags::DisableKnownFolderTracking,
      "The SpecialFolderDataBlock) and the KnownFolderDataBlock (section 2.5.6) are ignored when loading the shell link.If this bit is "
      "set, these extra data blocks SHOULD NOT be saved when saving the shell link." },
    { LinkFlags::DisableKnownFolderAlias,
      "If the link has a KnownFolderDataBlock, the unaliased form of the known folder IDList SHOULD be used when translating the target "
      "IDList at the time that the link is loaded." },
    { LinkFlags::AllowLinkToLink,
      "Creating a link that references another link is enabled. Otherwise, specifying a link as the target IDList SHOULD NOT be allowed." },
    { LinkFlags::UnaliasOnSave,
      "When saving a link for which the target IDList is under a known folder, either the unaliased form of that known folder or the "
      "target IDList SHOULD be used." },
    { LinkFlags::PreferEnvironmentPath,
      "The target IDList SHOULD NOT be stored; instead, the path specified in the EnvironmentVariableDataBlock SHOULD be used to refer to "
      "the target." },
    { LinkFlags::KeepLocalIDListForUNCTarget,
      "When the target is a UNC name that refers to a location on a local machine, the local path IDList in the PropertyStoreDataBlock "
      "SHOULD be stored, so it can be used when the link is loaded on the local machine." }
};

static const std::vector<LinkFlags> GetLinkFlags(uint32 flags)
{
    std::vector<LinkFlags> output;

    for (const auto& data : LinkFlagsNames)
    {
        const auto flag = static_cast<LinkFlags>(static_cast<decltype(flags)>(data.first) & flags);
        if (flag == data.first)
        {
            output.emplace_back(flag);
        }
    }

    return output;
}

#pragma pack(push, 4)
struct Header
{
    uint32 headerSize;
    uint8 classIdentifier[16];
    uint32 linkFlags;
    uint32 fileAttributeFlags;
    uint64 creationDate;
    uint64 lastAccessDate;
    uint64 lastModificationDate;
    uint32 filesize;
    int32 iconIndex;
    ShowWindow showCommand;
    HotKey hotKey;
    uint16 unknown0;
    uint32 unknown1;
    uint32 unknown2;
};
#pragma pack(pop)

static_assert(sizeof(Header) == 76);

enum class ClassTypeIndicators : uint8
{
    Unknown0                  = 0x00,
    Unknown1                  = 0x01,
    Unknown2                  = 0x17,
    CLSID_ShellDesktop_       = 0x1E, // Not seen in wild but reason to believe it exists.
    CLSID_ShellDesktop        = 0x1F, // Root folder shell item
    CLSID_MyComputer          = 0x20, // Volume shell item -> 0x20 � 0x2f
    CLSID_ShellFSFolder       = 0x30, // File entry shell item -> 0x30 � 0x3f
    CLSID_NetworkRoot         = 0x40, // Network location shell item -> 0x40 � 0x4f
    CompressedFolderShellItem = 0x52, // Compressed Folder Shell Item
    CLSID_Internet            = 0x61, // URI shell item
    ControlPanel_             = 0x70, // Not seen in wild but reason to believe it exists. Item has no item data at offset 0x04.
    ControlPanel              = 0x71, // Control Panel shell item
    Printers                  = 0x72, // Not seen in wild but reason to believe it exists.
    CommonPlacesFolder        = 0x73, // Not seen in wild but reason to believe it exists.
    UsersFilesFolder          = 0x74, // Only seen as delegate item.
    Unknown3                  = 0x76,
    Unknown4                  = 0x80, // Different meaning per class type indicator?
    Unknown5                  = 0xFF
};

static const std::map<ClassTypeIndicators, std::string_view> ClassTypeIndicatorsNames{
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::Unknown0),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::Unknown1),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::Unknown2),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::CLSID_ShellDesktop_),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::CLSID_ShellDesktop),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::CLSID_MyComputer),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::CLSID_ShellFSFolder),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::CLSID_NetworkRoot),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::CompressedFolderShellItem),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::CLSID_Internet),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::ControlPanel_),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::ControlPanel),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::Printers),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::CommonPlacesFolder),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::UsersFilesFolder),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::Unknown3),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::Unknown4),
    GET_PAIR_FROM_ENUM(ClassTypeIndicators::Unknown5)
};

#pragma pack(push, 2)
struct ExtensionBlock0xBEEF0017
{
    uint16 size;      // Extension size. Includes the 2 bytes of the size itself.
    uint16 version;   // Extension version.
    uint32 signature; // Extension signature.
    uint32 unknown0;  // Empty values
    uint32 unknown1;
    uint32 unknown2;
    uint32 unknown3;
    uint32 unknown4;
    uint32 unknown5;
    uint32 unknown6;
    uint64 unknown7; // Empty values
    uint32 unknown8;
    uint32 unknown9;
    uint32 unknown10;
    uint32 unknown11;
    uint32 unknown12;
    uint32 unknown13;
    uint32 unknown14;
    uint16 blockVersionOffset; // First extension block version offset. The offset is relative from the start of the shell item.
};
#pragma pack(pop)

static_assert(sizeof(ExtensionBlock0xBEEF0017) == 74);

enum class SortIndex : uint8
{
    InternetExplorer0 = 0x00,
    Libraries         = 0x42,
    Users             = 0x44,
    MyDocuments       = 0x48,
    MyComputer        = 0x50,
    Network           = 0x58,
    RecycleBin        = 0x60,
    InternetExplorer1 = 0x68,
    Unknown           = 0x70,
    MyGames           = 0x80
};

static const std::map<SortIndex, std::string_view> SortIndexNames{ GET_PAIR_FROM_ENUM(SortIndex::InternetExplorer0),
                                                                   GET_PAIR_FROM_ENUM(SortIndex::Libraries),
                                                                   GET_PAIR_FROM_ENUM(SortIndex::Users),
                                                                   GET_PAIR_FROM_ENUM(SortIndex::MyDocuments),
                                                                   GET_PAIR_FROM_ENUM(SortIndex::MyComputer),
                                                                   GET_PAIR_FROM_ENUM(SortIndex::Network),
                                                                   GET_PAIR_FROM_ENUM(SortIndex::RecycleBin),
                                                                   GET_PAIR_FROM_ENUM(SortIndex::InternetExplorer1),
                                                                   GET_PAIR_FROM_ENUM(SortIndex::Unknown),
                                                                   GET_PAIR_FROM_ENUM(SortIndex::MyGames) };

#pragma pack(push, 4)
struct RootFolderShellItem
{
    uint16 size;                   // The size of the shell item. Includes the 2 bytes of the size itself.
    ClassTypeIndicators indicator; // Class type indicator
    SortIndex sortIndex;
    uint8 shellFolderIdentifier[16]; // GUID
    // extension block maybe -> Present if shell item size > 20 (seen in Windows 7)
};
#pragma pack(pop)

struct RootFolderShellItemWithExtensionBlock0xBEEF0017
{
    RootFolderShellItem item;
    ExtensionBlock0xBEEF0017 block;
};

// The volume shell item is identified by a value of 0x20 after applying a bitmask of 0x70. The remaining bits in the class type indicator
// are presumed to be a sub-type or flags.
enum class VolumeShellItemFlags : uint8
{
    HasName          = 0x01,
    Unknown0         = 0x02,
    Unknown1         = 0x04,
    IsRemovableMedia = 0x08
};

static const std::map<VolumeShellItemFlags, std::string_view> VolumeShellItemFlagsNames{ GET_PAIR_FROM_ENUM(VolumeShellItemFlags::HasName),
                                                                                         GET_PAIR_FROM_ENUM(VolumeShellItemFlags::Unknown0),
                                                                                         GET_PAIR_FROM_ENUM(VolumeShellItemFlags::Unknown1),
                                                                                         GET_PAIR_FROM_ENUM(
                                                                                               VolumeShellItemFlags::IsRemovableMedia) };

static const std::vector<VolumeShellItemFlags> GetVolumeShellItemFlags(uint8 flags)
{
    std::vector<VolumeShellItemFlags> output;

    for (const auto& data : VolumeShellItemFlagsNames)
    {
        const auto flag = static_cast<VolumeShellItemFlags>(static_cast<decltype(flags)>(data.first) & flags);
        if (flag == data.first)
        {
            output.emplace_back(flag);
        }
    }

    return output;
}

struct VolumeShellItem
{
    uint16 size;        // The size of the shell item. Includes the 2 bytes of the size itself.
    uint8 indicator;    // Class type indicator 0x20 after applying a bitmask of 0x70.
    uint8 unknownFlags; // If class type indicator flag 0x01 (has name) is not set. Unknown (Flags) Seen 0x00, 0x1e, 0x80.
};

// The file entry shell item is identified by a value of 0x30 after applying a bitmask of 0x70. The remaining bits in the class type
// indicator are presumed to be a sub-type or flags.
enum class FileEntryShellItemFlags : uint8
{
    IsDirectory        = 0x01,
    IsFile             = 0x02,
    HasUnicodeStrings  = 0x04,
    Unknown0           = 0x08, // Related to the common item dialog?
    HasClassIdentifier = 0x80  // Related to junction?
};

static const std::map<FileEntryShellItemFlags, std::string_view> FileEntryShellItemFlagsNames{
    GET_PAIR_FROM_ENUM(FileEntryShellItemFlags::IsDirectory),        GET_PAIR_FROM_ENUM(FileEntryShellItemFlags::IsFile),
    GET_PAIR_FROM_ENUM(FileEntryShellItemFlags::HasUnicodeStrings),  GET_PAIR_FROM_ENUM(FileEntryShellItemFlags::Unknown0),
    GET_PAIR_FROM_ENUM(FileEntryShellItemFlags::HasClassIdentifier),
};

static const std::vector<FileEntryShellItemFlags> GetFileEntryShellItemFlags(uint8 flags)
{
    std::vector<FileEntryShellItemFlags> output;

    for (const auto& data : FileEntryShellItemFlagsNames)
    {
        const auto flag = static_cast<FileEntryShellItemFlags>(static_cast<decltype(flags)>(data.first) & flags);
        if (flag == data.first)
        {
            output.emplace_back(flag);
        }
    }

    return output;
}

#pragma pack(push, 1)
struct ExtensionBlock0xBEEF0003
{
    uint16 size;                     // Extension size. Includes the 2 bytes of the size itself.
    uint16 version;                  // Extension version.
    uint32 signature;                // Extension signature.
    uint8 shellFolderIdentifier[16]; // Contains a GUID
    uint16 blockVersionOffset;       // First extension block version offset. The offset is relative from the start of the shell item.
};
#pragma pack(pop)

static_assert(sizeof(ExtensionBlock0xBEEF0003) == 26);

enum class VersionBEEF0004 : uint16
{
    WindowsXPOr2003   = 0x03,
    WindowsVistaOrSP0 = 0x07,
    Windows2008Or7Or8 = 0x08,
    Windows8dot1or10  = 0x09,
};

static const std::map<VersionBEEF0004, std::string_view> VersionBEEF0004Names{ GET_PAIR_FROM_ENUM(VersionBEEF0004::WindowsXPOr2003),
                                                                               GET_PAIR_FROM_ENUM(VersionBEEF0004::WindowsVistaOrSP0),
                                                                               GET_PAIR_FROM_ENUM(VersionBEEF0004::Windows2008Or7Or8),
                                                                               GET_PAIR_FROM_ENUM(VersionBEEF0004::Windows8dot1or10) };

#pragma pack(push, 1)
struct ExtensionBlock0xBEEF0004Base
{
    uint16 size;                // Extension size. Includes the 2 bytes of the size itself.
    VersionBEEF0004 version;    // Extension version.
    uint32 signature;           // Extension signature.
    uint32 creationDateAndTime; // Contains a FAT date and time in UTC
    uint32 lastDateAndTime;     // Contains a FAT date and time in UTC
    uint16 unknown0;            // Unknown (version or identifier?)
};
#pragma pack(pop)

struct NTFSFileReference
{
    uint8 mftEntryIndex[6];
    uint16 sequenceNumber;
};

#pragma pack(push, 1)
struct ExtensionBlock0xBEEF0004_V3
{
    ExtensionBlock0xBEEF0004Base base;
    uint16 longStringSize; // If extension version >= 3 -> Contains the size of long name and localized name or 0 if no localized name is
                           // present. For extension version
    // 8 and later it also includes the size of values after this size and before the long name.
    // LocaLizedName    -> If extension version >= 3 and long string size > 0 -> ASCII string with end-of-string character
    // First extension -> If extension version >= 3 block version offset      -> The offset is relative from the start of the shell item.
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ExtensionBlock0xBEEF0004_V7
{
    ExtensionBlock0xBEEF0004Base base;
    uint16 unknown0;                 // If extension version >= 7
    NTFSFileReference fileReference; // If extension version >= 7
    uint64 unknown1;                 // If extension version >= 7
    uint16 longStringSize; // If extension version >= 3 -> Contains the size of long name and localized name or 0 if no localized name is
                           // present. For extension version
    // 8 and later it also includes the size of values after this size and before the long name.
    // LocaLizedName    -> If extension version >= 3 and long string size > 0 -> ASCII string with end-of-string character
    // LocaLizedName    -> If extension version >= 7 and long string size > 0 -> UTF-16 little-endian string with end-of-string character
    // First extension -> If extension version >= 3 block version offset      -> The offset is relative from the start of the shell item.
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ExtensionBlock0xBEEF0004_V8
{
    ExtensionBlock0xBEEF0004Base base;
    uint16 unknown0;                 // If extension version >= 7
    NTFSFileReference fileReference; // If extension version >= 7
    uint64 unknown1;                 // If extension version >= 7
    uint16 longStringSize; // If extension version >= 3 -> Contains the size of long name and localized name or 0 if no localized name is
                           // present. For extension version
    // 8 and later it also includes the size of values after this size and before the long name.
    uint32 unknown3; // If extension version >= 8
    // LocaLizedName    -> If extension version >= 7 and long string size > 0 -> UTF-16 little-endian string with end-of-string character
    // First extension -> If extension version >= 3 block version offset      -> The offset is relative from the start of the shell item.
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ExtensionBlock0xBEEF0004_V9
{
    ExtensionBlock0xBEEF0004Base base;
    uint16 unknown0;                 // If extension version >= 7
    NTFSFileReference fileReference; // If extension version >= 7
    uint64 unknown1;                 // If extension version >= 7
    uint16 longStringSize; // If extension version >= 3 -> Contains the size of long name and localized name or 0 if no localized name is
                           // present. For extension version
    // 8 and later it also includes the size of values after this size and before the long name.
    uint32 unknown2; // If extension version >= 9
    uint32 unknown3; // If extension version >= 8
    // LocaLizedName    -> If extension version >= 7 and long string size > 0 -> UTF-16 little-endian string with end-of-string character
    // First extension -> If extension version >= 3 block version offset      -> The offset is relative from the start of the shell item.
};
#pragma pack(pop)

// TODO:
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0005
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0006
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0008
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0009
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef000a
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef000b
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef000c
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef000e
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0010
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0013
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0014
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0016
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0019
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef001a
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0021
// https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc#extension_block_0xbeef0025

struct FileEntryShellItem_PreWindowsXP
{
};

#pragma pack(push, 2)
struct FileEntryShellItem_XPAndLater
{
    uint16 size;                        // The size of the shell item. Includes the 2 bytes of the size itself.
    uint8 indicator;                    // Class type indicator 0x20 after applying a bitmask of 0x70.
    uint8 unknown0;                     // Unknown (Empty value)
    uint32 fileSize;                    // What about > 32-bit file sizes?
    uint32 lastModificationDateAndTime; // Contains a FAT date and time in UTC
    uint16 fileAttributesFlags;         // Contains the lower 16-bit part of the file attribute flags.

    // Primary Name -> Depending on flag 0x04 an ASCII or UTF-16 little-endian string with end-of-string character. This value is
    // 16-bit aligned, so for ASCII strings it can contain an additional zero byte.

    // 	Extension block 0xbeef0004 -> This value contains the the size of the extension block or 0 if not set.

    // Present if shell item contains more data (and flag 0x80 is not set?) (seen in Windows 2003) -> Extension block -> Seen extension
    // block 0xbeef0005, 0xbeef0006 and 0xbeef001a.

    // If class type indicator flag 0x80 is set -> Extension block 0xbeef0003
};
#pragma pack(pop)

struct FileEntryShellItem_SolidWorks
{
};

#pragma pack(push, 1)
struct ControlPanelShellItem
{
    uint16 size;          // The size of the shell item. Includes the 2 bytes of the size itself.
    uint8 indicator;      // Class type indicator 0x20 after applying a bitmask of 0x70.
    uint8 unknown0;       // Unknown (sort order ?)
    uint8 unknown1;       // Unknown (empty values)
    uint8 identifier[16]; // Control Panel Item identifier. Contains a GUID.
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DelegateShellItem
{
    uint16 size;     // The size of the shell item. Includes the 2 bytes of the size itself.
    uint8 indicator; // Class type indicator 0x20 after applying a bitmask of 0x70.
    uint8 unknown0;
    uint16 unknown1; // Unknown (size ?). Size does not Includes the 2 bytes of the size itself, should map up to the start of the delegate
                     // item identifier Inner or delegated data size?
    uint32 unknownSignature;     // "CFSF"
    uint16 subShellItemDataSize; // Value does not includes the 2 bytes of the size itself
    uint8 subClassTypeIndicator;
    uint8 unknown2;
    uint32 filesize;                    // What about > 32-bit file sizes?
    uint32 lastModificationDateAndTime; // Contains a FAT date and time in UTC
    uint16 fileAttributes;
    // Primary Name -> ASCII string with end-of-string character. This value is 16 - bit aligned, so it can contain an additional zero byte.
    // Unknown (Empty values) -> Empty extension block? (uint16)
    // Delegate item identifier. Contains a GUID. -> 5e591a74-df96-48d3-8d67-1733bcee28ba
    // Item (class) identifier. Contains a GUID.
    // Extension block 0xbeef0004
};
#pragma pack(pop)

struct ShellItem
{
    uint8 type;
    uint8 data[1];
};

struct ItemID
{
    uint16 ItemIDSize;
    ShellItem item;
};

struct IDList
{
    // ItemID ItemIDList;
    uint16 TerminalID;
};

struct LinkTargetIDList
{
    uint16 IDListSize;
    // uint8 IDList[1];
};

enum class LocationFlags : uint32
{
    VolumeIDAndLocalBasePath               = 0x01,
    CommonNetworkRelativeLinkAndPathSuffix = 0x02
};

static const std::map<LocationFlags, std::string_view> LocationFlagsNames{
    GET_PAIR_FROM_ENUM(LocationFlags::VolumeIDAndLocalBasePath),
    GET_PAIR_FROM_ENUM(LocationFlags::CommonNetworkRelativeLinkAndPathSuffix),
};

static const std::map<LocationFlags, std::string_view> LocationFlagsDescriptions{
    { LocationFlags::VolumeIDAndLocalBasePath,
      "The linked file is on a volume. If set the volume informationand the local path contain data." },
    { LocationFlags::CommonNetworkRelativeLinkAndPathSuffix,
      "The linked file is on a network share. If set the network share informationand common path contain data." }
};

enum class DriveType : uint32
{
    Unknown         = 0,
    NoRootDirectory = 1,
    Removable       = 2,
    Fixed           = 3,
    Remote          = 4,
    CDRom           = 5,
    RamDisk         = 6,
};

static const std::map<DriveType, std::string_view> DriveTypeNames{
    GET_PAIR_FROM_ENUM(DriveType::Unknown), GET_PAIR_FROM_ENUM(DriveType::NoRootDirectory), GET_PAIR_FROM_ENUM(DriveType::Removable),
    GET_PAIR_FROM_ENUM(DriveType::Fixed),   GET_PAIR_FROM_ENUM(DriveType::Remote),          GET_PAIR_FROM_ENUM(DriveType::CDRom),
    GET_PAIR_FROM_ENUM(DriveType::RamDisk)
};

static const std::map<DriveType, std::string_view> DriveTypeDescriptions{
    { DriveType::Unknown, "Unknown." },
    { DriveType::NoRootDirectory, "No root directory" },
    { DriveType::Removable, "Removable storage media (floppy, usb)." },
    { DriveType::Fixed, "Fixed storage media (harddisk)." },
    { DriveType::Remote, "Remote storage." },
    { DriveType::CDRom, "Optical disc (CD-ROM, DVD, BD)." },
    { DriveType::RamDisk, "RAM drive." },
};

struct VolumeInformation
{
    uint32 size;              // The size of the volume information including the 4 bytes of the size itself.
    DriveType driveType;      //
    uint32 driveSerialNumber; //
    uint32 volumeLabelOffset; // The offset is relative to the start of the volume information.
    // Offset to the volume label > 16 -> Offset to the Unicode volume label. The offset is relative to the start of the volume information.
    // Volume information data
    //      The volume label -> ASCII string terminated by an end-of-string character.
    //      The Unicode volume label -> UTF-16 little-endian string terminated by an end-of-string character.
};

enum class NetworkShareFlags : uint32
{
    ValidDevice  = 0x01,
    ValidNetType = 0x02
};

static const std::map<NetworkShareFlags, std::string_view> NetworkShareFlagsNames{ GET_PAIR_FROM_ENUM(NetworkShareFlags::ValidDevice),
                                                                                   GET_PAIR_FROM_ENUM(NetworkShareFlags::ValidNetType)

};

static const std::map<NetworkShareFlags, std::string_view> NetworkShareFlagsDescriptions{
    { NetworkShareFlags::ValidDevice, "If set the device name contains data." },
    { NetworkShareFlags::ValidNetType, "If set the network provider type contains data." }
};

static const std::vector<NetworkShareFlags> GetNetworkShareFlags(uint32 flags)
{
    std::vector<NetworkShareFlags> output;

    for (const auto& data : NetworkShareFlagsNames)
    {
        const auto flag = static_cast<NetworkShareFlags>(static_cast<decltype(flags)>(data.first) & flags);
        if (flag == data.first)
        {
            output.emplace_back(flag);
        }
    }

    return output;
}

enum class NetworkProviderTypes : uint32
{
    AVID        = 0x001A0000,
    DOCUSPACE   = 0x001B0000,
    MANGOSOFT   = 0x001C0000,
    SERNET      = 0x001D0000,
    RIVERFRONT1 = 0x001E0000,
    RIVERFRONT2 = 0x001F0000,
    DECORB      = 0x00200000,
    PROTSTOR    = 0x00210000,
    FJ_REDIR    = 0x00220000,
    DISTINCT    = 0x00230000,
    TWINS       = 0x00240000,
    RDR2SAMPLE  = 0x00250000,
    CSC         = 0x00260000,
    _3IN1       = 0x00270000,
    EXTENDNET   = 0x00290000,
    STAC        = 0x002A0000,
    FOXBAT      = 0x002B0000,
    YAHOO       = 0x002C0000,
    EXIFS       = 0x002D0000,
    DAV         = 0x002E0000,
    KNOWARE     = 0x002F0000,
    OBJECT_DIRE = 0x00300000,
    MASFAX      = 0x00310000,
    HOB_NFS     = 0x00320000,
    SHIVA       = 0x00330000,
    IBMAL       = 0x00340000,
    LOCK        = 0x00350000,
    TERMSRV     = 0x00360000,
    SRT         = 0x00370000,
    QUINCY      = 0x00380000,
    OPENAFS     = 0x00390000,
    AVID1       = 0x003A0000,
    DFS         = 0x003B0000,
    KWNP        = 0x003C0000,
    ZENWORKS    = 0x003D0000,
    DRIVEONWEB  = 0x003E0000,
    VMWARE      = 0x003F0000,
    RSFX        = 0x00400000,
    MFILES      = 0x00410000,
    MS_NFS      = 0x00420000,
    GOOGLE      = 0x00430000
};

static const std::map<NetworkProviderTypes, std::string_view> NetworkProviderTypesNames{
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::AVID),        GET_PAIR_FROM_ENUM(NetworkProviderTypes::DOCUSPACE),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::MANGOSOFT),   GET_PAIR_FROM_ENUM(NetworkProviderTypes::SERNET),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::RIVERFRONT1), GET_PAIR_FROM_ENUM(NetworkProviderTypes::RIVERFRONT2),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::DECORB),      GET_PAIR_FROM_ENUM(NetworkProviderTypes::PROTSTOR),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::FJ_REDIR),    GET_PAIR_FROM_ENUM(NetworkProviderTypes::DISTINCT),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::TWINS),       GET_PAIR_FROM_ENUM(NetworkProviderTypes::RDR2SAMPLE),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::CSC),         GET_PAIR_FROM_ENUM(NetworkProviderTypes::_3IN1),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::EXTENDNET),   GET_PAIR_FROM_ENUM(NetworkProviderTypes::STAC),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::FOXBAT),      GET_PAIR_FROM_ENUM(NetworkProviderTypes::YAHOO),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::EXIFS),       GET_PAIR_FROM_ENUM(NetworkProviderTypes::DAV),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::KNOWARE),     GET_PAIR_FROM_ENUM(NetworkProviderTypes::OBJECT_DIRE),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::MASFAX),      GET_PAIR_FROM_ENUM(NetworkProviderTypes::HOB_NFS),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::SHIVA),       GET_PAIR_FROM_ENUM(NetworkProviderTypes::IBMAL),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::LOCK),        GET_PAIR_FROM_ENUM(NetworkProviderTypes::TERMSRV),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::SRT),         GET_PAIR_FROM_ENUM(NetworkProviderTypes::QUINCY),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::OPENAFS),     GET_PAIR_FROM_ENUM(NetworkProviderTypes::AVID1),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::DFS),         GET_PAIR_FROM_ENUM(NetworkProviderTypes::KWNP),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::ZENWORKS),    GET_PAIR_FROM_ENUM(NetworkProviderTypes::DRIVEONWEB),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::VMWARE),      GET_PAIR_FROM_ENUM(NetworkProviderTypes::RSFX),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::MFILES),      GET_PAIR_FROM_ENUM(NetworkProviderTypes::MS_NFS),
    GET_PAIR_FROM_ENUM(NetworkProviderTypes::GOOGLE)
};

struct NetworkShareInformation
{
    uint32 size;  // The size of the network share information.
    uint32 flags; // Network share flags (or type).
    uint32
          networkShareNameOffset; // Offset to the network share name. The offset is relative to the start of the network share information.
    uint32 deviceNameOffset; // Offset to the device name. The offset is relative to the start of the network share information or 0 if not
                             // present.
    NetworkProviderTypes networkProviderType;
    // Offset to the network share name > 20
    //  	(uint32) Offset to the Unicode network share name. The offset is relative to the start of the network share information.
    //      (uint32) Offset to the Unicode device name. The offset is relative to the start of the network share information or 0 if not
    //      present.
    // Network share information data
    //      The network share name -> ASCII string terminated by an end-of-string character.
    //      The device name -> ASCII string terminated by an end-of-string character.
    //      The Unicode network share name -> UTF-16 little-endian string terminated by an end-of-string character.
    //      The Unicode device name -> UTF-16 little-endian string terminated by an end-of-string character.
};

struct LocationInformation
{
    uint32 size;                    // The size of the location information including the 4 bytes of the size itself.
    uint32 headerSize;              // Location information header size.
    uint32 flags;                   // Location flags.
    uint32 volumeInformationOffset; // Offset to the volume information. The offset is relative to the start of the location information.
    uint32 localPathOffset;         // Offset to the local path. The offset is relative to the start of the location information.
    uint32 networkShareOffset; // Offset to the network share information. The offset is relative to the start of the location information.
    uint32 commonPathOffset;   // Offset to the common path. The offset is relative to the start of the location information.

    // If location information header size > 28 -> Offset to the Unicode local path.
    // If location information header size > 32 -> Offset to the Unicode common path.
    // Location information data
    //      The volume information        -> The local path string ASCII string terminated by an end-of-string character.
    //      The network share information -> The common path ASCII string terminated by an end-of-string character
    // If location information header size > 28
    //      The Unicode local path string UTF-16 little-endian string terminated by an end-of-string character
    // If location information header size > 32
    //      The Unicode common path UTF-16 little-endian string terminated by an end-of-string character
};

/*
 * Dependent on the flags in the file header the following data strings are present or not. They are stored in the following order directly
 * after the location information:
 *      description
 *      relative path
 *      working directory
 *      command line arguments
 *      icon location
 */

enum class DataStringTypes : uint8
{
    Description          = 0,
    RelativePath         = 1,
    WorkingDirectory     = 2,
    CommandLineArguments = 3,
    IconLocation         = 4,
};

static const std::map<DataStringTypes, std::string_view> DataStringTypesNames{ GET_PAIR_FROM_ENUM(DataStringTypes::Description),
                                                                               GET_PAIR_FROM_ENUM(DataStringTypes::RelativePath),
                                                                               GET_PAIR_FROM_ENUM(DataStringTypes::WorkingDirectory),
                                                                               GET_PAIR_FROM_ENUM(DataStringTypes::CommandLineArguments),
                                                                               GET_PAIR_FROM_ENUM(DataStringTypes::IconLocation) };
struct DataString
{
    uint16 charsCount; // The number of characters in the string
                       // The string ASCII or UTF-16 little-endian string
};

/*
 * The extra data consist of extra data blocks terminated by the terminal block (an empty extra data block).
 * The extra data blocks are stored in the following order directly after the last data string:
 *      ConsoleProperties,
 *      ConsoleCodepage,
 *      DarwinProperties,
 *      EnvironmentVariablesLocation,
 *      IconLocation,
 *      KnownFolderLocation,
 *      MetadataPropertyStore,
 *      ShimLayerProperties,
 *      SpecialFolderLocation,
 *      DistributedLinkTrackerProperties,
 *      ShellItemIdentifiersListProperties // Vista and Later
 *      Terminal Block (empty)
 */

enum class ExtraDataSignatures : uint32
{
    EnvironmentVariablesLocation       = 0xA0000001,
    ConsoleProperties                  = 0xA0000002,
    DistributedLinkTrackerProperties   = 0xA0000003,
    ConsoleCodepage                    = 0xA0000004,
    SpecialFolderLocation              = 0xA0000005,
    DarwinProperties                   = 0xA0000006,
    IconLocation                       = 0xA0000007,
    ShimLayerProperties                = 0xA0000008,
    MetadataPropertyStore              = 0xA0000009,
    KnownFolderLocation                = 0xA000000B,
    ShellItemIdentifiersListProperties = 0xA000000C // Vista and Later
};

static const std::map<ExtraDataSignatures, std::string_view> ExtraDataSignaturesNames{
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::EnvironmentVariablesLocation),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::ConsoleProperties),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::DistributedLinkTrackerProperties),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::ConsoleCodepage),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::SpecialFolderLocation),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::DarwinProperties),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::IconLocation),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::ShimLayerProperties),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::MetadataPropertyStore),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::KnownFolderLocation),
    GET_PAIR_FROM_ENUM(ExtraDataSignatures::ShellItemIdentifiersListProperties)
};

#pragma pack(push, 1)
struct ExtraDataBase
{
    uint32 size;                   // Includes 4 bytes of the size
    ExtraDataSignatures signature; // The extra block signature
};
#pragma pack(pop)

struct ExtraData_SpecialFolderLocation
{
    ExtraDataBase base;
    uint32 identifier;
    uint32 firstChildSegmentOffset; // The first child segment offset refers to the location of the (shell) item identifier of the first
                                    // child segment of the (shell) item identifiers list specified by the known folder identifier. The
                                    // offset contains the number of bytes relative from the start of the (shell) item identifiers list.
};

#pragma pack(push, 1)
struct MyGUID
{
    uint32 a;
    uint16 b;
    uint16 c;
    uint8 d;
    uint8 e;
    uint8 f;
    uint8 g;
    uint8 h;
    uint8 i;
    uint8 j;
    uint8 dk;
};
#pragma pack(pop)

static_assert(sizeof(MyGUID) == 16);

// legacy CSIDL value: CSIDL_NETWORK
// display name: "Network"
// legacy display name: "My Network Places"
// default path:
// {D20BEEC4-5CA8-4905-AE3B-BF251EA09B53}
constexpr MyGUID FOLDERID_NetworkFolder = { 0xD20BEEC4, 0x5CA8, 0x4905, 0xAE, 0x3B, 0xBF, 0x25, 0x1E, 0xA0, 0x9B, 0x53 };

// // {0AC0837C-BBF8-452A-850D-79D08E667CA7}
// DEFINE_KNOWN_FOLDER(FOLDERID_ComputerFolder, 0x0AC0837C, 0xBBF8, 0x452A, 0x85, 0x0D, 0x79, 0xD0, 0x8E, 0x66, 0x7C, 0xA7);
//
// // {4D9F7874-4E0C-4904-967B-40B0D20C3E4B}
// DEFINE_KNOWN_FOLDER(FOLDERID_InternetFolder, 0x4D9F7874, 0x4E0C, 0x4904, 0x96, 0x7B, 0x40, 0xB0, 0xD2, 0x0C, 0x3E, 0x4B);
//
// // {82A74AEB-AEB4-465C-A014-D097EE346D63}
// DEFINE_KNOWN_FOLDER(FOLDERID_ControlPanelFolder, 0x82A74AEB, 0xAEB4, 0x465C, 0xA0, 0x14, 0xD0, 0x97, 0xEE, 0x34, 0x6D, 0x63);
//
// // {76FC4E2D-D6AD-4519-A663-37BD56068185}
// DEFINE_KNOWN_FOLDER(FOLDERID_PrintersFolder, 0x76FC4E2D, 0xD6AD, 0x4519, 0xA6, 0x63, 0x37, 0xBD, 0x56, 0x06, 0x81, 0x85);
//
// // {43668BF8-C14E-49B2-97C9-747784D784B7}
// DEFINE_KNOWN_FOLDER(FOLDERID_SyncManagerFolder, 0x43668BF8, 0xC14E, 0x49B2, 0x97, 0xC9, 0x74, 0x77, 0x84, 0xD7, 0x84, 0xB7);
//
// // {0F214138-B1D3-4a90-BBA9-27CBC0C5389A}
// DEFINE_KNOWN_FOLDER(FOLDERID_SyncSetupFolder, 0xf214138, 0xb1d3, 0x4a90, 0xbb, 0xa9, 0x27, 0xcb, 0xc0, 0xc5, 0x38, 0x9a);
//
// // {4bfefb45-347d-4006-a5be-ac0cb0567192}
// DEFINE_KNOWN_FOLDER(FOLDERID_ConflictFolder, 0x4bfefb45, 0x347d, 0x4006, 0xa5, 0xbe, 0xac, 0x0c, 0xb0, 0x56, 0x71, 0x92);
//
// // {289a9a43-be44-4057-a41b-587a76d7e7f9}
// DEFINE_KNOWN_FOLDER(FOLDERID_SyncResultsFolder, 0x289a9a43, 0xbe44, 0x4057, 0xa4, 0x1b, 0x58, 0x7a, 0x76, 0xd7, 0xe7, 0xf9);
//
// // {B7534046-3ECB-4C18-BE4E-64CD4CB7D6AC}
// DEFINE_KNOWN_FOLDER(FOLDERID_RecycleBinFolder, 0xB7534046, 0x3ECB, 0x4C18, 0xBE, 0x4E, 0x64, 0xCD, 0x4C, 0xB7, 0xD6, 0xAC);
//
// // {6F0CD92B-2E97-45D1-88FF-B0D186B8DEDD}
// DEFINE_KNOWN_FOLDER(FOLDERID_ConnectionsFolder, 0x6F0CD92B, 0x2E97, 0x45D1, 0x88, 0xFF, 0xB0, 0xD1, 0x86, 0xB8, 0xDE, 0xDD);
//
// // {FD228CB7-AE11-4AE3-864C-16F3910AB8FE}
// DEFINE_KNOWN_FOLDER(FOLDERID_Fonts, 0xFD228CB7, 0xAE11, 0x4AE3, 0x86, 0x4C, 0x16, 0xF3, 0x91, 0x0A, 0xB8, 0xFE);
//
// // display name:        "Desktop"
// // default path:        "C:\Users\<UserName>\Desktop"
// // legacy default path: "C:\Documents and Settings\<userName>\Desktop"
// // legacy CSIDL value:  CSIDL_DESKTOP
// // {B4BFCC3A-DB2C-424C-B029-7FE99A87C641}
// DEFINE_KNOWN_FOLDER(FOLDERID_Desktop, 0xB4BFCC3A, 0xDB2C, 0x424C, 0xB0, 0x29, 0x7F, 0xE9, 0x9A, 0x87, 0xC6, 0x41);
//
// // {B97D20BB-F46A-4C97-BA10-5E3608430854}
// DEFINE_KNOWN_FOLDER(FOLDERID_Startup, 0xB97D20BB, 0xF46A, 0x4C97, 0xBA, 0x10, 0x5E, 0x36, 0x08, 0x43, 0x08, 0x54);
//
// // {A77F5D77-2E2B-44C3-A6A2-ABA601054A51}
// DEFINE_KNOWN_FOLDER(FOLDERID_Programs, 0xA77F5D77, 0x2E2B, 0x44C3, 0xA6, 0xA2, 0xAB, 0xA6, 0x01, 0x05, 0x4A, 0x51);
//
// // {625B53C3-AB48-4EC1-BA1F-A1EF4146FC19}
// DEFINE_KNOWN_FOLDER(FOLDERID_StartMenu, 0x625B53C3, 0xAB48, 0x4EC1, 0xBA, 0x1F, 0xA1, 0xEF, 0x41, 0x46, 0xFC, 0x19);
//
// // {AE50C081-EBD2-438A-8655-8A092E34987A}
// DEFINE_KNOWN_FOLDER(FOLDERID_Recent, 0xAE50C081, 0xEBD2, 0x438A, 0x86, 0x55, 0x8A, 0x09, 0x2E, 0x34, 0x98, 0x7A);
//
// // {8983036C-27C0-404B-8F08-102D10DCFD74}
// DEFINE_KNOWN_FOLDER(FOLDERID_SendTo, 0x8983036C, 0x27C0, 0x404B, 0x8F, 0x08, 0x10, 0x2D, 0x10, 0xDC, 0xFD, 0x74);
//
// // {FDD39AD0-238F-46AF-ADB4-6C85480369C7}
// DEFINE_KNOWN_FOLDER(FOLDERID_Documents, 0xFDD39AD0, 0x238F, 0x46AF, 0xAD, 0xB4, 0x6C, 0x85, 0x48, 0x03, 0x69, 0xC7);
//
// // {1777F761-68AD-4D8A-87BD-30B759FA33DD}
// DEFINE_KNOWN_FOLDER(FOLDERID_Favorites, 0x1777F761, 0x68AD, 0x4D8A, 0x87, 0xBD, 0x30, 0xB7, 0x59, 0xFA, 0x33, 0xDD);
//
// // {C5ABBF53-E17F-4121-8900-86626FC2C973}
// DEFINE_KNOWN_FOLDER(FOLDERID_NetHood, 0xC5ABBF53, 0xE17F, 0x4121, 0x89, 0x00, 0x86, 0x62, 0x6F, 0xC2, 0xC9, 0x73);
//
// // {9274BD8D-CFD1-41C3-B35E-B13F55A758F4}
// DEFINE_KNOWN_FOLDER(FOLDERID_PrintHood, 0x9274BD8D, 0xCFD1, 0x41C3, 0xB3, 0x5E, 0xB1, 0x3F, 0x55, 0xA7, 0x58, 0xF4);
//
// // {A63293E8-664E-48DB-A079-DF759E0509F7}
// DEFINE_KNOWN_FOLDER(FOLDERID_Templates, 0xA63293E8, 0x664E, 0x48DB, 0xA0, 0x79, 0xDF, 0x75, 0x9E, 0x05, 0x09, 0xF7);
//
// // {82A5EA35-D9CD-47C5-9629-E15D2F714E6E}
// DEFINE_KNOWN_FOLDER(FOLDERID_CommonStartup, 0x82A5EA35, 0xD9CD, 0x47C5, 0x96, 0x29, 0xE1, 0x5D, 0x2F, 0x71, 0x4E, 0x6E);
//
// // {0139D44E-6AFE-49F2-8690-3DAFCAE6FFB8}
// DEFINE_KNOWN_FOLDER(FOLDERID_CommonPrograms, 0x0139D44E, 0x6AFE, 0x49F2, 0x86, 0x90, 0x3D, 0xAF, 0xCA, 0xE6, 0xFF, 0xB8);
//
// // {A4115719-D62E-491D-AA7C-E74B8BE3B067}
// DEFINE_KNOWN_FOLDER(FOLDERID_CommonStartMenu, 0xA4115719, 0xD62E, 0x491D, 0xAA, 0x7C, 0xE7, 0x4B, 0x8B, 0xE3, 0xB0, 0x67);
//
// // {C4AA340D-F20F-4863-AFEF-F87EF2E6BA25}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicDesktop, 0xC4AA340D, 0xF20F, 0x4863, 0xAF, 0xEF, 0xF8, 0x7E, 0xF2, 0xE6, 0xBA, 0x25);
//
// // {62AB5D82-FDC1-4DC3-A9DD-070D1D495D97}
// DEFINE_KNOWN_FOLDER(FOLDERID_ProgramData, 0x62AB5D82, 0xFDC1, 0x4DC3, 0xA9, 0xDD, 0x07, 0x0D, 0x1D, 0x49, 0x5D, 0x97);
//
// // {B94237E7-57AC-4347-9151-B08C6C32D1F7}
// DEFINE_KNOWN_FOLDER(FOLDERID_CommonTemplates, 0xB94237E7, 0x57AC, 0x4347, 0x91, 0x51, 0xB0, 0x8C, 0x6C, 0x32, 0xD1, 0xF7);
//
// // {ED4824AF-DCE4-45A8-81E2-FC7965083634}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicDocuments, 0xED4824AF, 0xDCE4, 0x45A8, 0x81, 0xE2, 0xFC, 0x79, 0x65, 0x08, 0x36, 0x34);
//
// // {3EB685DB-65F9-4CF6-A03A-E3EF65729F3D}
// DEFINE_KNOWN_FOLDER(FOLDERID_RoamingAppData, 0x3EB685DB, 0x65F9, 0x4CF6, 0xA0, 0x3A, 0xE3, 0xEF, 0x65, 0x72, 0x9F, 0x3D);
//
// // {F1B32785-6FBA-4FCF-9D55-7B8E7F157091}
// DEFINE_KNOWN_FOLDER(FOLDERID_LocalAppData, 0xF1B32785, 0x6FBA, 0x4FCF, 0x9D, 0x55, 0x7B, 0x8E, 0x7F, 0x15, 0x70, 0x91);
//
// // {A520A1A4-1780-4FF6-BD18-167343C5AF16}
// DEFINE_KNOWN_FOLDER(FOLDERID_LocalAppDataLow, 0xA520A1A4, 0x1780, 0x4FF6, 0xBD, 0x18, 0x16, 0x73, 0x43, 0xC5, 0xAF, 0x16);
//
// // {352481E8-33BE-4251-BA85-6007CAEDCF9D}
// DEFINE_KNOWN_FOLDER(FOLDERID_InternetCache, 0x352481E8, 0x33BE, 0x4251, 0xBA, 0x85, 0x60, 0x07, 0xCA, 0xED, 0xCF, 0x9D);
//
// // {2B0F765D-C0E9-4171-908E-08A611B84FF6}
// DEFINE_KNOWN_FOLDER(FOLDERID_Cookies, 0x2B0F765D, 0xC0E9, 0x4171, 0x90, 0x8E, 0x08, 0xA6, 0x11, 0xB8, 0x4F, 0xF6);
//
// // {D9DC8A3B-B784-432E-A781-5A1130A75963}
// DEFINE_KNOWN_FOLDER(FOLDERID_History, 0xD9DC8A3B, 0xB784, 0x432E, 0xA7, 0x81, 0x5A, 0x11, 0x30, 0xA7, 0x59, 0x63);
//
// // {1AC14E77-02E7-4E5D-B744-2EB1AE5198B7}
// DEFINE_KNOWN_FOLDER(FOLDERID_System, 0x1AC14E77, 0x02E7, 0x4E5D, 0xB7, 0x44, 0x2E, 0xB1, 0xAE, 0x51, 0x98, 0xB7);
//
// // {D65231B0-B2F1-4857-A4CE-A8E7C6EA7D27}
// DEFINE_KNOWN_FOLDER(FOLDERID_SystemX86, 0xD65231B0, 0xB2F1, 0x4857, 0xA4, 0xCE, 0xA8, 0xE7, 0xC6, 0xEA, 0x7D, 0x27);
//
// // {F38BF404-1D43-42F2-9305-67DE0B28FC23}
// DEFINE_KNOWN_FOLDER(FOLDERID_Windows, 0xF38BF404, 0x1D43, 0x42F2, 0x93, 0x05, 0x67, 0xDE, 0x0B, 0x28, 0xFC, 0x23);
//
// // {5E6C858F-0E22-4760-9AFE-EA3317B67173}
// DEFINE_KNOWN_FOLDER(FOLDERID_Profile, 0x5E6C858F, 0x0E22, 0x4760, 0x9A, 0xFE, 0xEA, 0x33, 0x17, 0xB6, 0x71, 0x73);
//
// // {33E28130-4E1E-4676-835A-98395C3BC3BB}
// DEFINE_KNOWN_FOLDER(FOLDERID_Pictures, 0x33E28130, 0x4E1E, 0x4676, 0x83, 0x5A, 0x98, 0x39, 0x5C, 0x3B, 0xC3, 0xBB);

// {7C5A40EF-A0FB-4BFC-874A-C0F2E0B9FA8E}
constexpr MyGUID FOLDERID_ProgramFilesX86 = { 0x7C5A40EF, 0xA0FB, 0x4BFC, 0x87, 0x4A, 0xC0, 0xF2, 0xE0, 0xB9, 0xFA, 0x8E };

// // {DE974D24-D9C6-4D3E-BF91-F4455120B917}
// DEFINE_KNOWN_FOLDER(FOLDERID_ProgramFilesCommonX86, 0xDE974D24, 0xD9C6, 0x4D3E, 0xBF, 0x91, 0xF4, 0x45, 0x51, 0x20, 0xB9, 0x17);
//
// // {6D809377-6AF0-444b-8957-A3773F02200E}
// DEFINE_KNOWN_FOLDER(FOLDERID_ProgramFilesX64, 0x6d809377, 0x6af0, 0x444b, 0x89, 0x57, 0xa3, 0x77, 0x3f, 0x02, 0x20, 0x0e);
//
// // {6365D5A7-0F0D-45e5-87F6-0DA56B6A4F7D}
// DEFINE_KNOWN_FOLDER(FOLDERID_ProgramFilesCommonX64, 0x6365d5a7, 0xf0d, 0x45e5, 0x87, 0xf6, 0xd, 0xa5, 0x6b, 0x6a, 0x4f, 0x7d);
//
// // {905e63b6-c1bf-494e-b29c-65b732d3d21a}
// DEFINE_KNOWN_FOLDER(FOLDERID_ProgramFiles, 0x905e63b6, 0xc1bf, 0x494e, 0xb2, 0x9c, 0x65, 0xb7, 0x32, 0xd3, 0xd2, 0x1a);
//
// // {F7F1ED05-9F6D-47A2-AAAE-29D317C6F066}
// DEFINE_KNOWN_FOLDER(FOLDERID_ProgramFilesCommon, 0xF7F1ED05, 0x9F6D, 0x47A2, 0xAA, 0xAE, 0x29, 0xD3, 0x17, 0xC6, 0xF0, 0x66);
//
// // {5cd7aee2-2219-4a67-b85d-6c9ce15660cb}
// DEFINE_KNOWN_FOLDER(FOLDERID_UserProgramFiles, 0x5cd7aee2, 0x2219, 0x4a67, 0xb8, 0x5d, 0x6c, 0x9c, 0xe1, 0x56, 0x60, 0xcb);
//
// // {bcbd3057-ca5c-4622-b42d-bc56db0ae516}
// DEFINE_KNOWN_FOLDER(FOLDERID_UserProgramFilesCommon, 0xbcbd3057, 0xca5c, 0x4622, 0xb4, 0x2d, 0xbc, 0x56, 0xdb, 0x0a, 0xe5, 0x16);
//
// // {724EF170-A42D-4FEF-9F26-B60E846FBA4F}
// DEFINE_KNOWN_FOLDER(FOLDERID_AdminTools, 0x724EF170, 0xA42D, 0x4FEF, 0x9F, 0x26, 0xB6, 0x0E, 0x84, 0x6F, 0xBA, 0x4F);
//
// // {D0384E7D-BAC3-4797-8F14-CBA229B392B5}
// DEFINE_KNOWN_FOLDER(FOLDERID_CommonAdminTools, 0xD0384E7D, 0xBAC3, 0x4797, 0x8F, 0x14, 0xCB, 0xA2, 0x29, 0xB3, 0x92, 0xB5);
//
// // {4BD8D571-6D19-48D3-BE97-422220080E43}
// DEFINE_KNOWN_FOLDER(FOLDERID_Music, 0x4BD8D571, 0x6D19, 0x48D3, 0xBE, 0x97, 0x42, 0x22, 0x20, 0x08, 0x0E, 0x43);
//
// // {18989B1D-99B5-455B-841C-AB7C74E4DDFC}
// DEFINE_KNOWN_FOLDER(FOLDERID_Videos, 0x18989B1D, 0x99B5, 0x455B, 0x84, 0x1C, 0xAB, 0x7C, 0x74, 0xE4, 0xDD, 0xFC);
//
// // {C870044B-F49E-4126-A9C3-B52A1FF411E8}
// DEFINE_KNOWN_FOLDER(FOLDERID_Ringtones, 0xC870044B, 0xF49E, 0x4126, 0xA9, 0xC3, 0xB5, 0x2A, 0x1F, 0xF4, 0x11, 0xE8);
//
// // {B6EBFB86-6907-413C-9AF7-4FC2ABF07CC5}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicPictures, 0xB6EBFB86, 0x6907, 0x413C, 0x9A, 0xF7, 0x4F, 0xC2, 0xAB, 0xF0, 0x7C, 0xC5);
//
// // {3214FAB5-9757-4298-BB61-92A9DEAA44FF}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicMusic, 0x3214FAB5, 0x9757, 0x4298, 0xBB, 0x61, 0x92, 0xA9, 0xDE, 0xAA, 0x44, 0xFF);
//
// // {2400183A-6185-49FB-A2D8-4A392A602BA3}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicVideos, 0x2400183A, 0x6185, 0x49FB, 0xA2, 0xD8, 0x4A, 0x39, 0x2A, 0x60, 0x2B, 0xA3);
//
// // {E555AB60-153B-4D17-9F04-A5FE99FC15EC}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicRingtones, 0xE555AB60, 0x153B, 0x4D17, 0x9F, 0x04, 0xA5, 0xFE, 0x99, 0xFC, 0x15, 0xEC);
//
// // {8AD10C31-2ADB-4296-A8F7-E4701232C972}
// DEFINE_KNOWN_FOLDER(FOLDERID_ResourceDir, 0x8AD10C31, 0x2ADB, 0x4296, 0xA8, 0xF7, 0xE4, 0x70, 0x12, 0x32, 0xC9, 0x72);
//
// // {2A00375E-224C-49DE-B8D1-440DF7EF3DDC}
// DEFINE_KNOWN_FOLDER(FOLDERID_LocalizedResourcesDir, 0x2A00375E, 0x224C, 0x49DE, 0xB8, 0xD1, 0x44, 0x0D, 0xF7, 0xEF, 0x3D, 0xDC);
//
// // {C1BAE2D0-10DF-4334-BEDD-7AA20B227A9D}
// DEFINE_KNOWN_FOLDER(FOLDERID_CommonOEMLinks, 0xC1BAE2D0, 0x10DF, 0x4334, 0xBE, 0xDD, 0x7A, 0xA2, 0x0B, 0x22, 0x7A, 0x9D);
//
// // {9E52AB10-F80D-49DF-ACB8-4330F5687855}
// DEFINE_KNOWN_FOLDER(FOLDERID_CDBurning, 0x9E52AB10, 0xF80D, 0x49DF, 0xAC, 0xB8, 0x43, 0x30, 0xF5, 0x68, 0x78, 0x55);
//
// // {0762D272-C50A-4BB0-A382-697DCD729B80}
// DEFINE_KNOWN_FOLDER(FOLDERID_UserProfiles, 0x0762D272, 0xC50A, 0x4BB0, 0xA3, 0x82, 0x69, 0x7D, 0xCD, 0x72, 0x9B, 0x80);
//
// // {DE92C1C7-837F-4F69-A3BB-86E631204A23}
// DEFINE_KNOWN_FOLDER(FOLDERID_Playlists, 0xDE92C1C7, 0x837F, 0x4F69, 0xA3, 0xBB, 0x86, 0xE6, 0x31, 0x20, 0x4A, 0x23);
//
// // {15CA69B3-30EE-49C1-ACE1-6B5EC372AFB5}
// DEFINE_KNOWN_FOLDER(FOLDERID_SamplePlaylists, 0x15CA69B3, 0x30EE, 0x49C1, 0xAC, 0xE1, 0x6B, 0x5E, 0xC3, 0x72, 0xAF, 0xB5);
//
// // {B250C668-F57D-4EE1-A63C-290EE7D1AA1F}
// DEFINE_KNOWN_FOLDER(FOLDERID_SampleMusic, 0xB250C668, 0xF57D, 0x4EE1, 0xA6, 0x3C, 0x29, 0x0E, 0xE7, 0xD1, 0xAA, 0x1F);
//
// // {C4900540-2379-4C75-844B-64E6FAF8716B}
// DEFINE_KNOWN_FOLDER(FOLDERID_SamplePictures, 0xC4900540, 0x2379, 0x4C75, 0x84, 0x4B, 0x64, 0xE6, 0xFA, 0xF8, 0x71, 0x6B);
//
// // {859EAD94-2E85-48AD-A71A-0969CB56A6CD}
// DEFINE_KNOWN_FOLDER(FOLDERID_SampleVideos, 0x859EAD94, 0x2E85, 0x48AD, 0xA7, 0x1A, 0x09, 0x69, 0xCB, 0x56, 0xA6, 0xCD);
//
// // {69D2CF90-FC33-4FB7-9A0C-EBB0F0FCB43C}
// DEFINE_KNOWN_FOLDER(FOLDERID_PhotoAlbums, 0x69D2CF90, 0xFC33, 0x4FB7, 0x9A, 0x0C, 0xEB, 0xB0, 0xF0, 0xFC, 0xB4, 0x3C);
//
// // {DFDF76A2-C82A-4D63-906A-5644AC457385}
// DEFINE_KNOWN_FOLDER(FOLDERID_Public, 0xDFDF76A2, 0xC82A, 0x4D63, 0x90, 0x6A, 0x56, 0x44, 0xAC, 0x45, 0x73, 0x85);
//
// // {df7266ac-9274-4867-8d55-3bd661de872d}
// DEFINE_KNOWN_FOLDER(FOLDERID_ChangeRemovePrograms, 0xdf7266ac, 0x9274, 0x4867, 0x8d, 0x55, 0x3b, 0xd6, 0x61, 0xde, 0x87, 0x2d);
//
// // {a305ce99-f527-492b-8b1a-7e76fa98d6e4}
// DEFINE_KNOWN_FOLDER(FOLDERID_AppUpdates, 0xa305ce99, 0xf527, 0x492b, 0x8b, 0x1a, 0x7e, 0x76, 0xfa, 0x98, 0xd6, 0xe4);
//
// // {de61d971-5ebc-4f02-a3a9-6c82895e5c04}
// DEFINE_KNOWN_FOLDER(FOLDERID_AddNewPrograms, 0xde61d971, 0x5ebc, 0x4f02, 0xa3, 0xa9, 0x6c, 0x82, 0x89, 0x5e, 0x5c, 0x04);
//
// // {374DE290-123F-4565-9164-39C4925E467B}
// DEFINE_KNOWN_FOLDER(FOLDERID_Downloads, 0x374de290, 0x123f, 0x4565, 0x91, 0x64, 0x39, 0xc4, 0x92, 0x5e, 0x46, 0x7b);
//
// // {3D644C9B-1FB8-4f30-9B45-F670235F79C0}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicDownloads, 0x3d644c9b, 0x1fb8, 0x4f30, 0x9b, 0x45, 0xf6, 0x70, 0x23, 0x5f, 0x79, 0xc0);
//
// // {7d1d3a04-debb-4115-95cf-2f29da2920da}
// DEFINE_KNOWN_FOLDER(FOLDERID_SavedSearches, 0x7d1d3a04, 0xdebb, 0x4115, 0x95, 0xcf, 0x2f, 0x29, 0xda, 0x29, 0x20, 0xda);
//
// // {52a4f021-7b75-48a9-9f6b-4b87a210bc8f}
// DEFINE_KNOWN_FOLDER(FOLDERID_QuickLaunch, 0x52a4f021, 0x7b75, 0x48a9, 0x9f, 0x6b, 0x4b, 0x87, 0xa2, 0x10, 0xbc, 0x8f);
//
// // {56784854-C6CB-462b-8169-88E350ACB882}
// DEFINE_KNOWN_FOLDER(FOLDERID_Contacts, 0x56784854, 0xc6cb, 0x462b, 0x81, 0x69, 0x88, 0xe3, 0x50, 0xac, 0xb8, 0x82);
//
// // {A75D362E-50FC-4fb7-AC2C-A8BEAA314493}
// DEFINE_KNOWN_FOLDER(FOLDERID_SidebarParts, 0xa75d362e, 0x50fc, 0x4fb7, 0xac, 0x2c, 0xa8, 0xbe, 0xaa, 0x31, 0x44, 0x93);
//
// // {7B396E54-9EC5-4300-BE0A-2482EBAE1A26}
// DEFINE_KNOWN_FOLDER(FOLDERID_SidebarDefaultParts, 0x7b396e54, 0x9ec5, 0x4300, 0xbe, 0xa, 0x24, 0x82, 0xeb, 0xae, 0x1a, 0x26);
//
// // {DEBF2536-E1A8-4c59-B6A2-414586476AEA}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicGameTasks, 0xdebf2536, 0xe1a8, 0x4c59, 0xb6, 0xa2, 0x41, 0x45, 0x86, 0x47, 0x6a, 0xea);
//
// // {054FAE61-4DD8-4787-80B6-090220C4B700}
// DEFINE_KNOWN_FOLDER(FOLDERID_GameTasks, 0x54fae61, 0x4dd8, 0x4787, 0x80, 0xb6, 0x9, 0x2, 0x20, 0xc4, 0xb7, 0x0);
//
// // {4C5C32FF-BB9D-43b0-B5B4-2D72E54EAAA4}
// DEFINE_KNOWN_FOLDER(FOLDERID_SavedGames, 0x4c5c32ff, 0xbb9d, 0x43b0, 0xb5, 0xb4, 0x2d, 0x72, 0xe5, 0x4e, 0xaa, 0xa4);
//
// // {CAC52C1A-B53D-4edc-92D7-6B2E8AC19434} - deprecated
// DEFINE_KNOWN_FOLDER(FOLDERID_Games, 0xcac52c1a, 0xb53d, 0x4edc, 0x92, 0xd7, 0x6b, 0x2e, 0x8a, 0xc1, 0x94, 0x34);
//
// // {98ec0e18-2098-4d44-8644-66979315a281}
// DEFINE_KNOWN_FOLDER(FOLDERID_SEARCH_MAPI, 0x98ec0e18, 0x2098, 0x4d44, 0x86, 0x44, 0x66, 0x97, 0x93, 0x15, 0xa2, 0x81);
//
// // {ee32e446-31ca-4aba-814f-a5ebd2fd6d5e}
// DEFINE_KNOWN_FOLDER(FOLDERID_SEARCH_CSC, 0xee32e446, 0x31ca, 0x4aba, 0x81, 0x4f, 0xa5, 0xeb, 0xd2, 0xfd, 0x6d, 0x5e);
//
// // {bfb9d5e0-c6a9-404c-b2b2-ae6db6af4968}
// DEFINE_KNOWN_FOLDER(FOLDERID_Links, 0xbfb9d5e0, 0xc6a9, 0x404c, 0xb2, 0xb2, 0xae, 0x6d, 0xb6, 0xaf, 0x49, 0x68);
//
// // {f3ce0f7c-4901-4acc-8648-d5d44b04ef8f}
// DEFINE_KNOWN_FOLDER(FOLDERID_UsersFiles, 0xf3ce0f7c, 0x4901, 0x4acc, 0x86, 0x48, 0xd5, 0xd4, 0x4b, 0x04, 0xef, 0x8f);
//
// // {A302545D-DEFF-464b-ABE8-61C8648D939B}
// DEFINE_KNOWN_FOLDER(FOLDERID_UsersLibraries, 0xa302545d, 0xdeff, 0x464b, 0xab, 0xe8, 0x61, 0xc8, 0x64, 0x8d, 0x93, 0x9b);
//
// // {190337d1-b8ca-4121-a639-6d472d16972a}
// DEFINE_KNOWN_FOLDER(FOLDERID_SearchHome, 0x190337d1, 0xb8ca, 0x4121, 0xa6, 0x39, 0x6d, 0x47, 0x2d, 0x16, 0x97, 0x2a);
//
// // {2C36C0AA-5812-4b87-BFD0-4CD0DFB19B39}
// DEFINE_KNOWN_FOLDER(FOLDERID_OriginalImages, 0x2C36C0AA, 0x5812, 0x4b87, 0xbf, 0xd0, 0x4c, 0xd0, 0xdf, 0xb1, 0x9b, 0x39);
//
// // {7b0db17d-9cd2-4a93-9733-46cc89022e7c}
// DEFINE_KNOWN_FOLDER(FOLDERID_DocumentsLibrary, 0x7b0db17d, 0x9cd2, 0x4a93, 0x97, 0x33, 0x46, 0xcc, 0x89, 0x02, 0x2e, 0x7c);
//
// // {2112AB0A-C86A-4ffe-A368-0DE96E47012E}
// DEFINE_KNOWN_FOLDER(FOLDERID_MusicLibrary, 0x2112ab0a, 0xc86a, 0x4ffe, 0xa3, 0x68, 0xd, 0xe9, 0x6e, 0x47, 0x1, 0x2e);
//
// // {A990AE9F-A03B-4e80-94BC-9912D7504104}
// DEFINE_KNOWN_FOLDER(FOLDERID_PicturesLibrary, 0xa990ae9f, 0xa03b, 0x4e80, 0x94, 0xbc, 0x99, 0x12, 0xd7, 0x50, 0x41, 0x4);
//
// // {491E922F-5643-4af4-A7EB-4E7A138D8174}
// DEFINE_KNOWN_FOLDER(FOLDERID_VideosLibrary, 0x491e922f, 0x5643, 0x4af4, 0xa7, 0xeb, 0x4e, 0x7a, 0x13, 0x8d, 0x81, 0x74);
//
// // {1A6FDBA2-F42D-4358-A798-B74D745926C5}
// DEFINE_KNOWN_FOLDER(FOLDERID_RecordedTVLibrary, 0x1a6fdba2, 0xf42d, 0x4358, 0xa7, 0x98, 0xb7, 0x4d, 0x74, 0x59, 0x26, 0xc5);
//
// // {52528A6B-B9E3-4add-B60D-588C2DBA842D}
// DEFINE_KNOWN_FOLDER(FOLDERID_HomeGroup, 0x52528a6b, 0xb9e3, 0x4add, 0xb6, 0xd, 0x58, 0x8c, 0x2d, 0xba, 0x84, 0x2d);
//
// // {9B74B6A3-0DFD-4f11-9E78-5F7800F2E772}
// DEFINE_KNOWN_FOLDER(FOLDERID_HomeGroupCurrentUser, 0x9b74b6a3, 0xdfd, 0x4f11, 0x9e, 0x78, 0x5f, 0x78, 0x0, 0xf2, 0xe7, 0x72);
//
// // {5CE4A5E9-E4EB-479D-B89F-130C02886155}
// DEFINE_KNOWN_FOLDER(FOLDERID_DeviceMetadataStore, 0x5ce4a5e9, 0xe4eb, 0x479d, 0xb8, 0x9f, 0x13, 0x0c, 0x02, 0x88, 0x61, 0x55);
//
// // {1B3EA5DC-B587-4786-B4EF-BD1DC332AEAE}
// DEFINE_KNOWN_FOLDER(FOLDERID_Libraries, 0x1b3ea5dc, 0xb587, 0x4786, 0xb4, 0xef, 0xbd, 0x1d, 0xc3, 0x32, 0xae, 0xae);
//
// // {48daf80b-e6cf-4f4e-b800-0e69d84ee384}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicLibraries, 0x48daf80b, 0xe6cf, 0x4f4e, 0xb8, 0x00, 0x0e, 0x69, 0xd8, 0x4e, 0xe3, 0x84);
//
// // {9e3995ab-1f9c-4f13-b827-48b24b6c7174}
// DEFINE_KNOWN_FOLDER(FOLDERID_UserPinned, 0x9e3995ab, 0x1f9c, 0x4f13, 0xb8, 0x27, 0x48, 0xb2, 0x4b, 0x6c, 0x71, 0x74);
//
// // {bcb5256f-79f6-4cee-b725-dc34e402fd46}
// DEFINE_KNOWN_FOLDER(FOLDERID_ImplicitAppShortcuts, 0xbcb5256f, 0x79f6, 0x4cee, 0xb7, 0x25, 0xdc, 0x34, 0xe4, 0x2, 0xfd, 0x46);
//
// // {008ca0b1-55b4-4c56-b8a8-4de4b299d3be}
// DEFINE_KNOWN_FOLDER(FOLDERID_AccountPictures, 0x008ca0b1, 0x55b4, 0x4c56, 0xb8, 0xa8, 0x4d, 0xe4, 0xb2, 0x99, 0xd3, 0xbe);
//
// // {0482af6c-08f1-4c34-8c90-e17ec98b1e17}
// DEFINE_KNOWN_FOLDER(FOLDERID_PublicUserTiles, 0x0482af6c, 0x08f1, 0x4c34, 0x8c, 0x90, 0xe1, 0x7e, 0xc9, 0x8b, 0x1e, 0x17);
//
// // {1e87508d-89c2-42f0-8a7e-645a0f50ca58}
// DEFINE_KNOWN_FOLDER(FOLDERID_AppsFolder, 0x1e87508d, 0x89c2, 0x42f0, 0x8a, 0x7e, 0x64, 0x5a, 0x0f, 0x50, 0xca, 0x58);
//
// // {F26305EF-6948-40B9-B255-81453D09C785}
// DEFINE_KNOWN_FOLDER(FOLDERID_StartMenuAllPrograms, 0xf26305ef, 0x6948, 0x40b9, 0xb2, 0x55, 0x81, 0x45, 0x3d, 0x9, 0xc7, 0x85);
//
// // {A440879F-87A0-4F7D-B700-0207B966194A}
// DEFINE_KNOWN_FOLDER(FOLDERID_CommonStartMenuPlaces, 0xa440879f, 0x87a0, 0x4f7d, 0xb7, 0x0, 0x2, 0x7, 0xb9, 0x66, 0x19, 0x4a);
//
// // {A3918781-E5F2-4890-B3D9-A7E54332328C}
// DEFINE_KNOWN_FOLDER(FOLDERID_ApplicationShortcuts, 0xa3918781, 0xe5f2, 0x4890, 0xb3, 0xd9, 0xa7, 0xe5, 0x43, 0x32, 0x32, 0x8c);
//
// // {00BCFC5A-ED94-4e48-96A1-3F6217F21990}
// DEFINE_KNOWN_FOLDER(FOLDERID_RoamingTiles, 0xbcfc5a, 0xed94, 0x4e48, 0x96, 0xa1, 0x3f, 0x62, 0x17, 0xf2, 0x19, 0x90);
//
// // {AAA8D5A5-F1D6-4259-BAA8-78E7EF60835E}
// DEFINE_KNOWN_FOLDER(FOLDERID_RoamedTileImages, 0xaaa8d5a5, 0xf1d6, 0x4259, 0xba, 0xa8, 0x78, 0xe7, 0xef, 0x60, 0x83, 0x5e);
//
// // {b7bede81-df94-4682-a7d8-57a52620b86f}
// DEFINE_KNOWN_FOLDER(FOLDERID_Screenshots, 0xb7bede81, 0xdf94, 0x4682, 0xa7, 0xd8, 0x57, 0xa5, 0x26, 0x20, 0xb8, 0x6f);
//
// // {AB5FB87B-7CE2-4F83-915D-550846C9537B}
// DEFINE_KNOWN_FOLDER(FOLDERID_CameraRoll, 0xab5fb87b, 0x7ce2, 0x4f83, 0x91, 0x5d, 0x55, 0x8, 0x46, 0xc9, 0x53, 0x7b);
//
// // {A52BBA46-E9E1-435f-B3D9-28DAA648C0F6} - deprecated
// // Same GUID as FOLDERID_OneDrive
// DEFINE_KNOWN_FOLDER(FOLDERID_SkyDrive, 0xa52bba46, 0xe9e1, 0x435f, 0xb3, 0xd9, 0x28, 0xda, 0xa6, 0x48, 0xc0, 0xf6);
//
// // {A52BBA46-E9E1-435f-B3D9-28DAA648C0F6}
// // Same GUID as FOLDERID_SkyDrive
// DEFINE_KNOWN_FOLDER(FOLDERID_OneDrive, 0xa52bba46, 0xe9e1, 0x435f, 0xb3, 0xd9, 0x28, 0xda, 0xa6, 0x48, 0xc0, 0xf6);
//
// // {24D89E24-2F19-4534-9DDE-6A6671FBB8FE}
// DEFINE_KNOWN_FOLDER(FOLDERID_SkyDriveDocuments, 0x24d89e24, 0x2f19, 0x4534, 0x9d, 0xde, 0x6a, 0x66, 0x71, 0xfb, 0xb8, 0xfe);
//
// // {339719B5-8C47-4894-94C2-D8F77ADD44A6}
// DEFINE_KNOWN_FOLDER(FOLDERID_SkyDrivePictures, 0x339719b5, 0x8c47, 0x4894, 0x94, 0xc2, 0xd8, 0xf7, 0x7a, 0xdd, 0x44, 0xa6);
//
// // {C3F2459E-80D6-45DC-BFEF-1F769F2BE730}
// DEFINE_KNOWN_FOLDER(FOLDERID_SkyDriveMusic, 0xc3f2459e, 0x80d6, 0x45dc, 0xbf, 0xef, 0x1f, 0x76, 0x9f, 0x2b, 0xe7, 0x30);
//
// // {767E6811-49CB-4273-87C2-20F355E1085B}
// DEFINE_KNOWN_FOLDER(FOLDERID_SkyDriveCameraRoll, 0x767e6811, 0x49cb, 0x4273, 0x87, 0xc2, 0x20, 0xf3, 0x55, 0xe1, 0x08, 0x5b);
//
// // {0D4C3DB6-03A3-462F-A0E6-08924C41B5D4}
// DEFINE_KNOWN_FOLDER(FOLDERID_SearchHistory, 0x0d4c3db6, 0x03a3, 0x462f, 0xa0, 0xe6, 0x08, 0x92, 0x4c, 0x41, 0xb5, 0xd4);
//
// // {7E636BFE-DFA9-4D5E-B456-D7B39851D8A9}
// DEFINE_KNOWN_FOLDER(FOLDERID_SearchTemplates, 0x7e636bfe, 0xdfa9, 0x4d5e, 0xb4, 0x56, 0xd7, 0xb3, 0x98, 0x51, 0xd8, 0xa9);
//
// // {2B20DF75-1EDA-4039-8097-38798227D5B7}
// DEFINE_KNOWN_FOLDER(FOLDERID_CameraRollLibrary, 0x2b20df75, 0x1eda, 0x4039, 0x80, 0x97, 0x38, 0x79, 0x82, 0x27, 0xd5, 0xb7);
//
// // {3B193882-D3AD-4eab-965A-69829D1FB59F}
// DEFINE_KNOWN_FOLDER(FOLDERID_SavedPictures, 0x3b193882, 0xd3ad, 0x4eab, 0x96, 0x5a, 0x69, 0x82, 0x9d, 0x1f, 0xb5, 0x9f);
//
// // {E25B5812-BE88-4bd9-94B0-29233477B6C3}
// DEFINE_KNOWN_FOLDER(FOLDERID_SavedPicturesLibrary, 0xe25b5812, 0xbe88, 0x4bd9, 0x94, 0xb0, 0x29, 0x23, 0x34, 0x77, 0xb6, 0xc3);
//
// // {12D4C69E-24AD-4923-BE19-31321C43A767}
// DEFINE_KNOWN_FOLDER(FOLDERID_RetailDemo, 0x12d4c69e, 0x24ad, 0x4923, 0xbe, 0x19, 0x31, 0x32, 0x1c, 0x43, 0xa7, 0x67);
//
// // {1C2AC1DC-4358-4B6C-9733-AF21156576F0}
// DEFINE_KNOWN_FOLDER(FOLDERID_Device, 0x1C2AC1DC, 0x4358, 0x4B6C, 0x97, 0x33, 0xAF, 0x21, 0x15, 0x65, 0x76, 0xF0);
//
// // The file system directory that contains development files that have been copied to this device by a development tool. A
// // typical path is C:\Users\username\AppData\Local\DevelopmentFiles. This directory is used by development tools that need
// // to copy files to a device. This may include copying application binaries for temporary registration and execution in order
// // to allow a developer to test their application without having to go through the full app packaging process. It could also
// // include development time only components such as a remote debugger. Recommended practice is to create sub-directories rather
// // than copying files to the DevelopmentFiles directory. Development tools should be careful to use a naming convention that
// // avoids conflicts. For example application binaries should be copied to a directory with a unique name such as the app package
// // full name. This information is per user and will not roam.
// // {DBE8E08E-3053-4BBC-B183-2A7B2B191E59}
// DEFINE_KNOWN_FOLDER(FOLDERID_DevelopmentFiles, 0xdbe8e08e, 0x3053, 0x4bbc, 0xb1, 0x83, 0x2a, 0x7b, 0x2b, 0x19, 0x1e, 0x59);
//
// // {31C0DD25-9439-4F12-BF41-7FF4EDA38722}
// DEFINE_KNOWN_FOLDER(FOLDERID_Objects3D, 0x31c0dd25, 0x9439, 0x4f12, 0xbf, 0x41, 0x7f, 0xf4, 0xed, 0xa3, 0x87, 0x22);
//
// // {EDC0FE71-98D8-4F4A-B920-C8DC133CB165}
// DEFINE_KNOWN_FOLDER(FOLDERID_AppCaptures, 0xedc0fe71, 0x98d8, 0x4f4a, 0xb9, 0x20, 0xc8, 0xdc, 0x13, 0x3c, 0xb1, 0x65);
//
// // {f42ee2d3-909f-4907-8871-4c22fc0bf756}
// DEFINE_KNOWN_FOLDER(FOLDERID_LocalDocuments, 0xf42ee2d3, 0x909f, 0x4907, 0x88, 0x71, 0x4c, 0x22, 0xfc, 0x0b, 0xf7, 0x56);
//
// // {0ddd015d-b06c-45d5-8c4c-f59713854639 }
// DEFINE_KNOWN_FOLDER(FOLDERID_LocalPictures, 0x0ddd015d, 0xb06c, 0x45d5, 0x8c, 0x4c, 0xf5, 0x97, 0x13, 0x85, 0x46, 0x39);
//
// // {35286a68-3c57-41a1-bbb1-0eae73d76c95}
// DEFINE_KNOWN_FOLDER(FOLDERID_LocalVideos, 0x35286a68, 0x3c57, 0x41a1, 0xbb, 0xb1, 0x0e, 0xae, 0x73, 0xd7, 0x6c, 0x95);
//
// // {a0c69a99-21c8-4671-8703-7934162fcf1d}
// DEFINE_KNOWN_FOLDER(FOLDERID_LocalMusic, 0xa0c69a99, 0x21c8, 0x4671, 0x87, 0x03, 0x79, 0x34, 0x16, 0x2f, 0xcf, 0x1d);
//
// // {7d83ee9b-2244-4e70-b1f5-5393042af1e4}
// DEFINE_KNOWN_FOLDER(FOLDERID_LocalDownloads, 0x7d83ee9b, 0x2244, 0x4e70, 0xb1, 0xf5, 0x53, 0x93, 0x04, 0x2a, 0xf1, 0xe4);
//
// // {2f8b40c2-83ed-48ee-b383-a1f157ec6f9a}
// DEFINE_KNOWN_FOLDER(FOLDERID_RecordedCalls, 0x2f8b40c2, 0x83ed, 0x48ee, 0xb3, 0x83, 0xa1, 0xf1, 0x57, 0xec, 0x6f, 0x9a);
//
// // {7ad67899-66af-43ba-9156-6aad42e6c596}
// DEFINE_KNOWN_FOLDER(FOLDERID_AllAppMods, 0x7ad67899, 0x66af, 0x43ba, 0x91, 0x56, 0x6a, 0xad, 0x42, 0xe6, 0xc5, 0x96);
//
// // {3db40b20-2a30-4dbe-917e-771dd21dd099}
// DEFINE_KNOWN_FOLDER(FOLDERID_CurrentAppMods, 0x3db40b20, 0x2a30, 0x4dbe, 0x91, 0x7e, 0x77, 0x1d, 0xd2, 0x1d, 0xd0, 0x99);
//
// // {B2C5E279-7ADD-439F-B28C-C41FE1BBF672}
// DEFINE_KNOWN_FOLDER(FOLDERID_AppDataDesktop, 0xb2c5e279, 0x7add, 0x439f, 0xb2, 0x8c, 0xc4, 0x1f, 0xe1, 0xbb, 0xf6, 0x72);
//
// // {7BE16610-1F7F-44AC-BFF0-83E15F2FFCA1}
// DEFINE_KNOWN_FOLDER(FOLDERID_AppDataDocuments, 0x7be16610, 0x1f7f, 0x44ac, 0xbf, 0xf0, 0x83, 0xe1, 0x5f, 0x2f, 0xfc, 0xa1);
//
// // {7CFBEFBC-DE1F-45AA-B843-A542AC536CC9}
// DEFINE_KNOWN_FOLDER(FOLDERID_AppDataFavorites, 0x7cfbefbc, 0xde1f, 0x45aa, 0xb8, 0x43, 0xa5, 0x42, 0xac, 0x53, 0x6c, 0xc9);
//
// // {559D40A3-A036-40FA-AF61-84CB430A4D34}
// DEFINE_KNOWN_FOLDER(FOLDERID_AppDataProgramData, 0x559d40a3, 0xa036, 0x40fa, 0xaf, 0x61, 0x84, 0xcb, 0x43, 0xa, 0x4d, 0x34);

struct ExtraData_KnownFolderLocation
{
    ExtraDataBase base;
    MyGUID identifier;              // Contains a GUID.
    uint32 firstChildSegmentOffset; // The first child segment offset refers to the location of the (shell) item identifier of the first
                                    // child segment of the (shell) item identifiers list specified by the known folder identifier. The
                                    // offset contains the number of bytes relative from the start of the (shell) item identifiers list.
};
} // namespace GView::Type::LNK
