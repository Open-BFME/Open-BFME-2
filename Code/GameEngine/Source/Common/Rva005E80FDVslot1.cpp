// cl: /O1 /MD /EHsc
// ?rva005E716D@Rva005E80FD@@QAEXXZ @0x005E716D 17B
// Virtual slot 1 (offset 0x4) of vtable 0x00877F54 (class of ??1Rva005E80FD@@UAE@XZ).
// Helper-then-member forwarder: folded empty helper on this, then tail-call
// member at +0x10 slot 1. Retail calls 0x000B3FD0 annotated as
// ?validate@?$StringBase@G@@ABEXXZ; that address folds many 1B rets, so call
// the rowed public spelling ?init@SmudgeManager@@UAEXXZ for identical bytes
// without a private StringBase friend or class-gate.
// Evidence: packet disasm; vtable from Rva005E80FDDtor.cpp; precedent
// Rva005E21EB::rva005E25CD (helper plus member at +0x0C, same flags).
class SmudgeManager
{
public:
	virtual void init();
};
class Inner005E716D
{
public:
	virtual void v00();
	virtual void v01();
};
class Rva005E80FD
{
public:
	void rva005E716D();
private:
	char m_pad[0x10];
	Inner005E716D *m_10;
};
void Rva005E80FD::rva005E716D()
{
	((SmudgeManager *)this)->SmudgeManager::init();
	m_10->v01();
}
