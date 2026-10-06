// cl: /MD
// ??1Rva0029E00D@@QAE@XZ @0x0029E00D 8B
// Dtor tail-jmp to rowed ??1BfmeStringRecord000B94D2@@QAE@XZ at 0x000B6CF1;
// add ecx,4 then jmp. Member at +4 with 4B pad at +0; empty dtor lets the
// compiler tail-call. Unblocks 0x002A14FA 0x0029E0FE; callers 0x0029E101 etc.
struct BfmeStringRecord000B94D2
{
	~BfmeStringRecord000B94D2();
};

struct Rva0029E00D
{
	unsigned int m_00;
	BfmeStringRecord000B94D2 m_04;
	~Rva0029E00D();
};

Rva0029E00D::~Rva0029E00D()
{
}
