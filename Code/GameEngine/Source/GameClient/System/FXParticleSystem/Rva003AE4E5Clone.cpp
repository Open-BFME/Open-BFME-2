// cl: /EHsc
// ?clone@Rva003AE4E5@@QBEPAV1@XZ @0x003AE4AE 55B: vslot 2 (offset 0x8) of vtable 0x0081CC58
// (class of ??0Rva003AE4E5@@QAE@ABV0@@Z in ParticleModuleInfoCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clone 0x003AE64C (push 0x5c) in Rva003AE683Clone.cpp;
// here push 0x1c plus rowed copy Rva003AE4E5. Chain lane: calls 0x003AE4E5 just landed.
// ?clone@Rva003AE4E5@@QBEPAV1@XZ @0x003AE4AE present-unmatched
class Rva003AE4E5
{
public:
	Rva003AE4E5(const Rva003AE4E5 &other);
	Rva003AE4E5 *clone() const;
private:
	void *m_v0;
	char m_pad04[16];
	void *m_v14;
	void *m_v18;
};
Rva003AE4E5 *Rva003AE4E5::clone() const
{
	return new Rva003AE4E5(*this);
}
