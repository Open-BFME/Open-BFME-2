// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$_Destroy@PAVRva0032A3A9Element@@@_STL@@YAXPAVRva0032A3A9Element@@0@Z @0x0032B580 24B.
// _STL::_Destroy over Rva0032A3A9Element* (0x80-byte element with virtual dtor):
// creates a 1-byte __false_type tag local (lea eax,[ebp-1]) and tail-calls the
// rowed __destroy_aux at 0x0032A3A9. Evidence: chain from 0x0032A3A9 which this
// session landed; callers at 0x0032BE9A/0x0032BF07/0x0032BF23/0x0032C152.
// Named-local tag (not __false_type() temporary) avoids the 8B stosb zeroing.
class Rva0032A3A9Element {
public:
	virtual ~Rva0032A3A9Element();
private:
	char m_pad[124];
};
namespace _STL {
struct __false_type {
};
void __destroy_aux(Rva0032A3A9Element *first, Rva0032A3A9Element *last, const __false_type &);
template <class _ForwardIterator>
inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
	__false_type __tag;
	__destroy_aux(__first, __last, __tag);
}
template void _Destroy<Rva0032A3A9Element *>(Rva0032A3A9Element *, Rva0032A3A9Element *);
}
