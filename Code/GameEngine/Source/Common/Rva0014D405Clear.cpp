// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0014D405@Rva0014D405@@QAEXXZ @ 0x0014D405 18B: lea eax,[ecx+0xB8] / xor ecx,ecx / mov [eax+0x10],ecx / mov [eax+0x14],ecx / mov [eax+0x18],ecx; caller 0x0014A880; honest address name.
struct Rva0014D405Sub
{
	char m_pad[0x10];
	int m_10;
	int m_14;
	int m_18;
};
class Rva0014D405
{
public:
	void rva0014D405();
private:
	char m_pad[0xB8];
	Rva0014D405Sub m_sub;
};
void Rva0014D405::rva0014D405()
{
	Rva0014D405Sub *p = &m_sub;
	p->m_10 = 0;
	p->m_14 = 0;
	p->m_18 = 0;
}
