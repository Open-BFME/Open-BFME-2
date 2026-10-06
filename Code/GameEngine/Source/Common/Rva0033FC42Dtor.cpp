// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva0033FC42@@UAE@XZ, retail 0x0033FC42, 91 bytes.
// Dtor restoring vtable 0x00811DB0, calling member +0x20 slot 0x3C when
// present then deleting it via slot-0 scalarDeletingDestructor(0) plus
// operator delete with null->0 ternary then nulling it, then calling the
// fold base at 0x0049B47C. Caller is the deleting dtor 0x00343CBA.
// Precedent is Rva00340BDC (single delete) plus Rva00345F21 null->0 ternary;
// the extra slot-0x3C call is TU-local method3C. Layout is base 0x0C plus
// pad to +0x20 plus pointer.

void __cdecl operator delete(void *ptr);

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class Rva0033FC42Member
{
public:
	virtual void *scalarDeletingDestructor(unsigned int flags);
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual int method10();
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

struct Holder0033FC9D
{
	char m_pad00[0x38];
	bool m_38;
};

class Rva0033FC42 : public Rva0049B47C
{
public:
	virtual ~Rva0033FC42();
	int rva0033FC9D();

private:
	char m_pad0C[0x18 - 0x0C];
	Holder0033FC9D *m_ptr18;
	char m_pad1C[0x20 - 0x1C];
	Rva0033FC42Member *m_ptr20;
};

Rva0033FC42::~Rva0033FC42()
{
	if (m_ptr20 != 0) {
		m_ptr20->method3C();
		::operator delete(m_ptr20 != 0 ? m_ptr20->scalarDeletingDestructor(0) : 0);
		m_ptr20 = 0;
	}
}

int Rva0033FC42::rva0033FC9D()
{
	if (m_ptr20 == 0) {
		return 0;
	}
	m_ptr18->m_38 = true;
	int ret = m_ptr20->method10();
	if (ret > 0) {
		ret = 0;
	}
	m_ptr18->m_38 = false;
	return ret;
}

// ??1Rva00341D26@@UAE@XZ, retail 0x00341D26, 91 bytes: the same destructor for a
// sibling class over the same base and members, differing from ~Rva0033FC42's
// bytes only in the vftable it stores on entry (VA 0xc11740). Identity is not
// recovered.
class Rva00341D26 : public Rva0049B47C
{
public:
	virtual ~Rva00341D26();
private:
	char m_pad0C[0x18 - 0x0C];
	Holder0033FC9D *m_ptr18;
	char m_pad1C[0x20 - 0x1C];
	Rva0033FC42Member *m_ptr20;
};

Rva00341D26::~Rva00341D26()
{
	if (m_ptr20 != 0) {
		m_ptr20->method3C();
		::operator delete(m_ptr20 != 0 ? m_ptr20->scalarDeletingDestructor(0) : 0);
		m_ptr20 = 0;
	}
}
