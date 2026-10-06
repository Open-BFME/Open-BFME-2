// cl: /MD
// ?clone@Rva003AE1A7@@QBEPAV1@XZ, retail 0x003AE18A, 29 bytes.
// Vslot 2 of vtable 0x0081CA40: clone via new 0x44 plus rowed copy
// ??0Rva003AE1A7@@QAE@ABV0@@Z at 0x003AE1A7. Frameless null-checking new
// shape (no EH prolog).

class Rva003AE1A7
{
public:
	Rva003AE1A7(const Rva003AE1A7 &other) throw();
	Rva003AE1A7 *clone() const;

private:
	void *m_v0;
	char m_pad04[4];
	void *m_v8;
	void *m_v0C;
	char m_pad10[0x34];
};

Rva003AE1A7 *Rva003AE1A7::clone() const
{
	return new Rva003AE1A7(*this);
}
