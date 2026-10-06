// cl: /EHsc

// ?clone@Rva003AF208@@QBEPAV1@XZ @0x003AF1D1 55B: vslot 2 (offset 0x8) of vtable 0x0081CF9C
// (class of ??0Rva003AF208@@QAE@ABV0@@Z in ParticleModuleTemplateCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clones 0x003AEAA3 (push 0xAC) and 0x003AEF34
// (push 0xB4) and landed 0x003AF127 (push 0x40); here push 0x28 plus rowed copy
// Rva003AF208. Donor BFME1 DefaultModuleTag1ConcreteModuleTemplateCloneThunk.cpp
// (clone via new plus copy).

class Rva003AF208
{
public:
	Rva003AF208(const Rva003AF208 &other);
	Rva003AF208 *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_pad1C[12]; // +0x1C..0x27: makes sizeof 0x28 for new
};

Rva003AF208 *Rva003AF208::clone() const
{
	return new Rva003AF208(*this);
}
