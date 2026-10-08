// cl: /O1 /DNDEBUG /MD /EHsc
//
// GameLogic::TransitionFromLivingWorldTacticalBattle, retail 0x0023D0CD (22B),
// from the WorldBuilder lead (name, statement order; WorldBuilder asserts
// m_livingWorldVictorID != INVALID_LW_PLAYER_ID between the two calls at
// GameLogic.cpp 8502). Both calls go to the living-world logic g_009FEF10:
// 0x002B2A0A, then LivingWorldLogic::GameLogic_tacticalBattleComplete
// (WorldBuilder's name for 0x002BC1DA), which retail reaches by tail jump.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldLogic
{
public:
	void rva002B2A0A();
	void GameLogic_tacticalBattleComplete();
};

class GameLogic
{
public:
	void TransitionFromLivingWorldTacticalBattle();
};

void GameLogic::TransitionFromLivingWorldTacticalBattle()
{
	TheLivingWorldLogic->rva002B2A0A();
	TheLivingWorldLogic->GameLogic_tacticalBattleComplete();
}
