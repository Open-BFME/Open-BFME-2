// cl: /DNDEBUG /MD
// ?rva004E5821@Rva004E5821@@QAEXXZ @0x004E5821 (28B)
// __thiscall void method: frees member DisplayString at +4 through
// DisplayStringManager slot 0x3c and nulls it. Manager layout per
// TooltipHide_muse-f8cb (new at 0x38, free at 0x3c); global
// TheDisplayStringManager per packet. Evidence: unlock lane, callers
// 0x004E58F8 and 0x004E5AA5; unblocks 0x004E5A78. `and [m],0` idiom -> /O1.
class DisplayString;

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0C() = 0;
	virtual void s10() = 0;
	virtual void s14() = 0;
	virtual void s18() = 0;
	virtual void s1C() = 0;
	virtual void s20() = 0;
	virtual void s24() = 0;
	virtual void s28() = 0;
	virtual void s2C() = 0;
	virtual void s30() = 0;
	virtual void s34() = 0;
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString(DisplayString *s) = 0;
};

extern DisplayStringManager *TheDisplayStringManager;
// TheDisplayStringManager: matched references place it at VA 0xdfead8 (zero-filled .bss).
DisplayStringManager * TheDisplayStringManager;

class Rva004E5821 {
	int m_00;
	DisplayString *m_04;
public:
	void rva004E5821();
};

void Rva004E5821::rva004E5821()
{
	if (m_04 != 0) {
		TheDisplayStringManager->freeDisplayString(m_04);
		m_04 = 0;
	}
}
