// ?Rva005440F6Get@@YA_NPAVRva00544884State@@@Z
// partial score=0.98 date=2026-10-04
// ?Rva005440F6Get@@YA_NPAVRva00544884State@@@Z
// partial score=0.93 date=2026-10-03
// cl: /MD
// ?Rva005440F6Get@@YA_NPAVRva00544884State@@@Z, retail 0x005440F6, 61 bytes.
// Virtual slot 18 (offset 0x48) of vtable 0x00C69C30, class of ??0Rva00544884@@QAE@PAVStateMachine@@@Z.
// Gets TurretStateMachine goal via rowed getGoalObject 0x004D7726, finds BEC via rowed Object::getDockUpdateInterface 0x0028BCB4, calls slot 0x10 with owner and machine+0x3C, returns bool. Evidence: vslot slot 18; ctor TU Rva00544884Ctor; prev Rva005440BCVSlot5440CD same call pair; next Rva005447EDOnEnter same machine+owner pattern.

class Object;
class DockUpdateInterface;

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

class Object
{
public:
	DockUpdateInterface *getDockUpdateInterface();
};

class DockUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual unsigned char v04(Object *owner, int v);
};

class StateMachine
{
public:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class TurretMachine : public StateMachine
{
public:
	unsigned char m_pad18[0x3C - 0x18];
	int m_3C; // +0x3C
};

class Rva00544884State
{
public:
	unsigned char m_pad00[0x18];
	StateMachine *m_machine; // +0x18
};

bool Rva005440F6Get(Rva00544884State *state)
{
	Object *goal = ((TurretStateMachine *)state->m_machine)->getGoalObject();
	TurretMachine *machine = (TurretMachine *)state->m_machine;
	bool result;
	if (goal == 0) {
		result = false;
	} else {
		DockUpdateInterface *bec = goal->getDockUpdateInterface();
		if (bec == 0) {
			result = false;
		} else {
			Object *owner = state->m_machine->m_owner;
			result = bec->v04(owner, machine->m_3C) != 0;
		}
	}
	return result;
}
