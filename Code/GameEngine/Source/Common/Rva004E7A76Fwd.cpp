// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004E7A76@Rva004E7A76@@QAEXXZ @0x004E7A76 15B
// Null-checked tail forward to vtable slot 2 via +0x8. Evidence:
// __thiscall via ecx plus no stack args plus ret; cmp plus je plus mov
// plus jmp-indirect; 6 callers plus 4 unblocks (3 ready); name stays
// address-derived.
class Rva004E7A76Base
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
};

class Rva004E7A76
{
public:
	void rva004E7A76();

private:
	char m_pad[8];
	Rva004E7A76Base *m_p8;
};

void Rva004E7A76::rva004E7A76()
{
	if (m_p8 == 0)
		return;
	m_p8->slot2();
}
