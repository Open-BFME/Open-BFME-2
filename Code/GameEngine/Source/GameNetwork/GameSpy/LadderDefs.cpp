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
// LadderList's constructor 0x0054E546 (592B), loadLocalLadders 0x0054E426
// (288B) and checkLadder 0x0054E2FB (299B) are the Generals bodies too, over
// BFME 2 views of FileSystem (three-argument openFile, no-case FilenameList),
// File (close/read in slots 2/3), GlobalData (user-data path by value) and the
// GameSpy config (getLeftoverConfig in slot 12).
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
// The constructor appends each line's newline through the (text, length)
// concat with a one-character local, inline.
template<> inline void StringBase<char>::concat(char c)
{
	concat(&c, 1);
}
// Retail reads the last character inline (null buffer -> 0) on every line.
template<> inline char StringBase<char>::getCharAt(int index) const throw()
{
	return m_data ? m_data->data[index] : 0;
}
// BFME 2's FileSystem: openFile takes a third (buffer) argument, and the
// FilenameList set orders with the shared no-case comparator the ledger names
// (BfmeStringNoCaseLess); Zero Hour's header is replaced for this unit.
#define __FILESYSTEM_H
#define __FILE_H
#define _GLOBALDATA_H_
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
#include <set>
// BFME 2's GlobalData returns the user-data path by value (0x002360DE).
class GlobalData
{
public:
	AsciiString rva002360DE() const;
};
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData*)TheWritableGlobalData)

// BFME 2's File interface: one slot (the deleting dtor) precedes open, so
// close and read are slots 2 and 3; eof stays a plain member (0x006024AC).
class File
{
public:
	enum { READ = 0x01, TEXT = 0x20 };
	virtual void *deletingDtor(unsigned int flags);
	virtual bool open(const char *filename, int access);
	virtual void close();
	virtual int read(void *buffer, int bytes);
	bool eof();
};
struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};
typedef _STL::set<AsciiString, BfmeStringNoCaseLess> FilenameList;
class FileSystem
{
public:
	File *openFile(const char *filename, int access, int bufferSize);
	void getFileListInDirectory(const AsciiString &directory, const AsciiString &searchName, FilenameList &filenameList, bool searchSubdirectories) const;
};
extern FileSystem *TheFileSystem;


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
// (hard-coded America/China/GLA fallback). Retail 0x0054DA41, 2234 bytes.
static LadderInfo *parseLadder(AsciiString raw)
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


// BFME 2's GameSpy config interface has one slot fewer than Zero Hour's ahead
// of getLeftoverConfig: retail reads it from slot 12 (+0x30).
class GameSpyConfigView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual AsciiString getLeftoverConfig();
};

LadderList::LadderList()
{
	AsciiString rawMotd = ((GameSpyConfigView *)TheGameSpyConfig)->getLeftoverConfig();
	AsciiString line;
	Bool inLadders = FALSE;
	Bool inSpecialLadders = FALSE;
	Bool inLadder = FALSE;
	LadderInfo *lad = NULL;
	Int index = 1;
	AsciiString rawLadder;

	while (rawMotd.nextToken(&line, "\n"))
	{
		if (line.getCharAt(line.getLength()-1) == '\r')
			line.removeLastChar();	// there is a trailing '\r'

		line.trim();

		if (line.isEmpty())
			continue;

		if (!inLadders && line.compare("<Ladders>") == 0)
		{
			inLadders = TRUE;
			rawLadder.clear();
		}
		else if (inLadders && line.compare("</Ladders>") == 0)
		{
			inLadders = FALSE;
		}
		else if (!inSpecialLadders && line.compare("<SpecialLadders>") == 0)
		{
			inSpecialLadders = TRUE;
			rawLadder.clear();
		}
		else if (inSpecialLadders && line.compare("</SpecialLadders>") == 0)
		{
			inSpecialLadders = FALSE;
		}
		else if (inLadders || inSpecialLadders)
		{
			if (line.startsWith("<Ladder ") && !inLadder)
			{
				inLadder = TRUE;
				rawLadder.clear();
				rawLadder.concat(line);
				rawLadder.concat('\n');
			}
			else if (line.compare("</Ladder>") == 0 && inLadder)
			{
				inLadder = FALSE;
				rawLadder.concat(line);
				rawLadder.concat('\n');
				if ((lad = parseLadder(rawLadder)) != NULL)
				{
					lad->index = index++;
					if (inLadders)
					{
						m_standardLadders.push_back(lad);
					}
					else
					{
						m_specialLadders.push_back(lad);
					}
				}
				rawLadder.clear();
			}
			else if (inLadder)
			{
				rawLadder.concat(line);
				rawLadder.concat('\n');
			}
		}
	}

	// look for local ladders
	loadLocalLadders();
}

void LadderList::loadLocalLadders( void )
{
	AsciiString dirname;
	dirname.format("%s%s\\Ladders\\", TheGlobalData->rva002360DE().str(), "Online Files");
	FilenameList filenameList;
	TheFileSystem->getFileListInDirectory(dirname, AsciiString("*.ini"), filenameList, TRUE);

	Int index = -1;

	FilenameList::iterator it = filenameList.begin();
	while (it != filenameList.end())
	{
		AsciiString filename = *it;
		filename.toLower();
		checkLadder( filename, index-- );
		++it;
	}
}

void LadderList::checkLadder( AsciiString fname, Int index )
{
	File *fp = TheFileSystem->openFile(fname.str(), File::READ | File::TEXT, 0);
	char buf[1024];
	AsciiString rawData;
	if (fp)
	{
		Int len;
		while (!fp->eof())
		{
			len = fp->read(buf, 1023);
			buf[len] = 0;
			buf[1023] = 0;
			rawData.concat(buf);
		}
		fp->close();
		fp = NULL;
	}

	if (rawData.isEmpty())
		return;

	LadderInfo *li = parseLadder(rawData);
	if (!li)
	{
		return;
	}

	// sanity check
	if (((const StringBase<char> &)li->address).isEmpty())
	{
		delete li;
		return;
	}

	if (!li->port)
	{
		delete li;
		return;
	}

	if (li->validMaps.size() == 0)
	{
		delete li;
		return;
	}

	li->index = index;
	li->validQM = FALSE; // no local ladders in QM
	li->validCustom = FALSE;

	m_localLadders.push_back(li);
}
