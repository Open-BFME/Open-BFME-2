// cl: /MD
// ?rva00544E76@Rva00544C2A@@QAEHXZ @0x00544E76 59B.
// Leaf slot 4 of vtable 0x00869CF8 (class of Rva00544C2A ctor): chains
// +0x18->+0x14->+0x258 through slot 0x17C, then TheGameLogic+0x40 plus
// slot 0x24 into +0x20. Answers -2 on null and 0 after storing.
// Evidence: thiscall ecx passthrough; ret no args; callers none;
// vtable slot 4; TheGameLogic +0x40.
class GameLogic
{
public:
	char m_pad00[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

typedef void *(__fastcall *Rva00544E76Slot17c)(void *self);
typedef int (__fastcall *Rva00544E76Slot24)(void *self);

struct Rva00544E76Iface
{
	void **m_vtable;
};

struct Rva00544E76Mid
{
	char m_pad00[0x258];
	Rva00544E76Iface *m_258;
};

struct Rva00544E76Outer
{
	char m_pad00[0x14];
	Rva00544E76Mid *m_14;
};

class Rva00544C2A
{
public:
	int rva00544E76();
private:
	char m_pad00[0x18];
	Rva00544E76Outer *m_18;
	char m_pad1C[0x20 - 0x1C];
	int m_20;
};

int Rva00544C2A::rva00544E76()
{
	Rva00544E76Iface *iface = m_18->m_14->m_258;
	void *obj = ((Rva00544E76Slot17c)iface->m_vtable[0x17C / 4])(iface);
	if (obj == 0)
		return -2;
	int extra = TheGameLogic->m_40;
	void **vtable = *(void ***)obj;
	int val = ((Rva00544E76Slot24)vtable[0x24 / 4])(obj);
	m_20 = val + extra;
	return 0;
}
