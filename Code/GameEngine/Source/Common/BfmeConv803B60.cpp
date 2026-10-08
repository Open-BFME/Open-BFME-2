// cl: /GS
// FESL RLST builder @ 0x00803B60 (131B).
// NUM-REGIONS=0, optional TID from src, submit.

class BfmeMsg803B60
{
public:
	BfmeMsg803B60(char *buf, int n) throw();
	~BfmeMsg803B60() throw();
	void addInt(const char *k, int v) throw();

	char m_pad[0x1c];
	unsigned int m_category;
	char m_pad20[0x14];
};

class BfmeSrc803B60
{
public:
	int getInt(const char *k, int d) throw();
};

// The ledger row at the send callee is Rva008038F0Sender::send.
class BfmeC994;
class Rva008038F0Sender
{
public:
	void send(BfmeC994 *m) throw();
};

class BfmeOwner803B60
{
public:
	void go(BfmeSrc803B60 *src);
};


void BfmeOwner803B60::go(BfmeSrc803B60 *src)
{
	char buf[0x40];
	BfmeMsg803B60 msg(buf, 0x40);
	msg.m_category = 'RLST';
	msg.addInt((char *)"NUM-REGIONS", 0);
	int tid = src->getInt((char *)"TID", -1);
	if (tid != -1)
		msg.addInt((char *)"TID", tid);
	((Rva008038F0Sender *)this)->send((BfmeC994 *)&msg);
}
