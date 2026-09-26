// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
// ?Rva00549D30Median@@YAABURva00549D30Elem@@ABU1@00@Z, RVA 0x00549D30, 75B
// Median-of-three on the float key at +4. Evidence: sits between
// ?_M_advance (0x00549CD4) and ?_M_decrement (0x00549D7B) in
// stlport_deque_e8_o1.cpp page; caller 0x0054C199 in 278B introsort-like
// body; movss/comiss prove float at +4; 75B SSE shape needs /arch:SSE.
// Struct is a stand-in: only the 8-byte size and the float at +4 are fixed
// by the bytes; +0 is padding.
struct Rva00549D30Elem { int m_a; float m_key; };
const Rva00549D30Elem& Rva00549D30Median(const Rva00549D30Elem& a, const Rva00549D30Elem& b, const Rva00549D30Elem& c)
{
	if (b.m_key < a.m_key) {
		if (b.m_key > c.m_key)
			return b;
		else if (!(a.m_key > c.m_key))
			return a;
		else
			return c;
	} else {
		if (a.m_key > c.m_key)
			return a;
		else if (b.m_key > c.m_key)
			return c;
		else
			return b;
	}
}
