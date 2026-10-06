// cl: /DNDEBUG /MD
//
// ?rva00256A7C@GateProxyBehavior@@UBEMXZ, retail 0x00256A7C, 40 bytes.
// ?rva00256AA4@GateProxyBehavior@@UBEMXZ, retail 0x00256AA4, 40 bytes.
// Virtual slots 11 (offset 0x2C) and 12 (offset 0x30) of GateProxyBehavior
// primary vtable 0x00BEF338 (RVA 0x007EF338, installed at +0 by the rowed
// ctor 0x24E2CC). Each overrides the base GateOpenAndCloseBehavior float
// getters at 0x4987FA/0x4987FE: when the pinned ask at 0x256996
// (?bfmeAskBJA@BfmeThingBJA@@QAE_NXZ, also pinned as DSK/BJB) succeeds it
// returns the sub-object at +0x4C through that slot, otherwise 0.0f.
// No callers. Recipe: float temp via if/else assignment to one local plus
// single return (early returns give tail-jmp plus flds); /arch:SSE gives
// the retail xorps plus movss pair.

class BfmeThingBJA
{
public:
	bool bfmeAskBJA() throw();
};

class GateProxySub
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual float get11() throw();
	virtual float get12() throw();
};

class GateProxyBehavior
{
public:
	virtual void p00();
	virtual void p01();
	virtual void p02();
	virtual void p03();
	virtual void p04();
	virtual void p05();
	virtual void p06();
	virtual void p07();
	virtual void p08();
	virtual void p09();
	virtual void p10();
	virtual float rva00256A7C() const throw();
	virtual float rva00256AA4() const throw();
private:
	char m_pad[0x48];
	GateProxySub *m_sub;
};

float GateProxyBehavior::rva00256A7C() const throw()
{
	float f;
	if (((BfmeThingBJA *)(void *)this)->bfmeAskBJA())
		f = m_sub->get11();
	else
		f = 0.0f;
	return f;
}

float GateProxyBehavior::rva00256AA4() const throw()
{
	float f;
	if (((BfmeThingBJA *)(void *)this)->bfmeAskBJA())
		f = m_sub->get12();
	else
		f = 0.0f;
	return f;
}
