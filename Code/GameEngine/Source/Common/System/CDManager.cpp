// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/reference/shims/cdmanager /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?init@CDManager@@: Code/GameEngineDevice/Source/Win32Device/Common/Win32CDManager.cpp
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

//----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   Generals
//
// Module:    Game Engine Common
//
// File name: CDManager.cpp
//
// Created:   11/26/01 TR
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/CDManager.h"

//----------------------------------------------------------------------------
//         Externals                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Defines                                                         
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Types                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Data                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Data                                                      
//----------------------------------------------------------------------------

CDManagerInterface* TheCDManager = NULL;

//----------------------------------------------------------------------------
//         Private Prototypes                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Functions                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Functions                                                
//----------------------------------------------------------------------------


// The ledger retains only these two ICF-folded string getters. The former
// Zero Hour constructors and drive-list methods had no rows; none has an
// outside object reference. Their LList dependencies and CDManager vtable
// therefore do not belong to this getter-only unit. Keep TheCDManager above:
// FileSystem.cpp references that existing global.

AsciiString CDDrive::getPath(void)
{
    return m_drivePath;
}

AsciiString CDDrive::getDiskName(void)
{
    return m_diskName;
}
