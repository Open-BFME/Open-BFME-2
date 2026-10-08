// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/open-bfme-1/inputs/reference/shims/display /Ireference/open-bfme-1/inputs/reference/shims/asciistring8outofline /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/GUI/ControlBar/ControlBarResizer.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: ControlBarResizer::~ControlBarResizer 0x001DB92A (120B),
// ControlBarResizer::findResizerWindow 0x001DB775 (84B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
// Also ControlBarResizer::sizeWindowsDefault 0x001DB7C9 (100B) and
// sizeWindowsAlt 0x001DB82D (253B), the donor bodies without their debug
// output, through BFME 2 vtable views of TheWindowManager and TheDisplay.
// The cl line carries /O1 /arch:SSE (sizeWindowsAlt's scaling is SSE); the
// two earlier bodies compile identically under it.
#define BFME_STLP_NODE_ALLOC 1  // STLport _Node_alloc so list nodes free via the retail 0x0082E5F0 bucket allocator
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

// FILE: ControlBarResizer.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Sep 2002
//
//	Filename: 	ControlBarResizer.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	We want a "squished" control bar, this is the methods that will do it
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#define _STLP_NO_EXCEPTIONS 1	// Open-BFME7: this TU was built with STLport exceptions off (STLport helpers inline as in retail)
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "GameClient/ControlBar.h"
#include "GameClient/ControlBarResizer.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Display.h"


ControlBarResizer::~ControlBarResizer( void )
{
	ResizerWindowList::iterator it = m_resizerWindowsList.begin();
	while (it != m_resizerWindowsList.end())
	{
		ResizerWindow *rWin = *it;
		if( !rWin )
		{
			it = m_resizerWindowsList.erase(it);
			continue;
		}
		delete rWin;
		it = m_resizerWindowsList.erase(it);
	}
	m_resizerWindowsList.clear();
}
	
	
ResizerWindow *ControlBarResizer::findResizerWindow( AsciiString name )
{
	ResizerWindowList::iterator it = m_resizerWindowsList.begin();

	while (it != m_resizerWindowsList.end())
	{
		ResizerWindow *rWin = *it;
		if( !rWin )
		{
			DEBUG_ASSERTCRASH(FALSE,("There's no resizerWindow in ControlBarResizer::findResizerWindow"));
			it++;
			continue;
		}
		// find the scheme that best matches our resolution
		if(rWin->m_name.compare(name) == 0)
		{
			return rWin;
		}
		it ++;	
	}
	return NULL;
}


  // end parseMappedImage


//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------


// BFME 2 vtable views for the two sizers: TheWindowManager's
// winGetWindowFromId is slot 60 and TheDisplay's getWidth/getHeight are
// slots 16/17 (Zero Hour's headers have them earlier).
class BfmeResizerWindowManagerView
{
public:
#define RZ_SLOT(n) virtual void slot##n();
	RZ_SLOT(00) RZ_SLOT(01) RZ_SLOT(02) RZ_SLOT(03) RZ_SLOT(04) RZ_SLOT(05) RZ_SLOT(06) RZ_SLOT(07) RZ_SLOT(08) RZ_SLOT(09)
	RZ_SLOT(10) RZ_SLOT(11) RZ_SLOT(12) RZ_SLOT(13) RZ_SLOT(14) RZ_SLOT(15) RZ_SLOT(16) RZ_SLOT(17) RZ_SLOT(18) RZ_SLOT(19)
	RZ_SLOT(20) RZ_SLOT(21) RZ_SLOT(22) RZ_SLOT(23) RZ_SLOT(24) RZ_SLOT(25) RZ_SLOT(26) RZ_SLOT(27) RZ_SLOT(28) RZ_SLOT(29)
	RZ_SLOT(30) RZ_SLOT(31) RZ_SLOT(32) RZ_SLOT(33) RZ_SLOT(34) RZ_SLOT(35) RZ_SLOT(36) RZ_SLOT(37) RZ_SLOT(38) RZ_SLOT(39)
	RZ_SLOT(40) RZ_SLOT(41) RZ_SLOT(42) RZ_SLOT(43) RZ_SLOT(44) RZ_SLOT(45) RZ_SLOT(46) RZ_SLOT(47) RZ_SLOT(48) RZ_SLOT(49)
	RZ_SLOT(50) RZ_SLOT(51) RZ_SLOT(52) RZ_SLOT(53) RZ_SLOT(54) RZ_SLOT(55) RZ_SLOT(56) RZ_SLOT(57) RZ_SLOT(58) RZ_SLOT(59)
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);	// slot 60
};
class BfmeResizerDisplayView
{
public:
	RZ_SLOT(00) RZ_SLOT(01) RZ_SLOT(02) RZ_SLOT(03) RZ_SLOT(04) RZ_SLOT(05) RZ_SLOT(06) RZ_SLOT(07) RZ_SLOT(08) RZ_SLOT(09)
	RZ_SLOT(10) RZ_SLOT(11) RZ_SLOT(12) RZ_SLOT(13) RZ_SLOT(14) RZ_SLOT(15)
#undef RZ_SLOT
	virtual UnsignedInt getWidth(void);	// slot 16
	virtual UnsignedInt getHeight(void);	// slot 17
};
#define ResizerWindowManager ((BfmeResizerWindowManagerView *)TheWindowManager)
#define ResizerDisplay ((BfmeResizerDisplayView *)TheDisplay)

void ControlBarResizer::sizeWindowsDefault( void )
{
	ResizerWindowList::iterator it = m_resizerWindowsList.begin();
	GameWindow *win = NULL;
	while (it != m_resizerWindowsList.end())
	{
		ResizerWindow *rWin = *it;
		if( !rWin )
		{
			it++;
			continue;
		}
		win = ResizerWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey(rWin->m_name));
		if(!win)
		{
			it++;
			continue;
		}
		win->winSetPosition(rWin->m_defaultPos.x, rWin->m_defaultPos.y);
		win->winSetSize(rWin->m_defaultSize.x, rWin->m_defaultSize.y);
		it ++;
	}
}
void ControlBarResizer::sizeWindowsAlt( void )
{
	ResizerWindowList::iterator it = m_resizerWindowsList.begin();
	GameWindow *win = NULL;
	Real x = (Real)ResizerDisplay->getWidth() / 800;
	Real y = (Real)ResizerDisplay->getHeight() / 600;
	while (it != m_resizerWindowsList.end())
	{
		ResizerWindow *rWin = *it;
		if( !rWin )
		{
			it++;
			continue;
		}
		win = ResizerWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey(rWin->m_name));
		if(!win)
		{
			it++;
			continue;
		}

		win->winSetPosition(rWin->m_altPos.x * x, rWin->m_altPos.y * y);
		if(rWin->m_altSize.x >0 || rWin->m_altSize.y > 0)
			win->winSetSize(rWin->m_altSize.x *x, rWin->m_altSize.y *y);
		it ++;
	}
}
