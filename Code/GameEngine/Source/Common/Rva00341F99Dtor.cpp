// cl: /MD /EHsc
//
// ??1Rva00341F99@@UAE@XZ, retail 0x00341F99, 91 bytes.
// Twin of 0x00342157 (vtable 0x008118B0) and 0x00341E70: dtor restoring vtable,
// calling member +0x20 slot 0x3C when present then deleting it via slot-0
// scalarDeletingDestructor(0) plus operator delete with null->0 ternary
// then nulling it inside the if, then calling the fold base at 0x0049B47C.
// Caller is the deleting dtor 0x00342F79. Layout is base 0x0C plus pad to
// +0x20 plus pointer. Uses the inside-if shape that gives pop-before-or.

void __cdecl operator delete(void *ptr);

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class Rva00341F99Member
{
public:
	virtual void *scalarDeletingDestructor(unsigned int flags);
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void method3C();
};

class Rva00341F99 : public Rva0049B47C
{
public:
	virtual ~Rva00341F99();

private:
	char m_pad0C[0x20 - 0x0C];
	Rva00341F99Member *m_ptr20;
};

Rva00341F99::~Rva00341F99()
{
	if (m_ptr20 != 0) {
		m_ptr20->method3C();
		::operator delete(m_ptr20 != 0 ? m_ptr20->scalarDeletingDestructor(0) : 0);
		m_ptr20 = 0;
	}
}
