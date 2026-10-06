// cl: /EHsc /MD
// ??1Rva005F8CB0@@UAE@XZ retail 0x005F8CB0 79 bytes.
// Virtual dtor with two bases and one member. Evidence: EH_prolog with two
// vptr stores at +0/+8 then member at +0x1c via rowed 0x005E8908 then base
// at +8 via pinned 0x005E12D1 then base store; caller 0x005F8DEA deleting
// dtor; base size 8 puts second base at +8 size 0x14 puts member at +0x1c.
class Rva005E8908
{
public:
	~Rva005E8908();
private:
	char m_pad[0x1c];
};

class Rva005E12D1
{
public:
	virtual ~Rva005E12D1();
private:
	char m_pad[0x10];
};

class Rva005F8CB0Base0
{
public:
	virtual ~Rva005F8CB0Base0() {}
private:
	int m_04;
};

class Rva005F8CB0 : public Rva005F8CB0Base0, public Rva005E12D1
{
public:
	virtual ~Rva005F8CB0();
private:
	Rva005E8908 m_1c;
};

Rva005F8CB0::~Rva005F8CB0()
{
}
