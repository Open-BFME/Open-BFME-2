// cl: /O1 /Ob2 /EHsc /MD
// ??1Rva005E8D71@@UAE@XZ retail 0x005E8D71 60B
// MI dtor second base at +8 via pin 0x005E12D1 plus base vtable restore to g_00BC6F20.
// Twin of rowed 0x005E92F7 60B: EH_prolog then vptr stores C77F88/C77F68 then
// member-base call then BC6F20.

class Rva005E12D1
{
public:
	virtual ~Rva005E12D1();
};

class Rva005E8D71Base
{
public:
	virtual ~Rva005E8D71Base() {}
protected:
	int m_04;
};

class Rva005E8D71 : public Rva005E8D71Base, public Rva005E12D1
{
public:
	virtual ~Rva005E8D71();
};

Rva005E8D71::~Rva005E8D71()
{
}
