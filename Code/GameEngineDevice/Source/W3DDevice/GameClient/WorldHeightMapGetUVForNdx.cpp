// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// WorldHeightMap::getUVForNdx, retail AC2F6..AC40D (279 bytes).
// Semantic donor: BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d,
// game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp.
// Retail independently proves the signed-short index, table+B0,
// tile coordinate pair+2AB8, height+120D4, constants64/2048 and output order.
// Initializer B08F7 independently clears 4096 source slots+B0 paired with
// the 4096 edge slots+40B0. The untouched interior stays opaque.

struct TilePosition { int x,y; };
struct BfmeTileDataLocation { char pad[0x2ab8]; TilePosition m_tileLocationInTexture; };
struct BfmeUVLayout { char pad[0xb0]; BfmeTileDataLocation *sourceTiles[4096]; char pad1[0x120d4-0xb0-4096*4]; int terrainTexHeight; };
class WorldHeightMap { public: void getUVForNdx(int,float*,float*,float*,float*,bool); };
void WorldHeightMap::getUVForNdx(int tileNdx, float *minU, float *minV, float *maxU, float*maxV, bool fullTile)
{
	BfmeUVLayout *self = (BfmeUVLayout *)this;

	short baseNdx = tileNdx>>2;
	if (self->sourceTiles[baseNdx] == 0) {
		// Missing texture.
		*minU = *minV = *maxU = *maxV = 0.0f;
		return;
	}
	TilePosition pos = self->sourceTiles[baseNdx]->m_tileLocationInTexture;
	*minU = pos.x;
	*minV = pos.y;
	*maxU = *minU+64; 
	*maxV = *minV+64;
	*minU/=2048;
	*minV/=self->terrainTexHeight;
	*maxU/=2048;
	*maxV/=self->terrainTexHeight;
	if (!fullTile) {
		// Tiles are 64x64 pixels, height grids map to 32x32. 
		// So get the proper quadrant of the tile.
		float midX = (*minU+*maxU)/2;
		float midY = (*minV+*maxV)/2;
		if (tileNdx&2) {		// y's are flipped.
			*maxV = midY;
		} else {
			*minV = midY;
		}
		if (tileNdx&1) {
			*minU = midX;
		} else {
			*maxU = midX;
		}
	}
}

