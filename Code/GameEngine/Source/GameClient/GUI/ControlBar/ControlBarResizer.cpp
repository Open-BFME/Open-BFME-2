// cl: /Ireference/shims/bfmealloc /D_CRTIMP= /O1 /arch:SSE /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/open-bfme-1/inputs/reference/shims/display /Ireference/open-bfme-1/inputs/reference/shims/asciistring8outofline /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// newResizerWindow is adapted from donor f98983a7d3bb405f1a4ba94bb6a2a168062a819d.
// Native 1DB9A2..1DBA69 and WB AC4330 prove the 199B method and its ABI.
// The rowed 31B ResizerWindow constructor is only stores: its nonthrowing
// declaration removes the allocation cleanup state absent from retail.
// Native slot60 and nameToKey(AsciiString const&) agree with matched sizers.
//
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
class ResizerWindow
{
public:
ResizerWindow( void ) throw();
	AsciiString m_name;
	ICoord2D m_defaultSize;
	ICoord2D m_defaultPos;
	ICoord2D m_altSize;
	ICoord2D m_altPos;
};

class ControlBarResizer
{
public:
	ControlBarResizer( void );
	~ControlBarResizer( void );
	
	void init( void );

	// parse Functions for the INI file
	const FieldParse *getFieldParse() const { return m_controlBarResizerParseTable; }								///< returns the parsing fields
	static const FieldParse m_controlBarResizerParseTable[];																				///< the parse table

	ResizerWindow *findResizerWindow( AsciiString name ); ///< attempt to find the control bar scheme by it's name
	ResizerWindow *newResizerWindow( AsciiString name );	///< create a new control bar scheme and return it.
	
	void sizeWindowsDefault( void );
	void sizeWindowsAlt( void );

	typedef std::list< ResizerWindow *> ResizerWindowList;
	ResizerWindowList m_resizerWindowsList;

};

#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"


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
#undef RZ_SLOT
#define ResizerWindowManager ((BfmeResizerWindowManagerView *)TheWindowManager)
ResizerWindow *ControlBarResizer::newResizerWindow( AsciiString name )
{
	GameWindow *win = NULL;
	ResizerWindow *newRwin = NEW ResizerWindow;
	if(!newRwin)
		return NULL;

	newRwin->m_name = name;
	win = ResizerWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey(name));
	if( !win )
	{
		DEBUG_ASSERTCRASH(win,("ControlBarResizer::newResizerWindow could not find window %s Are you sure that window is loaded yet?", name.str()) );
		delete newRwin;
		return NULL;
	}
	win->winGetPosition(&newRwin->m_defaultPos.x,&newRwin->m_defaultPos.y);
	win->winGetSize(&newRwin->m_defaultSize.x,&newRwin->m_defaultSize.y);
	m_resizerWindowsList.push_back(newRwin);
	return newRwin;
}	


ResizerWindow::ResizerWindow(void) throw()
{
	m_defaultPos.y = 0;
	m_defaultPos.x = 0;
	m_defaultSize.y = 0;
	m_defaultSize.x = 0;
	m_altSize.y = 0;
	m_altSize.x = 0;
	m_altPos.y = 0;
	m_altPos.x = 0;
}
