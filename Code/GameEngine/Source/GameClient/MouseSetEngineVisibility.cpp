// cl: /FIzh_ascii.h /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/shims/sweep
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#define __SUBSYSTEMINTERFACE_H_
class SubsystemInterfaceList;
#include "PreRTS.h"
#include "../../../../reference/shims/bfme2_mouse/GameClient/Mouse.h"

// Evidence: retail 0x001EE5BE (24 bytes) is the REL32 call target named
// ?_bfme_setEngineVisibility@Mouse@@QAEX_N@Z at several already-matched call
// sites (e.g. Code/GameEngine/Source/Common/GameEngineClientSubsystems.cpp).
// The already byte-matched BFME1 conversion of the same method
// (reference/open-bfme-1/Code/GameEngine/Source/Common/
// promoted__bfme_setEngineVisibility_Mouse_QAEX_N_Z_005A4B50.cpp) documents:
//   void Mouse::_bfme_setEngineVisibility(bool visible)
//   {
//       if (m_cursorDirty) { m_cursor = m_pendingCursor; m_cursorState = m_pendingCursorState; m_cursorDirty = 0; }
//       applyCursor(visible, &m_cursor);
//   }
// BFME2 moved the five cursor-state bytes from Mouse+0x4DA1.. to +0x4F9D..
// and factored the commit-if-dirty block into its own private helper
// (retail 0x1EDDFF, verified against this exact byte layout), called
// unconditionally before applyCursor -- which itself moved from vtable
// slot 0x5C to 0x70 (five more virtuals ahead of it in BFME2's Mouse).


__declspec(noinline) void Mouse::commitPendingCursor( void )
{
	if ( m_cursorDirty )
	{
		m_visible = m_pendingCursor;
		m_cursorState = m_pendingCursorState;
		m_cursorDirty = 0;
	}
}

void Mouse::_bfme_setEngineVisibility( bool visible )
{
	commitPendingCursor();
	applyCursor( visible, &m_visible );
}

// Retail 0x001EE5D6 (24 bytes), directly after the method above: ZH's
// Mouse::setVisibility, which BFME1 matched as the same shape over
// m_cursorState (reference/open-bfme-1/Code/GameEngine/Source/Common/
// promoted__setVisibility_BfmeMouse_setVisibility_QAEX_N_Z_005A4BA0.cpp).
// ScriptEngine::reset calls it with TRUE.
void Mouse::setVisibility( bool visible )
{
	commitPendingCursor();
	applyCursor( visible, &m_cursorState );
}
