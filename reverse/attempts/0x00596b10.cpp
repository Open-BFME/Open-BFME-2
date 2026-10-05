// ?rva00596B10@Rva00596B10@@QAEXXZ
// partial score=0.9 date=2026-10-04
// cl: /O1 /MD
// ?rva00596B10@Rva00596B10@@QAEXXZ @0x00596B10 146B unlock from 0x004E9446
// Evidence: caller 0x004E9490; rowed getNthPlayer plus rowed rva003B0CB3
// plus rowed rva003B0D7C; prev/next dtor TU Rva0055B0CCDerived.
class Player;
class PlayerList
{
public:
	Player *getNthPlayer(int index);
};
extern PlayerList *ThePlayerList;

class Rva0039B795;
class Rva0039B7AD;
class Rva003B0D7C
{
public:
	unsigned int rva003B0CB3(unsigned int amount, Rva0039B795 *arg2, bool flag);
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
};

class Player
{
public:
	unsigned char m_pad00[0x94];
	int m_val94;
	unsigned char m_pad98[0x3BC - 0x98];
	char m_arg3BC;
};

class Rva00596B10
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07(int arg);
	void rva00596B10();
	unsigned char m_pad04[0x28];
	int m_idx2C;
	int m_idx30;
	int m_val34;
	int m_val38;
};

// ?rva00596B10@Rva00596B10@@QAEXXZ present-unmatched
void Rva00596B10::rva00596B10()
{
	Player *p1 = ThePlayerList->getNthPlayer(m_idx2C);
	Player *p2 = ThePlayerList->getNthPlayer(m_idx30);
	if (!p1 || !p2)
	{
		v07(3);
		return;
	}
	unsigned int a = (unsigned int)*(int *)((char *)p1 + 0x94);
	unsigned int b = (unsigned int)m_val38;
	unsigned int m = (a > b) ? b : a;
	if ((unsigned int)m <= 0u)
		return;
	unsigned int c = (unsigned int)m_val34;
	if (m > c)
		m = c;
	Rva003B0D7C *money1 = (Rva003B0D7C *)((char *)p1 + 0x90);
	money1->rva003B0CB3(m, (Rva0039B795 *)((char *)p1 + 0x3BC), true);
	Rva003B0D7C *money2 = (Rva003B0D7C *)((char *)p2 + 0x90);
	money2->rva003B0D7C((int)m, (Rva0039B7AD *)((char *)p2 + 0x3BC), true);
	m_val34 -= (int)m;
	if (m_val34 != 0)
		return;
	v07(2);
}
