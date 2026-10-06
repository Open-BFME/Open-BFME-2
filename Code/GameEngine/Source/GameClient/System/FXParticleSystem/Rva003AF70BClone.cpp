// cl: /EHsc

// ?clone@Rva003AF70B@@QBEPAV1@XZ @0x003AF6D4 55B: vslot 2 (offset 0x8) of vtable 0x0081D07C
// (class of ??0Rva003AF70B@@QAE@ABV0@@Z in ParticleModuleInfoCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clone 0x003AF1D1 (push 0x28) in Rva003AF208Clone.cpp;
// here push 0x28 plus rowed copy Rva003AF70B. Chain lane: calls 0x003AF70B just landed.

class Rva003AF70B
{
public:
	Rva003AF70B(const Rva003AF70B &other);
	Rva003AF70B *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1C; // +0x1c
	char m_pad20[8]; // +0x20..0x27: makes sizeof 0x28 for new
};

Rva003AF70B *Rva003AF70B::clone() const
{
	return new Rva003AF70B(*this);
}
