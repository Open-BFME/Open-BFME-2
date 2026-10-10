// cl: /O1 -DNDEBUG -MD /Ob1 /GX-
// ??0Rva003FD348@@QAE@IID@Z @0x003FD348 40B: constructor of an unnamed BfmeBaseVNH
// subclass (vtable 0x00837CA0, address-derived name): pinned base ctor 0x003FD199,
// own vtable, then the +0x0C member scaled by the same unsigned*0.03f static
// (0x00503E4F, arg in EAX) the base uses. Without /EHsc: no unwind state in retail.
// Target evidence: bytes and callee relocations of 0x003FD348; layout is a guess
// at +0x0C only (one dword written).
static unsigned rva003BB860Scale(unsigned w)
{
	return (int)((float)w * 0.03f);
}

class BfmeBaseVNH
{
public:
	BfmeBaseVNH(unsigned w, char f);
	virtual ~BfmeBaseVNH();
	virtual void handle();

	unsigned m_bfme04;
	char m_bfme08;
};

class Rva003FD348 : public BfmeBaseVNH
{
public:
	Rva003FD348(unsigned w, unsigned x, char f);
	virtual ~Rva003FD348();
	unsigned m_0c;
};

Rva003FD348::Rva003FD348(unsigned w, unsigned x, char f)
	: BfmeBaseVNH(w, f)
	, m_0c(rva003BB860Scale(x))
{
}
