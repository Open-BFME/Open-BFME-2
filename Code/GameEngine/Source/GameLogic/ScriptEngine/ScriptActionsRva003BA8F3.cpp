// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva003BA8F3Get@@YAEXZ @0x003BA8F3 69B: free predicate over PlayerList ScriptEngine GameLogic.
// Evidence: mov ecx,[0xDFEEE8] call 0x2A7DD0 test al jne true; mov ecx,[0xDFE16C]
// call getByte 0x203BDA test al jne true; esi=[0xDFE78C] call isInMultiplayer
// 0x42235 test al je false test esi je false cmp [esi+0x2A4],0 je true;
// false xor al,al ret true mov al,1 ret. Callers 0x3BE652 0x3BE736.

extern class PlayerList *ThePlayerList;
extern class ScriptEngine *TheScriptEngine;

class Rva002A7DD0
{
public:
	bool rva002A7DD0();
};

class Rva00203BDAByteField
{
public:
	unsigned char get() const;
};

class GameLogic
{
public:
	bool isInMultiplayerGame();
	char m_pad[0x2A4];
	int m_2A4;
};
extern GameLogic *TheGameLogic;

#define Rva00DFEEE8 (*(Rva002A7DD0 **)&ThePlayerList)
#define Rva00DFE16C (*(Rva00203BDAByteField **)&TheScriptEngine)

unsigned char Rva003BA8F3Get()
{
	if (Rva00DFEEE8->rva002A7DD0() || Rva00DFE16C->get())
		return 1;
	GameLogic *logic = TheGameLogic;
	if (logic->isInMultiplayerGame() && logic && logic->m_2A4 == 0)
		return 1;
	return 0;
}
