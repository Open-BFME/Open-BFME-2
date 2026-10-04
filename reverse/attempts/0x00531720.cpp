// ?rva00531720@Rva00531720@@QAEEII@Z
// partial score=0.92 date=2026-10-04
// cl: /Ot /MD
// ?rva00531720@Rva00531720@@QAEEII@Z @ 0x00531720 (55B): __thiscall bit-gated element test; array at +0xC stride 4 tests [e+1]&0x80 when (a>>1)&1 and [e+2]&1 when (a>>2)&1; callers at 0x0053192B 0x0053193A.
// ?rva00531720@Rva00531720@@QAEEII@Z present-unmatched
class Rva00531720
{
public:
	unsigned char rva00531720(unsigned int a, unsigned int idx);
	char m_pad[12];
	struct Elem
	{
		unsigned char b0;
		unsigned char b1;
		unsigned char b2;
		unsigned char b3;
	};
	Elem m_elems[1];
};
unsigned char Rva00531720::rva00531720(unsigned int a, unsigned int idx)
{
	unsigned int t = a;
	unsigned char b1 = (unsigned char)((t >> 1) & 1);
	unsigned int j = idx;
	unsigned char b2 = (unsigned char)((t >> 2) & 1);
	const unsigned char *e = &m_elems[j].b0;
	if (b1 && (e[1] & 0x80))
		return 0;
	if (b2 && (e[2] & 1))
		return 0;
	return 1;
}