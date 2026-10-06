// ?rva0031DFD1@Rva0031D5F8@@QAEXPAVPlayer@@HPAPBVCommandButton@@PAE22@Z
// partial score=0.9868 date=2026-10-06
// ?rva0031DFD1@Rva0031D5F8@@QAEXPAVPlayer@@HPAPBVCommandButton@@PAE22@Z
// partial score=0.9868 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0031D5F8@Rva0031D5F8@@QAEPAXPBVAsciiString@@@Z, retail 0x0031D5F8 (38B).
// Lookup AsciiString key in the Rva00056F61 bucket table at this+0x30 via
// rowed ?rva0041534B@Rva00056F61@@QAE?AURva0041534BIter@@PBVAsciiString@@@Z,
// returning payload at node+8 or NULL when the iterator node is NULL.
// Callers at 0x00219317 0x0031D623 0x0031D914 0x0031DFC7 prove the
// thiscall shape with one AsciiString arg and pointer return used as this.
// ?rva0031DF89@Rva0031D5F8@@QAEPAXPBX@Z, retail 0x0031DF89 (72B).
// Guarded lookup on the same table: arg+0x34 base must be non-null, variant
// AsciiString at base+0x138 or base+0x13c via TheBfmeGlob 0x00DFE78C gate,
// empty check via rowed StringBase isEmpty, then same-table rva0031D5F8.
extern class GameLogic *TheGameLogic;

#include "ascii_string.h"

class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
	Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

#define TheBfmeGlob (*(BfmeGlob939D **)&TheGameLogic)

enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL
{
template <class T> class vector
{
public:
	T *begin() const { return (T *)m_start; }
	T *end() const { return (T *)m_finish; }

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};
}

class Player
{
public:
	bool hasScience(ScienceType science) const;
};

class CommandButton
{
public:
	char m_pad[0xA4];
	_STL::vector<ScienceType> m_sciences;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};

class Rva0043D3A8;

class ScienceStore
{
public:
	bool playerHasRootPrereqsForScience(const Player *player, ScienceType science) const;
	bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType science) const;
};

extern ScienceStore *TheScienceStore;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
	void *rva0031DF89(const void *arg);
	void rva0031DFD1(Player *player, int slot, const CommandButton **out, unsigned char *b1, unsigned char *b2, unsigned char *b3);
	char m_pad[0x30];
	Rva00056F61 m_table;
};

void *Rva0031D5F8::rva0031D5F8(const AsciiString *key)
{
	Rva0041534BIter iter = m_table.rva0041534B(key);
	if (iter.m_node)
		return *(void **)((char *)iter.m_node + 8);
	return 0;
}

void *Rva0031D5F8::rva0031DF89(const void *arg)
{
	char *base = *(char **)((const char *)arg + 0x34);
	if (base == 0)
		return 0;
	AsciiString *name;
	if (TheBfmeGlob->bfmeCall939D())
		name = (AsciiString *)(base + 0x13c);
	else
		name = (AsciiString *)(base + 0x138);
	if (name->isEmpty())
		return 0;
	return rva0031D5F8(name);
}

class Rva0043D3A8;

// ?rva0031DFD1@Rva0031D5F8@@QAEXPAVPlayer@@HPAPBVCommandButton@@PAE22@Z present-unmatched
void Rva0031D5F8::rva0031DFD1(Player *player, int slot, const CommandButton **out, unsigned char *b1, unsigned char *b2, unsigned char *b3)
{
	*b1 = 0;
	*b2 = 0;
	*b3 = 0;
	void *raw = rva0031DF89(player);
	if (raw == 0)
		return;
	*out = ((const CommandSet *)raw)->getCommandButton(slot);
	if (*out == 0)
		return;
	*b1 = 1;
	const _STL::vector<ScienceType> *sciences = &(*out)->m_sciences;
	if (sciences->begin() == sciences->end())
		return;
	ScienceType st = *sciences->begin();
	Rva0043D3A8 *holder = player ? (Rva0043D3A8 *)((char *)player + 4) : 0;
	if (!TheScienceStore->playerHasRootPrereqsForScience((const Player *)holder, st))
		return;
	unsigned char *dst;
	if (!player->hasScience(st))
	{
		if (!TheScienceStore->rva001FF4D3(holder, st))
			return;
		dst = b2;
	}
	else
		dst = b3;
	*dst = 1;
}
