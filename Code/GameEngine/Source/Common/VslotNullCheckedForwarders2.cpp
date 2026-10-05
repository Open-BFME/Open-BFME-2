// cl: /O1 /DNDEBUG /MD
//
// 13B null-checked member forwarders with the VslotNullCheckedForwarders.cpp
// shape: load the member pointer and when set tail-jump to one method of it
// with the caller's stack arguments (the callee's ret N gives their count);
// when null return. Targets are unrowed and arrive as address-derived pins:
// 0x001EB72F +0x10 -> 0x001EB68A (ret 0); 0x001EB75C +0x10 -> 0x001EB6FE
// (ret 0); 0x0020EB41 +0x8 -> 0x0020E9A1 (ret 0); 0x005CCB16 +0x4 ->
// 0x005CB283; 0x005CCB23 +0x4 -> 0x0004232F (both forwarders ret 0 so no stack args). 0x005D13D5 +0xC
// reaches the folded 0x000B3FD0 through its existing
// Rva000B3FD0NullTarget pin. Every name is address-derived.

typedef int Int;
class Rva001EB68ANullTarget
{
public:
	void rva001EB68A();
};

class Rva001EB72FNullForwarder
{
public:
	void rva001EB72F();
private:
	char m_lead[0x10];
	Rva001EB68ANullTarget *m_member;
};

void Rva001EB72FNullForwarder::rva001EB72F()
{
	if (m_member)
		m_member->rva001EB68A();
}

class Rva001EB6FENullTarget
{
public:
	void rva001EB6FE();
};

class Rva001EB75CNullForwarder
{
public:
	void rva001EB75C();
private:
	char m_lead[0x10];
	Rva001EB6FENullTarget *m_member;
};

void Rva001EB75CNullForwarder::rva001EB75C()
{
	if (m_member)
		m_member->rva001EB6FE();
}

class Rva0020E9A1NullTarget
{
public:
	void rva0020E9A1();
};

class Rva0020EB41NullForwarder
{
public:
	void rva0020EB41();
private:
	char m_lead[0x8];
	Rva0020E9A1NullTarget *m_member;
};

void Rva0020EB41NullForwarder::rva0020EB41()
{
	if (m_member)
		m_member->rva0020E9A1();
}

class Rva005CB283NullTarget
{
public:
	void rva005CB283();
};

class Rva005CCB16NullForwarder
{
public:
	void rva005CCB16();
private:
	char m_lead[0x4];
	Rva005CB283NullTarget *m_member;
};

void Rva005CCB16NullForwarder::rva005CCB16()
{
	if (m_member)
		m_member->rva005CB283();
}

class Rva0004232FNullTarget
{
public:
	void rva0004232F();
};

class Rva005CCB23NullForwarder
{
public:
	void rva005CCB23();
private:
	char m_lead[0x4];
	Rva0004232FNullTarget *m_member;
};

void Rva005CCB23NullForwarder::rva005CCB23()
{
	if (m_member)
		m_member->rva0004232F();
}

class Rva000B3FD0NullTarget
{
public:
	void rva000B3FD0();
};

class Rva005D13D5NullForwarder
{
public:
	void rva005D13D5();
private:
	char m_lead[0xC];
	Rva000B3FD0NullTarget *m_member;
};

void Rva005D13D5NullForwarder::rva005D13D5()
{
	if (m_member)
		m_member->rva000B3FD0();
}
