// cl: /GS
// FESL HGAM/unsp request builder @ 0x00803C90 (123B).
// Local message, optional TID from src, submit via bfmeSend.

class BfmeMsg803C90
{
public:
	BfmeMsg803C90(char *buf, int n) throw();
	~BfmeMsg803C90() throw();
	void addInt(const char *k, int v) throw();

	char m_pad[0x1c];
	unsigned int m_category;
	unsigned int m_sub;
	char m_pad20[0x10];
};

class BfmeSrc803C90
{
public:
	int getInt(const char *k, int d) throw();
};

class BfmeOwner803C90
{
public:
	void go(BfmeSrc803C90 *src);
};

class BfmeC994;
class Rva008038F0Sender
{
public:
	void send(BfmeC994 *m) throw();
};


void BfmeOwner803C90::go(BfmeSrc803C90 *src)
{
	char buf[0x40];
	BfmeMsg803C90 msg(buf, 0x40);
	msg.m_category = 'HGAM';
	msg.m_sub = 'unsp';
	int tid = src->getInt((char *)"TID", -1);
	if (tid != -1)
		msg.addInt((char *)"TID", tid);
	((Rva008038F0Sender *)(void *)this)->send((BfmeC994 *)(void *)&msg);
}
