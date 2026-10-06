// cl: /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ??0Rva005750CF@@QAE@HPAX@Z retail 0x005750CF 86B
// Evidence: target calls rowed base ctor 0x005746AF with int arg; installs vtables 0x0086E4A4 and 0x0086E360 at the primary and +0x10 subobjects; stores manager at +0x14 and appends this+0x10 through rowed helper 0x005A0B4C. Class identity is address-derived; base relationship follows target offsets and vtable stores.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
};
class Rva005746AF
{
public:
	Rva005746AF(int arg);
	virtual ~Rva005746AF();
private:
	int m_04;
	unsigned long m_08;
	TreeHintRef00217D4C m_0C;
};
struct Rva002BA8F1Listener
{
	char opaque[4];
};
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};
class Rva005750CFSecond
{
public:
	virtual ~Rva005750CFSecond();
};
class Rva005750CF : public Rva005746AF, public Rva005750CFSecond
{
public:
	Rva005750CF(int a, void *mgr);
private:
	void *m_14;
};

Rva005750CF::Rva005750CF(int a, void *mgr)
	: Rva005746AF(a)
	, Rva005750CFSecond()
	, m_14(mgr)
{
	((Rva005A0B4CList *)((char *)mgr + 4))->append((Rva002BA8F1Listener *)((char *)this + 0x10));
}
