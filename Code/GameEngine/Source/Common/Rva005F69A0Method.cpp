// cl: /MD
// ?rva005F69A0@Rva005F69A0@@QAEXXZ retail 0x005F69A0 18 bytes.
// Evidence: leaf lane conditional virtual slot 0x10 on member +4 with outer this as arg plus caller 0x005F6AA0 sibling of helper 0x005F698E.
// Model: __thiscall method over member pointer at +4 cleaned via virtual slot 4 taking outer.
class Rva005F69A0Member
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual void m4(void *outer);
};

class Rva005F69A0
{
public:
	virtual ~Rva005F69A0();
	void rva005F69A0();
private:
	Rva005F69A0Member *m_ptr;
};

void Rva005F69A0::rva005F69A0()
{
	if (m_ptr == 0)
		return;
	m_ptr->m4(this);
}
