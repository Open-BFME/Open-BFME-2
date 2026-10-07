// cl: /MD /EHsc
// ??0Rva005E9FC1@@QAE@PAX@Z retail 0x005E9FC1 58 bytes.
// Ctor stores vtable 0x00878114 at +0, arg at +4, constructs Rva0057416B member at +8.
// Evidence: lea ecx [esi+8] call 0x0057416B rowed ??0Rva0057416B@@QAE@XZ; caller 0x005EA15B passes caller this.
class Rva0057416B
{
public:
	Rva0057416B();
private:
	unsigned long m_time;
	bool m_flag;
};

struct Rva005E9FC1Base
{
	Rva005E9FC1Base(void *p) : m_04(p) {}
	~Rva005E9FC1Base();
	void *m_04;
};

class Rva005E9FC1 : public Rva005E9FC1Base
{
public:
	Rva005E9FC1(void *p);
	virtual ~Rva005E9FC1(); // defined and verified at5EA224 in Rva005E9FC1Dtor.cpp
private:
	Rva0057416B m_08;
};

Rva005E9FC1::Rva005E9FC1(void *p)
	: Rva005E9FC1Base(p)
{
}
