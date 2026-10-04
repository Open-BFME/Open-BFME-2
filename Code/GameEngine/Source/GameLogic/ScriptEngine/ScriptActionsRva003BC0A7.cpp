// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?Rva003BC0A7Set@@YGXABVAsciiString@@H@Z @0x003BC0A7 96B leaf caller 0x003CC57C globals 0x009FE16C 0x009FEEE8
// Evidence: ScriptEngine::rva00357475 mask then getEachPlayer loop Money at Player+0x90 deposit if amount>=0 else withdraw -amount.
#include "ascii_string.h"

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *x);
};

class Player;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};

class Rva0039B795;
class Rva0039B7AD;

class Rva003B0D7C
{
public:
	unsigned int rva003B0CB3(unsigned int amount, Rva0039B795 *arg2, bool flag);
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
};

extern ScriptEngine *g_Va009FE16C;
extern PlayerList *ThePlayerList;

void __stdcall Rva003BC0A7Set(const AsciiString &name, int amount)
{
	int mask = g_Va009FE16C->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player == 0)
			continue;
		Rva003B0D7C *money = (Rva003B0D7C *)((char *)player + 0x90);
		if (money == 0)
			continue;
		if (amount < 0)
			money->rva003B0CB3((unsigned int)-amount, 0, true);
		else
			money->rva003B0D7C(amount, 0, true);
	} while (mask != 0);
}
