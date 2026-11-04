// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/iniexception /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/INI/INIDrawGroupInfo.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// parseInt 0x001DCC45 (46B), parsePercentToReal 0x001DCC73 (44B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
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

// FILE: INIDrawGroupInfo.cpp /////////////////////////////////////////////////////////////////////
// Author: John McDonald, October 2002
// Desc:   Parsing DrawGroupInfo INI entries
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/INI.h"
#include "Common/INIException.h"
#include "GameClient/DrawGroupInfo.h"
extern "C" {
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseQuotedAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parsePercentToReal@@YAXPAVINI@@PAX1PBX@Z")();
}
// The retail table at 0x007DBE10: 12 entries and the null terminator; every parser is a rowed code owner.
const FieldParse DrawGroupInfo::s_fieldParseTable[13] = {
	{ "UsePlayerColor", (INIFieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x9 },
	{ "ColorForText", (INIFieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "ColorForTextDropShadow", (INIFieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "FontName", (INIFieldParseProc)&__identifier("?parseQuotedAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
	{ "FontSize", (INIFieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "FontIsBold", (INIFieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "DropShadowOffsetX", (INIFieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ "DropShadowOffsetY", (INIFieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ "DrawPositionXPixel", (INIFieldParseProc)&__identifier("?parseInt@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "DrawPositionXPercent", (INIFieldParseProc)&__identifier("?parsePercentToReal@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "DrawPositionYPixel", (INIFieldParseProc)&__identifier("?parseInt@@YAXPAVINI@@PAX1PBX@Z"), (const void *)1, 0x0 },
	{ "DrawPositionYPercent", (INIFieldParseProc)&__identifier("?parsePercentToReal@@YAXPAVINI@@PAX1PBX@Z"), (const void *)1, 0x0 },
	{ 0, 0, 0, 0 }
};

void parseInt( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	DrawGroupInfo *dgi = (DrawGroupInfo*) store;
	if (userData == 0) {
		store = &dgi->m_pixelOffsetX;
		dgi->m_usingPixelOffsetX = TRUE;
	} else { 
		store = &dgi->m_pixelOffsetY;
		dgi->m_usingPixelOffsetY = TRUE;
	}

	INI::parseInt(ini, NULL, store, NULL);
}

void parsePercentToReal( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	DrawGroupInfo *dgi = (DrawGroupInfo*) store;
	if (userData == 0) {
		store = &dgi->m_pixelOffsetX;
		dgi->m_usingPixelOffsetX = FALSE;
	} else { 
		store = &dgi->m_pixelOffsetY;
		dgi->m_usingPixelOffsetY = FALSE;
	}

	INI::parsePercentToReal(ini, NULL, store, NULL);
}

// ?parseDrawGroupNumberDefinition@INI@@SAXPAV1@@Z @0x001DCC9F 63B evidence: REF table slot 0x009B8D30 neighbours DrawGroupInfo NONE HOLD; TheDrawGroupInfo null check INIException 9; initFromINI with FieldParse
/*static*/ void INI::parseDrawGroupNumberDefinition(INI* ini)
{
	if (!TheDrawGroupInfo) {
		throw INIException(9, "TheDrawGroupInfo==NULL");
	}

	ini->initFromINI(TheDrawGroupInfo, TheDrawGroupInfo->getFieldParse());
}

// INI block registration. BFME's INI keeps its block types on a list of
// 12-byte BlockParse nodes; each unit links its own nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the
// link. MSVC 7.1 builds token and parse in .data, so each node's .text$yc
// initializer is only the 21-byte link (retail .CRT$XCU 0x007AD19E,
// node 0x00DB8D28).
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theDrawGroupInfoBlockParse( "DrawGroupInfo", INI::parseDrawGroupNumberDefinition );
