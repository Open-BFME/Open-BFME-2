// cl: /EHsc
// ?clone@Rva003AE56F@@QBEPAV1@XZ @0x003AE538 55B: vslot 2 (offset 0x8) of vtable 0x0081CC98
// (class of ??0Rva003AE56F@@QAE@ABV0@@Z in ParticleModuleInfoCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clone 0x003AE4AE (push 0x1c) in Rva003AE4E5Clone.cpp;
// here push 0x1c plus rowed copy Rva003AE56F. Chain lane: calls 0x003AE56F just landed.
// ?clone@Rva003AE56F@@QBEPAV1@XZ @0x003AE538 present-unmatched
class Rva003AE56F
{
public:
	Rva003AE56F(const Rva003AE56F &other);
	Rva003AE56F *clone() const;
private:
	void *m_v0;
	char m_pad04[16];
	void *m_v14;
	void *m_v18;
};
Rva003AE56F *Rva003AE56F::clone() const
{
	return new Rva003AE56F(*this);
}
