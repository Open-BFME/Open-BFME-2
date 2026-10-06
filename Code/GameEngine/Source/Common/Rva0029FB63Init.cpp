// cl: /DNDEBUG /MD
// ??0Rva0029FB63@@QAE@PBHABURva0029E067@@@Z @0x0029FB63 29B
// Init ctor: *this = *arg1 plus m_04 copy via rowed 0x0029E067; returns this.
// Caller 0x002A3FF3; prev init; unblocks 0x002A3FAF.
#include <new>

struct Rva0029E067
{
	unsigned char m_data[0x34];
	Rva0029E067(const Rva0029E067 &src) throw();
};

struct Rva0029FB63
{
	int m_00;
	Rva0029E067 m_04;
	Rva0029FB63(const int *a, const Rva0029E067 &b);
};

Rva0029FB63::Rva0029FB63(const int *a, const Rva0029E067 &b) : m_00(*a), m_04(b)
{
}
