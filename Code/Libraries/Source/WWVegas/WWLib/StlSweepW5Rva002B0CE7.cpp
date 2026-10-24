// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x002B0CE7 (25B) is STLport's __destroy_aux range loop (const __false_type& tag): it calls the destructor rowed as
// ??1Rva002AF6C5Element@@QAE@XZ (0x002AF1EC, Rva002AF1ECDtor.cpp) on each
// 0x24-byte element. The element type is that row's (identity unresolved beyond it);
// its destructor is only declared here, so this unit emits the loop alone.
#include <memory>

struct Rva002AF6C5Element
{
	~Rva002AF6C5Element();
	unsigned char m_bytes[0x24];
};

template void _STL::__destroy_aux<Rva002AF6C5Element *>(Rva002AF6C5Element *, Rva002AF6C5Element *, const _STL::__false_type &);
