// cl: /DNDEBUG /MD /EHsc
// ??1Rva005E6D0D@@QAE@XZ retail 0x005E6D0D 103B
// Non-virtual dtor of a polymorphic class: own vptr C77E4C; under EH state 1
// the object passes itself to the rowed
// ?rva002B7250@Rva002B7250@@QAEXPAVCreateAHeroData@@@Z 0x002B7250 on its
// +0x10 container, then when the held ref at +0x1C is set and the owner at +8
// reports it through the no-arg virtual getter (pinned twin
// ?rva005CB265@Rva005CB265@@UAEHXZ 0x005CB265) the owner is cleared through
// the rowed forwarder 0x005CB260; the ref member's inline dtor releases it
// via the rowed fastcall ReleaseTreeHintRef00217D4C 0x0007DEEF and the base's
// inline dtor restores C79544. Same unlock check as Rva005E73B2Check.cpp.
// Names address-derived.

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *data);
};

#include "../../Include/Common/Rva005CB265.h"

class Rva005CB260
{
public:
	void rva005CB260();
};

struct Rva005E6D0DRef
{
	~Rva005E6D0DRef()
	{
		if (m_ref)
			ReleaseTreeHintRef00217D4C(m_ref);
	}

	TargetRef00217D4C *m_ref;
};

// Base vtable C79544 holds the three RET8/RET4/RET8 listener callbacks rowed
// in StrategicUiArmyHandler.cpp; same definition, so the COMDATs agree.
class Rva005FPrimaryCallbacks {public:

 virtual void primary0(void*,void*){}

 virtual void primary1(void*){}

 virtual void primary2(void*,void*){}
 __forceinline ~Rva005FPrimaryCallbacks(){}
};

class Rva005E6D0D : public Rva005FPrimaryCallbacks
{
public:
	~Rva005E6D0D();

private:
	char m_pad04[4];
	Rva005CB265 *m_owner; // +0x08
	char m_pad0C[4];
	Rva002B7250 *m_container; // +0x10
	char m_pad14[0x1C - 0x14];
	Rva005E6D0DRef m_held; // +0x1C
};

Rva005E6D0D::~Rva005E6D0D()
{
	m_container->rva002B7250(reinterpret_cast<CreateAHeroData *>(this));
	int held = (int)m_held.m_ref;
	if (held != 0 && m_owner->Rva005CB265::rva005CB265() == held)
		((Rva005CB260 *)m_owner)->rva005CB260();
}
