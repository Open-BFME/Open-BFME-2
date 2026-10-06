// cl: /Ob2 /EHsc /MD
// ??1Rva005CC37C@@UAE@XZ retail 0x005CC37C 60B
// Dtor with MI second base at +8 via pin 0x005E12D1 plus base vtable restore.
// Layout from deleting wrapper 0x005CC44C vtable 0x00C74E38#0.
// Evidence: EH_prolog with cookie plus two vptr stores then member-base call.

class Rva005E12D1
{
public:
	virtual ~Rva005E12D1();
};

class Rva005CC37CBase
{
public:
	virtual ~Rva005CC37CBase() {}
protected:
	int m_04;
};

class Rva005CC37C : public Rva005CC37CBase, public Rva005E12D1
{
public:
	virtual ~Rva005CC37C();
};

Rva005CC37C::~Rva005CC37C()
{
}
