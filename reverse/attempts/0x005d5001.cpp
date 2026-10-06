// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// partial score=0.85 date=2026-10-06
// ?rva005D5001@Rva005D5001@@QAEXPBUTreeHintRef00217D4C@@@Z retail 0x005D5001 141 bytes.
// BEST PARTIAL (140B compiled vs 141B retail: all 6 calls plus 4 EH states in
// right order). Remaining: frame sub 0x10 vs 0x0C (temp AsciiString takes its
// own slot at [ebp-0x10] instead of reusing dead arg slot [ebp+8]: needs
// placement new at arg); dlg dtor scope sets and-0 BEFORE 0x00579E47 call vs
// retail AFTER (throw() does not delay; try/catch bloats frame with esp-save
// and ebx; SEH __try changes prologue entirely); method const via C7 imm vs
// retail via-eax mov (needs pinned 0x005D4F27 address; PMF mis-resolves).
// t=75min model=muse-spark score=0.85
class AsciiString;
#include "ascii_string.h"

struct TreeHintRef00217D4C
{
	void *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};

struct TargetRef00217D4C
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual const char *f3();
};

struct DelegateDesc
{
	void *m_object;
	void *m_method;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva00579E47 : public TreeHintRef00217D4C
{
public:
	Rva00579E47 &rva00579E47(const DelegateDesc *d) throw();
	~Rva00579E47()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class Rva005D4F0E
{
public:
	void rva005D4F0E();
};

class Rva005D4F27
{
public:
	void rva005D4F27(int a, int b);
};

class Rva0057C394
{
public:
	void rva0057C394(const AsciiString &s, const TreeHintRef00217D4C &r);
};

class Rva005D5001
{
public:
	void rva005D5001(const TreeHintRef00217D4C *arg);
private:
	char m_00[8];
	TreeHintRef00217D4C m_08;
};

void Rva005D5001::rva005D5001(const TreeHintRef00217D4C *arg)
{
	((Rva005D4F0E *)this)->rva005D4F0E();
	m_08 = *arg;
	DelegateDesc desc;
	desc.m_object = this;
	desc.m_method = (void *)0x009D4F27;
	Rva00579E47 dlg;
	dlg.rva00579E47(&desc);
	AsciiString tmp(((TargetRef00217D4C *)m_08.m_ptr)->f3());
	((Rva0057C394 *)this)->rva0057C394(tmp, dlg);
}
