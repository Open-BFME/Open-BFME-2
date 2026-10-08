// ?update@AIMoneyLender@@QAEXXZ
// partial score=0.97 date=2026-10-06
// cl: /O1 /MD /arch:SSE
// AIMoneyLender.cpp -- AIMoneyLender members at their WorldBuilder home
// (reverse/wb_name_leads.csv: WB's debug build names the file and
// AIMoneyLender::update and its Money::withdraw callee); retail supplies the
// bytes.
//
// Layout (target evidence): the lender's and borrower's player indices at
// +0x2C/+0x30, the amount still to lend at +0x34 and the per-update rate at
// +0x38. A player's Money is at +0x90 (amount at +0x94) and the argument the
// money transfers take at +0x3BC. The lender reports its state through
// virtual slot 7 (3: a player is gone, 2: done).

typedef int Int;
typedef unsigned int UnsignedInt;

class Rva0039B795;
class Rva0039B7AD;

// The player's Money: withdraw (rowed 0x003B0CB3, WB Money::withdraw) and
// deposit (rowed 0x003B0D7C) under the ledger's placeholder class.
class Rva003B0D7C
{
public:
	UnsignedInt countMoney() const { return m_money; }
	UnsignedInt rva003B0CB3(UnsignedInt amount, Rva0039B795 *arg2, bool flag);	// 0x003B0CB3
	void rva003B0D7C(Int amount, Rva0039B7AD *arg2, bool flag);			// 0x003B0D7C

	void *m_vtbl;
	UnsignedInt m_money;					// +0x04
};

class Player
{
public:
	unsigned char m_pad00[0x90];
	Rva003B0D7C m_money;					// +0x90
	unsigned char m_pad98[0x3BC - 0x98];
	char m_moneyArg;					// +0x3BC
};

class PlayerList
{
public:
	Player *getNthPlayer(Int index);			// 0x002A7A29
};

extern PlayerList *ThePlayerList;


class AIMoneyLender
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void setState(Int state);			// slot 7 (+0x1C)

	void update();

private:
	unsigned char m_pad04[0x2c - 0x4];
	Int m_lenderIndex;					// +0x2C
	Int m_borrowerIndex;					// +0x30
	UnsignedInt m_remaining;				// +0x34
	UnsignedInt m_rate;					// +0x38
};

// AIMoneyLender::update, retail 0x00596B10 (146 bytes): moves up to the rate
// (capped by the lender's money and what is left to lend) from the lender to
// the borrower; done when nothing is left, failed when a player is gone.
void AIMoneyLender::update()
{
	Player *lender = ThePlayerList->getNthPlayer(m_lenderIndex);
	Player *borrower = ThePlayerList->getNthPlayer(m_borrowerIndex);
	if (lender == 0 || borrower == 0)
	{
		setState(3);
		return;
	}
	UnsignedInt amount = lender->m_money.countMoney();
	if (amount > m_rate)
		amount = m_rate;
	if (amount <= 0)
		return;
	if (amount > m_remaining)
		amount = m_remaining;
	lender->m_money.rva003B0CB3(amount, (Rva0039B795 *)&lender->m_moneyArg, true);
	borrower->m_money.rva003B0D7C(amount, (Rva0039B7AD *)&borrower->m_moneyArg, true);
	m_remaining -= amount;
	if (m_remaining == 0)
		setState(2);
}
