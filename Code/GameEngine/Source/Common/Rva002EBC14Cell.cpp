// cl: /O1 /MD
//
// ?Rva002EBC14Cell@@YAPAUICoord2D@@PAU1@PAXPBUCoord3D@@@Z, retail 0x002EBC14 (32 bytes).
// Free __cdecl (ICoord2D*, void*, const Coord3D*) -> ICoord2D*: odd = IsOdd(p),
// WorldToCell(out, odd, pos), return out. Evidence: retail pushes pos then p,
// calls IsOdd, pops p dead into ecx (ecx never read, so not __thiscall),
// pushes eax/out, calls WorldToCell, reloads out into eax, caller-cleans 0xc.
// Callees: the rowed parity test 0x002EBBFB (Rva002EBBFBIsOdd.cpp, rowed with
// an unsigned char result) and WorldToCell (PathfindShimWorldToCell.cpp).
// Retail passes the parity result straight on with no test/setne, so it is
// a bool here, through the bool spelling pinned at the same address; the
// parity body compiles identically under either result type.
struct ICoord2D;
struct Coord3D;
struct ICoord2D *__cdecl Rva002E7875WorldToCell(struct ICoord2D *out, bool center, const struct Coord3D *pos);
bool __cdecl Rva002EBBFBIsOdd(void *p);

struct ICoord2D *__cdecl Rva002EBC14Cell(struct ICoord2D *out, void *p, const struct Coord3D *pos)
{
	Rva002E7875WorldToCell(out, Rva002EBBFBIsOdd(p), pos);
	return out;
}
