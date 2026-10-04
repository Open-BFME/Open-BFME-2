// cl: /O1 /MD /EHsc
// ?rva00341891@Rva00341796@@QAEXXZ, retail 0x00341891, 89 bytes.
// Slot 4 of vtable 0x008113B8 (class of ??1Rva00341796@@UAE@XZ); new 0x3c via
// 0x0002FDA0 plus ctor 0x00544ED4 with owner at machine+0x14, store at +0x20,
// setGoalPosition 0x00262224 with machine+0x24, virtual slot 0x1c on +0x20.
// Evidence: vtable slot 4; neighbours Rva00341796Dtor and Rva003418EAMethod.
class Object;
struct Coord3D { float x; float y; float z; };
class TurretStateMachine
{
public:
	virtual ~TurretStateMachine();
	void setGoalPosition(const Coord3D *pos);
};
class Rva00544C51 : public TurretStateMachine
{
public:
	Rva00544C51(Object *owner);
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v07();
private:
	char m_pad[0x3c - 4];
};
class StateMachineView
{
public:
	char m_pad00[0x14];
	Object *m_owner;
	char m_pad18[0x24 - 0x18];
	Coord3D m_goal;
};
namespace FXParticleSystem {
class WindModuleInfo
{
public:
	virtual ~WindModuleInfo();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachineView *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};
}
class Rva00341796 : public FXParticleSystem::WindModuleInfo
{
public:
	void rva00341891();
private:
	Rva00544C51 *m_20;
};
void Rva00341796::rva00341891()
{
	Rva00544C51 *mach = new Rva00544C51(m_machine->m_owner);
	m_20 = mach;
	mach->setGoalPosition(&m_machine->m_goal);
	m_20->v07();
}
