// ?GetPurchaseScienceStatus@Rva0031D5F8@@QAEXPAVPlayer@@HPAPBVCommandButton@@PAE22@Z
// partial score=0.99 date=2026-10-06
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

// GetPurchaseScienceStatus's views: the player's science holder is its
// second base (+0x04), a command button lists its sciences at +0xA4, and
// TheScienceStore (VA 0x00DFE0E0) answers the prerequisite questions.
enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Rva0043D3A8 {};

class PlayerPrimaryBase
{
	void *m_vtbl;
};

class Player : public PlayerPrimaryBase, public Rva0043D3A8
{
public:
	bool hasScience(ScienceType st) const;			// 0x002AB7D5
};

struct ScienceVec
{
	bool empty() const { return m_begin == m_end; }
	const ScienceType &operator[](unsigned int n) const { return m_begin[n]; }
	ScienceType *m_begin;
	ScienceType *m_end;
};

class CommandButton
{
public:
	const ScienceVec &getScienceVec() const { return m_sciences; }

	char m_pad[0xA4];
	ScienceVec m_sciences;					// +0xA4
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;	// 0x00409EE8
};

class ScienceStore
{
public:
	bool playerHasRootPrereqsForScience(const Player *player, ScienceType st) const;	// 0x001FFC55
	bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType st) const;			// 0x001FF4D3
};

extern ScienceStore *TheScienceStore;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
	void *rva0031DF89(const void *arg);
	void GetPurchaseScienceStatus(Player *player, int slot, const CommandButton **button, unsigned char *available, unsigned char *purchasable, unsigned char *owned);
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

// ControlBar::GetPurchaseScienceStatus, retail 0x0031DFD1 (151 bytes; WB
// names it): the purchase-science command set's button in the slot is
// reported; when it lists a science whose root prerequisites the player has,
// the science is marked owned, or purchasable when the store allows it.
void Rva0031D5F8::GetPurchaseScienceStatus(Player *player, int slot, const CommandButton **button, unsigned char *available, unsigned char *purchasable, unsigned char *owned)
{
	*available = 0;
	*purchasable = 0;
	*owned = 0;
	const CommandSet *commandSet = (const CommandSet *)rva0031DF89(player);
	if (commandSet == 0)
		return;
	*button = commandSet->getCommandButton(slot);
	if (*button == 0)
		return;
	*available = 1;
	const ScienceVec &sciences = (*button)->getScienceVec();
	if (sciences.empty())
		return;
	ScienceType st = sciences[0];
	Rva0043D3A8 *holder = player;
	if (!TheScienceStore->playerHasRootPrereqsForScience(reinterpret_cast<const Player *>(holder), st))
		return;
	unsigned char *flag;
	if (!player->hasScience(st))
	{
		if (!TheScienceStore->rva001FF4D3(holder, st))
			return;
		flag = purchasable;
	}
	else
		flag = owned;
	*flag = 1;
}
