// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// FILE: ProgressBar.cpp //////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//
//                       Westwood Studios Pacific.
//
//                       Confidential Information
//                Copyright (C) 2001 - All Rights Reserved
//
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: ProgressBar.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      Progress bar GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Language.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"

// Retail GameWindowManager::winSendSystemMsg occupies vtable slot 0xE8.
class BfmeProgressWindowManager
{
public:
#define PROGRESS_MANAGER_SLOT(n) virtual void slot##n() = 0;
	PROGRESS_MANAGER_SLOT(0) PROGRESS_MANAGER_SLOT(1) PROGRESS_MANAGER_SLOT(2)
	PROGRESS_MANAGER_SLOT(3) PROGRESS_MANAGER_SLOT(4) PROGRESS_MANAGER_SLOT(5)
	PROGRESS_MANAGER_SLOT(6) PROGRESS_MANAGER_SLOT(7) PROGRESS_MANAGER_SLOT(8)
	PROGRESS_MANAGER_SLOT(9) PROGRESS_MANAGER_SLOT(10) PROGRESS_MANAGER_SLOT(11)
	PROGRESS_MANAGER_SLOT(12) PROGRESS_MANAGER_SLOT(13) PROGRESS_MANAGER_SLOT(14)
	PROGRESS_MANAGER_SLOT(15) PROGRESS_MANAGER_SLOT(16) PROGRESS_MANAGER_SLOT(17)
	PROGRESS_MANAGER_SLOT(18) PROGRESS_MANAGER_SLOT(19) PROGRESS_MANAGER_SLOT(20)
	PROGRESS_MANAGER_SLOT(21) PROGRESS_MANAGER_SLOT(22) PROGRESS_MANAGER_SLOT(23)
	PROGRESS_MANAGER_SLOT(24) PROGRESS_MANAGER_SLOT(25) PROGRESS_MANAGER_SLOT(26)
	PROGRESS_MANAGER_SLOT(27) PROGRESS_MANAGER_SLOT(28) PROGRESS_MANAGER_SLOT(29)
	PROGRESS_MANAGER_SLOT(30) PROGRESS_MANAGER_SLOT(31) PROGRESS_MANAGER_SLOT(32)
	PROGRESS_MANAGER_SLOT(33) PROGRESS_MANAGER_SLOT(34) PROGRESS_MANAGER_SLOT(35)
	PROGRESS_MANAGER_SLOT(36) PROGRESS_MANAGER_SLOT(37) PROGRESS_MANAGER_SLOT(38)
	PROGRESS_MANAGER_SLOT(39) PROGRESS_MANAGER_SLOT(40) PROGRESS_MANAGER_SLOT(41)
	PROGRESS_MANAGER_SLOT(42) PROGRESS_MANAGER_SLOT(43) PROGRESS_MANAGER_SLOT(44)
	PROGRESS_MANAGER_SLOT(45) PROGRESS_MANAGER_SLOT(46) PROGRESS_MANAGER_SLOT(47)
	PROGRESS_MANAGER_SLOT(48) PROGRESS_MANAGER_SLOT(49) PROGRESS_MANAGER_SLOT(50)
	PROGRESS_MANAGER_SLOT(51) PROGRESS_MANAGER_SLOT(52) PROGRESS_MANAGER_SLOT(53)
	PROGRESS_MANAGER_SLOT(54) PROGRESS_MANAGER_SLOT(55) PROGRESS_MANAGER_SLOT(56)
	PROGRESS_MANAGER_SLOT(57)
#undef PROGRESS_MANAGER_SLOT
	virtual Int winSendSystemMsg( GameWindow*, GadgetGameMessage, WindowMsgData, WindowMsgData ) = 0;
};

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////

// GadgetProgressBarSystem ====================================================
/** Handle system messages for Progress Bar */
//=============================================================================
WindowMsgHandledType GadgetProgressBarSystem( GameWindow *window, UnsignedInt msg,
									            WindowMsgData mData1, WindowMsgData mData2 )
{

  switch( msg )
	{

		// ------------------------------------------------------------------------
    case 0x4033: // BFME2 callback message from target body
    {
      Int newPos = (Int)mData1;

      if (newPos < 0 || newPos > 100)
        break;

      window->winSetUserData( (void *)newPos );

			break;

    }  // end set progress

		// ------------------------------------------------------------------------
		default:
			return MSG_IGNORED;

	}  // end switch

	return MSG_HANDLED;

}  // end GadgetProgressBarSystem

// GadgetProgressBarSetProgress ===============================================
/** send progress system message to Progress Bar */
//=============================================================================
void GadgetProgressBarSetProgress( GameWindow *g, Int progress )
{
	if(!g)
		return;

	((BfmeProgressWindowManager*)TheWindowManager)->winSendSystemMsg( g, (GadgetGameMessage)0x4033, progress, 0);
} // end GadgetProgressBarSetProgress
