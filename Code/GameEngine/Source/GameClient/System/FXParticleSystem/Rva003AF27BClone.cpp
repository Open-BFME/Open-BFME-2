// cl: /EHsc /Ob2

// ?clone@Rva003AF27B@@QBEPAV1@XZ @0x003AF27B 81B: EH new 0x28 plus rowed base copy
// 0x003AF2CC plus own 3 vftables (0x0081CFB0/0x0081C030/0x0081C8A8). Same EH
// new-plus-copy shape as rowed clones 0x003AEAA3 and 0x003AEF34, with the derived
// copy force-inlined (base call plus vtable stores in one body). Donor BFME1
// DefaultModuleTag1ConcreteModuleTemplateCloneThunk.cpp (clone via new plus copy).

class Rva003AF2CC
{
public:
	Rva003AF2CC(const Rva003AF2CC &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_pad1C[12]; // +0x1C..0x27: makes sizeof 0x28 for new
};

// Rva003AF27B_v0: matched references place it at VA 0xc1cfb0 (retail .rdata value 87).
extern "C" char Rva003AF27B_v0 = 87;
// Rva003AF27B_v14: matched references place it at VA 0xc1c030 (retail .rdata value -12).
extern "C" char Rva003AF27B_v14 = -12;
extern "C" char Rva003AF208_v18;

class Rva003AF27B : public Rva003AF2CC
{
public:
	__forceinline Rva003AF27B(const Rva003AF27B &that)
		: Rva003AF2CC(that)
	{
		*(void **)this = &Rva003AF27B_v0;
		*(void **)((char *)this + 0x14) = &Rva003AF27B_v14;
		*(void **)((char *)this + 0x18) = &Rva003AF208_v18;
	}
	Rva003AF27B *clone() const;
};

Rva003AF27B *Rva003AF27B::clone() const
{
	return new Rva003AF27B(*this);
}
