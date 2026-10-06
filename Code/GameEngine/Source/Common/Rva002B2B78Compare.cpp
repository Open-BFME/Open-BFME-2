// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002B2B78@Rva002B2B78@@QAEHPAV1@@Z, retail 0x002B2B78, 28 bytes.
// Cross-compare of two dwords: return 1 iff this.m_0 == o.m_4 and
// this.m_4 == o.m_0, else 0. Evidence: retail mov edx,[ecx]; mov eax,[esp+4];
// cmp edx,[eax+4]; jne false; mov ecx,[ecx+4]; cmp ecx,[eax]; jne false;
// xor+inc vs xor. Caller at 0x002BCFEE. Honest address name.
class Rva002B2B78
{
public:
	int rva002B2B78(Rva002B2B78 *o);
private:
	int m_0;
	int m_4;
};
int Rva002B2B78::rva002B2B78(Rva002B2B78 *o)
{
	if (m_0 != o->m_4 || m_4 != o->m_0)
		return 0;
	return 1;
}
