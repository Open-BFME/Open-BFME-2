// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?rva0028C570@Rva0028C570@@QAEXABV1@@Z @0x0028C570 27B
// 4-word bulk clear (this[i] &= ~other[i]). Evidence: same this/arg shape as
// rowed 4-word _M_do_or at 0x0028C53E (push 4 loop) and 32-word _M_do_or at
// 0x0028C557; called from Object Rva0028CDEB 0x0028CE16 as the clear counterpart
// to the or at 0x0028CE0F on the same Object+0x94 mask, and from 0x00290AD1 on
// Object+0x370; loop is not/needs no STL _M_do (no such STL op); ret 4 void
// __thiscall; name stays address-derived (bitset owner proven by sibling shape
// and shared call sites, method identity unproven).

class Rva0028C570
{
public:
	void rva0028C570(const Rva0028C570 &other);

private:
	unsigned long m_w[4];
};

void Rva0028C570::rva0028C570(const Rva0028C570 &other)
{
	for (unsigned i = 0; i < 4; ++i)
		m_w[i] &= ~other.m_w[i];
}
