// cl: /O1 /DNDEBUG /MD /EHsc
// ??1WorkerAIUpdate@@MAE@XZ @0x004A9A12 244B: WorkerAIUpdate virtual protected dtor.
// Evidence: chain lane calls rowed 0x004A99F6; pin ??1WorkerAIUpdate@@MAE@XZ; sole caller ??_GWorkerAIUpdate@@MAEPAXI@Z;
// BFME1 donor game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateDestructorThunk.cpp (three deleteInstance machines DockPoint[9] 0x1c and 0x24 pads);
// 8-subobject MI shape partagee with HordeWorkerAIUpdateDtor.cpp whose DBase block is copied verbatim below.
// Layout note: the +0x3E4 tail is reached by the rowed Rva004A99F6 method which observes Worker +0x4CC at its own +0xE8;
// the worker TU only needs the call so the tail stays empty here and +0x4CC is plain padding.
void __cdecl operator delete(void *p);

class Thing;
class ModuleData;

class DBaseRoot
{
public:
	virtual ~DBaseRoot();

private:
	char m_pad04[8];
};

class DBaseM1
{
public:
	virtual void f1();
};

class DBaseB2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class DBaseM3
{
public:
	virtual void f3();
};

class DBaseM4
{
public:
	virtual void f4();

private:
	// BFME1 donor WorkerAIUpdateDestructorThunk AIUpdateTail3 carries a vptr plus 0x318 pad here;
	// BFME2 grew this tail so the three interface tails land at +0x3E4/+0x3E8/+0x3EC (vptr tables gate-filled).
	char m_pad3E4[0x3E4 - 0x28];
};

class Rva0026E836 : public DBaseRoot, public DBaseM1, public DBaseB2, public DBaseM3, public DBaseM4
{
public:
	virtual ~Rva0026E836();
};

class Tail3e4
{
public:
	virtual void wt0();
};

class Tail3e8
{
public:
	virtual void wt1();
};

class Tail3ec
{
public:
	virtual void wt2();
};

class Rva004A99F6
{
public:
	void rva004A99F6();
private:
	char m_pad[0xE8];
	int m_e8;
};

class WorkerStateMachine
{
public:
	virtual void *deleteInstance(int pool);
};

class DozerPrimaryStateMachine
{
public:
	virtual void *deleteInstance(int pool);
};

class SupplyTruckStateMachine
{
public:
	virtual void *deleteInstance(int pool);
};

class BfmeWorkerDockPoint
{
public:
	~BfmeWorkerDockPoint();

private:
	char m_data[0x10];
};

class WorkerAIUpdate : public Rva0026E836, public Tail3e4, public Tail3e8, public Tail3ec
{
protected:
	virtual ~WorkerAIUpdate();

private:
	char m_pad03F0[0x1C];
	BfmeWorkerDockPoint m_dockPoint[9];
	char m_pad049C[0x24];
	WorkerStateMachine *m_workerMachine;
	DozerPrimaryStateMachine *m_dozerMachine;
	SupplyTruckStateMachine *m_supplyTruckStateMachine;
};

// ??1BfmeWorkerDockPoint@@QAE@XZ present-unmatched
BfmeWorkerDockPoint::~BfmeWorkerDockPoint()
{
}

WorkerAIUpdate::~WorkerAIUpdate()
{
	((Rva004A99F6 *)(Tail3e4 *)this)->rva004A99F6();
	::operator delete(m_dozerMachine ? m_dozerMachine->deleteInstance(0) : 0);
	m_dozerMachine = 0;
	::operator delete(m_supplyTruckStateMachine ? m_supplyTruckStateMachine->deleteInstance(0) : 0);
	m_supplyTruckStateMachine = 0;
	::operator delete(m_workerMachine ? m_workerMachine->deleteInstance(0) : 0);
	m_workerMachine = 0;
}

#pragma comment(linker, "/alternatename:?f1@DBaseM1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
