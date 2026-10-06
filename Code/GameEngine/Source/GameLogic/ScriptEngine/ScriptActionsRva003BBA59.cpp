// cl: /O1
// ?Rva003BBA59Reveal@@YGXABVAsciiString@@@Z @0x003BBA59 122B: free stdcall sibling of 0x003BB94C reaching rva007397C0 instead of rva00739780.
// Target evidence: calls ScriptEngine::rva00357475 (0x00357475) once, then getNthPlayer (0x002A7A29) loop over PlayerList count +0x14 checking Player +0x5c or getEachPlayerFromMask (0x002A7BC9) loop reading Player +0x54, both reaching rva007397C0 (0x007397C0) via TheShroudManager (0x009FE74C); globals g_Va009FE16C (0x009FE16C) and ThePlayerList (0x009FEEE8); ret 4; caller 0x003CBEB7.
class AsciiString;
class Player
{
public:
	char m_pad00[0x54];
	int m_index54; // +0x54
	char m_pad58[0x04];
	int m_field5C; // +0x5c
};
class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern class ScriptEngine *TheScriptEngine;
class PlayerList
{
public:
	Player *getNthPlayer(int i);
	Player *getEachPlayerFromMask(int &mask);
	char m_pad00[0x14];
	int m_playerCount; // +0x14
};
extern PlayerList *ThePlayerList;
class PartitionManager;
extern PartitionManager *TheShroudManager;
class Rva007397C0
{
public:
	void rva007397C0(int playerIndex);
};
void __stdcall Rva003BBA59Reveal(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0) {
		for (int i = 0; i < ThePlayerList->m_playerCount; ++i) {
			Player *p = ThePlayerList->getNthPlayer(i);
			if (p->m_field5C != 0)
				continue;
			((Rva007397C0 *)TheShroudManager)->rva007397C0(i);
		}
	} else {
		Player *p;
		do {
			p = ThePlayerList->getEachPlayerFromMask(mask);
			if (p)
				((Rva007397C0 *)TheShroudManager)->rva007397C0(p->m_index54);
		} while (mask != 0);
	}
}
