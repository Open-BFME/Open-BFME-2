// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva00342228@@UAE@XZ, retail 0x00342228, 91 bytes.
// Sibling of ??1Rva00342157 at 0x00342157 (same 91B shape): dtor restoring
// vtable 0x00811900, calling member +0x20 slot 0x3C when present then deleting
// it via slot-0 scalarDeletingDestructor(0) plus operator delete with null->0
// ternary then nulling it inside the if, then calling the fold base at
// 0x0049B47C (pinned ??1Rva0049B47C). Caller is the unclaimed deleting dtor
// at 0x00342FB1. Layout is base 0x0C plus pad to +0x20 plus pointer. Uses the
// inside-if shape that gives pop-before-or.

void __cdecl operator delete(void *ptr);

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class Rva00342228Member
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

class Rva00342228 : public Rva0049B47C
{
public:
	virtual ~Rva00342228();

private:
	char m_pad0C[0x20 - 0x0C];
	Rva00342228Member *m_ptr20;
};

Rva00342228::~Rva00342228()
{
	if (m_ptr20 != 0) {
		m_ptr20->method3C();
		::operator delete(m_ptr20 != 0 ? m_ptr20->scalarDeletingDestructor(0) : 0);
		m_ptr20 = 0;
	}
}
