// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0014D417@Rva0014D417@@QAEXH@Z @ 0x0014D417 26B: mov eax,[esp+4] / xor edx,edx / test eax,eax / setne dl / mov [ecx+0xD4],eax / mov [ecx+0xD0],edx / ret 4; caller 0x0017438B; honest address name.
class Rva0014D417
{
public:
	void rva0014D417(int x);
private:
	char m_pad[0xD0];
	int m_d0;
	int m_d4;
};
void Rva0014D417::rva0014D417(int x)
{
	m_d4 = x;
	m_d0 = (x != 0);
}
