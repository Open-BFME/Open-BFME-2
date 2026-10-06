// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva005E12D1@@UAE@XZ retail 0x005E12D1 99B
// Own vptr C779B4; under EH state 1, when the held ref at +0x10 is set and the
// owner at +0xC reports it through the no-arg virtual getter (pinned twin
// ?rva005CB265@Rva005CB265@@UAEHXZ 0x005CB265), the owner is cleared through
// the rowed forwarder 0x005CB260; then the ref member's inline dtor releases
// it via the rowed fastcall ?ReleaseTreeHintRef00217D4C@@YIXPAUTargetRef00217D4C@@@Z
// 0x0007DEEF and the rowed base dtor ??1Rva005E129B@@UAE@XZ 0x005E129B runs.
// Same unlock check as Rva005E73B2Check.cpp. Names address-derived.

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

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

struct Rva005E12D1Ref
{
	~Rva005E12D1Ref()
	{
		if (m_ref)
			ReleaseTreeHintRef00217D4C(m_ref);
	}

	TargetRef00217D4C *m_ref;
};

class Rva005E129B
{
public:
	virtual ~Rva005E129B();

private:
	char m_pad04[0x0C - 4];
};

class Rva005E12D1 : public Rva005E129B
{
public:
	virtual ~Rva005E12D1();

private:
	Rva005CB265 *m_owner; // +0x0C
	Rva005E12D1Ref m_held; // +0x10
};

Rva005E12D1::~Rva005E12D1()
{
	int held = (int)m_held.m_ref;
	if (held != 0 && m_owner->Rva005CB265::rva005CB265() == held)
		((Rva005CB260 *)m_owner)->rva005CB260();
}
