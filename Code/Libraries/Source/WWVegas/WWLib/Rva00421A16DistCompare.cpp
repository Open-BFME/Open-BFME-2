// cl: /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00421A16@Rva00421A16@@QAE_NPBM0@Z @0x00421A16 53B
// Comparator: true when a lies nearer the functor's own 2D point than b, by
// the squared distance at 0x004219F4 (Rva004219F4Dist.cpp, called twice,
// not inlined). Its caller 0x00421E43 walks list nodes, passes the payload
// at node+8 for both arguments and points ECX at a by-value functor in its
// frame. Retail compares the two results with fcompi, which MSVC 7.1 emits
// only under /arch:SSE. With the distance body visible in the same unit the
// compiler inlines or re-registers it, so the comparator is kept apart.
// Original class and member names are unknown.
float __cdecl Rva004219F4DistSquared(const float *small, const float *big);

class Rva00421A16
{
public:
	bool rva00421A16(const float *a, const float *b);
	float m_pos[2];
};

bool Rva00421A16::rva00421A16(const float *a, const float *b)
{
	return Rva004219F4DistSquared(m_pos, a) < Rva004219F4DistSquared(m_pos, b);
}
