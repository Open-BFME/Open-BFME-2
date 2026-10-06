// cl: /EHsc
// ?clone@Rva003AE5F9@@QBEPAV1@XZ @0x003AE5C2 55B: vslot 2 (offset 0x8) of vtable 0x0081CCD8
// (class of ??0Rva003AE5F9@@QAE@ABV0@@Z in ParticleModuleInfoCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clone 0x003AE4AE (push 0x1c) in Rva003AE4E5Clone.cpp;
// here push 0x1c plus rowed copy Rva003AE5F9. Chain lane: calls 0x003AE5F9 just landed.
// ?clone@Rva003AE5F9@@QBEPAV1@XZ @0x003AE5C2 present-unmatched
class Rva003AE5F9
{
public:
	Rva003AE5F9(const Rva003AE5F9 &other);
	Rva003AE5F9 *clone() const;
private:
	void *m_v0;
	char m_pad04[16];
	void *m_v14;
	void *m_v18;
};
Rva003AE5F9 *Rva003AE5F9::clone() const
{
	return new Rva003AE5F9(*this);
}
