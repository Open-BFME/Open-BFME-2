// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
//
// W3DTerrainLogic::reset, retail 0x00062B44..0x00062B75 (49 bytes, ends in a
// tail jump). Zero Hour's W3DTerrainLogic.cpp body unchanged: the base reset
// (rowed TerrainLogic::reset 0x00283567), the map extents cleared, the
// height range back to 0..1, then WorldHeightMap::freeListOfMapObjects
// (rowed 0x000ABD70 under an address-derived name).
//
// It lives apart from W3DTerrainLogic.cpp because that unit takes the class
// layout from the Zero Hour headers, where m_mapDX/m_mapDY sit at +0x0C/+0x10
// and m_mapMinZ/m_mapMaxZ at +0x53C/+0x540; BFME 2's are +0x18/+0x1C and
// +0x1918/+0x191C (also written by the sibling init 0x00062B17).

#include "../../../../GameEngine/Include/GameLogic/TerrainLogic.h"

// reset overrides the SubsystemInterface slot, so this is the +4 subobject: retail's
// +0x18/+0x1C/+0x1918/+0x191C displacements are full-object +0x1C/+0x20/+0x191C/+0x1920.
class W3DTerrainLogic : public TerrainLogic
{
public:
	virtual void reset();

private:
	float m_mapMinZ;					// +0x191C
	float m_mapMaxZ;					// +0x1920
};

void Rva000ABD70Clear();

void W3DTerrainLogic::reset( void )
{
	TerrainLogic::reset();
	field1C = 0;
	field20 = 0;
	m_mapMinZ = 0;
	m_mapMaxZ = 1;
	Rva000ABD70Clear();
}
