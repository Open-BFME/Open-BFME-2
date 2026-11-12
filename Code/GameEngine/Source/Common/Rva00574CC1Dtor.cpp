// cl: /O1 /MD /EHsc
// ??1Impl@CommonBehavior@StrategicInGameUI@@UAE@XZ, retail 0x00574CC1..0x00574E0E
// (333 bytes, EH): the destructor of StrategicInGameUI::CommonBehavior::Impl,
// whose constructor 0x0057525F installs the same six tables; table 0x00C6E528
// holds translateGameMessage 0x00574910 and the scalar deleting destructor
// 0x00574E86 that calls this one (own tables 0x00C6E528, 0x00C6E518 (+4),
// 0x00C6E504 (+8), 0x00C6E4F0 (+0xC), 0x00C6E4E4 (+0x10), 0x00C6E4E0
// (+0x14)). It takes its interfaces off the lists they joined (rowed erase
// 0x002B7250): +0x10 from the +0x24 owner, +4 from its +0x28 member's list,
// and for each of the +0x74 / +0x6C owners first releases the matching
// +0x78 / +0x70 hint through the rowed 0x005748B7, then takes +0xC / +8 off
// that owner. It then notifies the +0x20 object's two fields (slots 1 and
// 3). Retail's unwind map destroys the +0x78 and +0x70 hint holders (unwind
// copy 0x005F8F96), the +0x5C member (rowed 0x005CC287, constructor 0x005CC254), the +0x54 cell
// (rowed 0x000AD6F4), the +0x48 member (no own table store anywhere, so a
// novtable view; its out-of-line destructor is the jmp 0x00574338 to the
// rowed 0x005CB8D4), the +0x28 member (rowed 0x005C9B9C)
// and the six interfaces, whose inline destructors restore their tables
// (copies 0x005FED52, 0x00574265, 0x005E186A twice, 0x0057428C, 0x00429191).
// Base and member identities are not established.
class CreateAHeroData;

#include "../../Include/Common/Rva002B7250.h"

struct Rva0057Owner
{
	int m_00;
	Rva002B7250 m_list;			// +0x04
};

struct TargetRef00217D4C;

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Gen_uw_005f8f96
{
	~Gen_uw_005f8f96() { if (m_ref) ReleaseTreeHintRef00217D4C(m_ref); }
	TargetRef00217D4C *m_ref;
};

struct Rva002BED91;

class Rva005748B7
{
public:
	void rva005748B7(Rva002BED91 *hint);
};

class Rva0042D6FDPtrChaseField
{
public:
	int get() const;
};

#include "../../Include/Common/Rva0042D69DPtrChaseField.h"

class Rva0042D6FDTarget
{
public:
	virtual void v0();
	virtual void v1(int arg);
};

class Rva0042D69DTarget
{
public:
	virtual void v0(); virtual void v1(); virtual void v2();
	virtual void v3();
};

class Rva005C9B76
{
public:
	virtual ~Rva005C9B76();
	Rva002B7250 m_list;			// +0x04
private:
	unsigned char m_pad14[0x20 - 0x14];
};

class Rva005CB8D4
{
public:
	virtual ~Rva005CB8D4();
private:
	unsigned char m_pad04[0xC - 4];
};

class __declspec(novtable) Rva00574338 : public Rva005CB8D4
{
public:
	virtual ~Rva00574338() {}
};

#include "../../Include/Common/Rva000AD6F4.h"

class Rva005CC254
{
public:
	virtual ~Rva005CC254();
private:
	unsigned char m_pad04[0x10 - 4];
};

class Gen_uwm_00429191 { public: virtual void s0() = 0; ~Gen_uwm_00429191() {} };
class Gen_uwm_0057428c { public: virtual void s0() = 0; ~Gen_uwm_0057428c() {} };
class Gen_uwm_005e186a { public: virtual void s0() = 0; ~Gen_uwm_005e186a() {} };
class Rva005E186A { public: virtual void s0() = 0; ~Rva005E186A() {} };
class Gen_uwm_00574265 { public: virtual void s0() = 0; ~Gen_uwm_00574265() {} };
class Gen_uwm_005fed52 { public: virtual void s0() = 0; ~Gen_uwm_005fed52() {} };

namespace StrategicInGameUI
{
class CommonBehavior
{
public:
	class Impl;
};
}

class StrategicInGameUI::CommonBehavior::Impl : public Gen_uwm_00429191, public Gen_uwm_0057428c, public Gen_uwm_005e186a,
	public Rva005E186A, public Gen_uwm_00574265, public Gen_uwm_005fed52
{
public:
	virtual ~Impl();
private:
	int m_18;
	int m_1C;
	void *m_20;
	Rva0057Owner *m_24;
	Rva005C9B76 m_28;
	Rva00574338 m_48;
	Rva000AD6F4 m_54;
	int m_58;
	Rva005CC254 m_5C;
	Rva0057Owner *m_6C;
	Gen_uw_005f8f96 m_70;
	Rva0057Owner *m_74;
	Gen_uw_005f8f96 m_78;
};

StrategicInGameUI::CommonBehavior::Impl::~Impl()
{
	if (m_24)
		m_24->m_list.rva002B7250((CreateAHeroData *)static_cast<Gen_uwm_00574265 *>(this));
	m_28.m_list.rva002B7250((CreateAHeroData *)static_cast<Gen_uwm_0057428c *>(this));
	if (m_74)
	{
		((Rva005748B7 *)this)->rva005748B7((Rva002BED91 *)&m_78);
		m_74->m_list.rva002B7250((CreateAHeroData *)static_cast<Rva005E186A *>(this));
	}
	if (m_6C)
	{
		((Rva005748B7 *)this)->rva005748B7((Rva002BED91 *)&m_70);
		m_6C->m_list.rva002B7250((CreateAHeroData *)static_cast<Gen_uwm_005e186a *>(this));
	}
	if (Rva0042D6FDTarget *first = (Rva0042D6FDTarget *)((const Rva0042D6FDPtrChaseField *)m_20)->get())
		first->v1(0);
	if (Rva0042D69DTarget *second = (Rva0042D69DTarget *)((const Rva0042D69DPtrChaseField *)m_20)->get())
		second->v3();
}
