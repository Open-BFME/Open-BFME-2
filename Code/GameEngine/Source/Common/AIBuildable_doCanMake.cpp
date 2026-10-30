// cl: /DNDEBUG /MD
// ?doCanMake@AIBuildable@@QAEHPAVPlayer@@@Z @0x0055AE75 97B unlock lane spend via RTS map Money virtual.
// Evidence: mov ecx TheSkirmishAIManager call rowed rva002A8F24 0x002A8F24 then flag +0x21 gated rowed Money rva003B0D7C 0x003B0D7C and withdraw 0x003B0CB3 on Player+0x90 plus virtual slot 0x40; caller 0x004ECC85.
class Player;
class Rva0039B7AD;
class Rva0039B795;

class Rva003B0D7C
{
public:
    unsigned int withdraw(unsigned int amount, Rva0039B795 *arg2, bool flag);
    void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
};

class PlayerFull
{
public:
    char _0[0x90];
    Rva003B0D7C m_money;
};

struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *x);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *TheSkirmishAIManager;

struct MapResInner
{
    char _0[0x14];
    int m_14;
};
struct MapRes
{
    char _0[0x0C];
    MapResInner *m_0C;
};

class AIBuildable
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual float v09(Player *p);
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual bool v15(Player *p);
	virtual int v16(Player *p);
	int doCanMake(Player *player);
private:
	char m_pad04[0x21 - 4];
	bool m_flag21;
};

int AIBuildable::doCanMake(Player *player)
{
    MapRes *res = (MapRes *)TheSkirmishAIManager->rva002A8F24(player);
    int virtRes = 0;
    if (m_flag21)
    {
        int amount = res->m_0C->m_14;
        ((PlayerFull *)player)->m_money.rva003B0D7C(amount, 0, false);
    }
    virtRes = v16(player);
    if (m_flag21)
    {
        int amount = res->m_0C->m_14;
        ((PlayerFull *)player)->m_money.withdraw((unsigned int)amount, 0, false);
    }
    return virtRes;
}
