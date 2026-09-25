// Target boundary 0x0037BD81/111 is InGameUI::createReplayControl. The
// initialization path at 0x00248278 calls it at 0x00248307 after loading the
// TheInGameUI singleton. Retail constructs the exact
// "ReplayControl.wnd:ParentReplayControl" key and hides the returned window.
//
// AsciiString uses the BFME1 Code header's StringBase<char> storage view; target
// calls to StringBase construction/destruction at 0x37BA0/0x36410 independently
// support this representation. The target NameKeyGenerator ABI is pinned at
// 0x9FA65 and GameWindow::winHide is matched at 0x313C64.
//
// The GameWindowManager call is modeled as an opaque vtable-slot view because
// retail dispatches through TheWindowManager+vtable[0xF0] with (info=0,key).
// InGameUI's only field read here is the target-witnessed dword at this+0x1C;
// its semantic member name and the rest of the class layout remain unknown.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"

enum NameKeyType {
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator {
public:
	NameKeyType nameToKey(const AsciiString &);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager;
extern GameWindowManager *TheWindowManager;

// Method-only ABI view for the matched GameWindow::winHide target; no
// GameWindow fields or object layout are used in this TU.
class GameWindow {
public:
	int winHide(bool);
};

// Address-derived code-generation view of the target GameWindowManager vtable
// slot at +0xF0; no wider GameWindowManager layout is asserted here.
class Rva0037BD81WindowManagerSlotView {
public:
#define GWM_SLOT(N) virtual void slot##N() = 0;
	GWM_SLOT(00) GWM_SLOT(01) GWM_SLOT(02) GWM_SLOT(03) GWM_SLOT(04)
	GWM_SLOT(05) GWM_SLOT(06) GWM_SLOT(07) GWM_SLOT(08) GWM_SLOT(09)
	GWM_SLOT(10) GWM_SLOT(11) GWM_SLOT(12) GWM_SLOT(13) GWM_SLOT(14)
	GWM_SLOT(15) GWM_SLOT(16) GWM_SLOT(17) GWM_SLOT(18) GWM_SLOT(19)
	GWM_SLOT(20) GWM_SLOT(21) GWM_SLOT(22) GWM_SLOT(23) GWM_SLOT(24)
	GWM_SLOT(25) GWM_SLOT(26) GWM_SLOT(27) GWM_SLOT(28) GWM_SLOT(29)
	GWM_SLOT(30) GWM_SLOT(31) GWM_SLOT(32) GWM_SLOT(33) GWM_SLOT(34)
	GWM_SLOT(35) GWM_SLOT(36) GWM_SLOT(37) GWM_SLOT(38) GWM_SLOT(39)
	GWM_SLOT(40) GWM_SLOT(41) GWM_SLOT(42) GWM_SLOT(43) GWM_SLOT(44)
	GWM_SLOT(45) GWM_SLOT(46) GWM_SLOT(47) GWM_SLOT(48) GWM_SLOT(49)
	GWM_SLOT(50) GWM_SLOT(51) GWM_SLOT(52) GWM_SLOT(53) GWM_SLOT(54)
	GWM_SLOT(55) GWM_SLOT(56) GWM_SLOT(57) GWM_SLOT(58) GWM_SLOT(59)
#undef GWM_SLOT
	virtual GameWindow *slotF0(void *, NameKeyType) = 0;
};

// Partial target-layout emitter: only the method ABI and the dword at +0x1C
// are represented; this is not a complete InGameUI class declaration.
class InGameUI {
	unsigned char opaquePrefix[0x1C];
	int Rva0037BD81Field;
protected:
	void createReplayControl();
};

void InGameUI::createReplayControl()
{
	NameKeyType key;
	{
		AsciiString filename("ReplayControl.wnd:ParentReplayControl");
		key = TheNameKeyGenerator->nameToKey(filename);
	}
	GameWindow *window = reinterpret_cast<Rva0037BD81WindowManagerSlotView *>(TheWindowManager)->slotF0(0, key);
	if (window != 0)
		window->winHide(Rva0037BD81Field != 1);
}
