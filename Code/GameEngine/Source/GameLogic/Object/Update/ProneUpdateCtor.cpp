// cl: /DNDEBUG /MD
//
// ??0ProneUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0049FF06, 46 bytes.
// ProneUpdate behavior ctor over the rowed UpdateModule base (0x253390):
// zeroes +0x20, then re-stores the primary vtable slot and the +0x0C/+0x10
// secondary slots (address-of TU-local dummies, DIR32-masked). The rowed
// pool key at 0x49FE9A and ModuleData triple (proc 0x49FEF5 plus ctor
// 0x49FEDF plus factory 0x24E918) prove the class; the rowed instance
// factory 0x24E8E0 is the sole caller. Row supersedes the ctor pin.
// Written against ProneUpdate.cpp's class views: the compiler's own vtable
// stores after the UpdateModule base reproduce the native order.

typedef int Int;
typedef float Real;
typedef bool Bool;
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	void setStatus(ObjectStatusTypes status, bool set);
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
// MODELCONDITION_PRONE in BFME2: word 2 bit 7 of the Object condition words.
enum
{
	MODELCONDITION_PRONE = 2 * 32 + 7,
	OBJECT_STATUS_NO_ATTACK = 5
};
#include "../../../../Include/GameLogic/Damage.h"
#include "../../../../Include/GameClient/Drawable.h"
#include "ProneUpdateModuleDataView.h"
// ??0ProneUpdateModuleData@@QAE@XZ at retail 0x0049FEDF (16 bytes). The
// module-data half of ProneUpdate: vtable immediate 0x00C4ED70 modelled as an
// explicit first member (LifetimeUpdateModuleDataConstructor precedent, so no
// vtable is emitted and no dtor row is owed), an uninitialised word at +0x04
// retail never stores, and the single table-backed ratio at +0x08 (1.0f from
// the shared literal at 0x00BBB8D8). Field identity is retail's own one-entry
// INI table at 0x00C51964 joined to the Zero Hour ProneUpdate donor
// (DamageToFramesRatio, parseReal).
extern "C" const void *const __identifier("??_7ObjectHelperModuleData@@6B@")[];

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class ModuleData;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"



class Xfer;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

// Primary vftable slots as retail's ProneUpdate one (0x00C5191C) and
// UpdateModule's own (0x00BF004C) hold them: 0 the scalar deleting dtor,
// 1 loadPostProcess (0x0058B03E in UpdateModule's), 2 GetSnapshotName
// (0x002533CD), 3 xfer (0x0044DF9F), 4 getModuleNameKey (__purecall in
// UpdateModule's, 0x0049FE9A in ProneUpdate's).

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class ProneUpdate : public UpdateModule
{
public:
	ProneUpdate(Thing *thing, const ModuleData *moduleData);
	void goProne(const DamageInfo *damageInfo);
	virtual UpdateSleepTime update();
	virtual NameKeyType getModuleNameKey() const;
protected:
	const ProneUpdateModuleData *getProneUpdateModuleData() const
	{
		return (const ProneUpdateModuleData *)getModuleData();
	}
	void startProneEffects();
	void stopProneEffects();
	Int m_proneFrames; // +0x20
};

// ??0ProneUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x49FF06
ProneUpdate::ProneUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_proneFrames = 0;
}
