// cl: /MD
// ?rva00709E00@Rva00709B80@@QAEXXZ @0x00709E00 68B
// Virtual slot 11 (offset 0x2C) of vtable 0x008EE8C8 (class of ??1Rva00709B80@@UAE@XZ).
// Evidence: vtable slot annotation; tail-jmp to pinned ?rva0070DFE0@BfmeAptValue006DCD20@@QAEXXZ;
// direct callee row ?rva006E0D40@Rva006E0D40@@QAEXXZ at 0x006E0D40.

class Rva006D6470Owner
{
public:
	virtual ~Rva006D6470Owner();
};

class AptReleaseSlot
{
public:
	virtual ~AptReleaseSlot();
	virtual void release();
};

class Rva006E0D40
{
public:
	void rva006E0D40();
};

class BfmeAptValue006DCD20
{
public:
	void rva0070DFE0();
};

class Rva00709B80 : public Rva006D6470Owner
{
public:
	virtual void rva00709E00();
private:
	char m_pad04[0x1C];
	AptReleaseSlot *m_20;
	AptReleaseSlot *m_24;
	AptReleaseSlot *m_28;
};

void Rva00709B80::rva00709E00()
{
	if (m_28)
		m_28->release();
	AptReleaseSlot *a20 = m_20;
	m_28 = 0;
	a20->release();
	AptReleaseSlot *a24 = m_24;
	m_20 = 0;
	a24->release();
	((Rva006E0D40 *)m_24)->rva006E0D40();
	m_24 = 0;
	((BfmeAptValue006DCD20 *)this)->rva0070DFE0();
}
