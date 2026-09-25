// cl: /O1 /MD
// HAnimPrototypeOwner assign-from-Ref (retail 0x0014CDE4, 48 bytes).
// Validates the source prototype's FourCC via slot 0x34 ("MINA" 0x414E494D);
// null or matching sources assign through the folded 4B-holder copy at
// 0x000424D0 (twin-pinned as RefCountPtr<HierarchyPrototype>), mismatches
// clear through the folded 4B-holder clear at 0x0004D75B (twin-pinned as
// HAnimPrototypeOwner::clear). Called by the SEH copy ctor 0x0014CED0.
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
class HAnimPrototypeOwner
{
public:
	HAnimPrototypeOwner &operator=(const HierarchyPrototypeRef &source);
	void clear();
private:
	HierarchyPrototype *m_prototype;
};
HAnimPrototypeOwner &HAnimPrototypeOwner::operator=(const HierarchyPrototypeRef &source)
{
	if (source.m_object == 0 || source.m_object->Get_Type() == 0x414E494D)
	{
		*(RefCountPtr<HierarchyPrototype> *)this = *(RefCountPtr<HierarchyPrototype> *)&source;
	}
	else
	{
		((HAnimPrototypeOwner *)this)->clear();
	}
	return *this;
}
