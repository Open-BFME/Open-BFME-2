// cl: /DNDEBUG /MD
// ?rva00368344@Rva00368344@@QAEXPBUCoord3D@@H@Z @0x00368344 83B
// Evidence: leaf called from 0x0036BDCB plus sibling Rva003683EA layout (+0x30 machine +0x528 done) plus rowed callees.
struct Coord3D { float x; float y; float z; };
class Object { public: bool rva002907A1(); };
class Waypoint;
class AIStateMachine { public: void setGoalWaypoint(const Waypoint *p); };
class StateMachine {
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(int v);
	virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(const Coord3D *pos);
};
class Rva00263910 { public: void rva00265667(const Coord3D *pos, int flag); };
class Rva00368344 {
public:
	void rva00368344(const Coord3D *pos, int flag);
	void rva00368397(const Coord3D *pos, int flag);
	void rva00368433(const Coord3D *pos, int flag);
	void rva00368486(const Coord3D *pos, const Waypoint *wp, bool extra);
private:
	char m_pad00[8];
	Object *m_gate08; // +0x08
	char m_pad0C[0x30-0x0C];
	StateMachine *m_machine; // +0x30
	char m_pad34[0x528-0x34];
	int m_done; // +0x528
};
void Rva00368344::rva00368344(const Coord3D *pos, int flag)
{
	if (pos == 0)
		return;
	if (!m_gate08->rva002907A1())
		return;
	m_machine->s5();
	((Rva00263910 *)this)->rva00265667(pos, flag);
	((AIStateMachine *)this)->setGoalWaypoint((const Waypoint *)flag);
	m_machine->s8(0x3E9);
	m_done = 1;
}
void Rva00368344::rva00368397(const Coord3D *pos, int flag)
{
	if (pos == 0)
		return;
	if (!m_gate08->rva002907A1())
		return;
	m_machine->s5();
	((Rva00263910 *)this)->rva00265667(pos, flag);
	((AIStateMachine *)this)->setGoalWaypoint((const Waypoint *)flag);
	m_machine->s8(0x400);
	m_done = 1;
}
void Rva00368344::rva00368433(const Coord3D *pos, int flag)
{
	if (pos == 0)
		return;
	if (!m_gate08->rva002907A1())
		return;
	m_machine->s5();
	((Rva00263910 *)this)->rva00265667(pos, flag);
	((AIStateMachine *)this)->setGoalWaypoint((const Waypoint *)flag);
	m_machine->s8(0x3FD);
	m_done = 1;
}
void Rva00368344::rva00368486(const Coord3D *pos, const Waypoint *wp, bool extra)
{
	if (pos == 0)
		return;
	if (!m_gate08->rva002907A1())
		return;
	((AIStateMachine *)this)->setGoalWaypoint(wp);
	m_machine->s5();
	m_machine->s14(pos);
	if (extra)
		m_machine->s8(0x3F3);
	else
		m_machine->s8(0x3F2);
	m_done = 1;
}
