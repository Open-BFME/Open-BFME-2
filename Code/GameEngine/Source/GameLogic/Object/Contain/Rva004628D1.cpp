// cl: /O1 /DNDEBUG /MD
// ?rva004628D1@Rva004628D1@@UAEXPAVObject@@HH@Z @0x004628D1 125B: void guard-chain then forward via v_9c
// Identity: REF table slot 0x00846064 slot 0; honest address name.
// Evidence: slot 0 table, ret 0xc with 3 args, virtual offsets 0x1fc/0x4c/0x98/0x9c, offsets -0x1c/-0x24/-0x20/-4 and +0x258/+0x274.

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)
#define SLOT32(a) SLOT16(a##0_) SLOT16(a##1_)

class Object;

class Plus4View {
public:
	char m_pad[0x11F];
	unsigned char m_flag;
};

class ModDataView {
public:
	char m_pad[0x81];
	unsigned char m_flag;
};

class Target258 {
public:
	SLOT32(t0) SLOT32(t1) SLOT32(t2) SLOT16(t3) SLOT08(t40,t41,t42,t43,t44,t45,t46,t47)
	virtual void t50(); virtual void t51(); virtual void t52(); virtual void t53();
	virtual void t54(); virtual void t55(); virtual void t56();
	virtual Object *v_1fc();
};

class Object {
public:
	virtual void f0();
	Plus4View *m_p4; // +4
	char m_pad08[0x258 - 0x08];
	Target258 *m_258; // +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_274; // +0x274
};

class MainView {
public:
	SLOT16(m0) virtual void m10(); virtual void m11(); virtual void m12();
	virtual bool v_4c(Object *o);
};

class Base20View {
public:
	SLOT16(b0) SLOT16(b1)
	virtual void b20(); virtual void b21(); virtual void b22();
	virtual void b23(); virtual void b24(); virtual void b25();
	virtual bool v_98(Object *o, int a2, int a3);
	virtual void v_9c(Object *o);
};

class Rva004628D1 {
public:
	virtual void rva004628D1(Object *o, int a2, int a3);
};

// ?rva004628D1@Rva004628D1@@UAEXPAVObject@@HH@Z
void Rva004628D1::rva004628D1(Object *o, int a2, int a3)
{
	if (!o)
		return;
	{
		Object *obj = *(Object **)((char *)this - 0x1C);
		if (((obj->m_p4->m_flag & 0x80) != 0))
			return;
		Target258 *t = o->m_258;
		if (!t)
			return;
		if (t->v_1fc() != obj)
			return;
	}
	MainView *mainv = (MainView *)((char *)this - 0x24);
	if (!mainv->v_4c(o))
		return;
	Base20View *b20 = (Base20View *)((char *)this - 4);
	if (!b20->v_98(o, 1, 0))
		return;
	if (o->m_274 == *(Object **)((char *)this - 0x1C))
		return;
	ModDataView *md = *(ModDataView **)((char *)this - 0x20);
	if (md->m_flag == 0)
		return;
	b20->v_9c(o);
}
