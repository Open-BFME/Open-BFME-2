struct Gen009F5040Item;
struct Gen009F5040Node
{
public:
	char m_pad00[0x4];
	Gen009F5040Item *m_item; // +0x04
	char m_pad08[0x8];
	Gen009F5040Node **m_secondaryPreviousLink; // +0x10
	Gen009F5040Node *m_secondaryNext; // +0x14
	Gen009F5040Node **m_previousLink; // +0x18
	Gen009F5040Node *m_next; // +0x1C
	volatile int m_index; // +0x20
	int m_result24; // +0x24
	int m_result28; // +0x28
	int m_result2c; // +0x2C
};

class BfmeThingZU
{
public:
	void bfmeUnhookZU();
};

class BfmeThingYQ
{
public:
	virtual void bfmeV0YQ() = 0;
	virtual void bfmeV1YQ() = 0;
	virtual void bfmeV2YQ() = 0;
	virtual void bfmeV3YQ() = 0;
	virtual void bfmeV4YQ() = 0;
	virtual void bfmeClearYQ(int flag) = 0;
	virtual Gen009F5040Node *bfmeTakeYQ() = 0;
};

class PartitionManagerImpl
{
public:
	void remove(Gen009F5040Node *n);
	void bfmeDropYQ(BfmeThingYQ *t);
};

void PartitionManagerImpl::bfmeDropYQ(BfmeThingYQ *t)
{
	if (t == 0)
		return;

	Gen009F5040Node *n = t->bfmeTakeYQ();

	if (n == 0)
		return;

	remove(n);
	t->bfmeClearYQ(0);
	((BfmeThingZU *)n)->bfmeUnhookZU();

	::operator delete(n);
}
