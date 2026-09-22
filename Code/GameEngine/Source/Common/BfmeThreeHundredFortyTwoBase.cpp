// cl: /O1
extern "C" unsigned char bfmeVftTC[];

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
	m_bfmeVft = bfmeVftTC;
	return this;
}
