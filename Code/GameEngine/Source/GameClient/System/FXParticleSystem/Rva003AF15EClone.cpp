// cl: /EHsc

// ?clone@Rva003AF15E@@QBEPAV1@XZ @0x003AF127 55B: vslot 2 (offset 0x8) of vtable 0x0081CF88
// (class of ??0Rva003AF15E@@QAE@ABV0@@Z in ParticleModuleTemplateCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clones 0x003AEAA3 (push 0xAC) and 0x003AEF34
// (push 0xB4); here push 0x40 plus rowed copy Rva003AF15E. Donor BFME1
// DefaultModuleTag1ConcreteModuleTemplateCloneThunk.cpp (clone via new plus copy).

class Rva003AF15E
{
public:
	Rva003AF15E(const Rva003AF15E &other);
	Rva003AF15E *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_pad1C[36]; // +0x1C..0x3F: makes sizeof 0x40 for new
};

Rva003AF15E *Rva003AF15E::clone() const
{
	return new Rva003AF15E(*this);
}
