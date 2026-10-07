// cl: /MD
//
// ?rva004C4582@CloudBreakSpecialPower@@QAEXXZ retail 0x004C4582 77B.
// Iterate TheGameLogic objects; for each where BfmeTab1026 at [this+4]+0x24
// has (cur, controlling player of [this+8]) apply model condition (5, [this+8], 1).
// Evidence: CloudBreakSpecialPower member called on primary this after 0x004C4621
// by slot-12 override 0x004C482B; TheGameLogic pin in use; bfmeHas1026/bfmeApply pins.
class Object;
class Player;
class GameLogic;
class BfmeTab1026
{
public:
	char bfmeHas1026(int a, int b);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva0028EC68(int a, void *b, int c);
};

class GameLogic
{
public:
	Object *getFirstObject();
};

extern GameLogic *TheGameLogic;

struct Rva004C4582TabHolder
{
	char m_pad[0x24];
	BfmeTab1026 m_tab;
};

class CloudBreakSpecialPower
{
public:
	void rva004C4582();

private:
	char m_pad00[4];
	Rva004C4582TabHolder *m_04;
	Object *m_08;
};

void CloudBreakSpecialPower::rva004C4582()
{
	Object *cached08 = m_08;
	Object *cur = TheGameLogic->getFirstObject();
	if (cur == 0)
		return;
	for (; cur != 0; cur = *(Object **)((char *)cur + 0x8C))
	{
		Rva004C4582TabHolder *holder = m_04;
		if (holder->m_tab.bfmeHas1026((int)cur, (int)cached08->getControllingPlayer()))
			cur->rva0028EC68(5, cached08, 1);
	}
}
