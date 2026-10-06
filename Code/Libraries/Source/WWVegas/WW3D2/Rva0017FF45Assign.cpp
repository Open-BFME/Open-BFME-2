// cl: /MD
// ??4Rva00180023@@QAEAAV0@ABVHierarchyPrototypeRef@@@Z @0x0017FF45 50B: HLod owner assign-from-Ref validates HLOD FourCC 0x484C4F44 via slot 0x34; null or match assigns through folded 4B-holder copy at 0x000424D0 else clears through folded 4B-holder clear at 0x0004D75B; called by SEH ctor 0x00180023. Evidence: same 4-push plus 2-push shape as HTree assign 0x0017FB0F and HAnim assign 0x0014CDE4; callees rowed RefCountPtr assign and clear; caller 0x0018003E.
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
	Rva00180023 &operator=(const HierarchyPrototypeRef &source);
	void clear();
private:
	HierarchyPrototype *m_prototype;
};
Rva00180023 &Rva00180023::operator=(const HierarchyPrototypeRef &source)
{
	if (source.m_object == 0 || source.m_object->Get_Type() == 0x484C4F44)
	{
		*(RefCountPtr<HierarchyPrototype> *)this = *(RefCountPtr<HierarchyPrototype> *)&source;
	}
	else
	{
		((Rva00180023 *)this)->clear();
	}
	return *this;
}
