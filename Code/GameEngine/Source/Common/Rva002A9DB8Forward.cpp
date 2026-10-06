// cl: /MD
//
// Void chase with virtual tail call: if the pointer at +0x2DC is null
// fall off the end (ret 4 with address residue) else tail-jump to its
// vtable slot 15 returning the slot value. Takes one int arg (ret 4)
// that slot 15 receives: forwarding it is what lets cl emit retail's
// tail jmp instead of a call. Evidence: caller 0x003BCB6B pushes computed
// int plus sibling 0x002A9BBD slot 12 precedent. Built from the banked
// attempt reverse/attempts/0x002a9db8.cpp.
class Rva002A9DB8Target
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void *v15(int);
};

struct Rva002A9DB8Holder
{
	Rva002A9DB8Target *m_target;
};

class Rva002A9DB8
{
public:
	void *rva002A9DB8(int unused);
private:
	unsigned char m_pad[0x2DC];
	Rva002A9DB8Holder m_holder;
};

void *Rva002A9DB8::rva002A9DB8(int unused)
{
	if (m_holder.m_target != 0)
		return m_holder.m_target->v15(unused);
}
