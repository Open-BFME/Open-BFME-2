// cl: /MD /DNDEBUG
// stlport
//
// ??0RemoveUpgradeUpgradeModuleData@@QAE@XZ, retail 0x004B7FF1, 67 bytes
// (EBP-frame): base call into the rowed Rva00253487Base 0x253487,
// compiler vtable store at +0 (pinned ??_7 at 0xC58EF0, slot0 is the ??_G
// at 0x4B8034 sitting right after the ctor), two BfmeE16 vectors at
// +0x118/+0x124 via the rowed Vector_base 0x211E58, bytes at +0x130/+0x131.
// The own table holds UpgradeToRemove at +0x118 plus UpgradeGroupsToRemove
// at +0x124 plus SuppressEvaEventForRemoval at +0x130 plus
// RemoveFromAllPlayerObjects at +0x131. The owning factory at 0x0025082A
// (news 0x134) is the sole caller; the pool key at 0x4B7F3D names the
// class. Row supersedes the ctor pin.
#include <vector>

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
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

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"

class RemoveUpgradeUpgradeModuleData : public Rva00253487Base
{
public:
	RemoveUpgradeUpgradeModuleData();
	virtual ~RemoveUpgradeUpgradeModuleData();

	_STL::vector<BfmeE16> m_upgradeToRemove;
	_STL::vector<BfmeE16> m_upgradeGroupsToRemove;
	unsigned char m_suppressEvaEventForRemoval;
	unsigned char m_removeFromAllPlayerObjects;
};

RemoveUpgradeUpgradeModuleData::RemoveUpgradeUpgradeModuleData()
	: Rva00253487Base()
{
	m_suppressEvaEventForRemoval = 0;
	m_removeFromAllPlayerObjects = 0;
}
