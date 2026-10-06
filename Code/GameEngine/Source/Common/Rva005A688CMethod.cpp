// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005A688C@Rva005A688C@@QAEXHHHH@Z, 0x005A688C, 119B. Unlock wrapper that caches two (a,b) pairs at +0x94C/+0x950 and forwards 4/5->3/4 to Rva005DC3C1 at +0x28. Evidence: caller 0x005A6C90 passes [ecx+14]/[ecx+18]/[ecx+20]; callee row 0x005DC3C1; neighbours 0x005A687F/0x005A6A83.
class Rva005DC3C1
{
public:
	void rva005DC3C1(unsigned short a, unsigned short b, int expected, int newVal);
};
class Rva005A688C
{
public:
	void rva005A688C(int a, int b, int expected, int val);
	void rva005A6C90(int val);
private:
	char m_pad00[0x14];
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	Rva005DC3C1 m_28;
	char m_pad2C[0x94C - 0x2C];
	int m_94C;
	int m_950;
};
void Rva005A688C::rva005A688C(int a, int b, int expected, int val)
{
	if (a == b)
		return;
	if (a < 0 || a >= 8 || b < 0 || b >= 8)
		return;
	if (a == m_14)
	{
		if (b == m_18)
		{
			if (expected != m_20)
				return;
			m_94C = val;
		}
		else
			goto checkSwap;
	}
	else
	{
checkSwap:
		if (a != m_18)
			goto notify;
		if (b != m_14)
			goto notify;
		if (expected != m_20)
			return;
		m_950 = val;
	}
notify:
	if (val == 5)
		m_28.rva005DC3C1((unsigned short)a, (unsigned short)b, expected, 4);
	else if (val == 4)
		m_28.rva005DC3C1((unsigned short)a, (unsigned short)b, expected, 3);
}
void Rva005A688C::rva005A6C90(int val)
{
	rva005A688C(m_14, m_18, m_20, val);
}
