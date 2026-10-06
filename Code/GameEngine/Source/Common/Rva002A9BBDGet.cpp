// cl: /MD
//
// ?rva002A9BBD@Rva002A9BBD@@QAEPAXXZ retail 0x002A9BBD 23B
// Pointer-chase getter with virtual tail call: if the pointer at +0x2DC
// is null return null else tail-jump to its vtable slot 12. Evidence:
// 4 callers incl 0x00356F6E chaining +0x1A130 plus unlock of 2 bodies.
class Rva002A9BBDTarget
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
	virtual void *v12();
};

struct Rva002A9BBDHolder
{
	Rva002A9BBDTarget *m_target;
};

class Rva002A9BBD
{
public:
	void *rva002A9BBD();
private:
	unsigned char m_pad[0x2DC];
	Rva002A9BBDHolder m_holder;
};

void *Rva002A9BBD::rva002A9BBD()
{
	if (m_holder.m_target != 0)
		return m_holder.m_target->v12();
	return 0;
}
