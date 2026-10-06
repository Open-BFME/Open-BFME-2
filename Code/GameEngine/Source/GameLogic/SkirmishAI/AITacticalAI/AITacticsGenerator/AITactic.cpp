// cl: /MD
// AITactic::initializeTeamTemplate @ 0x004ECE61, 50 bytes: slot 3 of the AITactic
// vtable, which WorldBuilder names initializeTeamTemplate in every tactic that
// overrides it (the AIRingHero/AIRoamingDefense/AITacticDefensive overrides
// call this base); its literal is AITactic.cpp line 386.
// Reads [this+0x20]->+4, random 3..5 into [arg1+0x2d4], always returns true.
// Evidence: 4 callers forwarding (this, arg1, arg2) e.g. 0x005AC924; rowed callee
// ?GetGameLogicRandomValue@@YAHHHPADH@Z with file/line 0x182; vtable slot 3 refs.
int __cdecl GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class AITactic
{
public:
	virtual bool initializeTeamTemplate(void *p, int dummy);
private:
	char m_pad04[0x20 - 4];
	void *m_20;
};

bool AITactic::initializeTeamTemplate(void *p, int /*dummy*/)
{
	void *mid = m_20;
	if (mid == 0)
		return true;
	if (*(int *)((char *)mid + 4) != 0)
		return true;
	*(int *)((char *)p + 0x2D4) = GetGameLogicRandomValue(3, 5, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\AITactic.cpp", 0x182);
	return true;
}
