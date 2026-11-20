class BfmeSubBJB
{
public:
	virtual void bfmeSpareBJB0();
	virtual void bfmeSpareBJB1();
	virtual void bfmeSpareBJB2();
	virtual void bfmeSpareBJB3();
	virtual void bfmeSpareBJB4();
	virtual void bfmeSpareBJB5();
	virtual void bfmeSpareBJB6();
	virtual void bfmeSpareBJB7();
	virtual void bfmeRunBJB();
};

class Rva00128780GateBehaviorOwner
{
public:
	bool resolveGateBehavior();
};
class BfmeThingBJB
{
public:
	void bfmeGoBJB();
	unsigned char m_bfmeHead[0x4c];
	BfmeSubBJB *m_bfmeSub;
};

void BfmeThingBJB::bfmeGoBJB()
{
	if (((Rva00128780GateBehaviorOwner *)this)->resolveGateBehavior())
		m_bfmeSub->bfmeRunBJB();
}
