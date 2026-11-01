// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
//
// SpawnedModelConditionCreateModuleData: ctor at retail 0x00257840 (28B) and
// friend_newModuleData at 0x00257C3B (49B).
// Identity (target evidence): ModuleFactory::init (0x00257CB8, at 0x0025AE8B)
// registers "SpawnedModelConditionCreate" with the instance factory
// 0x0025496D (SpawnedModelConditionCreate::friend_newModuleInstance) and the
// data factory 0x00257C3B, which news 0x14 bytes, runs the ctor 0x00257840 and
// hands the data to INI::initFromINIMultiProc with the parse proc 0x003A49C0
// (field table 0x00C1B00C, single field "SpawnerTrigger").
// Layout (target evidence): the ctor installs vtable 0x00BF4228, whose slot 0
// is the deleting dtor 0x00257C6C chaining into the dtor 0x00257C88 (vector at
// +0x08 through vector<BfmeStringHeadRecord160> dtor 0x00257583, Snapshot base
// vtable 0x00BBB554). The dtor pair is rowed here under this class (it was
// rowed as StructureToppleUpdateModuleData); the deleting dtor 0x00257C6C is
// emitted by this unit's vtable.
// Shape: identical skeleton to ModelConditionAudioLoopClientBehaviorModuleData
// (0x004CC20A): Snapshot-rooted class, untouched dword at +4, vector default
// constructed through the folded Vector_base 0x00211E58 (allocator temporary
// at [esp+7], frameless). The factory carries no EH frame in retail, so this
// TU builds without /GX.
#include <vector>
#include "Common/Snapshot.h"
#include "../../../../Include/Common/BfmeModuleData.h"
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAUBfmeStringHeadRecord160@@@_STL@@YAXPAUBfmeStringHeadRecord160@@0ABU__f:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringHeadRecord160;
namespace _STL { template <> void __destroy_aux<BfmeStringHeadRecord160 *>(BfmeStringHeadRecord160 *,BfmeStringHeadRecord160 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAUBfmeStringHeadRecord160@@@_STL@@YAXPAUBfmeStringHeadRecord160@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringHeadRecord160;
namespace _STL { template <> void _Destroy<BfmeStringHeadRecord160 *>(BfmeStringHeadRecord160 *,BfmeStringHeadRecord160 *); }

struct BfmeStringHeadRecord160 { public: ~BfmeStringHeadRecord160(); };

class ModuleData;
class Xfer;
class MultiIniFieldParse;

#include "../../../../Include/Common/INI/INI.h"

// Native BF4228..BF42A4 contains the complete shared 31-slot ModuleData
// interface. Only slot 0 differs; the three Snapshot-shaped declarations
// formerly here omitted slots 4..30 and named callbacks with no provider.
class SpawnedModelConditionCreateModuleData : public ModuleData
{
public:
	SpawnedModelConditionCreateModuleData();
	virtual ~SpawnedModelConditionCreateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	int m_unused04;
	_STL::vector<BfmeStringHeadRecord160> m_vec08;
};

SpawnedModelConditionCreateModuleData::SpawnedModelConditionCreateModuleData()
	: m_vec08()
{
}

ModuleData *SpawnedModelConditionCreateModuleData::friend_newModuleData(INI *ini)
{
	SpawnedModelConditionCreateModuleData *data = new SpawnedModelConditionCreateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SpawnedModelConditionCreateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
