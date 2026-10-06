// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0059ECAD@Rva0059ECAD@@QAEXH@Z @0x0059ECAD 20B: 2-to-9 dword setter at +0x488.
// If int at this plus 0x488 equals 2 store 9; stack arg is ignored but still
// cleaned via ret 4. Evidence: retail lea/cmp/jne/mov/ret-4, neighbours
// Disp0/Disp32 setter TU same page, caller 0x005A547E.
class Rva0059ECAD
{
public:
	void rva0059ECAD(int unused);
	unsigned char rva0059EF33() const;
private:
	char m_pad00[0x488];
	int m_val488;
};

void Rva0059ECAD::rva0059ECAD(int /*unused*/)
{
	int *p = (int *)((char *)this + 0x488);
	if (*p == 2)
		*p = 9;
}

// ?rva0059EF33@Rva0059ECAD@@QBEEXZ @0x0059EF33 22B: 6-or-12 tester at +0x488.
// Returns 1 if int member equals 6 or 12 else 0. Evidence: retail mov/cmp-je
// twice plus xor/mov-al, same member as 0x0059ECAD setter in this TU,
// callers 0x0059FB5F 0x005AECCC.
unsigned char Rva0059ECAD::rva0059EF33() const
{
	if (m_val488 == 6 || m_val488 == 12)
		return 1;
	return 0;
}
