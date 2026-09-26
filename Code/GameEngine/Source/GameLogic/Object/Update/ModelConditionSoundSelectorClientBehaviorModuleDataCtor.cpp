// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0ModelConditionSoundSelectorClientBehaviorModuleData@@QAE@XZ at retail 0x004CAEE6.
// Root class (no base call): vtable plus a trailing E16 vector at +0x08
// default-constructed through the vector_base pinned at retail 0x00211E58,
// with the one-byte allocator temporary at [esp+0x07] (frameless).
// Target identity: ModuleFactory registers data factory 0x252C13 for
// ModelConditionSoundSelectorClientBehavior; it news 0x14 with this ctor and
// pushes parse proc 0x4CB0F3 (SoundState table 0x00C5F150). Vtable 0x00C5F098
// slot 0 is the deleting dtor 0x4CAFC1. Earlier ModelConditionSoundSelectorClientBehaviorModuleData name was
// a stub-order guess, refuted by the registration.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Thing;
class ModuleData;

class ModelConditionSoundSelectorClientBehaviorModuleData
{
public:
	ModelConditionSoundSelectorClientBehaviorModuleData();
	virtual ~ModelConditionSoundSelectorClientBehaviorModuleData();

private:
	int m_unused04;
	_STL::vector<BfmeE16> m_vec08;
};

ModelConditionSoundSelectorClientBehaviorModuleData::ModelConditionSoundSelectorClientBehaviorModuleData()
	: m_vec08()
{
}

ModelConditionSoundSelectorClientBehaviorModuleData::~ModelConditionSoundSelectorClientBehaviorModuleData()
{
}
