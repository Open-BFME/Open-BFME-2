// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME1 ba7ddda7 ControlBar_setControlCommand_GameWindow.cpp is the guide.
// Named WB 0x00C2E790 and full native 0x0031B641..0x0031B892 establish
// the target layout, image/text route, unconditional production flag and
// reference-counted hotkey action. Address-derived helpers retain uncertainty.
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"
class Image;
class WinInstanceData;
class GameWindow;
typedef void (*GameWinTooltipFunc)(GameWindow *,WinInstanceData *,unsigned int);
class GameWindow
{
public:
    virtual void unknown00(); virtual void unknown01(); virtual void unknown02();
    virtual void unknown03(); virtual void unknown04(); virtual void unknown05();
    virtual void unknown06(); virtual void unknown07();
    virtual bool isPushButton() const;
    int winSetTooltipFunc(GameWinTooltipFunc);
};
class CommandButton
{
public:
    const Image *rva0035B19E() const;
    const AsciiString &rva0035B1E9() const;
};
struct ShortcutScienceVectorView
{
    void *begin;
    void *end;
    void *limit;
    bool empty() const { return begin==end; }
};
struct ShortcutCommandButtonSetView
{
    char unknown00[0x10];
    AsciiString name;
    char unknown14[8];
    unsigned int options;
    char unknown20[0x84];
    ShortcutScienceVectorView sciences;
    char unknownB0[0x14];
    GameWindow *window;
    char unknownC8[0x3C];
    bool showProductionCount; bool productionCount() const { return showProductionCount; }
};
class Rva0035AFD0 { public: int rva0035AFD0(); };
class Rva0031417CDwordSlot { public: void set(int); };
void GadgetButtonEnableCheckLike(GameWindow *,bool,bool);
void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *,const Image *);
void GadgetButtonSetText(GameWindow *,UnicodeString);
void Rva00328518(GameWindow *,int);
void Rva00327D86Update(GameWindow *,bool);
void GadgetButtonSetAltSound(GameWindow *,AsciiString);
void commandButtonTooltip(GameWindow *,WinInstanceData *,unsigned int);
int Rva00328700(GameWindow *);
class Rva0053DAD0
{
public:
    Rva0053DAD0(int);
private:
    char unknown00[12];
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct ShortcutActionCountView { char unknown00[4]; int references; };
struct TreeHintRef00217D4C
{
    void *m_node;
    TreeHintRef00217D4C(Rva0053DAD0 *node) : m_node(node)
    {
        if (node) ++((ShortcutActionCountView *)node)->references;
    }
    ~TreeHintRef00217D4C()
    {
        if (m_node) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_node);
    }
};
// Existing 0x00359302 bank's eight-byte return view; full native callee
// writes node0 and alternate4, uses a hidden result argument and ret 0x10.
struct Rva00359302Result
{
    Rva00359302Result(void *node,bool alternate) : m_node(node),m_alt(alternate) {}
    void *m_node;
    bool m_alt;
};
class HotKeyManager
{
public:
    AsciiString rva00358CCD(const AsciiString &);
    Rva00359302Result addHotKey(const TreeHintRef00217D4C &,const AsciiString &,bool);
};
class Rva00E01E28Owner;
extern Rva00E01E28Owner *g_00E01E28;
class ControlBar
{
public:
    void rva0031B641(GameWindow *,const CommandButton *);
    void rva0031ABD9(GameWindow *,int);
};
void ControlBar::rva0031B641(GameWindow *button,const CommandButton *commandButton)
{
    if (!button->isPushButton()) return;
    ShortcutCommandButtonSetView *command=(ShortcutCommandButtonSetView *)commandButton;
    if (command && (command->options & 0x00000400))
        GadgetButtonEnableCheckLike(button,true,false);
    else
        GadgetButtonEnableCheckLike(button,false,false);
    if (commandButton && commandButton->rva0035B19E())
    {
        GadgetButtonSetText(button,UnicodeString::TheEmptyString);
        GadgetButtonSetEnabledImage_Rva002C0433(button,commandButton->rva0035B19E());
    }
    else
    {
        GadgetButtonSetEnabledImage_Rva002C0433(button,0);
        if (command && strncmp(command->name.str(),"NonCommand_",11)!=0)
        {
            UnicodeString text;
            text.translate(command->name);
            GadgetButtonSetText(button,text);
        }
        else
            GadgetButtonSetText(button,UnicodeString::TheEmptyString);
    }
    Rva00328518(button,(int)commandButton);
    if (!commandButton) return;
    button->winSetTooltipFunc(commandButtonTooltip);
    if (((const StringBase<char> *)&commandButton->rva0035B1E9())->isEmpty()
        && command->sciences.empty())
        GadgetButtonSetText(button,UnicodeString((const unsigned short *)L""));
    command->window=button;
    rva0031ABD9(button,((Rva0035AFD0 *)commandButton)->rva0035AFD0());
    Rva00327D86Update(button,command->productionCount());
    if (g_00E01E28)
    {
        AsciiString hotKey=((HotKeyManager *)g_00E01E28)->rva00358CCD(commandButton->rva0035B1E9());
        if (!hotKey.isEmpty())
            ((HotKeyManager *)g_00E01E28)->addHotKey(
                TreeHintRef00217D4C(new Rva0053DAD0((int)button)),hotKey,false);
    }
    GadgetButtonSetAltSound(button,AsciiString("GUIControlButtonClick"));
    ((Rva0031417CDwordSlot *)button)->set((int)Rva00328700);
}
