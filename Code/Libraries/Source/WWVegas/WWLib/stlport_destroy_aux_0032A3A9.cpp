// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?__destroy_aux@_STL@@YAXPAVRva0032A3A9Element@@0ABU__false_type@1@@Z @0x0032A3A9 29B.
// _STL::__destroy_aux over a 0x80-byte element with a virtual destructor:
// loops first..last calling the virtual deleting dtor with flags 0
// (mov eax,[esi]; push 0; mov ecx,esi; call [eax]; add esi,0x80).
// Evidence: caller 0x0032B580 passes first/last plus a 1-byte __false_type
// temporary (lea eax,[ebp-1]); landing this makes 0x0032B580 ready.
// Neighbours 0x0032A37A (__uninitialized_copy BfmePod128) and 0x0032A3E1
// (_M_allocate_and_copy BfmePod128) fix the TU flags and 128-byte stride.
class Rva0032A3A9Element {
public:
	virtual ~Rva0032A3A9Element();
private:
	char m_pad[124];
};

namespace _STL {
struct __false_type {
};
void __destroy_aux(Rva0032A3A9Element *first, Rva0032A3A9Element *last, const __false_type &) {
	for (; first != last; ++first)
		first->~Rva0032A3A9Element();
}
}
