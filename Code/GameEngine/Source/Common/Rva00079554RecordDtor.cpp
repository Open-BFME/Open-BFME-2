// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
//
// ??1Rva00079554Record@@QAE@XZ, retail 0x00079554, 86 bytes.
// Non-virtual record of three POD vectors at +0x00, +0x0C, +0x18: inline
// buffer frees (0x00030830) in reverse member order. A member at +0x00
// rules out a vptr, so the older ??1Rva0079554@@UAE@XZ pin spelling cannot
// describe this body and is left as recorded. Element types and owner are
// unrecovered.
#include <vector>

struct Rva00079554Record
{
	~Rva00079554Record();
	_STL::vector<int> m_00;
	_STL::vector<int> m_0C;
	_STL::vector<int> m_18;
};

Rva00079554Record::~Rva00079554Record()
{
}
