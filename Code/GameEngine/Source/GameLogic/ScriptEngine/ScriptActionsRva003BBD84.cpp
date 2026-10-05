// cl: /Ireference/shims/bfme2_ascii /O1
//
// Twin mask sweeps over players, range-17 batch (same family as rowed
// Rva003BB233Set 0x003BB233, which sweeps a caller val; these sweep constant
// 1 through two unrowed Player entries).
// ?rva003BBD84@@YGXABVAsciiString@@@Z @0x003BBD84 64B: mask from ScriptEngine
// rva00357475 0x00357475, then pinned Player::rva002AEEA7(1) per player.
// ?rva003BBDC4@@YGXABVAsciiString@@@Z @0x003BBDC4 64B: same through pinned
// Player::rva002AF037(1). Evidence: ret 4 single name arg, TheScriptEngine +
// ThePlayerList globals, getEachPlayerFromMask loop; player entries pinned
// address-derived.
#include "ascii_string.h"

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern ScriptEngine *TheScriptEngine;

class Player
{
public:
	void rva002AEEA7(int val);
	void rva002AF037(int val);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void __stdcall rva003BBD84(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->rva002AEEA7(1);
	} while (mask != 0);
}

void __stdcall rva003BBDC4(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->rva002AF037(1);
	} while (mask != 0);
}
