// cl: /O1 /MD
// Address-derived assignment view for the owner whose copy constructor is
// bounded at 0x0018043C. Retail calls this 50-byte body from that constructor
// at 0x00180457. The boundary is supported by the direct call, the leading
// push-esi, and ret-4 at 0x001803D0 immediately before the EH prolog at
// 0x001803D3; Ghidra did not recover this callee as a separate record.
// Target behavior is clear: test the source object's virtual slot +0x34 for
// 0x4D455348 ('MESH'), copy its one-pointer holder on null or a match, and
// release/zero this holder otherwise. The owner name remains address-derived;
// HierarchyPrototypeRef is inferred from the constructor's verified siblings.
class HierarchyPrototype
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual int Get_Type();
};

class HierarchyPrototypeRef
{
public:
	HierarchyPrototype *m_object;
};

template <typename T> class RefCountPtr
{
public:
	const RefCountPtr<T> &operator=(const RefCountPtr<T> &other);
};

class Rva00180023
{
public:
	void clear();
};

class Rva0018043C
{
public:
	Rva0018043C &operator=(const HierarchyPrototypeRef &source);
private:
	HierarchyPrototype *m_prototype;
};

Rva0018043C &Rva0018043C::operator=(const HierarchyPrototypeRef &source)
{
	if (source.m_object == 0 || source.m_object->Get_Type() == 0x4D455348)
	{
		*(RefCountPtr<HierarchyPrototype> *)this = *(RefCountPtr<HierarchyPrototype> *)&source;
	}
	else
	{
		// Reuse the already-rowed generic holder clear alias at 0x0004D75B.
		((Rva00180023 *)this)->clear();
	}
	return *this;
}
