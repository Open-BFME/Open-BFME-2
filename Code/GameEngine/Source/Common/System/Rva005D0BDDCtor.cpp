// cl: /Ireference/shims/bfme2_ascii /EHsc /O1 /arch:SSE /G7
// ??0Rva005D073A@@QAE@PAX@Z @ 0x005D0BDD 84B. Constructor of the rowed
// Rva005D073A (dtor 0x005D073A, scalar deleting dtor 0x005D0A83). Target
// evidence: owner argument stored at +4 of the first base, second base
// (vtable 0x00C62A14) at +8, final vtables 0x00C75568/0x00C7555C, and the
// second base joins TheLivingWorldLogic's list at +0x2C through the rowed
// append 0x005A0B4C. Base split and layout follow the dtor unit.
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

class Rva005D073ASecondBase
{
public:
	virtual ~Rva005D073ASecondBase() {}
};

class Rva005D073AFirstBase
{
public:
	Rva005D073AFirstBase(void *owner) : m_04(owner) {}
	virtual ~Rva005D073AFirstBase() {}
private:
	void *m_04;
};

class Rva005D073A : public Rva005D073AFirstBase, public Rva005D073ASecondBase
{
public:
	Rva005D073A(void *owner);
	virtual ~Rva005D073A();
};

Rva005D073A::Rva005D073A(void *owner)
	: Rva005D073AFirstBase(owner)
{
	TheLivingWorldLogic->m_list2C.append((Rva002BA8F1Listener *)static_cast<Rva005D073ASecondBase *>(this));
}
