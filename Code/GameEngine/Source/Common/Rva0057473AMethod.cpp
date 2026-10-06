// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0057473A@Rva005746AF@@UAEXXZ retail 0x0057473A 120B
// Virtual slot 1 of 0x0086E3B0 (base Rva005746AF ctor 0x005746AF) and 0x0086E3CC (derived Rva005747DA).
// Evidence: vtable slot 1 shared by both ctors; timeGetTime throttle 1000ms on +8; TreeHintRef at +0xC via rowed op= 0x002174A4 and Release 0x0007DEEF;
// slot 6 (0x18) virtual returning TreeHintRef by value through hidden pointer; second half via rowed get 0x0042D6B4 and forwarder 0x001FF3A9 with TreeHintRef arg.
// Honest Rva name on proven base class. Row type note: get row declares int but result is used as object pointer; forwarder row declares 0 args but retail passes TreeHintRef const& which its slot0 target pops.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	__forceinline ~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

class Rva0042D6B4PtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9_slot0();
	void rva001FF3A9(const TreeHintRef00217D4C &hint);
};

struct Rva0057473AOuter
{
	char m_pad[0x20];
	void *m_field20;
};

class Rva005746AF
{
public:
	virtual ~Rva005746AF();
	virtual void rva0057473A();
	virtual void m_slot2();
	virtual void m_slot3();
	virtual void m_slot4();
	virtual void m_slot5();
	virtual TreeHintRef00217D4C GetHint();
	int m_04;
	unsigned long m_08;
	TreeHintRef00217D4C m_hint;
};

void Rva005746AF::rva0057473A()
{
	if (m_hint.m_ptr != 0)
		return;
	if (timeGetTime() - m_08 < 1000)
		return;
	m_hint = GetHint();
	if (m_hint.m_ptr == 0)
		return;
	int q = ((Rva0042D6B4PtrChaseField *)((Rva0057473AOuter *)m_04)->m_field20)->get();
	if (!q)
		return;
	((Rva001FF3A9 *)q)->Rva001FF3A9::rva001FF3A9(m_hint);
}

// ??1Rva005746AF@@UAE@XZ retail 0x005746D2 104B
// Own vptr 0x0086E3B0; under EH state 0, when the hint at +0xC is set and the
// object fetched through the rowed get 0x0042D6B4 on m_04's +0x20 field
// reports it through the no-arg virtual getter (pinned twin
// ?rva005CB265@Rva005CB265@@UAEHXZ 0x005CB265), that object is cleared via
// the rowed forwarder 0x005CB260; then the hint member's inline dtor releases
// it through 0x0007DEEF. Same unlock check as Rva005E73B2Check.cpp.
class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

Rva005746AF::~Rva005746AF()
{
	if (m_hint.m_ptr == 0)
		return;
	int q = ((Rva0042D6B4PtrChaseField *)((Rva0057473AOuter *)m_04)->m_field20)->get();
	if (q == 0)
		return;
	int held = (int)m_hint.m_ptr;
	if (((Rva005CB265 *)q)->Rva005CB265::rva005CB265() == held)
		((Rva005CB260 *)q)->rva005CB260();
}