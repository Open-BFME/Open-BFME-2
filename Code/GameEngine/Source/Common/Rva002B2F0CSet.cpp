// flags: region default (reverse/retail_inventory/flag_regions.csv)

// ?rva002B2F0C@Rva002B2F0C@@QAEAAV1@PAURva002B2F0CTarget@@@Z, RVA 0x002B2F0C, 21 bytes.
// Intrusive-ref setter: stores the pointer at this+0 then increments the
// target's refcount at +0xB0 when non-null, returning *this. Evidence: retail
// mov edx,[esp+4] plus test plus mov eax,ecx plus mov [eax],edx plus je plus
// inc [edx+0xB0] plus ret 4; returning *this proves the mov eax,ecx (void
// shape is 19B without it); caller 0x0059B23A in 0x0059B1EC; neighbours are
// Disp8 small getters with /O1 /G7. Honest-address names: owner Rva002B2F0C,
// target with 0xB0 pad plus int refcount.

struct Rva002B2F0CTarget
{
	unsigned char m_pad[0xB0];
	int m_refs;
};

class Rva002B2F0C
{
	Rva002B2F0CTarget* m_ptr;
public:
	Rva002B2F0C& rva002B2F0C(Rva002B2F0CTarget* p);
};

Rva002B2F0C& Rva002B2F0C::rva002B2F0C(Rva002B2F0CTarget* p)
{
	m_ptr = p;
	if (p)
		++p->m_refs;
	return *this;
}
