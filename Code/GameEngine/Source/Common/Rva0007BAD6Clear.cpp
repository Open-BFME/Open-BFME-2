// cl: /MD
//
// ?rva0007BAD6@Rva0007BAD6@@QAEXXZ @ 0x0007BAD6 (64B): release-all clear
// over +0x14..+0x24. Retail unconditionally runs the rowed holder release
// ?rva005F2577@Rva005F2577Holder@@QAEXXZ (0x005F2577) on the members at
// +0x20/+0x24, then Release-style virtual slot 2 on the interface at +0x1c
// when non-null and nulls it (and-zero per /O1), then the rowed
// ?clear@BfmeResetTextureRef@@QAEXXZ (0x0004D75B) on +0x14/+0x18 each
// guarded by its leading pointer, the +0x18 one as a tail jmp. Member
// types are pinned by the exact callee manglings; the +0x1c interface is
// COM-style stdcall (retail pushes `this` for the slot-2 call, so stack
// `this` is target fact) and carries honest f0/f1/f2 names (slot 2 only
// is target fact). Owner
// unproven (callers 0x0007C10D/0x0007DC5D/0x0009A415 unclaimed), so the
// class carries the honest address name.

struct BfmeResetResource
{
	void Release_Ref();
};

struct BfmeResetTextureRef
{
	BfmeResetResource *pointer;
	void clear();
};

class Rva005F2577Holder
{
public:
	void rva005F2577();

private:
	void *m_ptr;
};

class Rva0007BAD6Inner
{
public:
	virtual void __stdcall f0();
	virtual void __stdcall f1();
	virtual void __stdcall f2();
};

class Rva0007BAD6
{
public:
	void rva0007BAD6();

private:
	int m_pad00[5];
	BfmeResetTextureRef m_14;
	BfmeResetTextureRef m_18;
	Rva0007BAD6Inner *m_1c;
	Rva005F2577Holder m_20;
	Rva005F2577Holder m_24;
};

void Rva0007BAD6::rva0007BAD6()
{
	m_20.rva005F2577();
	m_24.rva005F2577();
	if (m_1c != 0)
	{
		m_1c->f2();
		m_1c = 0;
	}
	if (m_14.pointer != 0)
		m_14.clear();
	if (m_18.pointer != 0)
		m_18.clear();
}
