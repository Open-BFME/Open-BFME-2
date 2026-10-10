// cl: /O1 /DNDEBUG /MD
//
// ?rva00489DE3@AIUpdateInterface@@QAEXXZ @0x00489DE3 75B.
// ?rva00489E2E@AIUpdateInterface@@QAEXXZ @0x00489E2E 99B.
// ?rva00489E91@AIUpdateInterface@@QAEXXZ @0x00489E91 27B.
// The id at +0x4A4 names an object. 0x00489DE3 marks it effectively dead,
// runs 0x0028BAC0 when its byte at +0x454 is set, and stores 1 at +0x4B0.
// 0x00489E2E tells the owner's controlling player, then clears that byte,
// calls 0x0028DCC4, and clears effectively-dead. 0x00489E91 runs
// AIUpdateInterface::loadPostProcess and tail-calls 0x00489DE3 when the
// id is live. A missing object clears the id.

enum ObjectID
{
	OBJECT_ID_NONE = 0
};

class Player;

class Object
{
public:
	void rva0028BAC0(); // 0x0028BAC0
	Player *getControllingPlayer() const;
	void rva0028DCC4();
	void setEffectivelyDead(bool dead);
	char m_pad[0x454];
	unsigned char m_flag454;
	char m_pad455[0x4B0 - 0x455];
	unsigned char m_flag4B0;
};

class Player
{
public:
	void rva002ACECC(ObjectID id);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
public:
	void rva00489DE3();
	void rva00489E2E();
	void rva00489E91();

protected:
	virtual void loadPostProcess();

private:
	char m_pad4[4];
	Object *m_owner;
	char m_padC[0x4A4 - 0x0C];
	ObjectID m_id;
};

void AIUpdateInterface::rva00489DE3()
{
	ObjectID id = m_id;
	if (id == 0)
		return;
	Object *found = TheGameLogic->findObjectByID(id);
	if (found == 0)
		m_id = OBJECT_ID_NONE;
	else
	{
		found->setEffectivelyDead(true);
		if (found->m_flag454 != 0)
			found->rva0028BAC0();
		found->m_flag4B0 = 1;
	}
}

void AIUpdateInterface::rva00489E2E()
{
	if (m_id == 0)
		return;
	if (m_owner != 0)
	{
		Player *player = m_owner->getControllingPlayer();
		if (player != 0)
			player->rva002ACECC(m_id);
	}
	Object *found = TheGameLogic->findObjectByID(m_id);
	if (found == 0)
		m_id = OBJECT_ID_NONE;
	else
	{
		found->m_flag4B0 = 0;
		found->rva0028DCC4();
		found->setEffectivelyDead(false);
	}
}

void AIUpdateInterface::rva00489E91()
{
	AIUpdateInterface::loadPostProcess();
	if (m_id != 0)
		rva00489DE3();
}
