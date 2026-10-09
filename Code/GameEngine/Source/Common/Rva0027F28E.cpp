// cl: /O1 /MD /Oy-
// ?rva0027F28E@TerrainLogic@@QAEXPBUCoord3D@@MH@Z retail 0x0027F28E (36
// bytes ret 0xC). Both callers (0x004C49E2 in TaintSpecialPower 0x004C49AE
// and 0x004C3B4B in the ElvenWood sibling) load TheTerrainLogic into ecx
// and the WorldBuilder twin 0x00C47E30 takes ecx as this: a TerrainLogic
// member (it passes this through untouched). The first argument is the
// caller's location pointer. Forwards (pos radius &copy-of-arg 0 0) to the
// stdcall-spelled 0x0027E4F3.
struct Coord3D;
void __stdcall rva0027E4F3(int a, float b, void *c, int d, int e);

class TerrainLogic
{
public:
	void rva0027F28E(const Coord3D *pos, float radius, int arg);
};

void TerrainLogic::rva0027F28E(const Coord3D *pos, float radius, int arg)
{
	int d = arg;
	rva0027E4F3((int)pos, radius, &d, 0, 0);
}
