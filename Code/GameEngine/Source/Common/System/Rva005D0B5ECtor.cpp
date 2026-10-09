// cl: /Ireference/shims/bfme2_ascii /EHsc /O1 /arch:SSE /G7
// ??0Rva005D06CB@@QAE@PAXPAX0@Z @ 0x005D0B5E 127B. Constructor of the rowed
// Rva005D06CB (dtor 0x005D06CB, scalar deleting dtor 0x005D0A67). Target
// evidence: first base (vtable 0x00C75290) owner at +4, second base (vtable
// 0x00C62A14) at +8, third base Rva005EB753 at +0xC built from (arg, owner+0x14,
// arg) via the rowed constructor 0x005EB706, final vtables 0x00C75554/48/40,
// byte flag at +0x14 cleared, then the second base joins TheLivingWorldLogic's
// list at +0x2C (rowed append 0x005A0B4C). The owner type is a structural
// inference from the +0x14 load.
struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};

class LivingWorldLogic
{
public:
	char m_pad[0x2C];
	Rva005A0B4CList m_list2C;
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005D06CBB2
{
public:
	virtual ~Rva005D06CBB2() {}
};

class Rva005D06CBB1
{
public:
	Rva005D06CBB1(void *owner) : m_04(owner) {}
	virtual ~Rva005D06CBB1() {}
private:
	void *m_04;
};

class Rva005EB753
{
public:
	Rva005EB753(void *a, void *b, void *c);
	virtual ~Rva005EB753();
private:
	void *m_04;
};

struct Rva005D06CBOwner
{
	char m_pad[0x14];
	void *m_14;
};

class Rva005D06CB : public Rva005D06CBB1, public Rva005D06CBB2, public Rva005EB753
{
public:
	Rva005D06CB(Rva005D06CBOwner *owner, void *a, void *c);
	virtual ~Rva005D06CB();
private:
	bool m_14;
};

Rva005D06CB::Rva005D06CB(Rva005D06CBOwner *owner, void *a, void *c)
	: Rva005D06CBB1(owner), Rva005EB753(a, owner->m_14, c)
{
	m_14 = false;
	TheLivingWorldLogic->m_list2C.append((Rva002BA8F1Listener *)static_cast<Rva005D06CBB2 *>(this));
}
