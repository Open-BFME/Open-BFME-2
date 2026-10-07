// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
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
#define ASCIISTRING_H
#include "ascii_string.h"
#include "PreRTS.h"
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "Common/INI.h"
#include "Common/Filesystem.h"
#include "Common/Registry.h"
#include "GameClient/HeaderTemplate.h"
#include "GameClient/GameFont.h"
#include "GameClient/GlobalLanguage.h"

// The shared headers above describe the ZH object sizes.  HeaderTemplate's
// loader is one of the BFME TUs that still carries the compact INI ABI, so its
// two automatic strings and INI are declared locally.  These are declarations
// only: the retail StringBase/INI bodies remain the shared engine bodies.
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

enum HeaderTemplateINILoadType
{
	HEADER_TEMPLATE_INI_LOAD_OVERWRITE = 1
};

class HeaderTemplateINI
{
public:
	HeaderTemplateINI( void );
	~HeaderTemplateINI( void );
	void load( HeaderTemplateString filename,
		HeaderTemplateINILoadType loadType, Xfer *xfer );

private:
	char m_unported[0x848];
};

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif
//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
const FieldParse HeaderTemplateManager::m_headerFieldParseTable[] =
{
	{ "Font",								INI::parseQuotedAsciiString,						NULL, offsetof( HeaderTemplate, m_fontName ) },
	{ "Point",							INI::parseInt,										NULL, offsetof( HeaderTemplate, m_point) },
	{ "Bold",								INI::parseBool,										NULL, offsetof( HeaderTemplate, m_bold ) },
	{ NULL, NULL, NULL, 0 },
};

HeaderTemplateManager *TheHeaderTemplateManager = NULL;
//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

HeaderTemplate *HeaderTemplateManager::getNextHeader( HeaderTemplate *ht )
{
	HeaderTemplateListIt it = m_headerTemplateList.begin();
	while(it != m_headerTemplateList.end())
	{
		if(*it == ht)
		{
			++it;
			if( it == m_headerTemplateList.end())
				return NULL;
			return *it;
		}
		++it;
	}
	return NULL;

}
