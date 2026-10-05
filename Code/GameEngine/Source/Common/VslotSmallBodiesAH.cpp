// cl: /O2 /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes) in the /O2 library range, batch AH. As in
// VslotSmallBodiesA-AG, classes and methods are address-derived unless the
// ledger already names them, and model only what each body touches.

typedef int Int;

// 0x00656A30 (seven tables from VA 0x00CE107C on): the rowed +0x254 getter
// 0x00656F20 of the object virtual slot 0 of the secondary base at +0x04
// answers.
class Rva00656F20DwordField
{
public:
	Int get() const;
};
class Rva00656A30First
{
public:
	virtual void firstSlot();
};
class Rva00656A30Second
{
public:
	virtual Rva00656F20DwordField *secondSlot();
};
class Rva00656A30 : public Rva00656A30First, public Rva00656A30Second
{
public:
	Int rva00656A30();
};
Int Rva00656A30::rva00656A30()
{
	return secondSlot()->get();
}

// 0x006EBE50 and 0x00711AB0: the rowed BfmeWrapper1279 0x006F8190 on the
// +0x24 (resp. +0x1C) member.
class BfmeWrapper1279
{
public:
	void rva006F8190();
};
class Rva006EBE50
{
public:
	void rva006EBE50();
private:
	char m_pad00[0x24];
	BfmeWrapper1279 m_24;
};
void Rva006EBE50::rva006EBE50()
{
	m_24.rva006F8190();
}
class Rva00711AB0
{
public:
	void rva00711AB0();
private:
	char m_pad00[0x1C];
	BfmeWrapper1279 m_1C;
};
void Rva00711AB0::rva00711AB0()
{
	m_1C.rva006F8190();
}

// 0x006252F0, 0x0066F5E0, 0x00739700 and 0x00739710: the pinned handlers
// 0x00627770 (+0x10), 0x00676A50 (+0x18) and the rowed ShroudManager
// reset 0x0073DFD0 / drainPending 0x0073D7D0 (+0x10) of a member object.
class Gen009F5040
{
public:
	void handle();
};
class Gen0080AB50
{
public:
	Int handle(unsigned int a);
};
class ShroudManager
{
public:
	void reset();
};
class ShroudManagerImpl008FBA40
{
public:
	void drainPending();
};
class Rva006252F0
{
public:
	void rva006252F0();
private:
	char m_pad00[0x10];
	Gen009F5040 *m_10;
};
void Rva006252F0::rva006252F0()
{
	m_10->handle();
}
class Rva0066F5E0
{
public:
	Int rva0066F5E0(unsigned int a);
private:
	char m_pad00[0x18];
	Gen0080AB50 *m_18;
};
Int Rva0066F5E0::rva0066F5E0(unsigned int a)
{
	return m_18->handle(a);
}
class Rva00739700
{
public:
	void rva00739700();
private:
	char m_pad00[0x10];
	ShroudManager *m_10;
};
void Rva00739700::rva00739700()
{
	m_10->reset();
}
class Rva00739710
{
public:
	void rva00739710();
private:
	char m_pad00[0x10];
	ShroudManagerImpl008FBA40 *m_10;
};
void Rva00739710::rva00739710()
{
	m_10->drainPending();
}
