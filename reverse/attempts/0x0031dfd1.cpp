// ?rva0031DFD1@Rva0031D5F8@@QAEXPAVPlayer@@HPAPBVCommandButton@@PAE22@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0031DFD1@Rva0031D5F8@@QAEX... retail 0x0031DFD1 (151B).
// Control-bar science availability: lookup CommandSet via rowed rva0031DF89,
// getCommandButton, publish button, require non-empty science list at +0xA4,
// require playerHasRootPrereqsForScience, then hasScience vs rva001FF4D3 set
// the two out bytes. Callers at 0x0031E083 prove 6 stack args plus this.
// TheScienceStore at VA 0x00DFE0E0.

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Player
{
public:
	bool hasScience(ScienceType st) const;
};

class CommandButton
{
public:
	char m_pad[0xA4];
	ScienceType *m_begin;
	ScienceType *m_end;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

class Rva0043D3A8;

class ScienceStore
{
public:
	bool playerHasRootPrereqsForScience(const Player *player, ScienceType st) const;
	bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType st) const;
};
extern ScienceStore *TheScienceStore;

class Rva0031D5F8
{
public:
	void *rva0031DF89(const void *arg);
	void rva0031DFD1(Player *player, int slot, const CommandButton **out, unsigned char *b1, unsigned char *b2, unsigned char *b3);
};

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
	const char *pp = (const char *)*out + 0xA4;
	ScienceType *begin = *(ScienceType * *)pp;
	ScienceType *end = *(ScienceType * *)(pp + 4);
	if (begin == end)
		return;
	ScienceType st = *begin;
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
