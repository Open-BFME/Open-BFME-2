// cl: /DNDEBUG /MD /EHsc
//
// ??0WeaponModeSpecialPowerUpdateBase@@QAE@PAVThing@@PBVModuleData@@@Z
// retail 0x0058959A, 181 bytes (Ghidra FUN_0098959a). Its identity is
// supported by the pinned direct call from WeaponModeSpecialPowerUpdate at
// 0x00494B38 and by the same base in the SiegeDeploy and Deflect constructors.
// The interface layout follows the converted BFME1 DynamicGeometryInfoUpdate
// and the ZH SpecialPowerUpdateModule/UpdateModule family; BFME2 offsets and
// callees remain governed by retail bytes.

class Thing;
class ModuleData;
class Object;

class ObjectModuleBase
{
public:
	virtual void objectModuleAnchor();
	virtual ~ObjectModuleBase();
	const ModuleData *m_moduleData;
};

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void updateAnchor() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;

	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
};

class SpecialPowerInterface
{
public:
	virtual void specialPowerAnchor() = 0;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Overridable
{
public:
	virtual void overridableAnchor();
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad04[0x55];
	unsigned char m_hasOverride;
};

class ModuleData
{
public:
	unsigned char m_pad00[8];
	const Overridable *m_overridable;
	unsigned char m_pad0C[8];
	unsigned char m_startsPaused;
};

class Rva005890A6
{
public:
	virtual void f0() = 0;
	virtual void f1() = 0;
	virtual float getPercentReady() const = 0;
	void rva0058943A(float value);
	void rva005890A6(bool pause);
	unsigned int m_availableOnFrame;
	int m_pausedCount;
	unsigned int m_pausedOnFrame;
	float m_pausedPercent;
};

class WeaponModeSpecialPowerUpdateBase : public UpdateModule,
	public SpecialPowerInterface,
	public Rva005890A6
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);
	virtual ~WeaponModeSpecialPowerUpdateBase();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime when);
};

WeaponModeSpecialPowerUpdateBase::WeaponModeSpecialPowerUpdateBase(
	Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_availableOnFrame = 0;
	m_pausedCount = 0;
	m_pausedOnFrame = 0;
	m_pausedPercent = 0.0f;
	if (m_moduleData->m_overridable->friend_getFinalOverride()->m_hasOverride == 0)
	{
		rva0058943A(1.0f);
	}
	if (m_moduleData->m_startsPaused != 0)
	{
		rva005890A6(true);
	}
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
