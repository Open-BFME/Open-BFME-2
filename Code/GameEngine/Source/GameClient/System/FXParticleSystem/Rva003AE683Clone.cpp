// cl: /EHsc
// ?clone@Rva003AE683@@QBEPAV1@XZ @0x003AE64C 55B: vslot 2 (offset 0x8) of vtable 0x0081CD14
// (class of ??0Rva003AE683@@QAE@ABV0@@Z in Rva003AE683CopyCtor.cpp).
// Same EH new-plus-copy shape as rowed clone 0x003AF548 (push 0x3c) in Rva003AF57FClone.cpp;
// here push 0x5c plus rowed copy Rva003AE683. Chain lane: calls 0x003AE683 just landed.
class Rva003AE683
{
public:
	Rva003AE683(const Rva003AE683 &other);
	Rva003AE683 *clone() const;
private:
	void *m_v0;
	char m_pad04[16];
	void *m_v14;
	void *m_v18;
	char m_pad1C[0x40];
};
Rva003AE683 *Rva003AE683::clone() const
{
	return new Rva003AE683(*this);
}
