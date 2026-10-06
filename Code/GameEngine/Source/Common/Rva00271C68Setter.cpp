// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00271C68@Rva00271C68@@QAEXH@Z retail 0x00271C68 17 bytes.
// Conditional bit setter if arg equals 26 then or 4 at +0x118. Unblocks
// 0x0043B278. Prev 0x00271892 next 0x00271C8A in Common with /O1.
// Evidence: caller 0x0043B29C plus prev plus next plus or-4 idiom.

class Rva00271C68
{
public:
	void rva00271C68(int value);
	void rva00271C79(int value);

private:
	unsigned char m_pre[0x118];
	int m_118;
};

void Rva00271C68::rva00271C68(int value)
{
	if (value == 0x1A)
		m_118 |= 4;
}

void Rva00271C68::rva00271C79(int value)
{
	if (value == 0x1A)
		m_118 &= ~4;
}
