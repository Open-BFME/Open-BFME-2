// Single-function extraction from BFME1 BfmeConv940.cpp.
//
// Retail 0x00483BCD is BFME1's ?bfmeGo940D@BfmeThing940D@@QAEXXZ verbatim:
// fetch the result from the source member, then invoke its virtual slot
// 0x44 with a zero argument.
//
// Identity is proven by adjacency: rowed ?bfmeGoBEC (0x00483BBB, same file
// family, same skeleton, virtual slot 0x44) sits immediately before with a
// push-1 where this body pushes 0, exactly matching the two donors
// (bfmeSendBEC(1) vs bfmeVirt940D(0)) and the BFME1 originals at 0x0020D850
// (push 1) and 0x0020D870 (push 0). The Find940D call resolves through the
// existing ?bfmeFind940D pin at 0x0028BCB4; no new pins.

// Open-BFME5 conversions.

class BfmeRes940D
{
public:
	virtual void bfmeSpare940D00();
	virtual void bfmeSpare940D01();
	virtual void bfmeSpare940D02();
	virtual void bfmeSpare940D03();
	virtual void bfmeSpare940D04();
	virtual void bfmeSpare940D05();
	virtual void bfmeSpare940D06();
	virtual void bfmeSpare940D07();
	virtual void bfmeSpare940D08();
	virtual void bfmeSpare940D09();
	virtual void bfmeSpare940D0A();
	virtual void bfmeSpare940D0B();
	virtual void bfmeSpare940D0C();
	virtual void bfmeSpare940D0D();
	virtual void bfmeSpare940D0E();
	virtual void bfmeSpare940D0F();
	virtual void bfmeSpare940D10();
	virtual void bfmeVirt940D(int v);
};

class BfmeSrc940D
{
public:
	BfmeRes940D *bfmeFind940D();
};

class BfmeThing940D
{
public:
	void bfmeGo940D();
	char m_bfmePad[8];
	BfmeSrc940D *m_bfmeSrc;
};

void BfmeThing940D::bfmeGo940D()
{
	BfmeRes940D *r = m_bfmeSrc->bfmeFind940D();
	r->bfmeVirt940D(0);
}
