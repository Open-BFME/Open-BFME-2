// cl: /MD /Oy-
// Interface slot at 0x0085B6C8 in the 0x0085B6xx module vtable (no direct callers;
// this is the +0x10 interface subobject, so the primary part sits at
// this-0x10 as in the matched BfmeConv698.cpp slots). The zero result is
// the false arm of a conditional expression, which retail materialises
// with xorps and a stack round-trip; the banked attempt used a volatile.
// ?rva004C1028@Rva004C1028@@QAEMH@Z, retail 0x004C1028, 50 bytes.
// Float getter: calls bool helper 0x004C0D4F on outer at this-0x10, on false
// returns 0.0f via SSE xorps, on true tail-jmps virtual slot 2 on inner at
// ([this+0xF0]+0x10) passing through int arg. Evidence: rowed bool callee,
// vptr+8 tail jmp, xmm0 zero plus fld return, neighbours BfmeConv700/575.
class Rva004C0D4F
{
public:
	bool rva004C0D4F();
};

class TailInner
{
public:
	virtual void f0();
	virtual void f1();
	virtual float f2(int x);
};

struct OuterPtr
{
	unsigned char m_pad[0x10];
	TailInner m_inner;
};

class Rva004C1028
{
public:
	float rva004C1028(int x);
private:
	unsigned char m_pad[0xF0];
	OuterPtr *m_pF0;
};

float Rva004C1028::rva004C1028(int x)
{
	Rva004C0D4F *outer = (Rva004C0D4F *)((char *)this - 0x10);
	return outer->rva004C0D4F() ? m_pF0->m_inner.f2(x) : 0.0f;
}
