// cl: /O1
// ?Rva003BB6C0Clear@@YGXABVAsciiString@@@Z @0x003BB6C0 64B: free stdcall clearing a byte slot for each player in a name mask.
// Target evidence: calls ScriptEngine::rva00357475 (0x00357475) once then getEachPlayerFromMask (0x002A7BC9) loop calling set@Rva002A9D98ByteSlot (0x002A9D98) with 0; globals g_Va009FE16C (0x009FE16C) and ThePlayerList (0x009FEEE8); ret 4; caller 0x003CBC77.
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
class Rva002A9D98ByteSlot
{
public:
	void set(unsigned char v);
};
void __stdcall Rva003BB6C0Clear(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *p;
	do {
		p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p)
			((Rva002A9D98ByteSlot *)p)->set(0);
	} while (mask != 0);
}
