class BfmeSubBJA
{
public:
	virtual void bfmeSpareBJA0();
	virtual void bfmeSpareBJA1();
	virtual void bfmeSpareBJA2();
	virtual void bfmeSpareBJA3();
	virtual void bfmeSpareBJA4();
	virtual void bfmeSpareBJA5();
	virtual void bfmeSpareBJA6();
	virtual void bfmeRunBJA();
};

class Rva00128780GateBehaviorOwner
{
public:
	bool resolveGateBehavior();
};
class BfmeThingBJA
{
public:
	void bfmeGoBJA();
	unsigned char m_bfmeHead[0x4c];
	BfmeSubBJA *m_bfmeSub;
};

void BfmeThingBJA::bfmeGoBJA()
{
	if (((Rva00128780GateBehaviorOwner *)this)->resolveGateBehavior())
		m_bfmeSub->bfmeRunBJA();
}
