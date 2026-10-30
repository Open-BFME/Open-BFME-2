// cl: /MD
// Retail compares the two floats with fcomi, a P6 instruction MSVC 7.1 emits
// only under /arch:SSE; /O1 /G6 alone gives fcom/fnstsw.
// ?doBuild@AIBuildable@@QAE_NPAVPlayer@@@Z @0x0055ADE2 147B
// __thiscall bool (Player*): lookup store via TheSkirmishAIManager map, amount=(int)(v09-cost),
// gated by +0x21 bool and float compare, spend via rowed 0x005963C8, tail v15.
// Evidence: chain from 0x005963C8; callees rowed 0x002A8F24 0x00629228;
// callers 0x004ECCE2; +0x21 bool matches Rva0055B0CC layout; vslots 0x24/0x3c.
// Native AIBuilder update4ECCE2 tests AL immediately after this call;
// bool return is a target fact. The final virtual slot15 result is forwarded.
class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex;
	char m_pad58[0x94 - 0x58];
	int m_cost94;
};

struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *x);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *TheSkirmishAIManager;

class AIEconomyStats
{
public:
	void withdrawSavedAmount(int amount);
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
	bool doBuild(Player *player);
private:
	char m_pad04[0x21 - 4];
	bool m_flag21;
};

bool AIBuildable::doBuild(Player *player)
{
	void *store = TheSkirmishAIManager->rva002A8F24(player);
	unsigned int c1 = (unsigned int)player->m_cost94;
	int amount = (int)(v09(player) - (float)c1);
	if (m_flag21) {
		unsigned int c2 = (unsigned int)player->m_cost94;
		if (v09(player) > (float)c2) {
			AIEconomyStats *spender = *(AIEconomyStats **)((char *)store + 0xc);
			if (*(unsigned int *)((char *)spender + 0x14) >= (unsigned int)amount) {
				spender->withdrawSavedAmount(amount);
			}
		}
	}
	return v15(player);
}
