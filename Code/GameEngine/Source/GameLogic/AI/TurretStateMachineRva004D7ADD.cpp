// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// ?rva004D7ADD@TurretStateMachine@@QAE_NXZ at retail 0x004D7ADD (30B).
// Turret goal-destroyed check: goalID at +0x20, Turret getGoalObject 0x004D7726,
// null means destroyed, else Object deadByte at +0x438 bit0 (isEffectivelyDead).
// Evidence: [ecx+0x20]==0 -> false; call rowed Turret getGoalObject; null -> true;
// else ([eax+0x438] & 1). Donor BFME1 StateMachine::isGoalObjectDestroyed plus
// TurretAI dead-flag layout (TurretAI_setTurretTargetObject +0x438-bit0).

class Object
{
public:
	unsigned char m_pad438[0x438];
	struct {
		unsigned char m_dead : 1;
		unsigned char m_rest : 7;
	};
};

class TurretStateMachine
{
public:
	unsigned char m_pad00[0x20]; // +0x00..0x1F (vtable + members)
	int m_goalObjectID; // +0x20

	Object *getGoalObject();
	bool rva004D7ADD();
};

bool TurretStateMachine::rva004D7ADD()
{
	if (m_goalObjectID == 0)
		return false;
	Object *obj = getGoalObject();
	if (!obj)
		return true;
	return obj->m_dead;
}
