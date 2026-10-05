// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 __destroy_aux range loops (28B each): for (first != last;
// ++first) _Destroy(&*first), stepping sizeof(element) and calling the
// element destructor out of line. Element views are size-only plus the
// destructor spelling the retail REL32 proves; each dtor is declared only
// and resolves through its existing symbols.csv pin:
//
//   0x002AE5CF  stride 0xD8  dtor 0x001EB63C (??1Rva001EB63C@@QAE@XZ)
//   0x00470398  stride 4     dtor 0x001EB940 (??1Rva001EB940@@QAE@XZ)
//   0x005C847B  stride 0x48  dtor 0x005C8FBD (??1Rva005C8FBD@@QAE@XZ)
#include <vector>

struct Rva001EB63C
{
	unsigned char m_body[0xD8];
	~Rva001EB63C();
};

struct Rva001EB940
{
	unsigned char m_body[4];
	~Rva001EB940();
};

struct Rva005C8FBD
{
	unsigned char m_body[0x48];
	~Rva005C8FBD();
};

namespace _STL {
template void __destroy_aux<Rva001EB63C *>(Rva001EB63C *, Rva001EB63C *, const __false_type &);
template void __destroy_aux<Rva001EB940 *>(Rva001EB940 *, Rva001EB940 *, const __false_type &);
template void __destroy_aux<Rva005C8FBD *>(Rva005C8FBD *, Rva005C8FBD *, const __false_type &);
}
