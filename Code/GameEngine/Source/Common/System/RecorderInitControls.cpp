// RecorderClass::initControls, retail 0x0037BD81 (111 B): show or hide the
// replay controls. Zero Hour Recorder.cpp text; BFME 1 recovers the same body
// as RecorderClass::initControls (RecorderInitControls_Thunk.cpp, m_mode at
// +0x18).
//
// Target evidence: the only caller, GameLogic at 0x00248307, loads ecx from
// 0x00A02290 (TheRecorder, created by createRecorder 0x0037BCC4), and the
// body hides the "ReplayControl.wnd:ParentReplayControl" window unless the
// dword at this+0x1C is 1 (RECORDERMODETYPE_PLAYBACK). Retail reads the mode
// field directly, so getMode() is inline here.
//
// The GameWindowManager call goes through vtable +0xF0 (winGetWindowFromId)
// with (parent=0, key); only that slot is modelled.
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
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

class GameWindow {
public:
	int winHide(bool);
};

class GameWindowManager {
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
	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id) = 0;
};
extern GameWindowManager *TheWindowManager;

enum RecorderModeType {
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class RecorderClass {
public:
	void initControls();
	RecorderModeType getMode() { return m_mode; }

protected:
	char m_opaque00[0x1C];
	RecorderModeType m_mode;
};

void RecorderClass::initControls()
{
	NameKeyType parentReplayControlID;
	{
		AsciiString name("ReplayControl.wnd:ParentReplayControl");
		parentReplayControlID = TheNameKeyGenerator->nameToKey(name);
	}
	GameWindow *parentReplayControl = TheWindowManager->winGetWindowFromId(0, parentReplayControlID);

	if (parentReplayControl != 0)
		parentReplayControl->winHide(getMode() != RECORDERMODETYPE_PLAYBACK);
}
