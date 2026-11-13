// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// Clean BFME1 ba7ddda7 ControlBarUpdateVirtual.cpp supplies the workflow.
// Named WB 0x00C2B8A0 and full native 0x0031E25E..0x0031E4BA supply
// the BFME2 offsets, 32-button loops, radar cleanup and actual call routes.
typedef bool Bool;
#include "ascii_string.h"
#include "../../../../Include/Common/NameKeyGenerator.h"
class GadgetCreateView;
class Image;
class GameWindow;
class WinInstanceData;
typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, unsigned int);
#include "../../../../Include/GameClient/Bfme2GameWindow.h"
class Player;
class Drawable;
class CommandButton;
class GameClient;
class GameWindowManager;
class PlayerList;
#include "../../../../Include/Common/RadarWindowOverrideSource.h"
// GameClient.cpp defines this singleton as GameClient*. Access its frame
// slot through the explicitly measured dispatch view below.
extern GameClient *TheGameClient;
extern GameWindowManager *TheWindowManager;
extern PlayerList *ThePlayerList;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
enum NameKeyType { NAMEKEY_INVALID=0 };
class Rva0031AEFF
{
public:
	void rva0031AEFF();
	char m_pad00[0x290];
	unsigned char m_flag; // +0x290
	char m_pad291[0x3];
	int m_counter; // +0x294
	GameWindow *m_window; // +0x298
};
class Rva0031FA8E { public: void rva0031FA8E(); };
class Rva002D36D8 { public: int rva002D36D8(); };
#include <vector>
#include "../../../../Include/Common/Rva000AD6F4.h"
#include "../../../../Include/Common/Rva000B3FD0Nop.h"
class BfmeMemberRV;
#include "../../../../Include/GameClient/BfmeThingRV.h"
void *GadgetButtonGetData(GameWindow *);
void Rva00328700(GameWindow *);
struct ControlBarDrawableView { char unknown00[0xFC]; void *object; };
struct ControlBarFlashButtonView { char unknown00[0xF8]; int flashCount; };
#define SLOT(n) virtual void unknown##n()=0;
class ControlBarManagerUpdateView
{
public:
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
    SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
    virtual void update()=0;
};
class ControlBarAnimateUpdateView : public ControlBarManagerUpdateView
{
public:
    char unknown04[0x10];
    bool needsUpdate;
    bool reverse;
};
class ControlBarWindowManagerView
{
public:
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
    SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
    SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
    SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
    SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
    SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
    SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
    SLOT(56) SLOT(57) SLOT(58) SLOT(59)
    virtual GameWindow *lookupWindow(GameWindow *,NameKeyType)=0;
};
class ControlBarGameClientView
{
public:
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
    SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
    SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
    SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
    virtual unsigned int getFrame()=0;
};
#undef SLOT
enum CommandButtonMappedBorderType
{
    COMMAND_BUTTON_BORDER_NONE,
    COMMAND_BUTTON_BORDER_BUILD,
    COMMAND_BUTTON_BORDER_UPGRADE,
    COMMAND_BUTTON_BORDER_ACTION,
    COMMAND_BUTTON_BORDER_SYSTEM,
    COMMAND_BUTTON_BORDER_BFME5
};
enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_ALLOWED = 4,
	COMMAND_NOT_READY = 5,
	COMMAND_CANT_AFFORD = 6,
	COMMAND_LIMITED = 7,
	COMMAND_DONE = 8
};
class CommandSet;
class INI;
class Object;
struct Coord3D;
class PlayerTemplate;
class WindowVideoManager;
class AnimateWindowManager;
struct ICoord2D;
struct Rva0031DBFCElement;
class ControlBarSchemeManager;
class WindowLayout;
class vector;
struct PlayerAITypeEntry;
#include "../../../../Include/GameClient/ControlBar.h"
void ControlBar::update()
{
    rva0031AA86();
    ((Rva0031AEFF *)this)->rva0031AEFF();
    if (field44) ((Rva0031FA8E *)field44)->rva0031FA8E();
    if (field0C) ((ControlBarManagerUpdateView *)field0C)->update();
    if (field10) ((ControlBarAnimateUpdateView *)field10)->update();
    if (field10 && !((ControlBarAnimateUpdateView *)field10)->needsUpdate && ((ControlBarAnimateUpdateView *)field10)->reverse)
    {
        NameKeyType id;
        {
            AsciiString name("ControlBar.wnd:ControlBarParent");
            id=TheNameKeyGenerator->nameToKey(name);
        }
        GameWindow *window=((ControlBarWindowManagerView *)TheWindowManager)->lookupWindow(0,id);
        if (window && !window->winIsHidden()) window->winHide(true);
    }
    if (field14) ((ControlBarAnimateUpdateView *)field14)->update();
    if (field14 && fieldD8 && !((ControlBarAnimateUpdateView *)field14)->needsUpdate
        && ((ControlBarAnimateUpdateView *)field14)->reverse && !fieldD8->winIsHidden())
        fieldD8->winHide(true);
    if (!field214)
    {
        if (theRadarWindowOverrideSource
            && (unsigned char)((Rva002D36D8 *)theRadarWindowOverrideSource)->rva002D36D8())
            theRadarWindowOverrideSource->rva002D370A();
        field2A4.clear();
    }
    field214=false;
    rva0031B210();
    for (int i=0; i!=32; ++i)
    {
        GameWindow *button=fieldDC[i];
        if (button)
        {
            ControlBarFlashButtonView *command=(ControlBarFlashButtonView *)GadgetButtonGetData(button);
            if (command && command->flashCount>0
                && ((ControlBarGameClientView *)TheGameClient)->getFrame()%10==0)
                --command->flashCount;
        }
    }
    if (field28)
    {
        rva0031D230();
        populateSpecialPowerShortcut((Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV());
    }
    if (field70==7)
    {
        updateContextMultiSelect();
        return;
    }
    if (!field6C || !((ControlBarDrawableView *)field6C)->object)
        if (field70 || field6C) switchToContext(0,0);
    switch (field70)
    {
    case 1: updateContextCommand(); break;
    case 2: updateContextStructureInventory(); break;
    case 3: updateContextContestedStructureInventory(); break;
    case 4: rva0053E6E1(); break;
    case 5: ((Rva000B3FD0Nop *)this)->noop(); break;
    case 6: rva0053E4B1(); break;
    case 10: updateContextOCLTimer(); break;
    }
    for (int i=0; i!=32; ++i)
        if (fieldDC[i]) Rva00328700(fieldDC[i]);
    ((ControlBarManagerUpdateView *)field2A0)->update();
}
