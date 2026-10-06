// cl: /MD /EHsc
// ??1Rva005F69F5@@UAE@XZ retail 0x005F69F5 59 bytes.
// Evidence: unlock lane vtable stores at this plus conditional virtual slot 0x18 on member +4 with outer this as arg plus EH prolog plus caller 0x005F6AB0 sibling of 0x005F6941.
// Model: virtual dtor over empty base, member pointer at +4 cleaned via virtual slot 6 taking outer.
class Rva005F69F5Member
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

class Rva005F69F5Base
{
public:
	virtual ~Rva005F69F5Base() {}
};

class Rva005F69F5 : public Rva005F69F5Base
{
public:
	virtual ~Rva005F69F5();
private:
	Rva005F69F5Member *m_ptr;
};

Rva005F69F5::~Rva005F69F5()
{
	if (m_ptr)
		m_ptr->m6(this);
}
