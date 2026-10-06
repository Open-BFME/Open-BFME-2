// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004DF161@Rva004DF161@@QBEMXZ, RVA 0x004DF161, 30 bytes.
// Float ratio: returns 1.0f when m_08 is zero else (float)m_04/(float)m_08.
// Evidence: fld 1.0f at 0x007BB8D8 plus fild [ecx+4] plus fidiv [ebp-4];
// callers at 0x0033AAAC 0x003E46FB use result as float; same 1.0f pool as 0x0039DA2A.
class Rva004DF161
{
public:
	float rva004DF161() const;
	int m_00;
	int m_04;
	int m_08;
};

float Rva004DF161::rva004DF161() const
{
	int denom = m_08;
	if (denom == 0)
		return 1.0f;
	return (float)m_04 / (float)denom;
}
