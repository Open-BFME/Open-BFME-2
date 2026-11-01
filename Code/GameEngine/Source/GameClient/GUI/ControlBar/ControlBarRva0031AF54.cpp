// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/inputs/vendor/stlport -Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc -Ireference/open-bfme-1/inputs/reference/shims/controlbarvtables -Ireference/open-bfme-1/inputs/reference/shims/controlbarlayout -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/ControlBar /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/iniexception /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Include
// stlport
typedef bool Bool;
#include "subsystem_interface.h"
// partial score=0.92 date=2026-09-30
// cl: /DNDEBUG /MD
// ?rva0031AF54@Rva0031AF54@@QAEX_N@Z @0x0031AF54 120B: search 10-window list at +0xA8 count +0xD0 for first with userData then animate via manager +0x14 and window +0xD8. Evidence: packet disasm with rowed winGetUserData 0x005C4ACD and registerGameWindow 0x0053B843 reverseAnimateWindow 0x0053B417 and virtual slot 9 at +0x24.
class GadgetCreateView;
class Image;
class GameWindow;
class WinInstanceData;
typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, unsigned int);
class GameWindow
{
public:
	int winGetPosition(int *x, int *y);
	int winGetScreenPosition(int *x, int *y);
	void snapshotCreateView(GadgetCreateView *view, bool keepInstance);
	unsigned int winGetStatus();
	void winSetUserData(void *userData);
	unsigned int winSetStatus(unsigned int status);
	unsigned int winClearStatus(unsigned int status);
	int winSetSize(int width, int height);
	int winSetPosition(int x, int y);
	int winSetTooltipFunc(GameWinTooltipFunc tooltip);
	int winEnable(bool enable);
	int winHide(bool hide);
	int winSetEnabledImage(int index, const Image *image);
	void *winGetUserData();
	bool winIsHidden();
	virtual void unknown00();
	virtual void unknown01();
	virtual void unknown02();
	virtual void unknown03();
	virtual void unknown04();
	virtual void unknown05();
	virtual void unknown06();
	virtual void unknown07();
	virtual bool isPushButton() const;
};

enum AnimTypes
{
	WIN_ANIMATION_NONE = 0,
	WIN_ANIMATION_SLIDE_RIGHT,
	WIN_ANIMATION_SLIDE_RIGHT_FAST,
	WIN_ANIMATION_SLIDE_LEFT,
	WIN_ANIMATION_SLIDE_TOP,
	WIN_ANIMATION_SLIDE_BOTTOM,
	WIN_ANIMATION_SPIRAL,
	WIN_ANIMATION_SLIDE_BOTTOM_TIMED,
	WIN_ANIMATION_SLIDE_TOP_FAST,
	WIN_ANIMATION_COUNT
};

class AnimateWindowManager : public SubsystemInterface
{
public:
    AnimateWindowManager();
    virtual void init();
    virtual void reset();
    virtual void update();
    void registerGameWindow(GameWindow *win, AnimTypes animType, bool needsToFinish, unsigned int ms, unsigned int delayMs);
    void reverseAnimateWindow();
private:
    char m_opaque[0x38 - 0x0C];
};

class Rva0031AF54
{
public:
	void rva0031AF54(bool flag);
	char m_pad00[0x14];
	AnimateWindowManager *m_manager; // +0x14
	char m_pad18[0x90];
	GameWindow *m_list[10]; // +0xA8
	int m_count; // +0xD0
	char m_padD4[0x4];
	GameWindow *m_window; // +0xD8
};

void Rva0031AF54::rva0031AF54(bool flag)
{
	if (m_window == 0)
		return;
	if (m_manager == 0)
		return;
	if (m_count == 0)
		return;
	int i = 0;
	for (; i < m_count; ++i) {
		if (m_list[i]->winGetUserData() == 0)
			continue;
		if (flag) {
			m_manager->reset();
			m_manager->registerGameWindow(m_window, WIN_ANIMATION_SLIDE_RIGHT, true, 500, 0);
		} else {
			m_manager->reverseAnimateWindow();
		}
		break;
	}
}
