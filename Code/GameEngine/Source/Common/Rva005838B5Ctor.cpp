// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005838B5@Rva005838B5@@QAEXXZ RVA 0x005838B5 39B
// Evidence: leaf lane; stores vtable 0x0086FC30; calls rowed base
//   ??0Rva005D6FCC@@QAE@PAX@Z 0x005D6FCC and rowed Vector_base BfmeE16
//   0x00211E58; ret 4 single-arg ctor with vector at +8.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

#include "../../../Libraries/Source/WWVegas/WWLib/Rva005D6FCC.h"

class Rva005838B5 : public Rva005D6FCC
{
public:
	Rva005838B5(void *held);
	virtual ~Rva005838B5();
private:
	_STL::vector<BfmeE16> m_vec; // +8
};

Rva005838B5::Rva005838B5(void *held)
	: Rva005D6FCC(held), m_vec(_STL::allocator<BfmeE16>())
{
}

// ?rva00468A6C@Rva00468A6CFactory@@QAEPAVRva005D6FCC@@PAX@Z RVA 0x00468A6C
// 64B: slot 1 of a factory table (its deleting destructor, ICF-shared at
// 0x00587752, is slot 0); creates the 0x14-byte object above around the
// given pointer. The factory's own identity is unknown.
class Rva00468A6CFactory
{
public:
	Rva005D6FCC *rva00468A6C(void *held);
};

Rva005D6FCC *Rva00468A6CFactory::rva00468A6C(void *held)
{
	return new Rva005838B5(held);
}
