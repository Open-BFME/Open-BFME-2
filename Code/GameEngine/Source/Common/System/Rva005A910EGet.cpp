// cl: /EHs /MD
// ?rva005A910E@Rva005A910E@@QAEPAVPlayer@@XZ, retail 0x005A910E, 23 bytes.
// Evidence: ecx+0x14 index with -1 early-out returning 0 else ThePlayerList->getNthPlayer 0x002A7A29; callers 0x0050539C 0x00505606; global ThePlayerList 0x009FEEE8.
class Player;
class PlayerList
{
public:
	Player *getNthPlayer(int i);
};
extern PlayerList *ThePlayerList;

class Rva005A910E
{
	int m_pad[0x14 / 4];
	int m_14;
public:
	Player *rva005A910E();
};

Player *Rva005A910E::rva005A910E()
{
	int idx = m_14;
	Player *p = 0;
	if (idx != -1)
		p = ThePlayerList->getNthPlayer(idx);
	return p;
}
