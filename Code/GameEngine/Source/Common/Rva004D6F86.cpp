// cl: /Oy- /MD
// ?rva004D6F86@Rva00263895Member@@UAEXPAX@Z retail 0x004D6F86 62B.
// The single slot of vftable 0x007F9200, which the damage-info ctor 0x00263895 and
// copy ctor 0x0028F68F install.
// Leaf via vtable slot 0 of 0x007F9200: if arg cond slot 0x10 is false then call arg slot 0x28
// with {1,1} temp then call member +0x04 slot0 and ptr +0x6c slot0 with arg.
// Evidence: member layout Rva00263895Member +0x04 size 0x68 plus ptr +0x6c plus virtual call pattern.
struct Temp004D6F86
{
	unsigned char a;
	unsigned char b;
	char m_pad[2];
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
	virtual void apply(Temp004D6F86 *t);
};
class Rva00263653View
{
public:
	virtual void add(void *arg);
private:
	char m_pad[0x68 - 4];
};
class Rva004D6F86Ptr
{
public:
	virtual void add(void *arg);
};
class Rva00263895Member
{
public:
	virtual void rva004D6F86(void *context);

	Rva00263653View m_mem04;
	Rva004D6F86Ptr m_obj6C;
};
void Rva00263895Member::rva004D6F86(void *context)
{
	Rva004D6F86Arg *a = (Rva004D6F86Arg *)context;
	Temp004D6F86 options;
	if (!a->cond()) {
		options.a = 1;
		options.b = 1;
		a->apply(&options);
		m_mem04.add(context);
		m_obj6C.add(context);
	}
}
