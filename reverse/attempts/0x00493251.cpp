// ?rva00493251@Rva00493251@@QAE_NXZ
// partial score=0.95 date=2026-10-05
// cl: /O1 /MD
// ?rva00493251@Rva00493251@@QAE_NXZ @ 0x00493251 77B
// Evidence: TheGameLogic ?TheGameLogic@@3PAVGameLogic@@A +0x114 cmp 3, bfmeCall939D 0x0023C6FD rowed, isValid 0x00360CED rowed, getControllingPlayer 0x0028AFA9 rowed, Player::rva002AB2D9 0x002AB2D9 rowed; callers 0x004932A4 0x00494676.
typedef bool Bool;

class GameLogic
{
public:
	char m_pad[0x114];
	int m_114;
};

extern GameLogic *TheGameLogic;

class BfmeGlob939D : public GameLogic
{
public:
	char bfmeCall939D();
};

class ObjectFilter
{
public:
	Bool isValid() const;
};

class BfmeTab1026;
class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	Bool rva002AB2D9(BfmeTab1026 *tab, Bool flag) const;
};

class Rva00493251
{
public:
	Bool rva00493251();
private:
	int m_00;
	char *m_p4;
	Object *m_p8;
};

Bool Rva00493251::rva00493251()
{
	char *p = m_p4;
	if (TheGameLogic->m_114 != 3)
		p += 0x3C;
	else
	{
		if (!((BfmeGlob939D *)TheGameLogic)->bfmeCall939D())
			goto is_true;
		p += 0x38;
	}
	if (!((ObjectFilter *)p)->isValid())
		goto is_true;
	if (m_p8->getControllingPlayer()->rva002AB2D9((BfmeTab1026 *)p, true))
		goto is_true;
	return false;
is_true:
	return true;
}
