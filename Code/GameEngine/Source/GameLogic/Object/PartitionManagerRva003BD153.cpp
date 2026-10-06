// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BD153Set@@YGXPAXHH@Z, retail 0x003BD153 73B leaf via rowed 0x00357475 0x002A7BC9 0x002A738F.
// Player-mask loop: name at p+0x10 via ScriptEngine mask then getEachPlayerFromMask loop calling +0x60 set(a b).
// Evidence: callees rowed; caller 0x003CE7FB; prev 0x003BCFC9 next 0x003BD28D same /O1; sibling Rva003BB39E pattern.
class AsciiString;
class Player;
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
class Rva002A738F
{
public:
	void set(int a, int b);
};

void __stdcall Rva003BD153Set(void *p, int a, int b)
{
	const AsciiString &name = *(const AsciiString *)((const char *)p + 0x10);
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *pl;
	do {
		pl = ThePlayerList->getEachPlayerFromMask(mask);
		if (pl)
			((Rva002A738F *)((char *)pl + 0x60))->set(a, b);
	} while (mask != 0);
}
