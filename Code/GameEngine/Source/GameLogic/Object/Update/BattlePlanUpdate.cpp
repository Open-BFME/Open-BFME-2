// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 BattlePlanUpdate active-plan getter, transferred from the exact
// BFME1 reconstruction
// (Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp).
// Retail BFME2 keeps the same fields: the affecting army at +0x2C and the
// transition status at +0x30; only the active status reads the army.

enum BattlePlanStatus
{
	PLANSTATUS_NONE = 0
};

class BattlePlanUpdate
{
public:
	BattlePlanStatus getActiveBattlePlan() const;

private:
	unsigned char m_pre[0x2C];
	int m_planAffectingArmy;	// +0x2C
	int m_status;		// +0x30
};

// ?getActiveBattlePlan@BattlePlanUpdate@@QBE?AW4BattlePlanStatus@@XZ
BattlePlanStatus BattlePlanUpdate::getActiveBattlePlan() const
{
	if (m_status == 2)
	{
		return (BattlePlanStatus)m_planAffectingArmy;
	}
	return PLANSTATUS_NONE;
}
