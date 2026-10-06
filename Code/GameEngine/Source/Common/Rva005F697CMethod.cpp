// cl: /MD
// ?rva005F697C@Rva005F697C@@QAEXXZ retail 0x005F697C 18 bytes.
// Evidence: unlock lane conditional virtual slot 0x18 on member +4 with outer this as arg plus callers 0x005F6A58 0x005F6AB0 sibling of dtors 0x005F6941 0x005F69F5.
// Model: __thiscall method over member pointer at +4 cleaned via virtual slot 6 taking outer.
class Rva005F697CMember
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual void m4();
	virtual void m5();
	virtual void m6(void *outer);
};

class Rva005F697C
{
public:
	virtual ~Rva005F697C();
	void rva005F697C();
private:
	Rva005F697CMember *m_ptr;
};

void Rva005F697C::rva005F697C()
{
	if (m_ptr == 0)
		return;
	m_ptr->m6(this);
}
