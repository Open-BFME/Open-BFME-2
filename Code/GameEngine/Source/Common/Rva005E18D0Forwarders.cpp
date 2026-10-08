// cl: /O1 /DNDEBUG /MD
//
// ?tail005E18D0@Rva005E18D0Forwarder@@QAEXXZ retail 0x005E18D0 (12 B) and
// ?tail005E18DC@Rva005E18DCForwarder@@QAEXXZ retail 0x005E18DC (14 B), the
// pin names their wrappers 0x005E1906 / 0x005E1917 call. Target evidence:
// both return when the dword at +0x24 is null; 0x005E18D0 then tail-jumps to
// the rowed 0x005E18B9 on the same object, 0x005E18DC to virtual slot 6 of
// the object held at +0x00. Owners are address-named.
class Rva005E18B9
{
public:
	void rva005E18B9();				// 0x005E18B9
};

class Rva005E18DCTarget
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();				// +0x18
};

class Rva005E18D0Forwarder
{
public:
	void tail005E18D0();

private:
	unsigned char m_pad[0x24];
	void *m_24;					// +0x24
};

void Rva005E18D0Forwarder::tail005E18D0()
{
	if (m_24)
		((Rva005E18B9 *)this)->rva005E18B9();
}

class Rva005E18DCForwarder
{
public:
	void tail005E18DC();

private:
	Rva005E18DCTarget *m_target;			// +0x00
	unsigned char m_pad[0x20];
	void *m_24;					// +0x24
};

void Rva005E18DCForwarder::tail005E18DC()
{
	if (m_24)
		m_target->slot06();
}
