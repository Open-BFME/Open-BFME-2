// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameNetwork/GameSpy/LadderDefs.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// LadderInfo::LadderInfo 0x0054D858 (128B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// parseLadder 0x0054DA41 (2234B) follows the Generals (not Zero Hour) source:
// retail falls back to the literal America/China/GLA factions. Its wide
// MultiByteToWideCharSingleLine temporaries free through the game's _free, so
// this unit uses the bfmealloc STLport allocator (/D_STLP_USE_MALLOC) rather
// than the node allocator; LadderInfo::LadderInfo is unchanged by that.
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

// FILE: LadderDefs.cpp //////////////////////////////////////////////////////
// Generals ladder code
// Author: Matthew D. Campbell, August 2002

// BFME 2's shared AsciiString (out-of-line compare/set/release, as retail
// calls them) instead of the Zero Hour header's inline bodies, so this unit
// emits no private copies of shared-class methods.
// Retail calls atoi through msvcrt's import table while the STL frees through
// the game's own _free (0x00030830); _CRTIMP is empty for the latter, so
// stdlib's atoi is set aside and redeclared as the import (PeerThread.cpp).
#define atoi atoi_unimported
#include <stdlib.h>
#undef atoi
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
#define ASCIISTRING_H
#include "ascii_string.h"
#include "unicode_string.h"
#define UNICODESTRING_H
// Retail reads the last character inline (null buffer -> 0) on every line.
template<> inline char StringBase<char>::getCharAt(int index) const throw()
{
	return m_data ? m_data->data[index] : 0;
}
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"

#include "Common/GameState.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/GameText.h"
#include "GameClient/MapUtil.h"


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

extern LadderList *TheLadderList;

// MapCache::getMapDir ("Maps") is rowed at 0x00300489 under this address-derived
// view; retail calls it directly (GameStatePortableMapPathToReal.cpp precedent).
class Rva00300489
{
public:
	virtual AsciiString rva00300489() const;
};

LadderInfo::LadderInfo()
{
	playersPerTeam = 1;
	minWins = 0;
	maxWins = 0;
	randomMaps = TRUE;
	randomFactions = TRUE;
	validQM = TRUE;
	validCustom = FALSE;
	port = 0;
	submitReplay = FALSE;
	index = -1;
}


// Zero Hour's file-static ladder parser, here in BFME 2's Generals-era form
// (hard-coded America/China/GLA fallback). Retail 0x0054DA41, 2234 bytes; its
// callers (LadderList's constructor and checkLadder) are not carried yet, so
// it keeps external linkage to stay emitted.
LadderInfo *parseLadder(AsciiString raw)
{
	LadderInfo *lad = NULL;
	AsciiString line;
	while (raw.nextToken(&line, "\n"))
	{
		if (line.getCharAt(line.getLength()-1) == '\r')
			line.removeLastChar();	// there is a trailing '\r'

		line.trim();

		if (line.isEmpty())
			continue;

		// woohoo!  got a line!
		line.trim();
		if ( !lad && line.startsWith("<Ladder ") )
		{
			// start of a ladder def
			lad = NEW LadderInfo;

			// fill in some info
			AsciiString tokenName, tokenAddr, tokenPort, tokenHomepage;
			line.removeLastChar(); // the '>'
			line = line.str() + 7; // the "<Ladder "
			line.nextToken(&tokenAddr, "\" ");
			line.nextToken(&tokenPort, " ");
			line.nextToken(&tokenHomepage, " ");

			lad->name = MultiByteToWideCharSingleLine(tokenName.str()).c_str();
			while (lad->name.getLength() > 20)
				lad->name.removeLastChar(); // Per Harvard's request, ladder names are limited to 20 chars
			lad->address = tokenAddr;
			lad->port = atoi(tokenPort.str());
			lad->homepageURL = tokenHomepage;
		}
		else if ( lad && line.startsWith("Name ") )
		{
			lad->name = MultiByteToWideCharSingleLine(line.str() + 5).c_str();
		}
		else if ( lad && line.startsWith("Desc ") )
		{
			lad->description = MultiByteToWideCharSingleLine(line.str() + 5).c_str();
		}
		else if ( lad && line.startsWith("Loc ") )
		{
			lad->location = MultiByteToWideCharSingleLine(line.str() + 4).c_str();
		}
		else if ( lad && line.startsWith("TeamSize ") )
		{
			lad->playersPerTeam = atoi(line.str() + 9);
		}
		else if ( lad && line.startsWith("RandomMaps ") )
		{
			lad->randomMaps = atoi(line.str() + 11);
		}
		else if ( lad && line.startsWith("RandomFactions ") )
		{
			lad->randomFactions = atoi(line.str() + 15);
		}
		else if ( lad && line.startsWith("Faction ") )
		{
			AsciiString faction = line.str() + 8;
			AsciiStringList outStringList;
			ThePlayerTemplateStore->getAllSideStrings(&outStringList);

			AsciiStringList::iterator aIt = std::find(outStringList.begin(), outStringList.end(), faction);
			if (aIt != outStringList.end())
			{
				// valid faction - now check for dupes
				aIt = std::find(lad->validFactions.begin(), lad->validFactions.end(), faction);
				if (aIt == lad->validFactions.end())
				{
					lad->validFactions.push_back(faction);
				}
			}
		}
		else if ( lad && line.startsWith("MinWins ") )
		{
			lad->minWins = atoi(line.str() + 8);
		}
		else if ( lad && line.startsWith("MaxWins ") )
		{
			lad->maxWins = atoi(line.str() + 8);
		}
		else if ( lad && line.startsWith("CryptedPass ") )
		{
			lad->cryptedPassword = line.str() + 12;
		}
		else if ( lad && line.compare("</Ladder>") == 0 )
		{
			// end of a ladder
			if (lad->playersPerTeam >= 1 && lad->playersPerTeam <= MAX_SLOTS/2)
			{
				if (lad->validFactions.size() == 0)
				{
					lad->validFactions.push_back("America");
					lad->validFactions.push_back("China");
					lad->validFactions.push_back("GLA");
				}
				else
				{
					AsciiStringList validFactions = lad->validFactions;
					for (AsciiStringListIterator it = validFactions.begin(); it != validFactions.end(); ++it)
					{
						AsciiString faction = *it;
						AsciiString marker;
						marker.format("INI:Faction%s", faction.str());
					}
				}

				if (lad->validMaps.size() == 0)
				{
					std::list<AsciiString> qmMaps = TheGameSpyConfig->getQMMaps();
					for (std::list<AsciiString>::const_iterator it = qmMaps.begin(); it != qmMaps.end(); ++it)
					{
						AsciiString mapName = *it;

						// check sizes on the maps before allowing them
						const MapMetaData *md = TheMapCache->findMap(mapName);
						if (md && md->m_numPlayers >= lad->playersPerTeam*2)
						{
							lad->validMaps.push_back(mapName);
						}
					}
				}
				return lad;
			}
			else
			{
				// no maps?  don't play on it!
				delete lad;
				lad = NULL;
				return NULL;
			}
		}
		else if ( lad && line.startsWith("Map ") )
		{
			// valid map
			AsciiString mapName = line.str() + 4;
			mapName.trim();
			if (!mapName.isEmpty())
			{
				mapName.format("%s\\%s\\%s.map", ((Rva00300489 *)TheMapCache)->Rva00300489::rva00300489().str(), mapName.str(), mapName.str());
				mapName = TheGameState->portableMapPathToRealMapPath(TheGameState->realMapPathToPortableMapPath(mapName));
				mapName.toLower();
				std::list<AsciiString> qmMaps = TheGameSpyConfig->getQMMaps();
				if (std::find(qmMaps.begin(), qmMaps.end(), mapName) != qmMaps.end())
				{
					// check sizes on the maps before allowing them
					const MapMetaData *md = TheMapCache->findMap(mapName);
					if (md && md->m_numPlayers >= lad->playersPerTeam*2)
						lad->validMaps.push_back(mapName);
				}
			}
		}
		else
		{
			// bad ladder - kill it
			delete lad;
			lad = NULL;
		}
	}

	if (lad)
	{
		delete lad;
		lad = NULL;
	}
	return NULL;
}

