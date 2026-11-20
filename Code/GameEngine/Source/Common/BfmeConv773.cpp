// Three small dispatchers through a sub-object.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv773.cpp); trimmed to the three T1
// bodies the sweep places. The donor's sibling DSM/DSN defs are declared,
// never defined.

class BfmeSubDSK
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual bool bfmeRunDSK();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual bool bfmeRun9DSK();
	virtual bool bfmeRunDSL();
};

class Rva00128780GateBehaviorOwner
{
public:
	bool resolveGateBehavior();
};
class BfmeThingDSK
{
public:
	bool bfmeGoDSK();
	void bfmeGoDSP();
	bool bfmeGoDSL();
	float bfmeGoDSM();
	float bfmeGoDSN();
	char m_bfmeHead[0x4c];
	BfmeSubDSK *m_bfmeSub;
};

bool BfmeThingDSK::bfmeGoDSK()
{
	if (((Rva00128780GateBehaviorOwner *)this)->resolveGateBehavior())
		return m_bfmeSub->bfmeRunDSK();
	return false;
}

bool BfmeThingDSK::bfmeGoDSL()
{
	if (((Rva00128780GateBehaviorOwner *)this)->resolveGateBehavior())
		return m_bfmeSub->bfmeRunDSL();
	return false;
}

void BfmeThingDSK::bfmeGoDSP()
{
	if (((Rva00128780GateBehaviorOwner *)this)->resolveGateBehavior())
		m_bfmeSub->bfmeRun9DSK();
}
