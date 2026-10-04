// cl: /O1 /MD /EHsc
// ??0Rva005CF8A1@@QAE@PAX@Z @0x005CF8A1 58B
// Ctor stores vtable 0x00875298 at +0, arg at +4, constructs Rva0057416B member at +8.
// Evidence: unlock lane; same 58B shape as Rva005E9FC1 precedent with empty base plus declared-only dtor arming EH state 0; callee rowed 0x0057416B; caller 0x005D0C45 passes through its arg; ret 4.
class Rva0057416B
{
public:
	Rva0057416B();
private:
	unsigned long m_time;
	bool m_flag;
};

struct Rva005CF8A1Base
{
	Rva005CF8A1Base(void *p) : m_04(p) {}
	~Rva005CF8A1Base();
	void *m_04;
};

class Rva005CF8A1 : public Rva005CF8A1Base
{
public:
	Rva005CF8A1(void *p);
	virtual ~Rva005CF8A1() {}
private:
	Rva0057416B m_08;
};

Rva005CF8A1::Rva005CF8A1(void *p)
	: Rva005CF8A1Base(p)
{
}
