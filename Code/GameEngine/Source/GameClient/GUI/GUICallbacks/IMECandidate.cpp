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
