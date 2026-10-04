// cl: /GS
// FESL LLST builder @ 0x00803BF0 (157B).
// NUM-LOBBIES=1, optional TID, submit, then bfmeGoVJH(TID).

class BfmeMsg803BF0
{
public:
	BfmeMsg803BF0(char *buf, int n) throw();
	~BfmeMsg803BF0() throw();
	void addInt(const char *k, int v) throw();

	char m_pad[0x1c];
	unsigned int m_category;
	char m_pad20[0x14];
};

class BfmeSrc803BF0
{
public:
	int getInt(const char *k, int d) throw();
};

class BfmeOwner803BF0
{
public:
	void go(BfmeSrc803BF0 *src);
	void bfmeGoVJH(int a) throw();
};

// Ledger row at 0x0066F930 owns the send body (?send@Rva008038F0Sender); call it by that name.
class BfmeC994;
class Rva008038F0Sender
{
public:
	void send(BfmeC994 *m) throw();
};


void BfmeOwner803BF0::go(BfmeSrc803BF0 *src)
{
	char buf[0x40];
	BfmeMsg803BF0 msg(buf, 0x40);
	msg.m_category = 'LLST';
	msg.addInt((char *)"NUM-LOBBIES", 1);
	int tid = src->getInt((char *)"TID", -1);
	if (tid != -1)
		msg.addInt((char *)"TID", tid);
	((Rva008038F0Sender *)this)->send((BfmeC994 *)&msg);
	bfmeGoVJH(src->getInt((char *)"TID", 0));
}
