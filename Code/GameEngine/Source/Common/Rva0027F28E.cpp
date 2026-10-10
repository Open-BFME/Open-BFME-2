// cl: /O1 /MD /Oy-
// ?rva0027F28E@TerrainLogic@@QAEXPBUCoord3D@@MH@Z retail 0x0027F28E (36
// bytes ret 0xC). Both callers (0x004C49E2 in TaintSpecialPower 0x004C49AE
// and 0x004C3B4B in the ElvenWood sibling) load TheTerrainLogic into ecx
// and the WorldBuilder twin 0x00C47E30 takes ecx as this: a TerrainLogic
// member (it passes this through untouched). The first argument is the
// caller's location pointer. Forwards (pos radius &copy-of-arg false 0) to
// the grid query 0x0027E4F3 on its own this: that body reads ECX as its
// owner, so it is a member call, not the stdcall it was first spelled as.
struct Coord3D;
class Rva0027D347;

class Rva0027E4F3
{
public:
	void rva0027E4F3(Coord3D *center, float radius, Rva0027D347 *out, bool flag, int mode);
};

class TerrainLogic
{
public:
	void rva0027F28E(const Coord3D *pos, float radius, int arg);
};

void TerrainLogic::rva0027F28E(const Coord3D *pos, float radius, int arg)
{
	int d = arg;
	((Rva0027E4F3 *)this)->rva0027E4F3((Coord3D *)pos, radius, (Rva0027D347 *)&d, false, 0);
}
