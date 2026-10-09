// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?loadMap@@YA_NVAsciiString@@PAX@Z
// retail 0x00302F2B..0x00303186 (604 bytes) cdecl.
//
// MapUtil.cpp's loadMap, BFME 2 form (one caller 0x00304F0E, which passes a
// local map record). Zero Hour's body: strip the extension into a scratch
// buffer, open the map through the cached file stream (rowed Rva00240000
// constructor 0x00240000, open 0x00308050, destructor 0x0023F4F0), build
// the DataChunkInput over it, allocate the waypoint map (global
// m_waypoints, its base map constructor folded at 0x00413727) and register
// the "HeightMapData", "WorldInfo" and "ObjectsList" parsers
// (ParseSizeOnlyInChunk 0x00302F1B, ParseWorldDictDataChunk 0x00300075,
// ParseObjectsDataChunk 0x00302B06), throwing ERROR_CORRUPT_FILE_FORMAT
// (0xDEAD0005) when the parse fails, then derive m_mapDX/m_mapDY from the
// width, height and border. BFME 2 adds the "MPPositionList" parser binding
// (rowed Rva00300419 constructor 0x00300419) that fills the record's +0x54
// positions; its base destructor (vftable 0x007C9574) unregisters through
// DataChunkInput's 0x00306D7B.
#include <string.h>
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

#define _MAX_PATH 260

enum ErrorCode
{
	ERROR_CORRUPT_FILE_FORMAT = 0xDEAD0005
};

class ChunkInputStream;
struct DataChunkInfo;
class UserParser;

// The cached file stream (CachedFileInputStream).
class Rva00240000
{
public:
	Rva00240000() throw();				// 0x00240000 (retail enters no EH state for asciiFile before it)
	~Rva00240000();					// 0x0023F4F0
	Bool rva00308050(AsciiString filename);		// 0x00308050, open
private:
	unsigned char m_data[0x20];
};

class DataChunkInput
{
public:
	DataChunkInput(ChunkInputStream *stream);	// 0x00307316
	~DataChunkInput();				// 0x00306F01
	UserParser *registerParser(const AsciiString &label, const AsciiString &parentLabel,
		Bool (*parser)(DataChunkInput &file, DataChunkInfo *info, void *userData), void *userData = 0);	// 0x00307779
	Bool parse(void *userData);			// 0x00307AC0
private:
	unsigned char m_data[0x28];
};

Bool ParseSizeOnlyInChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);	// 0x00302F1B
Bool ParseWorldDictDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);	// 0x00300075
Bool ParseObjectsDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);	// 0x00302B06

// DataChunkInput's parser unregistration, rowed under its address-era spelling.
class Q1Forwardee0000871A
{
public:
	void handle(int token);				// 0x00306D7B
};

class BfmeParserRegistryVE;

class BfmeParserBindingBaseVE
{
public:
	virtual ~BfmeParserBindingBaseVE() { m_registry->handle(m_token); }
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();

private:
	Q1Forwardee0000871A *m_registry;	// +0x04, the DataChunkInput
	int m_token;				// +0x08
};

// The "MPPositionList" binding.
class Rva00300419 : public BfmeParserBindingBaseVE
{
public:
	Rva00300419(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);	// 0x00300419
private:
	void *m_owner;
};

// The waypoint map: its base map constructor is the folded 0x00413727.
class Rva0029B63A
{
public:
	Rva0029B63A();					// 0x00413727
private:
	unsigned char m_tree[0x0C];
};
class WaypointMap : public Rva0029B63A
{
public:
	WaypointMap() : m_0C(0) {}
private:
	Int m_0C;					// +0x0C
};

extern "C" WaypointMap *m_waypoints;
extern "C" Int m_width;
extern "C" Int m_height;
extern "C" Int m_borderSize;
extern "C" Int m_mapDX;
extern "C" Int m_mapDY;

Bool loadMap(AsciiString filename, void *mapInfo)
{
	char tempBuf[_MAX_PATH];
	char filenameBuf[_MAX_PATH];
	AsciiString asciiFile;
	int length = 0;

	strcpy(tempBuf, filename.str());

	length = strlen(tempBuf);
	if (length >= 4)
	{
		memset(filenameBuf, '\0', _MAX_PATH);
		strncpy(filenameBuf, tempBuf, length - 4);
	}

	Rva00240000 fileStrm;

	asciiFile = filename;
	if (!fileStrm.rva00308050(asciiFile))
		return false;

	DataChunkInput file((ChunkInputStream *)&fileStrm);

	m_waypoints = new WaypointMap;

	file.registerParser(AsciiString("HeightMapData"), AsciiString::TheEmptyString, ParseSizeOnlyInChunk);
	file.registerParser(AsciiString("WorldInfo"), AsciiString::TheEmptyString, ParseWorldDictDataChunk);
	file.registerParser(AsciiString("ObjectsList"), AsciiString::TheEmptyString, ParseObjectsDataChunk);
	Rva00300419 positions((char *)mapInfo + 0x54, (BfmeParserRegistryVE *)&file, 0);
	if (!file.parse(0))
		throw ERROR_CORRUPT_FILE_FORMAT;

	m_mapDX = m_width - 2 * m_borderSize;
	m_mapDY = m_height - 2 * m_borderSize;

	return true;
}
