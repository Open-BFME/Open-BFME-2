// cl: /Ob2 /EHsc /MD
// ??1Rva005E92F7@@UAE@XZ retail 0x005E92F7 60B
// MI dtor second base at +8 via pin 0x005E12D1 plus base vtable restore to g_00BC6F20.
// Layout from twin 0x005E91A9 60B and 0x005CC37C 60B plus deleting wrapper 0x005E948B.
// Evidence: EH_prolog plus two vptr stores C78030/C78010 then member-base call then BC6F20.
// Pin QAE refuted: MI with virtual second base forces virtual dtor UAE same bytes.

class Rva005E12D1
{
public:
	virtual ~Rva005E12D1();
};

class Rva005E92F7Base
{
public:
	virtual ~Rva005E92F7Base() {}
protected:
	int m_04;
};

class Rva005E92F7 : public Rva005E92F7Base, public Rva005E12D1
{
public:
	virtual ~Rva005E92F7();
};

Rva005E92F7::~Rva005E92F7()
{
}
