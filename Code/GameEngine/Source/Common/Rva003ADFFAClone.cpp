// cl: /MD
// ?clone@Rva003AE017@@QBEPAV1@XZ, retail 0x003ADFFA, 29 bytes.
// Vslot 2 of vtable 0x0081CED8: clone via new 0x14 plus rowed copy
// ??0Rva003AE017@@QAE@ABV0@@Z at 0x003AE017. Same frameless null-checking new
// shape as rowed clone 0x003AE18A (throw on the copy drops EH).

class Rva003AE017
{
public:
	Rva003AE017(const Rva003AE017 &other) throw();
	Rva003AE017 *clone() const;

private:
	void *m_v0;
	char m_pad04[4];
	void *m_v8;
	void *m_v0C;
	int m_tail10;
};

Rva003AE017 *Rva003AE017::clone() const
{
	return new Rva003AE017(*this);
}
