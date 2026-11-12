// cl: /MD /EHsc
// ??1Rva005F6941@@UAE@XZ retail 0x005F6941 59 bytes.
// Evidence: unlock lane vtable stores at this plus conditional virtual slot 0x18 on member +4 with outer this as arg plus EH prolog plus caller 0x005F6A58.
// Model: virtual dtor over empty base, member pointer at +4 cleaned via virtual slot 6 taking outer.
class Rva005F6941Member
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

class Rva005F6941Base
{
public:
	virtual unsigned char rva004C9990() const = 0;	// an abstract interface: retail 0x00BFBCBC is all __purecall
	// Retail table 0x00BFBCBC: 9 __purecall entries follow.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	~Rva005F6941Base() {}
};

class Rva005F6941 : public Rva005F6941Base
{
public:
	virtual unsigned char rva004C9990() const;	// retail slot 0; the destructor is not virtual
	~Rva005F6941();
private:
	Rva005F6941Member *m_ptr;
};

Rva005F6941::~Rva005F6941()
{
	if (m_ptr)
		m_ptr->m6(this);
}
