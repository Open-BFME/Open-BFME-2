// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0040C598@Rva0040C598@@QAEXPBH@Z, retail 0x0040C598, 25 bytes.
// Target evidence: leaf bit-AND loop over 32 dwords; 1 caller at 0x0040C85B; no vtable;
// prev ConstIntGetters4 next DispDwordLeaFieldGetters.
class Rva0040C598
{
public:
	void rva0040C598(const int *src);
	void rva0040C5B1(const int *src);

private:
	int m_bits[32];
};

void Rva0040C598::rva0040C598(const int *src)
{
	for (int i = 0; i < 32; ++i)
		m_bits[i] &= src[i];
}

void Rva0040C598::rva0040C5B1(const int *src)
{
	for (int i = 0; i < 32; ++i)
		m_bits[i] &= ~src[i];
}
