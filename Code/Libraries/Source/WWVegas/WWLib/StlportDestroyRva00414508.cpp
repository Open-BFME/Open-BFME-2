// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$_Destroy@PAURva00414BDBElement@@@_STL@@YAXPAURva00414BDBElement@@0@Z @0x00414508 24B.
// _STL::_Destroy over Rva00414BDBElement* (48-byte element): creates a 1-byte tag local
// (lea eax,[ebp-1]) and calls the rowed range destroy at 0x00414476. Evidence: chain from
// 0x00414476 just landed; callers at 0x0041473B/0x004147B9 in StlportVectorDtorFamily.
struct Rva00414BDBElement {
	char m_pad[0x30];
};
struct Rva00414476Element {
	virtual ~Rva00414476Element();
	char m_pad[0x30 - 4];
};
void __cdecl Rva00414476Destroy(Rva00414476Element *first, Rva00414476Element *last, int tag);
namespace _STL {
struct __false_type {
};
template <class _ForwardIterator>
inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last);
template <>
inline void _Destroy<Rva00414BDBElement *>(Rva00414BDBElement *__first, Rva00414BDBElement *__last)
{
	__false_type __tag;
	Rva00414476Destroy((Rva00414476Element *)__first, (Rva00414476Element *)__last, (int)&__tag);
}
template void _Destroy<Rva00414BDBElement *>(Rva00414BDBElement *, Rva00414BDBElement *);
}
