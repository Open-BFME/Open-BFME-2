// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BC830Clear@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BC830 62B: ScriptActions member clearing dword via rowed clearer for each player in mask.
// Evidence: push ebp mov ebp,esp mov ecx,[0xDFE16C]=g_Va009FE16C push 0 push [ebp+8] call rowed rva00357475 0x00357475 test eax mov [ebp+8],eax je end; mov ecx,[0xDFEEE8]=ThePlayerList lea eax,[ebp+8] push eax call rowed getEachPlayerFromMask 0x002A7BC9 test eax je skip mov ecx,eax call rowed clear 0x002A9F0F; cmp [ebp+8],0 jne loop pop ebp ret 4; caller 0x003CDB02; sibling doPlayerDisableBaseConstruction same mask loop shape.
// ?doPlayerSellEverything@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BB2DF 62B (caller 0x003CB7AF) and
// ?doPlayerKill@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BB518 62B (caller 0x003CBA7F) are
// the same loop over the players' unrowed no-argument members 0x002AB5C7 (118B)
// and 0x002AB44A (381B), pinned by address.
class AsciiString;
class Player;
class Rva002AB5C7Player
{
public:
	void rva002AB5C7();
	void rva002AB44A();
};
class Rva002A9F0FDwordClearer
{
public:
	void clear();
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void ScriptActions::Rva003BC830Clear(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *player;
	do {
		player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002A9F0FDwordClearer *)player)->clear();
	} while (mask != 0);
}

void ScriptActions::doPlayerSellEverything(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *player;
	do {
		player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002AB5C7Player *)player)->rva002AB5C7();
	} while (mask != 0);
}

void ScriptActions::doPlayerKill(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *player;
	do {
		player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002AB5C7Player *)player)->rva002AB44A();
	} while (mask != 0);
}

// Member ABI: executeAction3CA4BE supplies its ScriptActions receiver in ECX.
// Canonical class declares these methods; original action verbs remain uncertain.
