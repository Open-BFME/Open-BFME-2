// cl: /DNDEBUG /MD
//
// ?rva002631A6@AIUpdateInterface@@MAEXMH@Z, retail 0x002631A6, 103 bytes.
// Vtable slot 87 of DeployStyle Siege Transport Wander HordeWorker AIUpdates:
// if m_object+0x04+0x53C float >= global 0x00BC6254 return else build
// Coord3D from float arg then clear via slot 0x14 then StateMachine
// setGoalPosition with FLT_MAX 0x00BBB8E0 then store int at +0x48
// then setState 0x48 via slot 0x20. Callees rowed 0x004D745C.


struct Coord3D
{
	float x;
	float y;
	float z;
};

class StateMachine
{
public:
	void setGoalPosition(const Coord3D *pos, float range);
};

struct FloatHolder
{
	char m_pad00[0x53C];
	float m_val;
};

struct MiniObj
{
	char m_pad00[4];
	FloatHolder *m_holder;
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
};

#define Gbl00BC6254 360.0f
#define Gbl00BBB8E0 3.4028235e+38f

class AIUpdateInterface
{
	char m_pad00[4];
	MiniObj *m_object;
	char m_pad0C[0x30 - 4 - 4 - 4];
	MiniMachine *m_machine;
	char m_pad34[0x48 - 0x34];
	int m_field48;
protected:
	virtual void rva002631A6(float f, int b);
};

void AIUpdateInterface::rva002631A6(float f, int b)
{
	if (m_object->m_holder->m_val >= Gbl00BC6254)
		return;
	Coord3D pos;
	pos.x = f;
	pos.y = f;
	pos.z = f;
	m_machine->clear();
	((StateMachine *)m_machine)->setGoalPosition(&pos, Gbl00BBB8E0);
	m_field48 = b;
	m_machine->setState(0x48);
}
