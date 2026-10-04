// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Helper
//
// ??0ObjectSMCHelper@@QAE@PAVThing@@PBVModuleData@@@Z
// retail 0x002927F8, 81 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelper.cpp
// (reference/open-bfme-1). The donor body is byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text, donor
// recompiled /Os). Only the placed body is defined here; the donor's other
// definition (the destructor) is omitted.
//

// stlport
// Open-BFME: ObjectSMCHelper constructor, retail 0x001C54A0.
//
// The identity is fixed by the three ObjectSMCHelper vftables installed here,
// the timer-list member at +0x20 used by setModelConditionState, and the
// matched ObjectSMCHelper destructor that clears that same list.

#include <list>

class Thing;
class ModuleData;

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();

private:
	unsigned char m_moduleData[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class ObjectHelper : public ModuleInterface,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	ObjectHelper(Thing *, const ModuleData *);
	virtual ~ObjectHelper();
	virtual void moduleInterfaceAnchor();
	virtual void behaviorModuleInterfaceAnchor();
	virtual void updateModuleInterfaceAnchor();

private:
	unsigned char m_helperData[0xc];
};

// Named setModelConditionState (0x002572A0) stores the condition argument
// and current frame + duration in this eight-byte element before push_back
// at 0x002571A0. Its original C++ type name is unknown.
// Preserve the existing Gen_p8pod template ABI: its list-base destructor
// already routes through ILT 0x00027854 to 0x001C3C70. The address-qualified
// local alias identifies this element without inventing an original type.
struct Gen_p8pod
{
	unsigned int m_condition;
	unsigned int m_frame;
};

typedef Gen_p8pod Rva002571A0Elem;

class ObjectSMCHelper : public ObjectHelper
{
public:
	ObjectSMCHelper(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectSMCHelper();
	virtual void moduleInterfaceAnchor();
	virtual void behaviorModuleInterfaceAnchor();
	virtual void updateModuleInterfaceAnchor();

private:
	_STL::list<Rva002571A0Elem> m_timers;
};

ObjectSMCHelper::ObjectSMCHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
}
