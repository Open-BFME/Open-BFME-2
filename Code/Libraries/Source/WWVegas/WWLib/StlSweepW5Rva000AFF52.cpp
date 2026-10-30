// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x000AFF52 (25B) is STLport's __destroy_aux range loop (const __false_type& tag):
// it calls the destructor rowed as ??1Rva00111B25Record@@QAE@XZ (0x00111B25,
// StringRecordDtors.cpp) on each 0x1C-byte element. The element type is that row's
// (identity unresolved beyond it); its destructor is only declared here, so this
// unit emits the loop alone.
#include <memory>

struct Rva00111B25Record
{
public:
	~Rva00111B25Record();
	unsigned char m_bytes[0x1C]; // +0x00
};

template void _STL::__destroy_aux<Rva00111B25Record *>(Rva00111B25Record *, Rva00111B25Record *, const _STL::__false_type &);
