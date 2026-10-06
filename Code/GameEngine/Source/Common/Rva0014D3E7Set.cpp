// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0014D3E7@Rva0014D3E7@@QAEXHHH@Z @ 0x0014D3E7 30B: lea eax,[ecx+0xB8] / mov ecx,[esp+4] / mov [eax+0x10],ecx / mov ecx,[esp+8] / mov [eax+0x14],ecx / mov ecx,[esp+0xC] / mov [eax+0x18],ecx / ret 0xC; caller 0x0014AB4E; honest address name.
struct Rva0014D3E7Sub
{
	char m_pad[0x10];
	int m_10;
	int m_14;
	int m_18;
};
class Rva0014D3E7
{
public:
	void rva0014D3E7(int a, int b, int c);
private:
	char m_pad[0xB8];
	Rva0014D3E7Sub m_sub;
};
void Rva0014D3E7::rva0014D3E7(int a, int b, int c)
{
	Rva0014D3E7Sub *p = &m_sub;
	p->m_10 = a;
	p->m_14 = b;
	p->m_18 = c;
}
