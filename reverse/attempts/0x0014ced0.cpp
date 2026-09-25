// ??0HAnimPrototypeOwner@@QAE@ABVHierarchyPrototypeRef@@@Z
// partial score=0.95 date=2026-09-25
// cl: /O1 /MD /EHsc /Oy-
// HAnimPrototypeOwner copy ctor from Ref (retail 0x0014CED0, 47 bytes).
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
	void Release_Ref();
};
class HierarchyPrototypeRef
{
public:
	~HierarchyPrototypeRef()
	{
		if (m_object != 0)
			m_object->Release_Ref();
	}
	HierarchyPrototype *m_object;
};
class HAnimPrototypeOwner
{
public:
	HAnimPrototypeOwner(const HierarchyPrototypeRef &source);
	HAnimPrototypeOwner &operator=(const HierarchyPrototypeRef &source);
private:
	HierarchyPrototypeRef m_prototype;
};
HAnimPrototypeOwner::HAnimPrototypeOwner(const HierarchyPrototypeRef &source)
{
	m_prototype.m_object = 0;
	*this = source;
}
