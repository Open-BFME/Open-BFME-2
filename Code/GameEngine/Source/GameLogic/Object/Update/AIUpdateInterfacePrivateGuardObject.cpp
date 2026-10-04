// cl: /O1 /DNDEBUG /MD
#include "../../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"

// ?privateGuardObject@AIUpdateInterface@@MAEXPAVObject@@W4GuardMode@@W4CommandSourceType@@@Z
// 0x00264D0E 115B: AIUpdateInterface guard order. Checks testStatus 0x26,
// rva002907A1 and KINDOF_PROJECTILE, sets guard target 0x50/0x54, stores
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

enum StateID
{
	BFME_AI_GUARD = 0x10
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }

	unsigned char m_unmodelled_08[0x108 - 8];
	unsigned char m_kindof[16];
};

class Thing
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return m_template->isKindOf(t); }

	virtual void slot00();
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool rva002907A1();

	unsigned char m_unmodelled_08[0x74 - 8];
	UnsignedInt m_id;
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
};

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
	if (!obj->rva002907A1())
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
