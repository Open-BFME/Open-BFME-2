// cl: /O1 /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /arch:SSE /G7
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
// IMECandidateMainDraw: native FunctionLexicon record VA00DBC998 binds
// the literal at00C028B8 directly to00427858; complete222B ends00427936.
// Based on Open-BFME-1 874e38488c7dcf8cf3343452e8e5371bb3a0e64c
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/IMECandidateMainDraw_Thunk.cpp
// and the EA Generals Zero Hour callback source. Existing BFME2 GUI headers
// supply the measured draw colors and virtual rect slots. The filled rectangle
// uses origin-plus-one temporaries before the end coordinates: preserving
// these values independently of start reproduces native LEA operand order.
void IMECandidateMainDraw(GameWindow *window, WinInstanceData *instData)
{
	ICoord2D origin, size, start, end;
	Color backColor;
	Color backBorder;
	Real borderWidth = 1.0f;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == 0)
	{
		backColor = window->winGetDisabledColor(0);
		backBorder = window->winGetDisabledBorderColor(0);
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		backColor = window->winGetHiliteColor(0);
		backBorder = window->winGetHiliteBorderColor(0);
	}
	else
	{
		backColor = window->winGetEnabledColor(0);
		backBorder = window->winGetEnabledBorderColor(0);
	}

	if (backBorder != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect(backBorder, borderWidth, start.x, start.y, end.x, end.y);
	}

	if (backColor != WIN_COLOR_UNDEFINED)
	{
		Int sx = origin.x + 1, sy = origin.y + 1;
		start.x = sx;
		start.y = sy;
		end.x = sx + size.x - 2;
		end.y = sy + size.y - 2;
		TheWindowManager->winFillRect(backColor, 0.0f, start.x, start.y, end.x, end.y);
	}
}

class DisplayString;
class DisplayStringManager;
extern DisplayStringManager *TheDisplayStringManager;
// Call-only factory prefix: native create/free slots38/3C, as independently
// used by the already recovered Rva004E5821 consumer. No object is constructed.
class ImeDisplayFactoryPrefix {
public:
 virtual void slot00() = 0;
 virtual void slot04() = 0;
 virtual void slot08() = 0;
 virtual void slot0C() = 0;
 virtual void slot10() = 0;
 virtual void slot14() = 0;
 virtual void slot18() = 0;
 virtual void slot1C() = 0;
 virtual void slot20() = 0;
 virtual void slot24() = 0;
 virtual void slot28() = 0;
 virtual void slot2C() = 0;
 virtual void slot30() = 0;
 virtual void slot34() = 0;
 virtual DisplayString *newDisplayString() = 0;
 virtual void freeDisplayString(DisplayString *) = 0;
};
// Native WindowSystem uses the same nullable four-byte file-static at
// VAE031F8 for create and destroy; the initial native storage is zero.
static DisplayString *Dstring = 0;

// Native FunctionLexicon DBCAB0 binds nameC02690 to427810. All72 bytes
// end427858 with cdecl return; only msg (second callback word) is used.
WindowMsgHandledType IMECandidateWindowSystem(GameWindow *window,UnsignedInt msg,WindowMsgData data1,WindowMsgData data2)
{
 switch(msg) {
  case GWM_CREATE:
   if(Dstring==0) Dstring=reinterpret_cast<ImeDisplayFactoryPrefix *>(TheDisplayStringManager)->newDisplayString();
   break;
  case GWM_DESTROY:
   if(Dstring!=0) {
    reinterpret_cast<ImeDisplayFactoryPrefix *>(TheDisplayStringManager)->freeDisplayString(Dstring);
    Dstring=0;
   }
   break;
  default: return MSG_IGNORED;
 }
 return MSG_HANDLED;
}
