// cl: /MD
// ??1Rva0051719B@@QAE@XZ @0x0051719B 8B
// Dtor tail-jmp to rowed ??1Rva00416088@@QAE@XZ at 0x00416088; add ecx,4 then jmp.
// Member Rva00416088 at +4 with 4B pad at +0; empty dtor lets the compiler tail-call.
struct Rva00416088
{
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned int m_10;
	~Rva00416088();
};

struct Rva0051719B
{
	unsigned int m_00;
	Rva00416088 m_04;
	~Rva0051719B();
};

Rva0051719B::~Rva0051719B()
{
}
