// cl: /O1 /DNDEBUG /MD
//
// W3DRadar::refreshTerrain, retail 0x000500E5 (27 bytes): slot 4 of vtable
// 0x00BC4E34, installed by the W3DRadar constructor (slot 10 is the rowed
// W3DRadar::clearShroud; slot 1, the base Radar::loadPostProcess, calls this
// slot with TheTerrainLogic). Ported from Zero Hour's GameEngineDevice/
// Source/W3DDevice/Common/System/W3DRadar.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): extend the base, then rebuild the
// terrain texture.
// Callees: Radar::refreshTerrain is the rowed opaque 0x002D7AA6 (it clears
// the queued refresh frame +0x1460), pinned by its Zero Hour name;
// W3DRadar::buildTerrainTexture is pinned at 0x0004FAFF.
class TerrainLogic;

class Radar
{
public:
	virtual void refreshTerrain(TerrainLogic *terrain);
};

class W3DRadar : public Radar
{
public:
	virtual void refreshTerrain(TerrainLogic *terrain);
protected:
	void buildTerrainTexture(TerrainLogic *terrain);
};

//-------------------------------------------------------------------------------------------------
void W3DRadar::refreshTerrain( TerrainLogic *terrain )
{

	// extend base class
	Radar::refreshTerrain( terrain );

	// build terrain texture
	buildTerrainTexture( terrain );

}
