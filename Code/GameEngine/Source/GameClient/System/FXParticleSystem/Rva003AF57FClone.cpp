// cl: /EHsc

// ?clone@Rva003AF57F@@QBEPAV1@XZ @0x003AF548 55B: vslot 2 (offset 0x8) of vtable 0x0081D02C
// (class of ??0Rva003AF57F@@QAE@ABV0@@Z in ParticleModuleInfoCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clone 0x003AF1D1 (push 0x28) in Rva003AF208Clone.cpp;
// here push 0x3c plus rowed copy Rva003AF57F. Chain lane: calls 0x003AF57F just landed.

class Rva003AF57F
{
public:
	Rva003AF57F(const Rva003AF57F &other);
	Rva003AF57F *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1C; // +0x1c
	char m_pad20[28]; // +0x20..0x3b: makes sizeof 0x3c for new
};

Rva003AF57F *Rva003AF57F::clone() const
{
	return new Rva003AF57F(*this);
}
