// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$fill@PAV?$vector@HV?$allocator@H@_STL@@@_STL@@V12@@_STL@@YAXPAV?$vector@HV?$allocator@H@_STL@@@0@0ABV10@@Z @0x00339A70 29B _STL::fill for 12-byte vectors.
// Retail: push esi / mov esi [esp+8] / jmp cmp / push [esp+0x10] / mov ecx esi / call 0x21C21B / add esi 0xC / cmp esi [esp+0xC] / jne / pop esi / ret.
// Target facts: __cdecl (first last value) -> void; loops *first=value via rowed vector<int> assign 0x0021C21B (int spelling of ScienceType vector assign per copy-file precedent); callers 0x0033A0E5 0x0033A125 pass 3.
// Callers: 0x0033A0E5 0x0033A125 in 0x0033A05E; callees: pinned 0x0021C21B vector<int> assign (same address as ScienceType assign, identical codegen).
// Precedent: same 29B shape as AsciiString fill 0x000B4300 and Rva00B6CF1 fill 0x000B67F6; int-for-ScienceType spelling per stlport_copy_sciencevec.cpp.
namespace _STL
{
template <class T> class allocator;
template <class T, class Alloc> class vector
{
	unsigned int m_body[3];
public:
	vector &operator=(const vector &x);
};
template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T &value)
{
	for (; first != last; ++first)
		*first = value;
}
}
typedef _STL::vector<int, _STL::allocator<int> > SciVec;
template void _STL::fill<SciVec *, SciVec>(SciVec *, SciVec *, const SciVec &);
