// cl: /DNDEBUG /MD
//
// ?rva0026316B@AIUpdateInterface@@MAEXPAXH@Z, retail 0x0026316B, 59 bytes.
// Vtable slot 86 of DeployStyle Siege Transport Wander HordeWorker AIUpdates:
// clear via slot 0x14 then slot 0x38 with obj then Turret setGoalPosition
// with obj+0x38 then store int at +0x48 then setState 0x46 via slot 0x20.
// Callees rowed: Turret setGoalPosition 0x00262224.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class StateMachine
{
public:
	void setGoalPosition(const Coord3D *pos);
};

struct MiniArg1
{
	char m_pad00[0x38];
	Coord3D m_pos;
};

class MiniMachine
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void clear();
	virtual void s6();
	virtual void s7();
	virtual int setState(int id);
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void slot14(void *a);
};

class AIUpdateInterface
{
	char m_pad00[0x30 - 4];
	MiniMachine *m_machine;
	char m_pad34[0x48 - 0x34];
	int m_field48;
protected:
	virtual void rva0026316B(void *a, int b);
};

void AIUpdateInterface::rva0026316B(void *a, int b)
{
	MiniArg1 *arg = (MiniArg1 *)a;
	m_machine->clear();
	m_machine->slot14(a);
	((StateMachine *)m_machine)->setGoalPosition(&arg->m_pos);
	m_field48 = b;
	m_machine->setState(0x46);
}
