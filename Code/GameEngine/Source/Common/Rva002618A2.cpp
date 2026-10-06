// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002618A2@Rva002618A2@@QAEPAV1@HHHH@Z, retail 0x002618A2, 88 bytes.
// BitFlags7 init: memset 0x1c then set bits b1 b2 b3; first arg unused (always 0 in callers).
// Evidence: caller 0x00261CCF pushes 0 0x6d 7 0x59 with this 0x00DFEA9C; sibling 0x002618FA 6-arg 5-bit same first-0 pattern; neighbours 0x0026185B/0x002619A0; BitFlags<69> 7 words.
extern "C" void *memset(void *s, int c, unsigned n);
class Rva002618A2
{
public:
	Rva002618A2 *rva002618A2(int unused, int b1, int b2, int b3);
	Rva002618A2 *rva002618FA(int unused, int b1, int b2, int b3, int b4, int b5);
private:
	unsigned m_words[7];
};
Rva002618A2 *Rva002618A2::rva002618A2(int unused, int b1, int b2, int b3)
{
	(void)unused;
	memset(this, 0, 0x1c);
	m_words[(unsigned)b1 >> 5] |= (1u << (b1 & 31));
	m_words[(unsigned)b2 >> 5] |= (1u << (b2 & 31));
	m_words[(unsigned)b3 >> 5] |= (1u << (b3 & 31));
	return this;
}
Rva002618A2 *Rva002618A2::rva002618FA(int unused, int b1, int b2, int b3, int b4, int b5)
{
	(void)unused;
	memset(this, 0, 0x1c);
	m_words[(unsigned)b1 >> 5] |= (1u << (b1 & 31));
	m_words[(unsigned)b2 >> 5] |= (1u << (b2 & 31));
	m_words[(unsigned)b3 >> 5] |= (1u << (b3 & 31));
	m_words[(unsigned)b4 >> 5] |= (1u << (b4 & 31));
	m_words[(unsigned)b5 >> 5] |= (1u << (b5 & 31));
	return this;
}
