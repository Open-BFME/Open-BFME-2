// cl: /O1 /EHsc /arch:SSE2

// ?clone@Rva003AEF6E@@QBEPAV1@XZ @0x003AEF34 58B: vslot 2 (offset 0x8) of vtable 0x0081CF38
// (class of ??0Rva003AEF6E@@QAE@ABV0@@Z in ConcreteModuleTemplateCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clones 0x003AE9DB (push 0xA0) and 0x003AEAA3
// (push 0xAC); here push 0xB4 plus rowed outer copy Rva003AEF6E. Donor BFME1
// DefaultModuleTag1ConcreteModuleTemplateCloneThunk.cpp (clone via new plus copy).

class Rva003AEF6E
{
public:
	Rva003AEF6E(const Rva003AEF6E &other);
	Rva003AEF6E *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
	char m_pad20[136]; // +0x20..0xA7 owned by base copy
	char m_tail[12]; // +0xA8..0xB3: makes sizeof 0xB4 for new
};

Rva003AEF6E *Rva003AEF6E::clone() const
{
	return new Rva003AEF6E(*this);
}
