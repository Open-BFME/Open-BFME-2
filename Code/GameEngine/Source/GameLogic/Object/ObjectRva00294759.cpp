// cl: /Ireference/shims/bfme2_ascii
// ?rva00294759@Rva00294759@@QAEXH@Z @0x00294759 79B
// Unlock: __thiscall ret 4 with int param; this+0x264 is ExperienceTracker
// (m_24 at +0x24 compared to param); rowed rva0029439D 0x0029439D twice plus
// virtual slot 0xc4 loop esi times; pin rva0039B4EC 0x0039B4EC (int bool bool).
// Evidence: callers 0x002947CE 0x002952D5 0x003C7E99; prev ObjectRva002943B2
// /O1 /G7; next StlportListInsertFootprints /O1.
#include "ascii_string.h"

class Object
{
public:
	void *rva0029439D();
	void rva00293275(AsciiString s);
};

class ExperienceTracker
{
public:
	bool rva0039B4EC(int a, bool b, bool c);
	char m_pad[0x24];
	int m_24;
};

struct V49Holder
{
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30();
	virtual void f31();
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36();
	virtual void f37();
	virtual void f38();
	virtual void f39();
	virtual void f40();
	virtual void f41();
	virtual void f42();
	virtual void f43();
	virtual void f44();
	virtual void f45();
	virtual void f46();
	virtual void f47();
	virtual void f48();
	virtual void f49();
};

class Rva00294759
{
public:
	void rva00294759(int param);
	void rva002947A8();
private:
	char m_pad[0x264];
	ExperienceTracker *m_exp;
	char m_pad268[0x494 - 0x268];
	AsciiString m_494;
	int m_498;
};

void Rva00294759::rva00294759(int param)
{
	ExperienceTracker *exp = m_exp;
	if (exp == 0)
		return;
	if (exp->m_24 == param)
		return;
	int diff = param - exp->m_24;
	exp->rva0039B4EC(diff, false, false);
	Object *o = (Object *)((Object *)this)->rva0029439D();
	if (o == 0)
		return;
	if (diff <= 0)
		return;
	for (;;) {
		void *p = ((Object *)this)->rva0029439D();
		((V49Holder *)p)->f49();
		if (--diff == 0)
			break;
	}
}

// ?rva002947A8@Rva00294759@@QAEXXZ @0x002947A8 46B chain from 0x00294759.
// Thiscall no args; AsciiString at +0x494 via rowed rva00293275 then int at
// +0x498 via just-landed rva00294759. Evidence: caller 0x0039F269.
void Rva00294759::rva002947A8()
{
	((Object *)this)->rva00293275(m_494);
	rva00294759(m_498);
}
