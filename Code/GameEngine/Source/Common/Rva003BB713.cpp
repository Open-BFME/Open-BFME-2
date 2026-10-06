// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB713Set@@YGXABVAsciiString@@PAVObject@@0@Z @0x003BB713 91B: free stdcall mapping two player-name strings to players then linking via 0x002ADF9C.
// Target evidence: calls ScriptEngine::rva00357475 (0x00357475) twice with NULL bool*, then PlayerList::getPlayerFromMask (0x002A7B91) twice, then rva002ADF9C (0x002ADF9C) when both players non-null; ret 0xc; globals g_Va009FE16C (0x009FE16C) and ThePlayerList (0x009FEEE8); caller 0x003CBCB9.
class AsciiString;
class Player;
class Object;
class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern class ScriptEngine *TheScriptEngine;
class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;
class Rva002ADF9C
{
public:
	void rva002ADF9C(const Player *p, Object *o);
};
void __stdcall Rva003BB713Set(const AsciiString &name1, Object *obj, const AsciiString &name2)
{
	int mask1 = TheScriptEngine->rva00357475(name2, 0);
	int mask2 = TheScriptEngine->rva00357475(name1, 0);
	Player *p1 = ThePlayerList->getPlayerFromMask(mask1);
	Player *p2 = ThePlayerList->getPlayerFromMask(mask2);
	if (p1 && p2)
		((Rva002ADF9C *)p2)->rva002ADF9C(p1, obj);
}
