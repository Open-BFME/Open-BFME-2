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

class TerrainLogic
{
public:
	virtual void reset();				// 0x00283567

private:
	unsigned char m_pad04[0x18 - 0x04];

protected:
	int m_mapDX;						// +0x18
	int m_mapDY;						// +0x1C
};

class W3DTerrainLogic : public TerrainLogic
{
public:
	virtual void reset();

private:
	unsigned char m_pad20[0x1918 - 0x20];
	float m_mapMinZ;					// +0x1918
	float m_mapMaxZ;					// +0x191C
};

// WorldHeightMap::freeListOfMapObjects, rowed under this name.
void Rva000ABD70Clear();

void W3DTerrainLogic::reset( void )
{
	TerrainLogic::reset();
	m_mapDX = 0;
	m_mapDY = 0;
	m_mapMinZ = 0;
	m_mapMaxZ = 1;
	Rva000ABD70Clear();
}
