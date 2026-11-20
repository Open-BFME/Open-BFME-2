// cl: /GX /DNDEBUG /MD /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii
// stlport
// ??1SpawnedModelConditionCreateModuleData@@UAE@XZ @0x00257C88 48B
// ModuleData dtor: tears down the vector at +0x08 through the rowed
// vector<BfmeStringHeadRecord160> dtor at 0x00257583, then restores the
// Snapshot base vtable 0x00BBB554. Empty derived body with EH state 0
// (EH prolog 0xB71C4A, no base call since Snapshot dtor is inline).
// Identity: this pair (dtor 0x00257C88, slot-0 ??_G 0x00257C6C) sits after
// the SpawnedModelConditionCreateModuleData friend_newModuleData 0x00257C3B
// and belongs to that class: its ctor 0x00257840 installs vtable 0x00BF4228
// whose slot 0 is 0x00257C6C (see SpawnedModelConditionCreateModuleData.cpp).
// It was rowed as StructureToppleUpdateModuleData; the real Topple dtor is
// 0x00257B7A (StructureToppleUpdateModuleDataDtor.cpp).
// Layout via the class ctor TU plus member via 0x00257583.
#include <vector>
struct BfmeStringHeadRecord160 { public: ~BfmeStringHeadRecord160(); };

#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/Common/BfmeModuleData.h"
// The constructor installs ModuleData's 31-slot interface. Native teardown
// restores Snapshot's BBB554 table after destroying the vector; the shared
// ModuleData view leaves the intermediate inheritance unrecovered.
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
// bfme link decl-only begin
namespace _STL { template <> void __destroy_aux<BfmeStringHeadRecord160 *>(BfmeStringHeadRecord160 *, BfmeStringHeadRecord160 *, __false_type const &); }
namespace _STL { template <> vector<BfmeStringHeadRecord160, allocator<BfmeStringHeadRecord160> >::~vector(); }
// bfme link decl-only end
class __declspec(novtable) SpawnedModelConditionCreateModuleData : public ModuleData
{
public:
	virtual ~SpawnedModelConditionCreateModuleData();
private:
	int m_unused04;
	_STL::vector<BfmeStringHeadRecord160, _STL::allocator<BfmeStringHeadRecord160> > m_vec08;
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline SpawnedModelConditionCreateModuleData::~SpawnedModelConditionCreateModuleData()
{
}

// ?bfmeAnchorSpawnedModelConditionCreateModuleDataDtor absent-from-retail
void bfmeAnchorSpawnedModelConditionCreateModuleDataDtor(SpawnedModelConditionCreateModuleData *spawnedModelConditionCreateModuleData)
{
	spawnedModelConditionCreateModuleData->SpawnedModelConditionCreateModuleData::~SpawnedModelConditionCreateModuleData();
}
