#include <AppCUI/include/AppCUI.hpp>
#include <../GViewCore/include/GView.hpp>

#include <set>

using namespace AppCUI::Controls;
using namespace AppCUI::Graphics;
using namespace AppCUI::Utils;

namespace GView
{
namespace Utils
{
}
namespace Type
{
    namespace DefaultTypePlugin
    {
        bool Validate(const GView::Utils::Buffer& buf, const std::string_view& extension);
        Utils::Instance CreateInstance();
        void DeleteInstance(Utils::Instance instance);
        bool PopulateWindow(Reference<GView::View::WindowInterface> win);
    }                                               // namespace DefaultTypePlugin
    constexpr unsigned int MAX_PATTERN_VALUES = 21; // muwt be less than 255
    class SimplePattern
    {
        unsigned char CharactersToMatch[MAX_PATTERN_VALUES];
        unsigned char Count;
        unsigned short Offset;

      public:
        SimplePattern();
        bool Init(std::string_view text, unsigned int ofs);
        bool Match(GView::Utils::Buffer buf) const;
        inline bool Empty() const
        {
            return Count == 0;
        }
    };
    constexpr unsigned int PLUGIN_NAME_MAX_SIZE = 31; // must be less than 255 !!!
    class Plugin
    {
        SimplePattern Pattern;
        std::vector<SimplePattern> Patterns;
        unsigned long long Extension;
        std::set<unsigned long long> Extensions;
        unsigned char Name[PLUGIN_NAME_MAX_SIZE];
        unsigned char NameLength;
        unsigned short Priority;
        bool Loaded, Invalid;

        bool (*fnValidate)(const GView::Utils::Buffer& buf, const std::string_view& extension);
        Utils::Instance (*fnCreateInstance)();
        void (*fnDeleteInstance)(Utils::Instance instance);
        bool (*fnPopulateWindow)(Reference<GView::View::WindowInterface> win);

        bool LoadPlugin();

      public:
        Plugin();
        bool Init(AppCUI::Utils::IniSection section);
        void Init();
        bool Validate(GView::Utils::Buffer buf, std::string_view extension);
        bool PopulateWindow(Reference<GView::View::WindowInterface> win) const;
        Utils::Instance CreateInstance() const;
        void DeleteInstance(Utils::Instance instance) const;
        inline bool operator<(const Plugin& plugin) const
        {
            return Priority > plugin.Priority;
        }
    };
} // namespace Type
namespace View
{
    class BufferView : public View::ViewControl, public View::BufferViewInterface
    {
        enum class CharacterFormatMode : unsigned char
        {
            Hex,
            Octal,
            SignedDecimal,
            UnsignedDecimal,
        };
        struct OffsetTranslationMethod
        {
            FixSizeString<17> name;
            MethodID methodID;
        };
        struct DrawLineInfo
        {
            unsigned long long offset;
            unsigned int offsetAndNameSize;
            unsigned int numbersSize;
            unsigned int textSize;
            const unsigned char* start;
            const unsigned char* end;
            Character* chNameAndSize;
            Character* chNumbers;
            Character* chText;
            bool recomputeOffsets;
            DrawLineInfo() : recomputeOffsets(true)
            {
            }
        };
        struct
        {
            CharacterFormatMode charFormatMode;
            unsigned int nrCols;
            unsigned int lineOffsetSize;
            unsigned int lineNameSize;
            unsigned int charactersPerLine;
            unsigned int visibleRows;
        } Layout;
        struct
        {
            unsigned long long startView, currentPos;
        } Cursor;

        Reference<GView::Object> obj;
        Utils::Selection selection;
        CharacterBuffer chars;
        const char16_t* CodePage;
        GView::Utils::ZonesList zList;
        unsigned long long bookmarks[10];
        OffsetTranslationMethod translationMethods[16];
        unsigned int translationMethodsCount;
        FixSizeString<29> name;

        void PrepareDrawLineInfo(DrawLineInfo& dli);
        void WriteLineOffset(DrawLineInfo& dli);
        void WriteLineNumbersToChars(DrawLineInfo& dli);
        void WriteLineTextToChars(DrawLineInfo& dli);
        void UpdateViewSizes();
        void MoveTo(unsigned long long offset, bool select);
        void MoveScrollTo(unsigned long long offset);
        void MoveToSelection(unsigned int selIndex);
        void SkipCurentCaracter(bool selected);
        void MoveTillEndBlock(bool selected);
        void MoveTillNextBlock(bool select, int dir);

      public:
        BufferView(const std::string_view& name, Reference<GView::Object> obj);

        virtual void Paint(Renderer& renderer) override;
        virtual void OnAfterResize(int newWidth, int newHeight) override;
        virtual bool OnKeyEvent(AppCUI::Input::Key keyCode, char16_t characterCode) override;

        virtual bool GoTo(unsigned long long offset) override;
        virtual bool Select(unsigned long long offset, unsigned long long size) override;
        virtual std::string_view GetName() override;

        virtual void AddZone(unsigned long long start, unsigned long long size, ColorPair col, std::string_view name) override;
        virtual void AddBookmark(unsigned char bookmarkID, unsigned long long fileOffset) override;
        virtual void AddOffsetTranslationMethod(std::string_view name, MethodID methodID) override;
    };

} // namespace View
namespace App
{
    namespace MenuCommands
    {
        constexpr int ARRANGE_VERTICALLY       = 100000;
        constexpr int ARRANGE_HORIZONTALLY     = 100001;
        constexpr int ARRANGE_CASCADE          = 100002;
        constexpr int ARRANGE_GRID             = 100003;
        constexpr int CLOSE                    = 100004;
        constexpr int CLOSE_ALL                = 100005;
        constexpr int CLOSE_ALL_EXCEPT_CURRENT = 100006;
        constexpr int SHOW_WINDOW_MANAGER      = 100007;

        constexpr int CHECK_FOR_UPDATES = 110000;
        constexpr int ABOUT             = 110001;

    }; // namespace MenuCommands
    class Instance
    {
        AppCUI::Controls::Menu* mnuWindow;
        AppCUI::Controls::Menu* mnuHelp;
        std::vector<GView::Type::Plugin> typePlugins;
        GView::Type::Plugin defaultPlugin;
        unsigned int defaultCacheSize;

        bool BuildMainMenus();
        bool LoadSettings();
        bool Add(std::unique_ptr<AppCUI::OS::IFile> file, const AppCUI::Utils::ConstString& name, std::string_view ext);

      public:
        Instance();
        bool Init();
        bool AddFileWindow(const std::filesystem::path& path);
        void Run();
    };
    class FileWindow : public Window, public GView::View::WindowInterface
    {
        Reference<Splitter> vertical, horizontal;
        Reference<Tab> view, verticalPanels, horizontalPanels;
        GView::Object obj;

      public:
        FileWindow(const AppCUI::Utils::ConstString& name);

        Reference<Object> GetObject() override;
        bool AddPanel(Pointer<TabPage> page, bool vertical) override;
        Reference<View::BufferViewInterface> AddBufferView(const std::string_view& name) override;
    };
} // namespace App

} // namespace GView
