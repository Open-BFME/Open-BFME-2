// cl: /DNDEBUG /MD
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
