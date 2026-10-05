// cl: /O1 /Ob2 /EHsc /MD
// ??1Rva005E91A9@@UAE@XZ retail 0x005E91A9 60B
// MI dtor second base at +8 via pin 0x005E12D1 plus base vtable restore to g_00BC6F20.
// Layout from deleting wrapper 0x005E9279 vtable 0x00C77FF0#0 and twin 0x005CC37C 60B.
// Evidence: EH_prolog plus two vptr stores C77FF0/C77FD0 then member-base call then BC6F20.

class Rva005E12D1
{
public:
	virtual ~Rva005E12D1();
};

class Rva005E91A9Base
{
public:
	virtual ~Rva005E91A9Base() {}
protected:
	int m_04;
};

class Rva005E91A9 : public Rva005E91A9Base, public Rva005E12D1
{
public:
	virtual ~Rva005E91A9();
};

Rva005E91A9::~Rva005E91A9()
{
}
