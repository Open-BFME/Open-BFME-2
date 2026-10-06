// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// TerrainTypeCollection::newTerrain @0x0031816C (149B): Zero Hour
// TerrainTypes.cpp's body. A new 0x30-byte TerrainType (its ctor 0x00317F6F,
// vtable 0x0080C66C) is filled from the "DefaultTerrain" entry through the
// rowed findTerrain 0x00317D18 and the type's operator= 0x0031804D, named
// through 0x00317C34 (the +0x04 AsciiString findTerrain compares) and pushed
// on the list head at this+0x0C through the +0x20 link findTerrain walks.
// BFME allocates with plain operator new where ZH used newInstance(). The
// only caller is INI::parseTerrainDefinition 0x00200A65, after findTerrain
// misses, as in ZH INITerrain.cpp.
#include "ascii_string.h"

class TerrainType
{
public:
	TerrainType();
	TerrainType &operator=(const TerrainType &that);
	void friend_setName(AsciiString name);
	void friend_setNext(TerrainType *next) { m_next = next; }

private:
	char m_pad00[0x20];
	TerrainType *m_next;   // +0x20
	char m_pad24[0x0C];
};

class TerrainTypeCollection
{
public:
	TerrainType *findTerrain(AsciiString name);
	TerrainType *newTerrain(AsciiString name);

private:
	char m_pad00[0x0C];
	TerrainType *m_terrainList;   // +0x0C
};

TerrainType *TerrainTypeCollection::newTerrain(AsciiString name)
{
	TerrainType *terrain = 0;

	terrain = new TerrainType;

	TerrainType *defaultTerrain = findTerrain(AsciiString("DefaultTerrain"));
	if (defaultTerrain)
		*terrain = *defaultTerrain;

	terrain->friend_setName(name);

	terrain->friend_setNext(m_terrainList);
	m_terrainList = terrain;

	return terrain;
}
