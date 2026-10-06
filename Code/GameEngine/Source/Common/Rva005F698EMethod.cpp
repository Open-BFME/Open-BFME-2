// cl: /MD
// ?rva005F698E@Rva005F698E@@QAEXXZ retail 0x005F698E 18 bytes.
// Evidence: leaf lane conditional virtual slot 0x04 on member +4 with outer this as arg plus caller 0x005F6B03 sibling of helper 0x005F697C.
// Model: __thiscall method over member pointer at +4 cleaned via virtual slot 1 taking outer.
class Rva005F698EMember
{
public:
	virtual void m0();
	virtual void m1(void *outer);
};

class Rva005F698E
{
public:
	virtual ~Rva005F698E();
	void rva005F698E();
private:
	Rva005F698EMember *m_ptr;
};

void Rva005F698E::rva005F698E()
{
	if (m_ptr == 0)
		return;
	m_ptr->m1(this);
}
