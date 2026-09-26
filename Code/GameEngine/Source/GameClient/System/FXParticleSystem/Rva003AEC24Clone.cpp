// cl: /O1 /EHsc /arch:SSE2

// ?clone@Rva003AEC5E@@QBEPAV1@XZ @0x003AEC24 58B: vslot 2 (offset 0x8) of vtable 0x0081CE98
// (class of ??0Rva003AEC5E@@QAE@ABV0@@Z in ConcreteModuleTemplateCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clones 0x003AE9DB (push 0xA0) and 0x003AEAA3
// (push 0xAC) and landed 0x003AEF34 (push 0xB4); here push 0x84 plus rowed outer
// copy Rva003AEC5E. Donor BFME1 DefaultModuleTag1ConcreteModuleTemplateCloneThunk.cpp.

class Rva003AEC5E
{
public:
	Rva003AEC5E(const Rva003AEC5E &other);
	Rva003AEC5E *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
	char m_pad20[88]; // +0x20..0x77 owned by base copy
	char m_tail[12]; // +0x78..0x83: makes sizeof 0x84 for new
};

Rva003AEC5E *Rva003AEC5E::clone() const
{
	return new Rva003AEC5E(*this);
}
