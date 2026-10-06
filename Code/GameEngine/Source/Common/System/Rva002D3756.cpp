// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D3756@Rva002D3756@@QAEXPAX@Z, retail 0x002D3756 28B unlock via rowed 0x005258B2.
// Null-guarded double check: arg null or inner null returns; else tail jmp to rowed setter.
// Evidence: callee ?rva005258B2@Rva005258B2@@QAEXPAX@Z rowed; caller 0x0027B469; prev 0x002D371D next 0x002D3772.
class Rva005258B2
{
public:
	void rva005258B2(void *p);
};

struct Rva002D3756Mid
{
	char m_pad[0xC4];
	Rva005258B2 *m_c4;
};

class Rva002D3756
{
public:
	void rva002D3756(void *p);
private:
	char m_pad[0x10];
	Rva002D3756Mid *m_mid;
};

void Rva002D3756::rva002D3756(void *p)
{
	if (p == 0)
		return;
	Rva005258B2 *inner = m_mid->m_c4;
	if (inner != 0)
		inner->rva005258B2(p);
}
