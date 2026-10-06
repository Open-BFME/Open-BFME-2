// cl: /DNDEBUG /MD
//
// ?rva002633B6@AIUpdateInterface@@QAEXXZ @0x002633B6 (61B).
// AI slot advance: if +0x38 is set delete the +0x30 tracked object through
// its slot15 virtual then its slot0 deleteInstance(0) return-fed to the rowed
// operator delete at 0x0002FD60 then move +0x38 to +0x30. Layout follows the
// rowed AIUpdateInterface machine at +0x30 (rva002630FD). Caller at 0x0029A1E0
// passes the Object+0x258 AI. Sibling of 0x0026331C which moves +0x34.

void __cdecl operator delete(void *block);

class Tracked
{
public:
	virtual void *deleteInstance(int flags) = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
};

class AIUpdateInterface
{
public:
	void rva002633B6();

private:
	char m_pad00[0x30 - 4];
	Tracked *m_30;
	char m_pad34[0x38 - 0x34];
	Tracked *m_38;

	virtual void dummy();
};

void AIUpdateInterface::rva002633B6()
{
	if (m_38 != 0) {
		if (m_30 != 0) {
			m_30->s15();
			void *toDelete;
			if (m_30 != 0)
				toDelete = m_30->deleteInstance(0);
			else
				toDelete = 0;
			::operator delete(toDelete);
			m_30 = 0;
		}
		m_30 = m_38;
		m_38 = 0;
	}
}
