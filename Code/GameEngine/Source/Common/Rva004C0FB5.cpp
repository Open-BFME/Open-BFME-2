// cl: /MD
// ?rva004C0FB5@Rva004C0FB5@@QAEPAXPAX@Z 0x004C0FB5 81B: Ask-gated 8B copy via float+int.
// Evidence: chain from 0x004C0D4F row; prev BfmeConv540; slot 0x7C; zero fallback.
class Rva004C0D4F
{
public:
	bool rva004C0D4F();
};

struct Pair8
{
	float f;
	int i;
};

class RvaInner004C0FB5
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
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
	virtual Pair8 *GetPtr(Pair8 *tmp);
};

struct RvaSub004C0FB5
{
	char m_pad[0x10];
	RvaInner004C0FB5 m_inner;
};

class Rva004C0FB5
{
public:
	void *rva004C0FB5(void *dst);
	char m_pad[0xF0];
	RvaSub004C0FB5 *m_sub;
};

void *Rva004C0FB5::rva004C0FB5(void *dst)
{
	Pair8 tmp;
	Pair8 zero;
	Pair8 *src;
	zero.i = 0;
	if (((Rva004C0D4F *)((char *)this - 0x10))->rva004C0D4F())
		src = m_sub->m_inner.GetPtr(&tmp);
	else
	{
		zero.f = 0;
		*(float *)&zero.i = 0;
		src = &zero;
	}
	((Pair8 *)dst)->f = src->f;
	((Pair8 *)dst)->i = src->i;
	return dst;
}
