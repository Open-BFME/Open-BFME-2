// ?bfmeGo1026F@BfmeF1026@@QAEXHHH@Z, retail 0x004BD6DA (52B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1026.cpp
// (BFME1 0x00217500). Trimmed TU: only this body is defined here; the donor's
// unplaced siblings stay out so the unmatched gate has nothing to refuse.
//
// Callee repair (retail-measured, not guessed): the body the donor spells
// BfmeSrc1026::bfmeGet1026 is the rowed ?getControllingPlayer@Object@@ (18B @
// 0x0028AFA9, Code/GameEngine/Source/GameLogic/Object/
// ObjectGetControllingPlayer.cpp), and the store call the donor spells
// BfmeStore1026::bfmeDo1026 is the pinned ?destroyObject@GameLogic@@
// (@0x00242C09) -- both reproduce the three retail REL32 targets
// (0x28AFA9/0x362437/0x242C09) decoded from the target bytes, so the calls
// spell the settled names. Only ?bfmeHas1026@BfmeTab1026@@ (@0x00362437,
// Ghidra FUN_00762437 42B) needs a pin. The store global is DIR32-copied.

class Player;

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

// The table probe is the rowed Rva2225E0Filter::accepts.
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

class BfmeTab1026
{
public:
	char bfmeHas1026(int h, int v);
};

struct BfmeOwner1026
{
	char m_bfmePad[8];
	BfmeTab1026 m_bfmeTab;
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class BfmeF1026
{
public:
	void bfmeGo1026F(int h, int u1, int u2);
};

void BfmeF1026::bfmeGo1026F(int h, int u1, int u2)
{
	if (h == 0)
		return;

	BfmeOwner1026 *o = *(BfmeOwner1026 **)((char *)this - 0xc);
	Object *p = *(Object **)((char *)this - 8);

	if (((Rva2225E0Filter *)&o->m_bfmeTab)->accepts((Object *)h, (Player *)p->getControllingPlayer()) != 0)
		TheGameLogic->destroyObject((Object *)h);
}
