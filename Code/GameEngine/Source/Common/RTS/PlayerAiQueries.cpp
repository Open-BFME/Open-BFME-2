// cl: /DNDEBUG /MD
//
// Player AI query forwarders after the BFME1/Zero Hour donor (Player.cpp),
// reading the AI player at +0x2DC.
//
// ?isSkirmishAIPlayer@Player@@QAE_NXZ @0x002A9B7B 23B: return m_ai ?
// m_ai->isSkirmishAI() : false; isSkirmishAI is AIPlayer vtable slot 11
// (0x2C; the AIPlayer table 0x00C62DC8 has a folded constant getter there).
//
// ?rva002A9CB8@Player@@QAE_NXZ @0x002A9CB8 18B (existing pin): the donor's
// Player::isSupplySourceAttacked, if (m_ai) return
// m_ai->isSupplySourceAttacked(); return false; with the callee tail-jumped.
// The callee 0x004F1138 is pinned as AIPlayer::isSupplySourceAttacked: like
// the donor it reads TheGameLogic's frame, sets the check frame to 10 when the
// frame is zero and otherwise clears the attacked supply centre.

class AIPlayer
{
public:
	virtual ~AIPlayer();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual bool isSkirmishAI();
	bool isSupplySourceAttacked();
};

class Player
{
public:
	bool isSkirmishAIPlayer();
	bool rva002A9CB8();
private:
	char m_pad00[0x2DC];
	AIPlayer *m_ai;
};

bool Player::isSkirmishAIPlayer()
{
	return m_ai ? m_ai->isSkirmishAI() : false;
}

bool Player::rva002A9CB8()
{
	if (m_ai)
		return m_ai->isSupplySourceAttacked();
	return false;
}
