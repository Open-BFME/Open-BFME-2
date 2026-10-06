// cl: /EHsc
// ?clone@Rva003AEDE9@@QBEPAV1@XZ @0x003AEDB2 55B: vslot 2 (offset 0x8) of vtable 0x0081CF18
// (class of ??0Rva003AEDE9@@QAE@ABV0@@Z in Rva003AEDE9CopyCtor.cpp).
// Same EH new-plus-copy shape as rowed clone 0x003AF127 (push 0x40) in Rva003AF15EClone.cpp;
// here push 0x40 plus rowed copy Rva003AEDE9. Chain lane: calls 0x003AEDE9 just landed.
// ?clone@Rva003AEDE9@@QBEPAV1@XZ @0x003AEDB2 present-unmatched
class Rva003AEDE9
{
public:
	Rva003AEDE9(const Rva003AEDE9 &other);
	Rva003AEDE9 *clone() const;
private:
	void *m_v0;
	char m_pad04[16];
	void *m_v14;
	void *m_v18;
	char m_pad1C[36];
};
Rva003AEDE9 *Rva003AEDE9::clone() const
{
	return new Rva003AEDE9(*this);
}
