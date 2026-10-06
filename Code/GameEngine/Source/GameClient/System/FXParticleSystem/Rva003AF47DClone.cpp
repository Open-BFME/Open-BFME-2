// cl: /EHsc

// ?clone@Rva003AF47D@@QBEPAV1@XZ @0x003AF446 55B: vslot 2 (offset 0x8) of vtable 0x0081D00C
// (class of ??0Rva003AF47D@@QAE@ABV0@@Z in ParticleModuleInfoCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clones; here push 0x24 plus rowed copy Rva003AF47D.
// Chain lane: calls 0x003AF47D just landed.

class Rva003AF47D
{
public:
	Rva003AF47D(const Rva003AF47D &other);
	Rva003AF47D *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1C; // +0x1c
	char m_pad20[4]; // +0x20..0x23: makes sizeof 0x24 for new
};

Rva003AF47D *Rva003AF47D::clone() const
{
	return new Rva003AF47D(*this);
}
