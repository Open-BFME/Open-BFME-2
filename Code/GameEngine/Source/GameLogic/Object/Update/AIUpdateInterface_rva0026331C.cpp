// cl: /DNDEBUG /MD
//
// ?rva0026331C@AIUpdateInterface@@QAEXXZ @0x0026331C (81B).
// AI slot advance with 0x3E0 gate: if +0x34 is set and +0x30 is set with the
// byte at +0x3E0 clear delete the +0x30 tracked object through its slot15
// virtual then its slot0 deleteInstance(0) return-fed to the rowed operator
// delete at 0x0002FD60 then move +0x34 to +0x30 and tail-call slot89 at
// +0x164. Layout follows the rowed machine at +0x30. Callers include
// 0x002989B5 and 0x0029A1D9 passing the Object+0x258 AI. Sibling of 0x002633B6.

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
	void rva0026331C();

private:
	char m_pad00[0x30 - 4];
	Tracked *m_30;
	Tracked *m_34;
	char m_pad38[0x3E0 - 0x38];
	unsigned char m_3E0;

	virtual void s00() = 0;
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
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void s21() = 0;
	virtual void s22() = 0;
	virtual void s23() = 0;
	virtual void s24() = 0;
	virtual void s25() = 0;
	virtual void s26() = 0;
	virtual void s27() = 0;
	virtual void s28() = 0;
	virtual void s29() = 0;
	virtual void s30() = 0;
	virtual void s31() = 0;
	virtual void s32() = 0;
	virtual void s33() = 0;
	virtual void s34() = 0;
	virtual void s35() = 0;
	virtual void s36() = 0;
	virtual void s37() = 0;
	virtual void s38() = 0;
	virtual void s39() = 0;
	virtual void s40() = 0;
	virtual void s41() = 0;
	virtual void s42() = 0;
	virtual void s43() = 0;
	virtual void s44() = 0;
	virtual void s45() = 0;
	virtual void s46() = 0;
	virtual void s47() = 0;
	virtual void s48() = 0;
	virtual void s49() = 0;
	virtual void s50() = 0;
	virtual void s51() = 0;
	virtual void s52() = 0;
	virtual void s53() = 0;
	virtual void s54() = 0;
	virtual void s55() = 0;
	virtual void s56() = 0;
	virtual void s57() = 0;
	virtual void s58() = 0;
	virtual void s59() = 0;
	virtual void s60() = 0;
	virtual void s61() = 0;
	virtual void s62() = 0;
	virtual void s63() = 0;
	virtual void s64() = 0;
	virtual void s65() = 0;
	virtual void s66() = 0;
	virtual void s67() = 0;
	virtual void s68() = 0;
	virtual void s69() = 0;
	virtual void s70() = 0;
	virtual void s71() = 0;
	virtual void s72() = 0;
	virtual void s73() = 0;
	virtual void s74() = 0;
	virtual void s75() = 0;
	virtual void s76() = 0;
	virtual void s77() = 0;
	virtual void s78() = 0;
	virtual void s79() = 0;
	virtual void s80() = 0;
	virtual void s81() = 0;
	virtual void s82() = 0;
	virtual void s83() = 0;
	virtual void s84() = 0;
	virtual void s85() = 0;
	virtual void s86() = 0;
	virtual void s87() = 0;
	virtual void s88() = 0;
	virtual void tail89() = 0;
};

void AIUpdateInterface::rva0026331C()
{
	if (m_34 == 0)
		return;
	if (m_30 != 0 && m_3E0 == 0) {
		m_30->s15();
		void *toDelete;
		if (m_30 != 0)
			toDelete = m_30->deleteInstance(0);
		else
			toDelete = 0;
		::operator delete(toDelete);
		m_30 = 0;
	}
	m_30 = m_34;
	m_34 = 0;
	tail89();
}
