// cl: /O1 /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/INI/INIWater.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: INI::parseWaterSettingDefinition 0x00200BEB (198B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
// One adaptation read off retail: the AsciiString assignment from a C string
// calls StringBase<char>::set (0x000055F5) directly rather than the rowed
// operator= at 0x000065B8, so it is spelled as set().
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

// FILE: INIWater.cpp /////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, December 2001
// Desc:   Water settings 
///////////////////////////////////////////////////////////////////////////////////////////////////

// Keep the parser's BFME 2 views local to this TU. The donor headers also
// declare unrelated STL, override and water-transparency types, which prevent
// composition with the other verified INIWater fragments.
#include "ascii_string.h"

class INI;
struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseWaterSettingDefinition(INI *ini);
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(const char *errorMessage);
	INIException(int argCount, const char *errorMessage, ...);
	INIException(const INIException &that);
	~INIException();
};

// Target: WaterSettingsArray.cpp's rowed initializer constructs six 0x7C-byte
// elements. Only the virtual destructor, stride and field table are used here.
class WaterSetting
{
public:
	virtual ~WaterSetting();
	const FieldParse *getFieldParse() { return m_waterSettingFieldParseTable; }
	static const FieldParse m_waterSettingFieldParseTable[];

private:
	char m_body[0x78];
};

extern WaterSetting WaterSettings[6];
extern char *TimeOfDayNames[];
typedef int Int;

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Water setting, note that this does not support override situations.  As the water
	* system becomes more complex we may want to change this */
//-------------------------------------------------------------------------------------------------
void INI::parseWaterSettingDefinition( INI* ini )
{
	AsciiString name;
	WaterSetting *waterSetting = NULL;

	// read the name
	name.set( ini->getNextToken() );	// retail calls StringBase::set (0x000055F5), not the operator= thunk

	// get the water setting we want to load based on name
	char **timeOfDayName = TimeOfDayNames;
	Int timeOfDayIndex = 0;  // TIME_OF_DAY_INVALID
	while( timeOfDayName && *timeOfDayName )
	{

		if( _strcmpi( *timeOfDayName, name.str() ) == 0 )
		{

			waterSetting = &WaterSettings[ timeOfDayIndex ];
			break;

		}  // end if

		// next name
		timeOfDayName++;
		timeOfDayIndex++;

	}  // end while

	// check for no time of day match
	if( waterSetting == NULL )
		throw INIException( 3, "No water setting found for time of day '%s'", name.str() );

	// parse the data
	ini->initFromINI( waterSetting, waterSetting->getFieldParse() );

}


