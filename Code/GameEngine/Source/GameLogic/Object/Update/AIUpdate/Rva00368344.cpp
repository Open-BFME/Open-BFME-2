// cl: /O1 /DNDEBUG /MD
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
};
class Rva00263910 { public: void rva00265667(const Coord3D *pos, int flag); };
class Rva00368344 {
public:
	void rva00368344(const Coord3D *pos, int flag);
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
