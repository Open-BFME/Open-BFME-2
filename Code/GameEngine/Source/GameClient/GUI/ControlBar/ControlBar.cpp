// cl: -DNDEBUG -DWIN32 -MD -D_STLP_USE_STATIC_LIB -EHsc -Ireference/open-bfme-1/inputs/vendor/stlport -Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc -Ireference/open-bfme-1/inputs/reference/shims/controlbarvtables -Ireference/open-bfme-1/inputs/reference/shims/controlbarlayout -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/ControlBar
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: ControlBar.cpp ///////////////////////////////////////////////////////////////////////////
// Author: Colin Day, March 2002
// Desc:   Context sensitive command interface
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////

#define BFME_STLP_NODE_ALLOC

// Retail 0x0040FD8F, 19 bytes:
//
//     8B 41 1C  mov eax,[ecx+1C]     ; the callback, read through this
//     85 C0     test eax,eax
//     74 09     jz  +9               ; null callback: skip the call
//     FF 74 24 04 push [esp+4]       ; userData pushed FIRST
//     51        push ecx             ; `this` pushed SECOND
//     FF D0     call eax
//     59 59     pop ecx / pop ecx
//     C2 04 00  ret 4
//
// Dedicated TU: the body below is the only definition; the donor's other
// sixty-six are omitted.
//
// `ret 4` is this body, not the callback: the one `pop ecx` after the call
// balances the `push ecx`, and the stack argument is popped by the callee's
// own `ret 4`.  So the callback is cdecl and both arguments travel on the
// stack.
//
// PUSH ORDER IS THE WHOLE ARGUMENT QUESTION, and it settles the header.  A
// measured isolated experiment (seven spellings, build/scratch_wl_try.py)
// shows MSVC 7.1 at these flags always materialises the callback pointer
// last -- `push ecx` first, then `push [esp+N]` -- whenever the callee takes
// `this` as a __thiscall argument.  Retail pushes in the other order, so the
// stack argument is the LAST callback parameter and `this` is the FIRST.
// That is exactly what the named header already says:
// `typedef void (*WindowLayoutUpdateFunc)( WindowLayout *, void * )` with
// `m_update( this, userData )`.  The typedef below is the header's own, and
// the argument order is not an inversion of it.
//
// WHAT IS SHADOWED, AND WHY.  `WindowLayout.h` declares the class with a
// memory-pool base and an inline body, so it cannot be reopened here; and
// pulling in GameClient/ControlBar.h to get the real declaration drags in
// symbols this TU is not allowed to claim.  Only three things about the class
// are used by this body -- `this`, a callback pointer at +0x1C, and `ret 4` --
// and only the +0x1C one is a layout claim.  The gap before m_update is
// padding to that single offset; the class is deliberately NOT made
// polymorphic, because nothing here shows retail's WindowLayout is, and the
// bytes need no vtable to reproduce.  The padding does not claim the real
// size of the class.  The header's `void *userData = NULL` default belongs to
// the header's inline; the out-of-line body takes the pushed value.

class WindowLayout;

typedef void (*WindowLayoutUpdateFunc)( WindowLayout *layout, void *userData );

class WindowLayout
{
public:
	void runUpdate( void *userData );

	unsigned char m_unmodelled_00[0x1C];
	WindowLayoutUpdateFunc m_update;					///< retail this+0x1C
};

// ?runUpdate@WindowLayout@@QAEXPAX@Z
void WindowLayout::runUpdate( void *userData )
{
	if( m_update )
		m_update( this, userData );
}
