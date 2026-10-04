// ?rva00531720@Rva00531720@@QAEEII@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD
// ?rva00531720@Rva00531720@@QAEEII@Z @ 0x00531720 (55B): __thiscall bit-gated element test;
// array at +0xC stride 4 tests [e+1]&0x80 when (a>>1)&1 and [e+2]&1 when (a>>2)&1;
// callers at 0x0053192B 0x0053193A. The two gate masks live in a local two-byte
// ARRAY rather than two scalars: that keeps both computed mask values
// simultaneously live across the whole body, which is what makes MSVC 7.1 /O1
// allocate a callee-save for the index and emit the retail
// push esi / mov esi,[esp+0xc] bracket with the index still live at the lea.
// Two scalar locals (the previous bank) collapse to the same shape at 53B with
// no register save at all. See re_attempts.log row.
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
	unsigned char m[2];
	m[0] = (unsigned char)((t >> 1) & 1);
	m[1] = (unsigned char)((t >> 2) & 1);
	const unsigned char *e = &m_elems[idx].b0;
	if (m[0] && (e[1] & 0x80))
		return 0;
	if (m[1] && (e[2] & 1))
		return 0;
	return 1;
}