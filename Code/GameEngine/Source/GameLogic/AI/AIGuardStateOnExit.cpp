// cl: /DNDEBUG /MD
//
// AIGuardState::onExit, retail 0x0035135D (108 bytes): slot 5 of vtable
// 0x00C11740, whose slot-2 name getter returns "AIGuardState". Ported from
// Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference), whose body
// deletes the guard sub-machine and clears the guard target type.
// BFME 2 differences (target evidence): instead of clearGuardTargetType it
// clears the AI flag byte +0x3CD, and when the guarded object (AI
// getGuardObject, vslot 119, through the rowed GameLogic::findObjectByID)
// still exists and the guard target type (vslot 123) is GUARDTARGET_OBJECT
// it hands that object to the owner's out-of-line Object member at
// 0x0028BBF3 (pinned opaque as rva0028BBF3: if the owner's +0x23C helper
// exists, forward to it). The sub-machine's deleteInstance is the inlined
// slot-0 release then global operator delete, as in other BFME 2 pooled
// releases.
// Layout: m_guardMachine +0x20; AI at owner +0x258.

typedef bool Bool;
enum ObjectID { INVALID_ID = 0 };
enum StateExitType { EXIT_NORMAL = 0 };
enum StateReturnType { STATE_CONTINUE = 0 };
enum GuardTargetType { GUARDTARGET_LOCATION = 0, GUARDTARGET_OBJECT };
class Object;
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class AIUpdateInterface : public VSlots<119>
{
public:
	virtual const ObjectID getGuardObject( void ) const = 0;
	virtual void slot120() = 0;
	virtual void slot121() = 0;
	virtual void slot122() = 0;
	virtual GuardTargetType getGuardTargetType() const = 0;
	void clearBfme3CD() { m_bfme3CD = false; }
private:
	unsigned char m_pad004[0x3CD - 0x004];
	Bool m_bfme3CD; // +0x3CD
};
class Object
{
public:
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
	void rva0028BBF3(Object *guardee);
private:
	unsigned char m_pad00[0x258];
	AIUpdateInterface *m_ai; // +0x258
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class StateMachine
{
public:
	virtual void *deleteInstance(int flags);
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIGuardState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	StateMachine *m_guardMachine; // +0x20
};

void AIGuardState::onExit( StateExitType status )
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = Object::getAI(owner);
	ai->clearBfme3CD();
	Object *guardee = TheGameLogic->findObjectByID(ai->getGuardObject());
	if (guardee && ai->getGuardTargetType() == GUARDTARGET_OBJECT)
		owner->rva0028BBF3(guardee);

	// m_guardMachine->deleteInstance(): the machine's virtual slot-0 release
	// (flags 0), whose result is then freed through the global operator delete.
	::operator delete(m_guardMachine ? m_guardMachine->deleteInstance(0) : 0);
	m_guardMachine = 0;
}
