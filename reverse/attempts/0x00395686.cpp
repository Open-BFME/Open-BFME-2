// ?rva00395686@Rva00395686@@QAEHPAVPlayer@@PAVThingTemplate@@@Z
// partial score=0.97 date=2026-10-05
// ?rva00395686@Rva00395686@@QAEHPAVPlayer@@PAVThingTemplate@@@Z
// partial score=0.96 date=2026-10-05
// cl: /O1
//
// ?rva00395686@Rva00395686@@QAEHPAVPlayer@@PAVThingTemplate@@@Z @0x00395686 (61B).
// Guarded player-match then ThingTemplate check: controlling player of m_obj8
// must equal p and t non-null, then rva0033A69A via rowed 0x0033A69A compared
// unsigned against p+0x94 via sbb/inc (unsigned char return, not bool).
// Callees rowed 0x0028AFA9 plus pinned 0x0033A69A. Callers 0x00296D96 0x00379F43.
// Prev Disp8CmpBoolGetters next Rva003956C3 flags /O1.
// Retail block layout: the p==0 and t==0 je's and the ctrl!=p fallthrough all
// reach ONE shared fail block (xor-al / jmp epilogue); only ctrl==p jumps
// forward past it into the pass body. That is three separate early returns for
// the guards with the compute as the tail, NOT one && guard.
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};

class ThingTemplate
{
public:
	int rva0033A69A(Object *o, int a, int b) const;
};

class Player
{
public:
	char m_pad94[0x94];
	unsigned int m_94;
};

class Rva00395686
{
public:
	int rva00395686(Player *p, ThingTemplate *t);
private:
	char m_pad[8];
	Object *m_obj8;
};

// ?rva00395686@Rva00395686@@QAEHPAVPlayer@@PAVThingTemplate@@@Z
int Rva00395686::rva00395686(Player *p, ThingTemplate *t)
{
	Player *ctrl = m_obj8->getControllingPlayer();
	if (p == 0)
		return 0;
	if (t == 0)
		return 0;
	if (ctrl != p)
		return 0;
	unsigned int field = p->m_94;
	int v = t->rva0033A69A((Object *)p, 0, -1);
	unsigned int r = field >= (unsigned int)v;
	return (int)r;
}
