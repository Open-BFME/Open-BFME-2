// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// Identity: ModuleFactory registers this data class under "ModelConditionAudioLoopClientBehaviorModuleData" (addModule
// pairs the name with this factory); formerly misnamed RepairDockUpdate/RepairDockUpdateModuleData.
// stlport
//
// ??0ModelConditionAudioLoopClientBehaviorModuleData@@QAE@XZ at retail 0x004CC20A.
// Root class (no base call): vtable plus a trailing StringTail156 vector at +0x08
// default-constructed through the vector_base pinned at retail 0x00211E58,
// with the one-byte allocator temporary at [esp+0x07] (frameless).
// Factory stub order names it; stub size 0x14 confirms the layout.
// The member destroys through the rowed vector dtor at 0x004CC1AD (56B dtor
// at 0x004CC226 calls it); the E16 spelling was a stand-in with identical
// ctor bytes via the folded base.
#include <vector>
#include "Common/Snapshot.h"

struct BfmeStringTailRecord156 { public: ~BfmeStringTailRecord156(); };

class Thing;
class ModuleData;

class ModelConditionAudioLoopClientBehaviorModuleData : public Snapshot
{
public:
	ModelConditionAudioLoopClientBehaviorModuleData();
	virtual ~ModelConditionAudioLoopClientBehaviorModuleData();

private:
	int m_unused04;
	_STL::vector<BfmeStringTailRecord156> m_vec08;
};

ModelConditionAudioLoopClientBehaviorModuleData::ModelConditionAudioLoopClientBehaviorModuleData()
	: m_vec08()
{
}

ModelConditionAudioLoopClientBehaviorModuleData::~ModelConditionAudioLoopClientBehaviorModuleData()
{
}
