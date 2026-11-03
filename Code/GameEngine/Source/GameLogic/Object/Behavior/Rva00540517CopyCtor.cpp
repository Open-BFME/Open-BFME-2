// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00540517@@QAE@ABV0@@Z @0x00540517 66B. Copy ctor for member-plus-vector
// holder, same shape as the rowed Rva00541913 copy (0x00541913).
// Evidence: calls rowed Rva00330757Member default ctor 0x00330757 for +0 then
// the rowed vector<Rva00540295Element> copy ctor 0x00540295 for +0x10 then
// copies dword +0x1c; caller 0x00540845 (member at +0x24). The 40-byte element
// view matches the vector row's TU. Honest Rva name.
#include <vector>

struct Rva00540295Element {
	unsigned char bytes[40];
};
// bfme link decl-only begin
namespace _STL { template <> vector<Rva00540295Element, allocator<Rva00540295Element> >::vector(const vector<Rva00540295Element, allocator<Rva00540295Element> > &); }
// bfme link decl-only end

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

#include "../../../../Include/Common/Rva00330757Member.h"

class Rva00540517
{
public:
	Rva00540517(const Rva00540517 &that);
private:
	Rva00330757Member m_00;
	_STL::vector<Rva00540295Element> m_10;
	int m_1C;
};

Rva00540517::Rva00540517(const Rva00540517 &that)
	: m_10(that.m_10)
	, m_1C(that.m_1C)
{
}
