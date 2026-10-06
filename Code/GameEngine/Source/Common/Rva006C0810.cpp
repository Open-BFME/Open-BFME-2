// cl: /MD
// ?rva006C0810@Rva006C0810@@QAEXPBURegion3D@@M@Z @ 0x006C0810 8B
// Honest address name: tail jmp loading member at +0x10 then jumping to rowed
// Gen_008812D0::bfmeSetRegion. Same (const Region3D*, float) signature forwards.
// Evidence: mov ecx [ecx+0x10] plus jmp shape, callee row in Bfme5SeventySix.cpp,
// callers at 0x0024406E and 0x00246D81, neighbours 0x006C0800 and 0x006C0820.
// /O2: frameless float-arg tail jmp; /O1 emits fld/fstp plus call.
struct Region3D;
class Gen_008812D0
{
public:
	void bfmeSetRegion(const Region3D *region, float cellSize);
};
class Rva006C0810
{
public:
	void rva006C0810(const Region3D *region, float cellSize);
private:
	char m_pad[0x10];
	Gen_008812D0 *m_ptr;
};
void Rva006C0810::rva006C0810(const Region3D *region, float cellSize)
{
	m_ptr->bfmeSetRegion(region, cellSize);
}
