// cl: /O1 /DNDEBUG /MD /EHsc
// ??1W3DTerrainVisual@@UAE@XZ, retail 0x0009203A..0x00092123 (233 bytes,
// EH): the destructor the scalar deleting destructor ??_GRva009203A calls
// (call at 0x00092126). Zero Hour's W3DTerrainVisual::~W3DTerrainVisual,
// ported from Open-BFME-1's
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualDestructorBfme.cpp
// (reference @ 575ba2b04).
//
// BFME 2 target facts: two vptrs (0x00BC80A0 at +0, 0x00BC8068 at +4) and a
// 0x14-byte base whose destructor is rowed as Rva002DAB18; the terrain
// render object, water object and logic height map sit at +0x14/+0x18/+0x1C.
// The tracks system and shadow manager are deleted through non-virtual views
// of their destructor bodies (pinned 0x00084CEF and 0x0009A500), the
// smudge manager (g_bfmeB991 at 0x00DE612C) through a global ::delete of its
// virtual destructor, and the water global keeps its ledger spelling
// (W3DGCData00DE2000 at 0x00DE2000).

// Rva002DAB18's bases: the Snapshot table 0x00BBB554 (slots 1-3 __purecall)
// and the SubsystemInterface table 0x00C039A0.
class Rva002DAB18Primary
{
public:
	virtual void loadPostProcess() = 0;
};

class Rva002DAB18Secondary
{
public:
	virtual void init() = 0;
private:
	int m_04;
	int m_08;
	int m_0C;
};

class Rva002DAB18 : public Rva002DAB18Primary, public Rva002DAB18Secondary
{
public:
	virtual ~Rva002DAB18();
};

#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"

class BaseHeightMapRenderObjClass : public RefCountClass
{
};

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

class WaterRenderObjClassBase
{
public:
	virtual ~WaterRenderObjClassBase() {}
};

// RefCountClass is the water object's secondary base at +4.
class WaterRenderObjClass : public WaterRenderObjClassBase, public RefCountClass
{
};

class TerrainTracksRenderObjClassSystem;
class W3DShadowManager;

// Non-virtual views of the two pinned destructor bodies (the ledger's
// opaque spellings there are virtual); identities stay address-derived.
class Rva00084CEF
{
public:
	~Rva00084CEF();
};

#include "../../../../GameEngine/Include/Common/Rva009A500.h"

// The shadow manager's destructor 0x0009A500 is rowed virtual as
// Rva009A500; the delete below calls it directly.
class Rva0009A500
{
public:
	__declspec(dllimport) __forceinline ~Rva0009A500()
	{ reinterpret_cast<Rva009A500 *>(this)->Rva009A500::~Rva009A500(); }
};

class BfmeB991
{
public:
	virtual ~BfmeB991();
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;
extern W3DShadowManager *TheW3DShadowManager;
extern BfmeB991 *g_bfmeB991;
extern void *W3DGCData00DE2000;

class W3DTerrainVisual : public Rva002DAB18
{
public:
	virtual ~W3DTerrainVisual();
	// Tables 0x00BC80A0 slot 1 is the empty body 0x000B3FD0 and 0x00BC8068
	// slot 1 the rowed init 0x00091AEA.
	virtual void loadPostProcess() {}
	virtual void init();

private:
	BaseHeightMapRenderObjClass *m_terrainRenderObject;	// +0x14
	WaterRenderObjClass *m_waterRenderObject;		// +0x18
	WorldHeightMap *m_logicHeightMap;			// +0x1C
};

W3DTerrainVisual::~W3DTerrainVisual()
{
	if (TheTerrainRenderObject == m_terrainRenderObject)
		TheTerrainRenderObject = 0;

	if (TheTerrainTracksRenderObjClassSystem) {
		delete reinterpret_cast<Rva00084CEF *>(TheTerrainTracksRenderObjClassSystem);
		TheTerrainTracksRenderObjClassSystem = 0;
	}

	if (TheW3DShadowManager) {
		delete reinterpret_cast<Rva0009A500 *>(TheW3DShadowManager);
		TheW3DShadowManager = 0;
	}

	if (g_bfmeB991) {
		::delete g_bfmeB991;
		g_bfmeB991 = 0;
	}

	if (m_waterRenderObject) {
		m_waterRenderObject->Release_Ref();
		m_waterRenderObject = 0;
	}
	W3DGCData00DE2000 = 0;

	if (m_terrainRenderObject) {
		m_terrainRenderObject->Release_Ref();
		m_terrainRenderObject = 0;
	}

	if (m_logicHeightMap) {
		m_logicHeightMap->Release_Ref();
		m_logicHeightMap = 0;
	}
}
