// cl: /MD /EHsc
// ??1Rva005F69F5@@QAE@XZ retail 0x005F69F5 59 bytes.
// Evidence: unlock lane vtable stores at this plus conditional virtual slot 0x18 on member +4 with outer this as arg plus EH prolog plus caller 0x005F6AB0 sibling of 0x005F6941.
// Model: dtor over empty base, member pointer at +4 cleaned via virtual slot 6 taking outer.
// Not virtual: slot 0 of the class's table 0x00C797C4 is the byte getter 0x004C9990, the base
// table 0x00BFBCBC it restores is __purecall throughout, and no deleting dtor calls 0x005F69F5
// (its only call is the derived QueuedIconSlot dtor 0x005F6AB0). The pure placeholder keeps the
// base polymorphic, as its all-__purecall table shows.
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
	~Rva005F69F5Base() {}
	virtual void vslot00() = 0;
};

class Rva005F69F5 : public Rva005F69F5Base
{
public:
	~Rva005F69F5();
private:
	Rva005F69F5Member *m_ptr;
};

Rva005F69F5::~Rva005F69F5()
{
	if (m_ptr)
		m_ptr->m6(this);
}
