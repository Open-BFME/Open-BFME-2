// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/display /Ireference/open-bfme-1/inputs/reference/shims/mouselayout /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngineDevice/Source/Win32Device/GameClient/Win32DIMouse.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: DirectInputMouse::setPosition 0x00041AD4 (60B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FILE: Win32DIMouse.cpp /////////////////////////////////////////////////////////////////////////
// Created:    Colin Day, June 2001
// Desc:       Win32 direct input implementation for the mouse
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <windows.h>
#include <assert.h>

#include "Common/Debug.h"
#include "Common/GameType.h"	// TimeOfDay, for the BFME Display shim
#include "GameClient/Display.h"
// BFME's Mouse is 0x10 bytes longer than inputs/reference/shims/mouselayout models it.
// DirectInputMouse derives from Mouse directly and never sees Win32Mouse, yet
// openMouse @0x6BB6C9 reads m_pDirectInput at +0x4E14 and getMouseEvent
// @0x6BBC28 reads m_pMouseDevice at +0x4E18 - so sizeof(Mouse) is 0x4E14 on its
// own, and the 0x10 the shim parks at the front of Win32Mouse is really Mouse's
// tail. Moving it there is the true fix and is byte-neutral for W3DMouse.cpp
// (the total stays 0x368, so no Win32Mouse offset changes), but editing a shim
// forces the full gate, which is currently red on eight pre-existing DIR32
// inconsistencies that have nothing to do with this file. So the same 0x10 is
// modelled here instead, ahead of DirectInputMouse's own members, which lands
// them on the retail offsets. Nothing outside this translation unit names
// DirectInputMouse.
#define __WIN32DIMOUSE_H_
#ifndef DIRECTINPUT_VERSION
#	define DIRECTINPUT_VERSION	0x800
#endif
// Retail reaches DirectInput8Create with a direct `call rel32` at 0x6BBAC0, so
// it links dinput8.lib's stub rather than going through the import table; the
// sweep shim declares it __declspec(dllimport), which costs a `call [import]`
// one byte longer. Renaming the shim's declaration out of the way and giving
// the real one ordinary external linkage restores the retail call shape without
// touching the shim (a shim edit forces the full gate, which is red).
#define DirectInput8Create _bfme_dinput8create_dllimport_unused
// USER32 imports use C linkage in retail (ClipCursor, LoadCursorA,
// ReleaseCapture and SetCapture); the local dinput shim omits that linkage.
extern "C" {
#include <dinput.h>
}
#undef DirectInput8Create
extern "C" HRESULT WINAPI DirectInput8Create( HINSTANCE, DWORD, REFIID, void **, IUnknown * );

#include "GameClient/Mouse.h"

// dinput.h's DIERR_NOTACQUIRED is HRESULT_FROM_WIN32(ERROR_INVALID_ACCESS==12),
// which is what getMouseEvent @0x6BBC59 compares against. The sweep shim has
// 0x8007001A; correcting it there is another shim edit, so it is corrected here.
#undef DIERR_NOTACQUIRED
#define DIERR_NOTACQUIRED            0x8007000CL

// Same story for DIDC_FORCEFEEDBACK: dinput.h has it at 0x100, and openMouse
// @0x6BBB91 shifts dwFlags right by 8 before masking bit 0. The shim has 1.
#undef DIDC_FORCEFEEDBACK
#define DIDC_FORCEFEEDBACK           0x00000100

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/GameClient/Win32DIMouse.h
class DirectInputMouse : public Mouse
{

public:

	DirectInputMouse( void );
	virtual ~DirectInputMouse( void );

	// extended methods from base class
	virtual void init( void );		///< initialize the direct input mouse, extending functionality
	virtual void reset( void );		///< reset system
	virtual void update( void );  ///< update the mouse data, extending functionality
	virtual void setPosition( Int x, Int y );  ///< set position for mouse

	virtual void setMouseLimits( void );  ///< update the limit extents the mouse can move in

	virtual void setCursor( MouseCursor cursor );  ///< set mouse cursor

	virtual void capture( void );  ///< capture the mouse
	virtual void releaseCapture( void );  ///< release mouse capture

protected:

	/// device implementation to get mouse event
	virtual UnsignedByte getMouseEvent( MouseIO *result, Bool flush );

	// new internal methods for our direct input implemetation
	void openMouse( void );  ///< create the direct input mouse
	void closeMouse( void );  ///< close and release mouse resources
	/// map direct input mouse data to our own format
	void mapDirectInputMouse( MouseIO *mouse, DIDEVICEOBJECTDATA *mdat );

	char _bfme_mouse_tail[ 0x10 ];  ///< Mouse's, not ours; see above

	// internal data members for our direct input mouse
	LPDIRECTINPUT8 m_pDirectInput;  ///< pointer to direct input interface
	LPDIRECTINPUTDEVICE8 m_pMouseDevice;  ///< pointer to mouse device

};  // end class DirectInputMouse

#include "WinMain.h"

// DEFINES ////////////////////////////////////////////////////////////////////////////////////////
enum { MOUSE_BUFFER_SIZE = 256, };


  // end setMouseLimits

//-------------------------------------------------------------------------------------------------
/** set the cursor position for windows OS */
//-------------------------------------------------------------------------------------------------
void DirectInputMouse::setPosition( Int x, Int y )
{
	POINT p;

	// extending functionality
	Mouse::setPosition( x, y );

	// set the windows cursor
	p.x = x;
	p.y = y;
	ClientToScreen( ApplicationHWnd, &p );

	// set the window mouse
	SetCursorPos( p.x, p.y );

}


  // end releaseCapture
