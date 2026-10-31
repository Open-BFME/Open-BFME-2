// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva000E1185@Rva000E3B41@@QAEXXZ, retail 0x000E1185 (236 bytes): the
// On_Frame_Update slot of the tiled terrain render object whose update-list
// override is rowed as Rva000E3B41::rva000E3CE1 (FlatHeightMapUpdateCenter.cpp),
// next to the RenderObjClass Add/Remove slots in table 0x007CE7BC. Zero Hour's
// FlatHeightMapRenderObjClass::On_Frame_Update with BFME 2's budget: nothing
// while the byte 0x00DFE7A8 is set; else the base frame update (the folded
// empty body 0x000B3FD0) and the update state (+0x3934): idle returns, moving
// becomes "moving 2" (3), state 2 updates one tile texture and state 3 two,
// any camera move (+0x38C0) up to 99; the 0xD4-byte W3DTerrainBackground tiles
// (+0x3888, width +0x3890 by height +0x3894) are walked column by column, each
// successful updateTexture (rowed 0x001125BE) spends one, and every tile
// visited runs 0x00115DD2. A budget left over returns the state to idle; the
// camera-moved flag is cleared. Names are address-derived.
typedef int Int;
typedef bool Bool;

extern unsigned char g_00DFE7A8;

class RenderInfoClass;
namespace FXShader { class RenderingMethod; }
struct IRegion2D;
class WorldHeightMap;
class W3DTerrainBackground
{
public:
	void rva0011580A(RenderInfoClass&,bool,FXShader::RenderingMethod*);
	void doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, bool doTextures, bool flag);
	bool updateTexture(void);
	void rva00115DD2();
	char m_pad00[0xD4];
};

// 0x000B3FD0 is the one-byte empty body the toolchain folds many empties into.
class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

class Rva000E3B41
{
public:
	void rva000E1185();

private:
	unsigned char m_pad0000[0x3888];
	W3DTerrainBackground *m_tiles;	// +0x3888
	Int m_numTiles;	// +0x388C
	Int m_tilesWidth;	// +0x3890
	Int m_tilesHeight;	// +0x3894
	unsigned char m_pad3898[0x38C0 - 0x3898];
	Bool m_camerasMoved;	// +0x38C0
	unsigned char m_pad38C1[0x3934 - 0x38C1];
	Int m_updateState;	// +0x3934
};

void Rva000E3B41::rva000E1185()
{
	if (g_00DFE7A8)
		return;

	((Rva000B3FD0 *)this)->rva000B3FD0();

	Int numToUpdate = 0;
	switch (m_updateState)
	{
	case 0:
		return;
	case 1:
		m_updateState = 3;
		return;
	case 2:
		numToUpdate = 1;
		m_updateState = 3;
		break;
	case 3:
		numToUpdate = 2;
		break;
	}
	if (m_camerasMoved)
		numToUpdate = 99;
	if (numToUpdate > 0)
	{
		Int i, j;
		for (i = 0; i < m_tilesWidth; i++)
		{
			for (j = 0; j < m_tilesHeight && numToUpdate >= 1; j++)
			{
				W3DTerrainBackground *tile = m_tiles + j * m_tilesWidth + i;
				if (tile->updateTexture())
					numToUpdate--;
				tile->rva00115DD2();
			}
		}
		if (numToUpdate >= 1)
			m_updateState = 0;
	}
	m_camerasMoved = false;
}
