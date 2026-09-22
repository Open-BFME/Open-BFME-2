// cl: /O1
// The base init stores retail vtable 0x00C0BBF8, not bfmeInitTC's 0x00C67840,
// so it needs its own symbol for the DIR32 check.
extern "C" unsigned char bfmeVftTCBase[];

class BfmeThingTC
{
public:
	BfmeThingTC *bfmeBaseTC();
	void *m_bfmeVft;
	int m_bfmeStateFlags04;
	int m_bfmeStateFlags08;
	void *m_bfmeWhat;
};

BfmeThingTC *BfmeThingTC::bfmeBaseTC()
{
	m_bfmeStateFlags04 &= 0;
	m_bfmeStateFlags08 &= 0;
	m_bfmeVft = bfmeVftTCBase;
	return this;
}
