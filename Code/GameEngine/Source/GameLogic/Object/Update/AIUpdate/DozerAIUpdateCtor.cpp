// cl: /DNDEBUG /MD /GX
//
// Zero Hour's DozerAIUpdate (GeneralsMD GameLogic/Object/Update/AIUpdate/
// DozerAIUpdate.cpp) as BFME 2 kept it.
//
// ?createMachines@DozerAIUpdate@@AAEXXZ, retail 0x00488EFC, 86 bytes. Called
// by the ctor 0x004894F5 and by construct 0x00488F52 (which first stores its
// isRebuild argument at +0x40C, ZH's m_isRebuild); +0x400 is the machine
// pointer both test. As in ZH: without a machine, make a
// DozerPrimaryStateMachine (0x3C bytes, plain operator new; ctor 0x00488DAB
// defines the dozer states) for the object and enter its default state
// (machine vslot 7, initDefaultState).

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

class DozerPrimaryStateMachine : public StateMachine
{
public:
	DozerPrimaryStateMachine(Object *owner);
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
	virtual void slot0() = 0;
};

class DozerAIUpdate : public AIUpdateInterface, public DozerAIInterface
{
public:
	DozerAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DozerAIUpdate();
	virtual void slot0();
private:
	void createMachines();

	unsigned char m_pad3E8[0x400 - 0x3E8];
	DozerPrimaryStateMachine *m_dozerMachine; // +0x400
};

void DozerAIUpdate::createMachines()
{
	if (m_dozerMachine == 0)
	{
		m_dozerMachine = new DozerPrimaryStateMachine(getObject());
		m_dozerMachine->initDefaultState();
	}
}
