// cl: /O1 /DNDEBUG /MD
//
// ?rva0014D440@Rva0014D440Holder@@QAEXPBV2@0@Z placeholder (renamed below).
// @0x0014D440 52B void. Retail (this=esi Holder with vtable slot02 at +8,
// 2 args ret 8): char buf[0x40] at ebp-0x40; ((Rva0007671F*)buf)->rva()
// via pin 0x0007671F; this->slot02(&buf); outer=[ebp+8];
// inner=outer->m_body00; inner->slot44(outer,[ebp+0xC],&buf) via 45-virtual
// iface (idx44, 3 args). Names opaque; pin proves nothing.
class Rva0007671F
{
public:
	void rva0007671F(void);
};

class Rva0014D440Inner
{
public:
	char m_pad00[0xB0];
	void (__stdcall *m_fnB0)(void *a, void *b, void *c); // +0xB0 member fnptr
};

class Rva0014D440Outer
{
public:
	Rva0014D440Inner *m_body00; // +0x00
};

class Rva0014D440Holder
{
public:
	virtual void h00();
	virtual void h01();
	virtual void slot02(void *p);
	void rva0014D440(Rva0014D440Outer *o, void *b);
};

void Rva0014D440Holder::rva0014D440(Rva0014D440Outer *o, void *b)
{
	char buf[0x40];
	((Rva0007671F *)buf)->rva0007671F();
	slot02(buf);
	Rva0014D440Inner *inner = o->m_body00;
	inner->m_fnB0(o, b, buf);
}
