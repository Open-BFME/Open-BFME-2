// cl: /FIzh_ascii.h /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/shims/sweep
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#define __SUBSYSTEMINTERFACE_H_
class SubsystemInterfaceList;
#include "PreRTS.h"
#include "../../../../reference/shims/bfme2_mouse/GameClient/Mouse.h"
#include <vector>
#include "../../../../reference/shims/bfme2_mouse/GameClient/GameText.h"
// ?setCursor@Mouse@@UAEXW4MouseCursor@1@@Z, retail 0x001EEFD2, 137 bytes.
// Mouse::setCursor from Zero Hour's Mouse.cpp. Win32Mouse::setCursor
// (0x00041A83) extends it with a direct call, which names the address.
// BFME 2 differs from Zero Hour in two guards read off the target: the
// cursor text display string at +0x4FA8 must exist, and the cursor must lie
// in [0, NUM_MOUSE_CURSORS) before m_cursorInfo (+0x0C, stride 0x54) is
// indexed. The text comes from TheGameText's const-char fetch at slot 15
// (+0x3C) and goes to the rowed setMouseText 0x001EEBD5, whose colour
// parameters are named RGBAColorInt there.
class Mouse;
#include "ascii_string.h"
#include "unicode_string.h"

typedef RGBAColorInt RGBAColorInt;




class DisplayString;


// Retail folds this empty hook with the shared 1B ret at 0x000B3FD0
// (pin: ResetResolution calls it on TheMouse; ZH mouseNotifyResolution-
// Change is the identity lead). Defined here because this TU makes no
// calls to it, so nothing inlines or deletes the out-of-line call that
// GameClientDisplayModeChange's rowed body needs.
void Mouse::rva000B3FD0()
{
}

void Mouse::setCursor( MouseCursor cursor )
{
	// only if changing
	if( m_currentCursor == cursor )
		return;

	if( m_cursorTextDisplayString == 0 )
		return;

	if( cursor < NONE || (unsigned int)cursor >= NUM_MOUSE_CURSORS )
		return;

	CursorInfo &info = m_cursorInfo[ cursor ];

	// set the new cursor text
	if( info.cursorText.isEmpty() == false )
	{
		setMouseText( TheGameText->fetch( info.cursorText.str() ),
								 &info.cursorTextColor,
								 &info.cursorTextDropColor );
	}
	else
		setMouseText( UnicodeString( L"" ), 0, 0 );
}
