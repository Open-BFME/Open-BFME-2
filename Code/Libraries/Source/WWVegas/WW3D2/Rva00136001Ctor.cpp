// cl: /O1 /EHsc /MD
// ??0Rva00136001@@QAE@ABVHierarchyPrototypeRef@@@Z @ 0x00136001 (49 bytes).
// SEH owner copy ctor zeroes holder then assigns through rowed rva00135E86 at
// 0x00135E86 which validates texture class ids; same 49B SEH shape as HTree
// ctor 0x0017FBED and HAnim ctor 0x0014CED0; caller factory 0x00136032.
class HierarchyPrototype
{
public:
	void *m_obj;
};
class HierarchyPrototypeRef
{
public:
	void *m_object;
};
template <typename T> class RefCountPtr
{
public:
	RefCountPtr() { m_object = 0; }
	~RefCountPtr();
	T *m_object;
};
class Rva00136001
{
public:
	Rva00136001(const HierarchyPrototypeRef &source);
	Rva00136001 &rva00135E86(const HierarchyPrototype &proto);
private:
	RefCountPtr<HierarchyPrototype> m_prototype;
};
Rva00136001::Rva00136001(const HierarchyPrototypeRef &source)
{
	rva00135E86(*(const HierarchyPrototype *)&source);
}
