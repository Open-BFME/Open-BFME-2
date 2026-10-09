// cl: /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Native [00063153,00063318),453B, RET16. BFME 2 W3DTerrainLogic::loadMap; the
// ZH W3DTerrainLogic::loadMap (W3DTerrainLogic.cpp) is the semantic guide:
// bail without TheMapCache, copy the name minus its extension, build a
// WorldHeightMap from the stream, record the extents and the height range
// (MAP_HEIGHT_SCALE 0.0390625), release it and chain to TerrainLogic::loadMap,
// then apply the global time of day. BFME 2 differences from retail: the
// stream is an argument (rewound through its slot +0x08), the height map
// constructor 0x000B0C38 takes three ints from +0x54/+0x58/+0x5C, the map's
// +0x14 vector is copied to +0x30 and +0x3C is cleared. Extents +0x1C/+0x20,
// height range +0x191C/+0x1920.
#include <string.h>
#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;

#define _MAX_PATH 260
#define MAP_HEIGHT_SCALE (10.0f / 256.0f)

struct BfmePod8 { int a[2]; };

namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector
{
public:
	vector<T, A> &operator=(const vector<T, A> &x);

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class ChunkInputStream
{
public:
	virtual Int read(void *pData, Int numBytes) = 0;
	virtual unsigned int tell(void) = 0;
	virtual Bool absoluteSeek(unsigned int pos) = 0;
};

class MapCache;
extern MapCache *TheMapCache;

enum TimeOfDay { TIME_OF_DAY_INVALID = 0 };

class GlobalData
{
public:
	Bool setTimeOfDay(TimeOfDay tod);

	unsigned char m_pad00[0x134];
	TimeOfDay m_timeOfDay;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

template<int N> class GameClientSlots : public GameClientSlots<N-1> { public: virtual void unusedSlot(GameClientSlots<N> *); };
template<> class GameClientSlots<0> {};

class GameClient : public GameClientSlots<30>
{
public:
	virtual void setTimeOfDay(TimeOfDay tod);	// slot +0x78
};

extern GameClient *TheGameClient;

class BoundedShortGrid
{
public:
	short rva00062A58(Int x, Int y);
};

class WorldHeightMap
{
public:
	WorldHeightMap(ChunkInputStream *strm, Int a, Int b, Int c);
	virtual void Delete_This();

	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }

	Int m_numRefs;
	Int m_width;
	Int m_height;
	Int m_pad10;
	_STL::vector<BfmePod8> m_objectLayers;
	unsigned char m_pad20[0x120F0 - 0x20];
};

class TerrainLogic
{
public:
	virtual Bool loadMap(const AsciiString &filename, ChunkInputStream *strm, Bool query, Bool b);
	Int get54() const { return m_54; }
	Int get58() const { return m_58; }
	Int get5C() const { return m_5C; }

protected:
	unsigned char m_pad04[0x1C - 0x04];
	Int m_mapDX;
	Int m_mapDY;
	unsigned char m_pad24[0x30 - 0x24];
	_STL::vector<BfmePod8> m_objectLayers;
	Int m_3C;
	unsigned char m_pad40[0x54 - 0x40];
	Int m_54;
	Int m_58;
	Int m_5C;
	unsigned char m_pad60[0x191C - 0x60];
	Real m_minHeight;
	Real m_maxHeight;
};

class W3DTerrainLogic : public TerrainLogic
{
public:
	virtual Bool loadMap(const AsciiString &filename, ChunkInputStream *strm, Bool query, Bool b);
};

Bool W3DTerrainLogic::loadMap(const AsciiString &filename, ChunkInputStream *strm, Bool query, Bool b)
{
	if (!TheMapCache)
		return false;

	char tempBuf[_MAX_PATH];
	char filenameBuf[_MAX_PATH];
	strcpy(tempBuf, filename.str());
	Int length = strlen(tempBuf);
	if (length >= 4) {
		memset(filenameBuf, '\0', _MAX_PATH);
		strncpy(filenameBuf, tempBuf, length - 4);
	}

	strm->absoluteSeek(0);
	WorldHeightMap *terrainHeightMap = new WorldHeightMap(strm, get54(), get58(), get5C());
	if (terrainHeightMap) {
		m_mapDX = terrainHeightMap->getXExtent();
		m_mapDY = terrainHeightMap->getYExtent();
		m_objectLayers = terrainHeightMap->m_objectLayers;
		m_3C = 0;

		Int minHeight = 0xffff;
		Int maxHeight = 0;
		for (Int j = 0; j < m_mapDY; j++) {
			for (Int i = 0; i < m_mapDX; i++) {
				Int height = terrainHeightMap->getHeight(i, j);
				if (height < minHeight)
					minHeight = height;
				if (maxHeight < height)
					maxHeight = height;
			}
		}
		m_minHeight = minHeight * MAP_HEIGHT_SCALE;
		m_maxHeight = maxHeight * MAP_HEIGHT_SCALE;
		terrainHeightMap->Release_Ref();

		if (TerrainLogic::loadMap(filename, strm, query, b)) {
			if (TheGlobalData->setTimeOfDay(TheGlobalData->m_timeOfDay))
				TheGameClient->setTimeOfDay(TheGlobalData->m_timeOfDay);
			return true;
		}
	}
	return false;
}
