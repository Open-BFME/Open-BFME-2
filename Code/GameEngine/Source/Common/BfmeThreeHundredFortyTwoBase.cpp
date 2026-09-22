// cl: /O1
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
