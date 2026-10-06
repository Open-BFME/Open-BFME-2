// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva003F7E83@Rva003F7E83@@QAEXXZ @0x003F7E83 13B.
// Null-checked tail forward to virtual slot 3 of the +0x1C member.
// Evidence: retail mov ecx,[ecx+0x1C]; test ecx,ecx; je ret; mov eax,[ecx];
// jmp [eax+0xC]. Caller at 0x003F807D is a tail jmp (chain). Slot 3 is the
// fourth virtual; inner layout is honest size-free.
struct Rva003F7E83Inner
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
};
class Rva003F7E83
{
	char m_pad[0x1C];
	Rva003F7E83Inner *m_ptr1C;
public:
	void rva003F7E83();
	void rva003F7E90();
};

void Rva003F7E83::rva003F7E83()
{
	Rva003F7E83Inner *p = m_ptr1C;
	if (p == 0)
		return;
	p->v3();
}

// ?rva003F7E90@Rva003F7E83@@QAEXXZ @0x003F7E90 13B.
// Sibling forward to slot 4 (0x10) of the same +0x1C member.
// Evidence: retail mov ecx,[ecx+0x1C]; test; je; mov eax,[ecx]; jmp [eax+0x10].
// Caller at 0x003F808A is a tail jmp.
void Rva003F7E83::rva003F7E90()
{
	Rva003F7E83Inner *p = m_ptr1C;
	if (p == 0)
		return;
	p->v4();
}
