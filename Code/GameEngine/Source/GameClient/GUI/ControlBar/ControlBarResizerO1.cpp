// cl: /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/open-bfme-1/inputs/reference/shims/display /Ireference/open-bfme-1/inputs/reference/shims/asciistring8outofline /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

