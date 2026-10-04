// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?Rva003BC048Set@@YGXABVAsciiString@@H@Z @0x003BC048 95B leaf caller 0x003CC558 globals 0x009FE16C 0x009FEEE8
// Evidence: ScriptEngine::rva00357475 mask-from-name then PlayerList::getEachPlayerFromMask loop with Money withdraw-all then deposit arg at Player+0x90.
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
public:
	char m_pad00[4];
	unsigned int m_val04;
};

extern ScriptEngine *g_Va009FE16C;
extern PlayerList *ThePlayerList;

void __stdcall Rva003BC048Set(const AsciiString &name, int amount)
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
		money->rva003B0CB3(money->m_val04, 0, true);
		money->rva003B0D7C(amount, 0, true);
	} while (mask != 0);
}
