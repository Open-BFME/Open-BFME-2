// cl: /O1
// ?Rva003BB39EClear@@YGXABVAsciiString@@@Z @0x003BB39E 62B: free stdcall clearing Player byte +0x338 for each player in a name mask.
// Target evidence: calls ScriptEngine::rva00357475 (0x00357475) once then getEachPlayerFromMask (0x002A7BC9) loop writing byte [eax+0x338]=0; globals g_Va009FE16C (0x009FE16C) and ThePlayerList (0x009FEEE8); ret 4; caller 0x003CB804; sibling of 0x003BB31D (+0x339).
class AsciiString;
class Player
{
public:
	char m_pad00[0x338];
	unsigned char m_flag338; // +0x338
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
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;
void __stdcall Rva003BB39EClear(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *p;
	do {
		p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p)
			p->m_flag338 = 0;
	} while (mask != 0);
}
