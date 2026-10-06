// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002196A9@Rva002196A9@@QAEHI@Z 0x002196A9 34B bit-test word at +0x68 caller 0x0021D5A2 tests al
class Rva002196A9
{
public:
	int rva002196A9(unsigned int bit);
	char m_pad[0x68];
	int m_words[16];
};
int Rva002196A9::rva002196A9(unsigned int bit)
{
	return (m_words[bit >> 5] & (1 << (bit & 0x1f))) != 0;
}
