// ?hasRGBDataForWidth@TileData@@QAE_NH@Z
// cl: /O1 /G7 /arch:SSE /MD
//
// 0x001117B4 47B TileData::hasRGBDataForWidth (Zero Hour WorldHeightMap's
// TILE_PIXEL_EXTENT mip ladder 64..1). Both retail callers (0x000AC8F1 in
// the raw-tile loader 0x000AC88E and 0x000AEDFA in 0x000AED2E) load the
// TileData into ecx: a thiscall member that ignores this (formerly spelled
// as the free stdcall ?Rva001117B4IsPow2@@YGEH@Z). Retail keeps a single
// `mov al,1` true block at +9; the first test (cmp 0x40) falls into it and
// every later test branches back to it.
class TileData
{
public:
	bool hasRGBDataForWidth(int width);
};

bool TileData::hasRGBDataForWidth(int v)
{
	bool r;
	if (v == 0x40) {
		r = 1;
	} else if (v == 0x20) {
		r = 1;
	} else if (v == 0x10) {
		r = 1;
	} else if (v == 8) {
		r = 1;
	} else if (v == 4) {
		r = 1;
	} else if (v == 2) {
		r = 1;
	} else {
		r = (v == 1);
	}
	return r;
}
