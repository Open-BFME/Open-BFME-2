// ?rva004FB382@Rva004FB382@@QAE_NXZ
// partial score=0.92 date=2026-10-08
// ?rva004FB382@Rva004FB382@@QAE_NXZ
// partial score=0.92 date=2026-10-08
// cl: /O2 /DNDEBUG /MD
// cl: /O2 /DNDEBUG /MD
//
// ?rva004FB382@Rva004FB382@@QAE_NXZ @0x004FB382 112B: thiscall, no args, bool.
// Null-owner gate on the first dword of this, then a loop over the living
// world's player vector at +0x8C (begin, end). For each index, the owner's
// id test (rva002E0BC0) decides; on a miss the player's +0x3C4 flag must be
// set or the scan fails. Owner-to-player relation and the pointer-diff
// divisor are structural inferences from the bytes, not named identities.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002E2903Player
{
public:
	char at00[0x14];
	int at14;
	char at18[0x3C4 - 0x18];
	bool m_3C4;
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(int index);
};

class Rva002E071E
{
public:
	int rva002E0BC0(int id);
};

// Re-read on every test: the id callee may change the list.
struct Rva004FB382Range
{
	Rva002E2903Player **begin;
	Rva002E2903Player **end;
};

static int playerCount()
{
	char *base = (char *)TheLivingWorldLogic;
	Rva004FB382Range *range = (Rva004FB382Range *)(base + 0x8C);
	return range->end - range->begin;
}

class Rva004FB382
{
public:
	bool rva004FB382();
	Rva002E071E *owner;
};

// ?rva004FB382@Rva004FB382@@QAE_NXZ
bool Rva004FB382::rva004FB382()
{
	if (owner != 0) {
		for (int i = 0; i < playerCount(); ++i) {
			Rva002E2903Player *p = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B52A8(i);
			int id = p->at14;
			if ((unsigned char)owner->rva002E0BC0(id) == 0) {
				p = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B52A8(i);
				if (!p->m_3C4)
					return false;
			}
		}
	}
	return true;
}
