// cl: /MD
// ?rva0029D9CA@Rva0029D9CA@@QAEXXZ @0x0029D9CA 47B.
// Chain from 0x0029A407: if m_0 free via global 0xDFE77C slot 0x74 then clear m_4 via that row plus operator delete 0x2FD60.
// Caller 0x002A3E3F. Unlocks 0x002A3E24.
extern class ClientFrameSubsystem *TheGameClient;

class Rva0029A407 {
public: void rva0029A407();
};
void __cdecl operator delete(void *block);
class Rva0029D9CAHolder {
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(void *p);
};
class Rva0029D9CA {
public:
	void rva0029D9CA();
private:
	void *m_0;
	Rva0029A407 *m_4;
};
void Rva0029D9CA::rva0029D9CA()
{
	if (m_0 != 0) {
		(*(Rva0029D9CAHolder **)&TheGameClient)->s29(m_0);
		m_0 = 0;
	}
	Rva0029A407 *p = m_4;
	if (p != 0) {
		p->rva0029A407();
		::operator delete(p);
	}
}
