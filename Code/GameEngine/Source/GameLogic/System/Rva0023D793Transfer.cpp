// cl: /DNDEBUG /MD
// ?Rva0023D793Transfer@@YGXHHH@Z, retail 0x0023D793, 241 bytes.
// Player index pair transfer with Money withdraw/deposit and tracker adds.
// Evidence: leaf lane; callees Rva0023D339Get getNthPlayer Rva002AA22AByteField MoneyRva003B0D7C Rva0039B795; caller 0x0037AB1B.
bool Rva0023D339Get();
class Player;
class PlayerList
{
public:
	Player *getNthPlayer(int i);
};
extern PlayerList *ThePlayerList;
class Rva002AA22AByteField
{
public:
	unsigned char get() const;
};
class Rva0039B795
{
public:
	void rva0039B795(int delta);
	void rva0039B7CB(int delta);
	void rva0039B7E3(int delta);
};
class Rva0039B7AD
{
public:
	void rva0039B7AD(int delta);
};
class Rva003B0D7C
{
public:
	unsigned int rva003B0CB3(unsigned int amount, Rva0039B795 *arg2, bool flag);
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
public:
	char m_pad00[4];
	unsigned int m_val04;
	int m_val08;
};
class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex;
	char m_pad58[0x90 - 0x58];
	Rva003B0D7C m_money;
	char m_pad9C[0x3BC - 0x9C];
	char m_track[0x14];
};
void __stdcall Rva0023D793Transfer(int a1, int a2, int a3)
{
	if (!Rva0023D339Get())
		return;
	if (a1 < 0 || a1 >= 20)
		return;
	if (a2 < 0 || a2 >= 20)
		return;
	Player *p2 = 0;
	Player *p1 = 0;
	for (int i = 0; i < 20; i++) {
		Player *p = ThePlayerList->getNthPlayer(i);
		if (p == 0)
			continue;
		if (p->m_playerIndex == a1)
			p1 = p;
		else if (p->m_playerIndex == a2)
			p2 = p;
		if (p1 == 0)
			continue;
		if (p2 == 0)
			continue;
		break;
	}
	if (p1 == 0 || p2 == 0)
		return;
	if (((Rva002AA22AByteField *)p1)->get() != 0)
		return;
	if (((Rva002AA22AByteField *)p2)->get() != 0)
		return;
	Rva003B0D7C *m1 = &p1->m_money;
	if (m1 == 0)
		return;
	unsigned int reqSlot = a3;
	unsigned int balSlot = m1->m_val04;
	unsigned int *pmin = (balSlot < reqSlot) ? &balSlot : &reqSlot;
	Rva0039B795 *t1 = (Rva0039B795 *)p1->m_track;
	unsigned int got = m1->rva003B0CB3(*pmin, t1, true);
	Rva0039B795 *t2 = (Rva0039B795 *)p2->m_track;
	Rva003B0D7C *m2 = &p2->m_money;
	m2->rva003B0D7C((int)got, (Rva0039B7AD *)t2, true);
	t1->rva0039B7E3((int)got);
	t2->rva0039B7CB((int)got);
}
