// cl: /O1 /MD
// GameState::determineCurrentGameSaveFileMode @0x002DBE62 123B
// Name: WorldBuilder (GameState.cpp asserts 497..540; same TheGameLogic
// +0x114/+0x118-shifted mode tests and 2/4/6/3/5/0 results). Retail callers
// load ecx from TheGameState (0x00434B51, 0x00435762) or pass their own this
// (0x002DD3A0), so it is a member that never reads this.
// Evidence: unlock lane; callers 0x002DD3A7 0x002DD7F8 0x00434B57 0x00435768 0x00435A44; callees rowed isSelectionLocked 0x4253A and get 0x210C66; globals TheGameLogic g_009FEF10 g_Rva0023D607Holder; GameLogic +0x110 +0x114 layout from Disp8 getters and holder check.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class GameLogic
{
public:
	char m_pad[0x110];
	int m_110;
	int m_114;
};
extern GameLogic *TheGameLogic;
class Rva002BA8F1Logic;

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};
struct Rva0023D607Holder
{
	char m_00[16];
	int m_10;
};
extern Rva0023D607Holder *g_Rva0023D607Holder;
class Rva00210C66CmpBoolField
{
public:
	bool get() const;
};
class GameState
{
public:
	int determineCurrentGameSaveFileMode();
};
int GameState::determineCurrentGameSaveFileMode()
{
	GameLogic *logic = TheGameLogic;
	Rva002BA8F1Logic *sel;
	if (logic == 0 || (sel = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)) == 0)
		return 2;
	if (((BfmeSelectionState *)sel)->isSelectionLocked())
		return logic->m_114 != 0 ? 6 : 4;
	if (g_Rva0023D607Holder->m_10 != 0)
		return logic->m_110 == 9;
	if (logic->m_114 == 0)
		return 3;
	if (((Rva00210C66CmpBoolField *)logic)->get())
		return 5;
	return logic->m_110 == 6 ? 0 : 2;
}

int Rva002DBE62Get()
{
	GameLogic *logic = TheGameLogic;
	Rva002BA8F1Logic *sel;
	if (logic == 0 || (sel = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)) == 0)
		return 2;
	if (((BfmeSelectionState *)sel)->isSelectionLocked())
		return logic->m_114 != 0 ? 6 : 4;
	if (g_Rva0023D607Holder->m_10 != 0)
		return logic->m_110 == 9;
	if (logic->m_114 == 0)
		return 3;
	if (((Rva00210C66CmpBoolField *)logic)->get())
		return 5;
	return logic->m_110 == 6 ? 0 : 2;
}
