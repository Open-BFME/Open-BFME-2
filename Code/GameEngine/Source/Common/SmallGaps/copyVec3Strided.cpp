// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/SmallGaps/copyVec3Strided.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?copyVec3Strided@@YAXPAURva0090FB60Vec3@@HPBU1@H@Z 0x00177C7B (45B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// ?copyVec3Strided@@YAXPAURva0090FB60Vec3@@HPBU1@H@Z
struct Rva0090FB60Vec3 { float x; float y; float z; };
void copyVec3Strided(Rva0090FB60Vec3* dst, int stride, const Rva0090FB60Vec3* src, int count)
{
	for (; count; --count) {
		dst->x = src->x; dst->y = src->y; dst->z = src->z;
		++src;
		dst = (Rva0090FB60Vec3*)((char*)dst + stride);
	}
}
