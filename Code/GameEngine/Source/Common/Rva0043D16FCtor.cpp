// cl: /DNDEBUG /MD
// stlport
// ??0Rva0043D16F@@QAE@XZ @0x0043D16F 36B
// Ctor with vtable 0x0083D7E8 at +0, int at +4 cleared via and-0, BfmeE16
// vector at +8 via rowed Vector_base ctor 0x00211E58, int at +0x14 cleared.
// Layout mirrors the Rva0043D3A8Clear TU (vptr+int+vector+int). Evidence:
// packet disasm with rowed callee, caller 0x0043D686, prev/next rows.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::~_Vector_base(); }
namespace _STL { template <> vector<BfmeE16,_STL::allocator<BfmeE16> >::~vector(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}

enum ScienceType { SCIENCE_INVALID = 0 };
class CreateAHeroData;

// Retail table 0x0083D7E8: 0x0043CCFC, 0x0043C772, 0x0043C754.
class Rva0043D16F
{
public:
	Rva0043D16F();
	virtual bool rva0043CCFC(ScienceType science);
	virtual int rva0043C772();
	virtual void rva0043C754(CreateAHeroData *hero, bool *out);
private:
	int m_04; // +0x04 cleared
	_STL::vector<struct BfmeE16> m_vec; // +0x08
	int m_14; // +0x14 cleared
};

Rva0043D16F::Rva0043D16F()
	: m_04(0), m_14(0)
{
}
