// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva006575F0@Rva006575F0@@QAEXXZ retail 0x006575F0 8 bytes.
// Forwarder to the pinned T_007ea5e0::m through the pointer at +4: two call
// sites in the same unclaimed 116B caller as the 0x006572A0 sibling; LINK
// BONUS on the callee names it ?m@T_007ea5e0@@QAEXXZ, declared here exactly
// so the tail jmp resolves through the pin.
class T_007ea5e0
{
public:
	void m();
};

class Rva006575F0
{
public:
	void rva006575F0();

	char m_pad[4];
	T_007ea5e0 *m_ptr04;
};

void Rva006575F0::rva006575F0()
{
	m_ptr04->m();
}
