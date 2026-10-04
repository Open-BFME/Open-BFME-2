// cl: /O1 /EHsc /MD
// ??1Rva0057A2B0@@UAE@XZ @0x0057A2B0 84B: MI dtor over 8B trivial first base
// plus Rva005D40A6 second base at +8. Evidence: MI vptr prologue pair plus
// virtual slot6 call through member at +0x54 plus rowed ??1Rva005D40A6 at
// 0x005D40A6 plus deleting-dtor caller 0x0057A455.
class Rva005D40A6
{
public:
	virtual ~Rva005D40A6();
private:
	char m_pad[0x28];
};

class Rva0057A2B0B1
{
public:
	virtual ~Rva0057A2B0B1() {}
private:
	int m_b1x;
};

struct If0057A2B0
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6(void *obj);
};

class Rva0057A2B0 : public Rva0057A2B0B1, public Rva005D40A6
{
public:
	virtual ~Rva0057A2B0();
private:
	char m_pad[0x20];
	If0057A2B0 *m_54;
};
Rva0057A2B0::~Rva0057A2B0()
{
	if (m_54 != 0)
		m_54->s6(this);
}
