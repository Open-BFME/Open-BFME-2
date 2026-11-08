// cl: /DNDEBUG /MD
#include "../../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"

// ?privateGuardObject@AIUpdateInterface@@MAEXPAVObject@@W4GuardMode@@W4CommandSourceType@@@Z
// 0x00264D0E 115B: AIUpdateInterface guard order. Checks testStatus 0x26,
// isMobile and KINDOF_PROJECTILE, sets guard target 0x50/0x54, stores
// guardMode +0x4C, object id +0x64 from +0x74, clear via slot 0x14 and
// setState 0x10 via slot 0x20. Vtable slot 64 of DeployStyle/Siege/Supply/
// Transport/Wander/HordeWorker AIUpdates. Prev/next same flags.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ObjectStatusTypes
{
	BFME_OBJECT_STATUS_26 = 0x26
};

enum KindOfType
{
	KINDOF_PROJECTILE = 0x19
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum GuardTargetType
{
	GUARDTARGET_OBJECT = 1,
	GUARDTARGET_LOCATION = 2,
	GUARDTARGET_AREA = 3,
	GUARDTARGET_NONE = 4
};

enum
{
	BFME_AI_GUARD = 0x10
};

#include "../../../../Include/Common/Overridable.h"
#include "../../../../Include/Common/ThingTemplate.h"

// Keep the guard kind checks inline without exporting competing private
// Thing/ThingTemplate helper bodies. No import remains when fully inlined.

class Thing
{
public:
	__declspec(dllimport) __forceinline Bool isKindOf(KindOfType t) const { return (((unsigned char)(m_template->m_kindof[t >> 5] >> (t & 24)) & (1 << (t & 7))) != 0); }

	virtual void slot00();
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isMobile() const;

	unsigned char m_unmodelled_08[0x74 - 8];
	UnsignedInt m_id;
};

#include "../../../../Include/Common/StateMachineClass.h"

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;

protected:
	virtual void privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType commandSource);

public:

	Object *getObject() const { return m_object; }

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	GuardMode m_guardMode;
	GuardTargetType m_guardTargetType[2];
	unsigned char m_unmodelled_58[0x64 - 0x58];
	UnsignedInt m_objectToGuard;
};

void AIUpdateInterface::privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType commandSource)
{
	Object *obj = m_object;
	if (obj->testStatus(BFME_OBJECT_STATUS_26))
		return;
	if (!obj->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;
	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_OBJECT;
	else
		m_guardTargetType[0] = GUARDTARGET_OBJECT;
	m_guardMode = guardMode;
	m_objectToGuard = objectToGuard->m_id;
	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}
