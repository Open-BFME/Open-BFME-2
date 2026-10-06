// ?rva0049D9A2@Rva0049D9A2@@QAEXPBVUpgradeTemplate@@@Z
// partial score=0.88 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva0049D9A2@Rva0049D9A2@@QAEXPBVUpgradeTemplate@@@Z @0x0049D9A2 146B.
// Production-queue cancel: controlling player, in-production guard when the
// template type at +4 is 0, type-2 queue node, Money at Player+0x90, the
// list helper at this-0x20, then slot 0 and operator delete.

class UpgradeTemplate
{
public:
	char m_pad[4];
	int m_type;
};

class Rva0039B7AD
{
public:
	char m_dummy;
};

class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *slot, bool play);
	char m_dummy;
};

class Player
{
public:
	bool rva002AA8EF(const UpgradeTemplate *upgrade) const;
	void rva002ADAC3(const UpgradeTemplate *upgrade, int zero);

	char m_pad[0x90];
	Rva003B0D7C m_money;
	char m_gap[0x3BC - 0x91];
	Rva0039B7AD m_slot;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva0049D526
{
public:
	void rva0049D57F(void *entry);
};

class QueueNode
{
public:
	virtual void *s0(int flag);

	int m_kind;
	char m_pad8[4];
	UpgradeTemplate *m_upgrade;
	char m_pad10[0x18];
	int m_cost;
	char m_pad2C[0x1C];
	QueueNode *m_next;
};

class Rva0049D9A2
{
public:
	void rva0049D9A2(const UpgradeTemplate *upgrade);

private:
	char m_pad[8];
	QueueNode *m_queue;
};

void Rva0049D9A2::rva0049D9A2(const UpgradeTemplate *upgrade)
{
	if (upgrade == 0)
		return;
	Object *obj = *(Object **)((char *)this - 0x18);
	Player *player = obj->getControllingPlayer();
	if (upgrade->m_type == 0)
	{
		if (!player->rva002AA8EF(upgrade))
			return;
	}
	QueueNode *node = m_queue;
	while (node != 0)
	{
		if (node->m_kind == 2 && node->m_upgrade == upgrade)
			break;
		node = node->m_next;
	}
	if (node == 0)
		return;
	player->m_money.rva003B0D7C(node->m_cost, &player->m_slot, true);
	((Rva0049D526 *)((char *)this - 0x20))->rva0049D57F(node);
	void *block = node->s0(0);
	::operator delete(block);
	if (upgrade->m_type == 0)
		player->rva002ADAC3(upgrade, 0);
}
