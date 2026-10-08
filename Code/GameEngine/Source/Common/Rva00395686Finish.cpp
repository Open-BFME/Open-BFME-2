// ?rva00395686@Rva00395686@@QAE_NPAVPlayer@@PAVThingTemplate@@@Z
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// 0x00395686 (61B). Guarded player-match then ThingTemplate check: the
// controlling player of m_obj8 must equal p and t non-null, then rowed
// 0x0033A69A is compared unsigned against p+0x94 via sbb/inc.
// Callees rowed 0x0028AFA9 plus pinned 0x0033A69A. Callers 0x00296D96
// 0x00379F43. Prev Disp8CmpBoolGetters next CastleBehavior flags /O1.
// Retail block layout: the p==0 and t==0 je's and the ctrl!=p fallthrough all
// reach ONE shared fail block (xor-al / jmp epilogue); only ctrl==p jumps
// forward past it into the pass body. That is three separate early returns for
// the guards with the compute as the tail, NOT one && guard.
// The return type is bool, not int: retail's fail block is xor al,al (32 c0)
// while an int-returning build emits xor eax,eax (33 c0) there. Retail emits no
// movzx on the sbb/inc tail, which an int return also spells as a full-width
// zero, so both ends of the body are byte-width only under bool.
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
	bool rva00395686(Player *p, ThingTemplate *t);
private:
	char m_pad[8];
	Object *m_obj8;
};

bool Rva00395686::rva00395686(Player *p, ThingTemplate *t)
{
	Player *ctrl = m_obj8->getControllingPlayer();
	if (p == 0)
		return false;
	if (t == 0)
		return false;
	if (ctrl != p)
		return false;
	unsigned int field = p->m_94;
	int v = t->rva0033A69A((Object *)p, 0, -1);
	return field >= (unsigned int)v;
}
