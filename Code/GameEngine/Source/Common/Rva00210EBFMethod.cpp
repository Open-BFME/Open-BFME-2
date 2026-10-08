// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00210EBF@Rva00210EBF@@QAEXXZ @0x00210EBF 16B null-checked tail-jmp forwarder.
// Member Rva003F9DB0* at +0x2C4 forwards to rowed rva003F9DB0 0x003F9DB0.
// Evidence: caller 0x00565554 loads global TheLivingWorldManager as this; same shape as sibling 0x00210EE1; callee row Rva003F9DB0Erase.cpp.
// No fallback paths.
class Rva003F9DB0
{
public:
	void rva003F9DB0();
};

class Rva00210EBF
{
	char m_pad[0x2c4];
	Rva003F9DB0 *m_ptr2C4;
public:
	void rva00210EBF();
};

void Rva00210EBF::rva00210EBF()
{
	Rva003F9DB0 *p = m_ptr2C4;
	if (!p)
		return;
	p->rva003F9DB0();
}
