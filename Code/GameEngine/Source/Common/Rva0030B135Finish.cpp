// ?rva0030B135@Rva0030B92C@@QAEXPBUBfmePod8@@@Z
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0030B135@Rva0030B92C@@QAEXPBUBfmePod8@@@Z @0x0030B135 114B
// Two halves: a step-8 vector accumulate over [_STL::vector<BfmePod8>] at +0
// with addss from the argument pair, then a flag-gated (byte +0x24) accumulate
// of the same argument pair into the four mid floats at +0x0C..+0x18, in the
// order x,y,x,y. Evidence: calls [ecx]/[ecx+4] step 8, flag +0x24, mids
// +0x0C..+0x18, caller 0x00330B75, same layout as the matched 0x0030B92C
// operator= and 0x0030B1A7 scale siblings in this directory.
//
// The mid accumulate goes through a float lvalue (`pm[0] = pm[0] + pa[0]`)
// instead of field-named `m_0c += a->x`. With either `+=` or `m_0c = m_0c +
// a->x`, MSVC emits the *argument* as the movss source and the member as the
// addss memory operand for the first two adds, while retail loads the member
// first (`movss xmm0,[ecx+0xc]; addss xmm0,[edx]`). The lvalue array spelling
// pins the load/operand association so all four come out member-first.

#include <vector>

struct BfmePod8
{
	float x;
	float y;
};

struct Rva0030B92C
{
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > m_vec;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	int m_1c;
	int m_20;
	unsigned char m_24;
	void rva0030B135(const BfmePod8 *a);
};

void Rva0030B92C::rva0030B135(const BfmePod8 *a)
{
	for (BfmePod8 *p = m_vec.begin(), *e = m_vec.end(); p != e; ++p) {
		p->x += a->x;
		p->y += a->y;
	}
	if (m_24 != 0)
		return;
	float *pm = &m_0c;
	const float *pa = &a->x;
	pm[0] = pm[0] + pa[0];
	pm[1] = pm[1] + pa[1];
	pm[2] = pm[2] + pa[0];
	pm[3] = pm[3] + pa[1];
}
