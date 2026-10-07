// cl: /MD
//
// Three small dump-range bodies: 0x4E52DC walks a circular node list
// calling the pinned 0x4E50C8 on each member, 0x4E7277 is an m_08/m_40
// state gate tail-calling the rowed 0x4E6846, and 0x4E7392 copy-inits
// m_00/m_04/m_08 through the pinned 0x4E72C0. Retail 0x004E52DC 31B,
// 0x004E7277 36B, 0x004E7392 39B. Callee pins are honest address-derived
// candidates; the 0xBFD010 VA goes through a g_00 file-RVA extern (the
// pointed-to bytes read as pointers, so static-struct, not vtable).

extern int g_007FD010;

class Rva004E50C8
{
public:
	void rva004E50C8();
};

struct Rva004E52DCNode
{
	Rva004E52DCNode *m_next;
	char m_pad[4];
	Rva004E50C8 m_sub;
};

class Rva004E52DC
{
public:
	void rva004E52DC();

private:
	void *m_00;
	Rva004E52DCNode *m_04;
};

// ?rva004E52DC@Rva004E52DC@@QAEXXZ @0x004E52DC 31B.
void Rva004E52DC::rva004E52DC()
{
	for (Rva004E52DCNode *n = m_04->m_next; n != m_04; n = n->m_next)
		n->m_sub.rva004E50C8();
}

class Rva004E6846
{
public:
	void rva004E6846();
};

class Rva004E7277
{
public:
	void rva004E701E();
	void rva004E7277();
	void *rva004E7392(Rva004E7277 *arg);
	void rva004E72C0(void *arg);

private:
	void *m_00;
	void *m_04;
	int m_08;
	char m_pad0C[0x40 - 0x0C];
	int m_40;
};

// ?rva004E7277@Rva004E7277@@QAEXXZ @0x004E7277 36B.
void Rva004E7277::rva004E7277()
{
	if (m_08 == 0)
		return;
	if (m_40 != 0)
		rva004E701E();
	if (m_08 == 3)
		((Rva004E6846 *)this)->rva004E6846();
}

// ?rva004E7392@Rva004E7277@@QAEXPAVRva004E7277@@@Z @0x004E7392 39B.
