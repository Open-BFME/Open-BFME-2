// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva002834C4@@QAE@XZ, RVA 0x002834C4, 34 bytes.
// Ctor: base Rva00330757Member at +0, int at +0x10 set to 1, vector BfmeE16 at +0x14.
// Evidence: callees rowed member ctor 0x00330757 and vector_base 0x00211E58; callers at 0x0028402E etc.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

#include "../../Include/Common/Rva00330757Member.h"

class Rva002834C4
{
public:
	Rva002834C4();
private:
	Rva00330757Member m_00;
	int m_10;
	_STL::vector<BfmeE16> m_14;
};

Rva002834C4::Rva002834C4()
	: m_00(),
	  m_10(1),
	  m_14(_STL::allocator<BfmeE16>())
{
}
