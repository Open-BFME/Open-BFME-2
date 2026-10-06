// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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
#include "ascii_string.h"

#define NULL 0

class File
{
public:
	virtual ~File();
	virtual bool open(const char *filename, int access);
	virtual void close();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access = 0, int bufferSize = 0);
};
extern FileSystem *TheFileSystem;

class MapMetaData
{
public:
	char m_unrecovered00[0x25];
	bool m_bfme25;
	bool m_bfme26;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};
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
static inline void concatChar(AsciiString &s, char c)
{
	((StringBase<char> *)&s)->concat(&c, 1);
}

class GameInfo
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual bool amIHost() const;
	void setMap(AsciiString mapName);

private:
	char m_unrecovered04[0x0C];
	bool m_inGame;
	char m_unrecovered11[0x2F];
	AsciiString m_mapName;
	unsigned int m_mapCRC;
	unsigned int m_mapSize;
	int m_mapMask;
};

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
			path.concat("tga");
			File *fp = TheFileSystem->openFile(path.str());
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
				while (mapName.find('\\') != NULL)
				{
					if (newMapName.getLength() > 0)
					{
						concatChar(newMapName, '/');
					}
					newMapName.concat(token);
					mapName.nextToken(&token, "\\/");
				}
			}
			newMapName.concat("/map.ini");
			fp = TheFileSystem->openFile(newMapName.str());
			if (fp)
			{
				m_mapMask |= 4;
				fp->close();
				fp = NULL;
			}

			path = GetStrFileFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 8;
				fp->close();
				fp = NULL;
			}

			path = GetSoloINIFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 16;
				fp->close();
				fp = NULL;
			}

			path = GetAssetUsageFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 32;
				fp->close();
				fp = NULL;
			}

			path = GetReadmeFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 64;
				fp->close();
				fp = NULL;
			}

			path = GetArtPreviewFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 128;
				fp->close();
				fp = NULL;
			}

			path = GetPicPreviewFromMap(m_mapName);
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 256;
				fp->close();
				fp = NULL;
			}

			if (mapData->m_bfme25 || mapData->m_bfme26)
				m_mapMask |= 512;
		}
		else
		{
			m_mapMask = 0;
		}
	}
}
