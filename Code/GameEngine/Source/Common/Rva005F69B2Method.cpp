// cl: /MD
// ?rva005F69B2@Rva005F69B2@@QAEXXZ retail 0x005F69B2 18 bytes.
// Evidence: leaf lane conditional virtual slot 0x14 on member +4 with outer this as arg plus caller 0x005F6AA8 sibling of 0x005F69A0.
// Model: __thiscall method over member pointer at +4 cleaned via virtual slot 5 taking outer.
class Rva005F69B2Member
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual void m4();
	virtual void m5(void *outer);
};

class Rva005F69B2
{
public:
	virtual ~Rva005F69B2();
	void rva005F69B2();
private:
	Rva005F69B2Member *m_ptr;
};

void Rva005F69B2::rva005F69B2()
{
	if (m_ptr == 0)
		return;
	m_ptr->m5(this);
}
