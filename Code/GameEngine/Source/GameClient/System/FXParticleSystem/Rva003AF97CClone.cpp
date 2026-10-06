// cl: /EHsc

// ?clone@Rva003AF97C@@QBEPAV1@XZ @0x003AF945 55B: vslot 2 (offset 0x8) of vtable 0x0081D0EC
// (class of ??0Rva003AF97C@@QAE@ABV0@@Z in ParticleModuleInfoCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clones; here push 0x4c plus rowed copy Rva003AF97C.
// Chain lane: calls 0x003AF97C just landed.

class Rva003AF97C
{
public:
	Rva003AF97C(const Rva003AF97C &other);
	Rva003AF97C *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1C; // +0x1c
	char m_pad20[44]; // +0x20..0x4b: makes sizeof 0x4c for new
};

Rva003AF97C *Rva003AF97C::clone() const
{
	return new Rva003AF97C(*this);
}
