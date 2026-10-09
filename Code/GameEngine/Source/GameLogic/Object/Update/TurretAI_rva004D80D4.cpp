// cl: /MD
// ?rva004D80D4@TurretAI@@UAEXXZ, retail 0x004D80D4, 26 bytes.
// Gap between ??1Rva004D7E61 (TurretStateMachine dtor) and Disp8 setters.
// TurretAI layout from TurretAI_setTurretTargetObject.cpp: machine at +0x14,
// victimInitialTeam at +0x28. Object team at +0x304. Single callee
// getGoalObject 0x004D7726 already rowed in TurretAI_friendGetTurretTarget.cpp.
// Honest address name: class proven by +0x14/+0x28 layout, method unproven.

class Team;
class Object
{
public:
	char m_pad00[0x304];
	Team *m_team;
};

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

class TurretAI
{
public:
	virtual void rva004D80D4();
	char m_pad04[0x10 - 4];
	Object *m_owner;
	TurretStateMachine *m_machine;
	char m_pad18[0x28 - 0x18];
	Team *m_victimInitialTeam;
};

void TurretAI::rva004D80D4()
{
	Object *obj = m_machine->getGoalObject();
	if (obj)
		m_victimInitialTeam = obj->m_team;
}
