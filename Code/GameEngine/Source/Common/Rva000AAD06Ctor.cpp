// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva000AAD06@@QAE@XZ @0x000AAD06 32B frameless ctor over vector at +0x08
// Evidence: push ecx push esi mov esi ecx and [esi+4] 0 lea eax esp+7 push allocator call rowed Vector_base BfmeE16 0x00211E58; vtable 0x00BC9454 at +0 gate DIR32; caller 0x000AAD5C derived ctor calls this then stores 0x00BC9468; BfmeE16 16B stand-in from stlport_vector_e16_o1; owner unproven honest Rva name
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
class Rva000AAD06
{
public:
	Rva000AAD06();
protected:
	virtual void _0();
	// Slots 1..4 of retail table 0x00BC9454: /OPT:ICF folded constant bodies
	// 0x000910FB (return 1), 0x000D43D0 (return 0), 0x0047A6A9 (return this)
	// and 0x000D43D0 again.
	virtual int vslot1() { return 1; }
	virtual int vslot2() { return 0; }
	virtual Rva000AAD06 *vslot3() { return this; }
	virtual int vslot4() { return 0; }
private:
	int m_04;
	_STL::vector<BfmeE16> m_vec08;
};

Rva000AAD06::Rva000AAD06()
	: m_04(0), m_vec08(_STL::allocator<BfmeE16>())
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?_0@Rva000AAD06@@MAEXXZ=??_GRva00AAD26@@UAEPAXI@Z")
