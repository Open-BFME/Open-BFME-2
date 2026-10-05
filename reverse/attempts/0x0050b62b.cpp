// ?rva0050B62B@Made002CCB67@@UAEXPBURva0050B62BArg@@PAVObject@@@Z
// partial score=0.94 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva0050B62B@Made002CCB67@@UAEXPBURva0050B62BArg@@PAVObject@@@Z retail 0x0050B62B 137B
// Evidence: vslot slot 5 (offset 0x14) of vtable 0x00864D80 installed by
// ??0Made002CCB67 0x0050B6B4; StealMoney nugget built by parseStealMoneyNugget
// 0x002CCB8C; callees findObjectByID 0x00049DC5 + getControllingPlayer
// 0x0028AFA9 + Money withdraw 0x003B0CB3 / deposit 0x003B0D7C + __ftol2;
// float amount at +0x128 same as ctor; Player Money at +0x90 tracker at +0x3BC.
enum ObjectID
{
	INVALID_ID = 0
};

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva0039B795
{
public:
	void rva0039B795(int delta);
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
private:
	char m_pad00[4];
	int m_val04;
	int m_val08;
};

class Player
{
public:
	char m_pad00[0x90];
	Rva003B0D7C m_money90;
	char m_pad9C[0x3BC - 0x90 - 12];
	Rva0039B795 m_tracker;
};

struct Rva0050B62BArg
{
	int m_00;
	int m_04;
	ObjectID m_08;
};

class Rva00507823
{
public:
	virtual ~Rva00507823();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void rva0050B62B(const Rva0050B62BArg *arg, Object *other);
private:
	char m_pad04[0x128 - 4];
};

class Made002CCB67 : public Rva00507823
{
public:
	virtual void rva0050B62B(const Rva0050B62BArg *arg, Object *other);
private:
	float m_128;
};

// ?rva0050B62B@Made002CCB67@@UAEXPBURva0050B62BArg@@PAVObject@@@Z present-unmatched
void Made002CCB67::rva0050B62B(const Rva0050B62BArg *arg, Object *other)
{
	Object *object = TheGameLogic->findObjectByID(arg->m_08);
	if (!object)
		return;
	Player *thief = object->getControllingPlayer();
	if (!thief)
		return;
	Player *victim = other->getControllingPlayer();
	if (!victim)
		return;
	unsigned int taken = victim->m_money90.rva003B0CB3((unsigned int)m_128, &victim->m_tracker, true);
	int deposit = (int)(float)taken;
	thief->m_money90.rva003B0D7C(deposit, (Rva0039B7AD *)&thief->m_tracker, true);
}
