// Copied from reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameText.h.
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
// Project:    RTS 3
//
// File name:  GameClient/GameText.h
//
// Created:    11/07/01
//
//----------------------------------------------------------------------------

#pragma once

#ifndef __GAMECLIENT_GAMETEXT_H_
#define __GAMECLIENT_GAMETEXT_H_


//----------------------------------------------------------------------------
//           Includes                                                      
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//           Forward References
//----------------------------------------------------------------------------

class AsciiString;
class UnicodeString;

//----------------------------------------------------------------------------
//           Type Defines
//----------------------------------------------------------------------------
typedef std::vector<AsciiString> AsciiStringVec;

//===============================
// GameTextInterface 
//===============================
/** Game text interface object for localised text.
	*/
//===============================

class GameTextInterface : public SubsystemInterface
{

	public:

		virtual ~GameTextInterface() {};
		// BFME 2: Mouse::setCursor 0x001EEFD2 calls fetch(const char *, bool *) at vtable +0x3C.
		virtual void slot00();
		virtual void slot01();
		virtual void slot02();
		virtual void slot03();
		virtual void slot04();
		virtual void slot05();
		virtual void slot06();
		virtual void slot07();
		virtual void slot08();
		virtual void slot09();
		virtual void slot10();
		virtual void slot11();
		virtual void slot12();


		virtual UnicodeString fetch( const Char *label, Bool *exists = NULL ) = 0;		///< Returns the associated labeled unicode text
		virtual UnicodeString fetch( AsciiString label, Bool *exists = NULL ) = 0;		///< Returns the associated labeled unicode text
		// This function is not performance tuned.. Its really only for Worldbuilder. jkmcd
		virtual AsciiStringVec& getStringsWithLabelPrefix(AsciiString label) = 0;

		virtual void					initMapStringFile( const AsciiString& filename ) = 0;
};


extern GameTextInterface *TheGameText;
extern GameTextInterface* CreateGameTextInterface( void );

//----------------------------------------------------------------------------
//           Inlining                                                       
//----------------------------------------------------------------------------


#endif // __GAMECLIENT_GAMETEXT_H_
