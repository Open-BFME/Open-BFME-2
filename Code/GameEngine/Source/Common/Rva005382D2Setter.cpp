// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005382D2@Rva005382A6@@QAEXHHPAUBfmeE8@@@Z @0x005382D2 34B
// Indexed 8-byte store: base at +0 plus index*16 plus offset.
// Evidence: prev 0x005382A6 same class same addressing; caller 0x0030BDEE compares/passes two floats; next vector float4 save.
struct BfmeE8 { float x, y; };
class Rva005382A6
{
public:
	void rva005382D2(int i, int off, BfmeE8 *src);
private:
	void *m_base;
};
void Rva005382A6::rva005382D2(int i, int off, BfmeE8 *src)
{
	char *dst = (char *)m_base + i * 16 + off;
	*(BfmeE8 *)dst = *src;
}
