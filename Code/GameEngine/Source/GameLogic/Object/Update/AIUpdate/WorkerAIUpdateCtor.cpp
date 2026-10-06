// cl: /DNDEBUG /MD /GX
//
// Zero Hour's WorkerAIUpdate (GeneralsMD GameLogic/Object/Update/AIUpdate/
// WorkerAIUpdate.cpp) as BFME 2 kept it.
//
// ?createMachines@WorkerAIUpdate@@AAEXXZ, retail 0x004A9ED5, 218 bytes. As in
// ZH: without a worker machine, make one (0x3C bytes, plain operator new;
// pinned ctor 0x004A9D79) and, where missing, the dozer (pinned 0x00488DAB)
// and supply truck (pinned 0x004A7010) machines, entering each one's default
// state (machine vslot 7) and the worker machine's last. The three machine
// pointers are the rowed dtor 0x004A9A12's +0x4C0/+0x4C4/+0x4C8.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;

enum StateReturnType
{
	STATE_CONTINUE,
	STATE_SUCCESS,
	STATE_FAILURE
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual StateReturnType initDefaultState();
};

class WorkerStateMachine : public StateMachine
{
public:
	WorkerStateMachine(Object *owner);
private:
	unsigned char m_pad04[0x3C - 0x04];
};

class DozerPrimaryStateMachine : public StateMachine
{
public:
	DozerPrimaryStateMachine(Object *owner);
private:
	unsigned char m_pad04[0x3C - 0x04];
};

class SupplyTruckStateMachine : public StateMachine
{
public:
	SupplyTruckStateMachine(Object *owner);
private:
	unsigned char m_pad04[0x3C - 0x04];
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class AICommandInterface
{
public:
	virtual void aiDoCommand();
};

class AIUpdateInterface24
{
public:
	virtual void slot0();
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x3E4 - 0x28];
};

class DozerAIInterface
{
public:
	virtual void dozerSlot0() = 0;
};

class SupplyTruckAIInterface
{
public:
	virtual void supplyTruckSlot0() = 0;
};

class WorkerAIInterface3EC
{
public:
	virtual void workerSlot0() = 0;
};

class WorkerAIUpdate : public AIUpdateInterface, public DozerAIInterface, public SupplyTruckAIInterface, public WorkerAIInterface3EC
{
public:
	WorkerAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual void dozerSlot0();
	virtual void supplyTruckSlot0();
	virtual void workerSlot0();
protected:
	virtual ~WorkerAIUpdate();
private:
	void createMachines();

	unsigned char m_pad3F0[0x4C0 - 0x3F0];
	WorkerStateMachine *m_workerMachine; // +0x4C0
	DozerPrimaryStateMachine *m_dozerMachine; // +0x4C4
	SupplyTruckStateMachine *m_supplyTruckStateMachine; // +0x4C8
	Int m_4CC; // +0x4CC
};

void WorkerAIUpdate::createMachines()
{
	if (m_workerMachine == 0)
	{
		m_workerMachine = new WorkerStateMachine(getObject());

		if (m_dozerMachine == 0)
		{
			m_dozerMachine = new DozerPrimaryStateMachine(getObject());
			m_dozerMachine->initDefaultState();
		}

		if (m_supplyTruckStateMachine == 0)
		{
			m_supplyTruckStateMachine = new SupplyTruckStateMachine(getObject());
			m_supplyTruckStateMachine->initDefaultState();
		}

		m_workerMachine->initDefaultState();
	}
}
