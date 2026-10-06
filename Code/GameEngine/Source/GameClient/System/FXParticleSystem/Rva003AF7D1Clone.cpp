// cl: /EHsc

// ?clone@Rva003AF7D1@@QBEPAV1@XZ @0x003AF79A 55B: vslot 2 (offset 0x8) of vtable 0x0081D09C
// (class of ??0Rva003AF7D1@@QAE@ABV0@@Z in ParticleModuleInfoCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clone 0x003AF548 (push 0x3c) in Rva003AF57FClone.cpp;
// here push 0x3c plus rowed copy Rva003AF7D1. Chain lane: calls 0x003AF7D1 just landed.

class Rva003AF7D1
{
public:
	Rva003AF7D1(const Rva003AF7D1 &other);
	Rva003AF7D1 *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1C; // +0x1c
	char m_pad20[28]; // +0x20..0x3b: makes sizeof 0x3c for new
};

Rva003AF7D1 *Rva003AF7D1::clone() const
{
	return new Rva003AF7D1(*this);
}
