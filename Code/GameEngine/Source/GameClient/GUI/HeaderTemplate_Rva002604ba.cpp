// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
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

// FILE: HeaderTemplate.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Aug 2002
//
//	Filename: 	HeaderTemplate.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	The header template system is used to maintain a unified look across
//						windows.  It also allows Localization to customize the looks based
//						on language fonts.
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------


// The compact string view calls the shared StringBase storage operations.
template <typename T> class HeaderTemplateStringBase
{
friend class HeaderTemplateString;
private:
	HeaderTemplateStringBase( void );
	HeaderTemplateStringBase( const HeaderTemplateStringBase<T> &that );
	HeaderTemplateStringBase( const T *text );
	void releaseBuffer( void );
	void set( const HeaderTemplateStringBase<T> &that );
};

class HeaderTemplateString
{
public:
	HeaderTemplateString( void ) : m_text( 0 ) {}
	HeaderTemplateString( const HeaderTemplateString &that )
	{
		((HeaderTemplateStringBase<char> *)this)->HeaderTemplateStringBase<char>::HeaderTemplateStringBase(
			*(const HeaderTemplateStringBase<char> *)&that);
	}
	HeaderTemplateString( const char *text )
	{
		((HeaderTemplateStringBase<char> *)this)->HeaderTemplateStringBase<char>::HeaderTemplateStringBase( text );
	}
	~HeaderTemplateString( void );

	void format( HeaderTemplateString fmt, ... );
	const char *str( void ) const
	{
		return m_text ? m_text + 8 : "";
	}
	HeaderTemplateString &operator=( const HeaderTemplateString &that )
	{
		((HeaderTemplateStringBase<char> *)this)->set(
			*(const HeaderTemplateStringBase<char> *)&that);
		return *this;
	}

private:
	char *m_text;
};

// Return type is deliberately TU-local: the ABI is the same two-word value
// used by GetRegistryLanguage, while its body is the retail global language
// accessor (pinned by the conversion ledger when this row is landed).
HeaderTemplateString HeaderTemplateGetRegistryLanguage( void );

HeaderTemplateString bfmeHeaderTemplateRegistryLanguage( void )
{
	return HeaderTemplateGetRegistryLanguage();
}

// The retail call in this body reads 0x00235029, an address the ledger already
// carries as ?GetRegistryLanguage@@YA?AVAsciiString@@XZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?HeaderTemplateGetRegistryLanguage@@YA?AVHeaderTemplateString@@XZ=?GetRegistryLanguage@@YA?AVAsciiString@@XZ")
