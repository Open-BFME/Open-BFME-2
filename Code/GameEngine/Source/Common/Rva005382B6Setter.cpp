// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005382B6@Rva005382A6@@QAEXHABUBfmePod16@@@Z @0x005382B6 28B
// Indexed 16-byte store plus flag set: base at +0 plus index*16, flag at +0x20 set to 1.
// Evidence: prev 0x005382A6 same class same addressing stride 16; next 0x005382D2 same class 8-byte store; caller 0x0030BDDD.
struct BfmePod16 { int a[4]; };
class Rva005382A6
{
public:
	void rva005382B6(int i, const BfmePod16 &src);
private:
	void *m_base;
	char m_pad[0x20 - 4];
	unsigned char m_20;
};
void Rva005382A6::rva005382B6(int i, const BfmePod16 &src)
{
	char *dst = (char *)m_base + i * 16;
	*(BfmePod16 *)dst = src;
	m_20 = 1;
}
