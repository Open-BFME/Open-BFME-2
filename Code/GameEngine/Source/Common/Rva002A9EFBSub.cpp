// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002A9EFB@Rva002A9EFB@@QAEXH@Z @ 0x002A9EFB (20B). Unlock lane saturated
// subtract. Evidence: lea eax=[ecx+0x31C]; sub [eax],ecx-arg; jns skip else
// and [eax],0; ret 4. Callers at 0x00451179 0x004942CA pass dword.
// Opaque address-derived name; and-zero idiom matches /O1.

class Rva002A9EFB
{
	char _pad[0x31C];
	int m_value;
public:
	void rva002A9EFB(int delta);
};

void Rva002A9EFB::rva002A9EFB(int delta)
{
	m_value -= delta;
	if (m_value < 0)
		m_value = 0;
}
