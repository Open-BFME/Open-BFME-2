// ?rva0035A61F@TerrainResourceManager@@QAEXPAIHHH@Z
// partial score=0.95 date=2026-10-10
// ?rva0035A61F@TerrainResourceManager@@QAEXPAIHHH@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0035A61F@TerrainResourceManager@@QAEXPAIHHH@Z
// Retail 0x0035A61F..0x0035A8D7 (696 bytes, ret 0x10).
// Fades a terrain-resource overlay colour by how claimable the half-
// resolution cell around (x y) is for the given claimant: an unclaimable
// centre cell clears the colour; otherwise the alpha weight starts at 12, an
// unclaimable +x neighbour sets it to 8, the other three edge neighbours take
// 4 each, the diagonals 2 (+x+y / -x-y) or 3 (-x+y / +x-y) and the cells two
// steps away 1 each. A weight <= 0 clears the colour; below 12 the colour's
// alpha byte is scaled by weight/12.
// Evidence (target): thirteen calls to the pinned 0x0035A4A3
// (WorldBuilder's TerrainResourceManager::isCellClaimable, as named in
// TerrainResourceManagerRva0035AA43.cpp) with the same claimant argument and
// zero/false fillers; float constants 12/8/4/2/3/1 and 1/12 read from the
// image; __ftol2 for the scaled alpha. WorldBuilder 0x00E61580 (unnamed) has
// the same calls. The method and colour view names are address-derived.
// NEAR (banked, ~0.95; 697 vs 696 bytes): everything after the first call
// matches instruction for instruction (shifted one byte); only the prologue
// is scheduled differently: retail keeps this in ecx until the first call and
// halves y in its stack slot (sar [ebp-4],1), this source copies this to edi
// first and halves y in ecx. Tried: assignment inside the call, split
// declarations, direct calls, /G5 /G6 /G7 /arch:SSE2. The early clear must
// be the then-branch of an if/else (not an early return) and the alpha
// must go through a float local, or the clear block and fimul differ.

class Rva0035A4A3
{
public:
	bool rva0035A4A3(int x, int y, int c, int zero, bool flag, int d);
};

typedef unsigned int Rva0035A61FColor;

class TerrainResourceManager
{
public:
	void rva0035A61F(Rva0035A61FColor *color, int x, int y, int claimant);
private:
	__forceinline bool isClaimable(int cx, int cy, int claimant)
	{
		return ((Rva0035A4A3 *)this)->rva0035A4A3(cx, cy, 0, 0, false, claimant);
	}
};

void TerrainResourceManager::rva0035A61F(Rva0035A61FColor *color, int x, int y, int claimant)
{
	int cy = y / 2;
	int cx = x / 2;
	if (!isClaimable(cx, cy, claimant))
	{
		*color = 0;
	}
	else
	{
	float weight = 12.0f;
	int xp = (x + 1) / 2;
	if (!isClaimable(xp, cy, claimant))
		weight = 8.0f;
	int yp = (y + 1) / 2;
	if (!isClaimable(cx, yp, claimant))
		weight -= 4.0f;
	int xm = (x - 1) / 2;
	if (!isClaimable(xm, cy, claimant))
		weight -= 4.0f;
	int ym = (y - 1) / 2;
	if (!isClaimable(cx, ym, claimant))
		weight -= 4.0f;
	if (!isClaimable(xp, yp, claimant))
		weight -= 2.0f;
	if (!isClaimable(xm, ym, claimant))
		weight -= 2.0f;
	if (!isClaimable(xm, yp, claimant))
		weight -= 3.0f;
	if (!isClaimable(xp, ym, claimant))
		weight -= 3.0f;
	if (!isClaimable((x + 2) / 2, cy, claimant))
		weight -= 1.0f;
	if (!isClaimable((x - 2) / 2, cy, claimant))
		weight -= 1.0f;
	if (!isClaimable(cx, (y + 2) / 2, claimant))
		weight -= 1.0f;
	if (!isClaimable(cx, (y - 2) / 2, claimant))
		weight -= 1.0f;
	if (weight <= 0.0f)
	{
		*color = 0;
	}
	else if (weight < 12.0f)
	{
		float alpha = (float)((unsigned char *)color)[3];
		*color = (*color & 0x00FFFFFF) | ((int)(alpha * (weight / 12.0f)) << 24);
	}
}
}
