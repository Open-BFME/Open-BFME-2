// ?rva004E9B70@Rva004E9B70@@QAEXXZ
// partial score=0.93 date=2026-09-30
// ?rva004E9B70@Rva004E9B70@@QAEXXZ
// partial score=0.93 date=2026-09-30
// cl: /O1 /DNDEBUG /MD
//
// ?rva004E9B70@Rva004E9B70@@QAEXXZ, retail 0x004E9B70, 86 bytes.
// Clears member vector at +0x0C via rowed voidptr erase 0x0031BD55, then
// releases global vector g_00E04484 elements through virtual slot0 with 0
// return-fed to rowed operator delete 0x0002FD60, then erases the global
// vector. Evidence: caller 0x004E9BC6 passes same this; erase row + delete
// row + FireWeaponWhenDamagedBehavior deleteInstance(0) precedent.

struct RvaVector
{
	void **m_begin;
	void **m_end;
	void **m_cap;
	void **erase(void **first, void **last);
};

struct Elem
{
	virtual void *deleteInstance(int flags);
};

RvaVector g_00E04484;

class Rva004E9B70
{
	char m_pad[0x0C];
	RvaVector m_vec; // +0x0C
public:
	void rva004E9B70();
};

void Rva004E9B70::rva004E9B70()
{
	RvaVector *v = &m_vec;
	v->erase(v->m_begin, v->m_end);
	void **pp = g_00E04484.m_begin;
	void **end = g_00E04484.m_end;
	if (pp != end) {
		do {
			Elem *e = (Elem *)*pp;
			void *p = e ? e->deleteInstance(0) : 0;
			::operator delete(p);
			++pp;
		} while (pp != end);
		g_00E04484.erase(g_00E04484.m_begin, g_00E04484.m_end);
	}
}
