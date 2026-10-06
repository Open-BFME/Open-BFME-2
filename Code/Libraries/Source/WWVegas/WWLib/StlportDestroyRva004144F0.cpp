// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$_Destroy@PAUBfmeAssignRecord44@@@_STL@@YAXPAUBfmeAssignRecord44@@0@Z @0x004144F0 24B.
// _STL::_Destroy over BfmeAssignRecord44* (44-byte element): creates a 1-byte tag local
// (lea eax,[ebp-1]) and calls the rowed range destroy at 0x0041445C. Evidence: chain from
// 0x0041445C which this session landed; callers at 0x004146FC/0x0041477F/0x0041479B.
struct BfmeAssignRecord44 {
	char m_pad[0x2C];
};
struct Rva0041445CElement {
	virtual ~Rva0041445CElement();
	char m_pad[0x2C - 4];
};
void __cdecl Rva0041445CDestroy(Rva0041445CElement *first, Rva0041445CElement *last, int tag);
namespace _STL {
struct __false_type {
};
template <class _ForwardIterator>
inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last);
template <>
inline void _Destroy<BfmeAssignRecord44 *>(BfmeAssignRecord44 *__first, BfmeAssignRecord44 *__last)
{
	__false_type __tag;
	Rva0041445CDestroy((Rva0041445CElement *)__first, (Rva0041445CElement *)__last, (int)&__tag);
}
template void _Destroy<BfmeAssignRecord44 *>(BfmeAssignRecord44 *, BfmeAssignRecord44 *);
}
