// ?rva00553222@Rva00553222@@QAEXXZ
// partial score=0.98 date=2026-09-29
// cl: /MD
// ?rva00553222@Rva00553222@@QAEXXZ retail 0x00553222 58B stop thread plus
// clear plus virtual destroy plus delete. Evidence: chain calls clear
// 0x0009990D plus Stop 0x006105F0 plus delete 0x0002FD60; caller at 0x00557CEA.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
void __cdecl operator delete(void *p);
struct Rva0009990D { void clear(); };
struct ThreadClass {
	void Stop();
	virtual void *v0(int flags);
};
class Rva00553222
{
public:
	void rva00553222();
private:
	char _pad00[0x64];
	ThreadClass *m_64;
	char _pad68[0xA4 - 0x68];
	Rva0009990D m_A4;
};
void Rva00553222::rva00553222()
{
	if (m_64 != 0) {
		m_A4.clear();
		m_64->Stop();
		ThreadClass *t = m_64;
		void *p;
		if (t != 0)
			p = t->v0(0);
		else
			p = 0;
		::operator delete(p);
		_ReadWriteBarrier();
	}
	m_64 = 0;
}
