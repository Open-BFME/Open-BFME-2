// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// GameInfo::setMap, retail 0x00400126, 1030 bytes.
// Derived from GameInfo.cpp, Copyright 2025 Electronic Arts Inc., GPL-3.0-or-later.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameNetwork/GameInfoSetMap.cpp
// (matched there at 0x00620510). Carried from the donor: the method identity,
// the map-mask probe sequence and the two map-metadata predicates.
// Target facts read from this body: m_inGame at +0x10, m_mapName at +0x40,
// m_mapMask at +0x4C; amIHost at vtable +0x30; File::close at +0x08;
// FileSystem::openFile(name, 0, 0); the metadata predicates at +0x25/+0x26.
#include <cstddef>
#include "ascii_string.h"

#include "../../Include/Common/File.h"

#include "../../Include/Common/FileSystem.h"

#include "unicode_string.h"
#include "../../Include/GameClient/MapMetaData.h"

#include "../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;

AsciiString GetStrFileFromMap(AsciiString mapName);
AsciiString GetSoloINIFromMap(AsciiString mapName);
AsciiString GetAssetUsageFromMap(AsciiString mapName);
AsciiString GetReadmeFromMap(AsciiString mapName);
AsciiString GetArtPreviewFromMap(AsciiString mapName);
AsciiString GetPicPreviewFromMap(AsciiString mapName);

// The donor's StringBase<char>::concat(char): the character goes through its
// own one-byte slot (retail's [ebp-0x10]) into concat(text, 1). The canonical
// operator+=(char) shares a slot and leaves the frame four bytes short.
static inline void concatChar(AsciiString &asciiString, char c)
{
	((StringBase<char> *)&asciiString)->concat(&c, 1);
}

#include "../../Include/GameNetwork/GameInfo.h"

class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;

void GameInfo::setMap(AsciiString mapName)
{
	m_mapName = mapName;
	if (m_inGame && amIHost())
	{
		const MapMetaData *mapData = TheMapCache->findMap(mapName);
		if (mapData)
		{
			m_mapMask = 1;
			AsciiString path = mapName;
			path.removeLastChar();
			path.removeLastChar();
			path.removeLastChar();
			reinterpret_cast<StringBase<char> *>(&path)->concat("tga");
			File *fp = TheFileSystem->openFile(path.str(), 0);
			if (fp)
			{
				m_mapMask |= 2;
				fp->close();
				fp = NULL;
			}

			AsciiString newMapName;
			if (mapName.getLength() > 0)
			{
				AsciiString token;
				mapName.nextToken(&token, "\\/");
				// add all the tokens except the last one.
				// that way we don't add the filename, just the
				// directory name, we can do this since the filename
				// is just the directory name with the file extention
				// added onto it.
				while (((const StringBase<char> *)&mapName)->find('\\') != NULL)
				{
					if (newMapName.getLength() > 0)
					{
						concatChar(newMapName, '/');
					}
					newMapName.concat(token);
					mapName.nextToken(&token, "\\/");
				}
			}
			reinterpret_cast<StringBase<char> *>(&newMapName)->concat("/map.ini");
			fp = TheFileSystem->openFile(newMapName.str(), 0);
			if (fp)
			{
				m_mapMask |= 4;
				fp->close();
				fp = NULL;
			}

			path = GetStrFileFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str(), 0);
			if (fp)
			{
				m_mapMask |= 8;
				fp->close();
				fp = NULL;
			}

			path = GetSoloINIFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str(), 0);
			if (fp)
			{
				m_mapMask |= 16;
				fp->close();
				fp = NULL;
			}

			path = GetAssetUsageFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str(), 0);
			if (fp)
			{
				m_mapMask |= 32;
				fp->close();
				fp = NULL;
			}

			path = GetReadmeFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str(), 0);
			if (fp)
			{
				m_mapMask |= 64;
				fp->close();
				fp = NULL;
			}

			path = GetArtPreviewFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str(), 0);
			if (fp)
			{
				m_mapMask |= 128;
				fp->close();
				fp = NULL;
			}

			path = GetPicPreviewFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str(), 0);
			if (fp)
			{
				m_mapMask |= 256;
				fp->close();
				fp = NULL;
			}

			if (mapData->m_isScenarioMP || mapData->m_isOfficial)
				m_mapMask |= 512;
		}
		else
		{
			m_mapMask = 0;
		}
	}
}

// Retail call sequence at 0x00521C5A: set the skirmish map name, look it up,
// then copy metadata offsets +0x2c and +0x28 into GameInfo when found. The
// callback's original identity is unproven; this address-derived name records
// only the behavior and direct target evidence.
bool __stdcall rva00521C5A(const AsciiString &mapName)
{
	(*(GameInfo * *)&TheSkirmishGameInfo)->setMap(mapName);
	const MapMetaData *mapData = TheMapCache->findMap(mapName);
	if (mapData) {
		(*(GameInfo * *)&TheSkirmishGameInfo)->setMapCRC(*(const unsigned int *)((const char *)mapData + 0x2C));
		(*(GameInfo * *)&TheSkirmishGameInfo)->setMapSize(*(const unsigned int *)((const char *)mapData + 0x28));
	}
	return true;
}
