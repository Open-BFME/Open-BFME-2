// cl: /O1 /MD
// ?rva004D70D5@Rva0028C6D6@@UAEXPAX@Z @0x004D70D5 82B
// REF via table slot 0x007F91AC (vtable Rva0028C6D6); pattern matches prev 0x004D6F86 cond slot 0x10 then apply slot 0x28 with {1 1} temp then triple virtual chain 0x70 0x70 0x90; all calls indirect so gate has no direct callees.
struct Temp004D6F86
{
	unsigned char a;
	unsigned char b;
	char m_pad[2];
};

class Mid
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual Mid *f70(void *out);
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void f90(void *out);
};

class Rva004D6F86Arg
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual bool cond();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual Mid *apply(Temp004D6F86 *t);
};

#include "../../Include/Common/Rva0028C6D6.h"

// Retail 0x00262093, 26 bytes: zero two scalar fields and the flag.
Rva0028C6D6::Rva0028C6D6() throw()
    : m_real04(0.0f), m_real08(0.0f), m_field0C(0)
{
}

void Rva0028C6D6::rva004D70D5(void *arg)
{
	Rva004D6F86Arg *a = (Rva004D6F86Arg *)arg;
	Temp004D6F86 t;
	if (!a->cond()) {
		t.a = 1;
		t.b = 1;
		Mid *m1 = a->apply(&t);
		Mid *m2 = m1->f70(&m_field04);
		Mid *m3 = m2->f70(&m_field08);
		m3->f90(&m_field0C);
	}
}
