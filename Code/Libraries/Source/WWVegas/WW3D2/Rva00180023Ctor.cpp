// cl: /EHsc /MD
// ??0Rva00180023@@QAE@ABVHierarchyPrototypeRef@@@Z @0x00180023 49B: HLod owner copy ctor zeroes holder then assigns from source ref through rowed operator= at 0x0017FF45 which validates HLOD FourCC. Evidence: same SEH shape as HTree ctor 0x0017FBED and HAnim ctor 0x0014CED0; caller 0x0018008A factory; callee rowed assign.
class HierarchyPrototype;
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
class Rva00180023
{
public:
	Rva00180023(const HierarchyPrototypeRef &source);
	Rva00180023 &operator=(const HierarchyPrototypeRef &source);
private:
	RefCountPtr<HierarchyPrototype> m_prototype;
};
Rva00180023::Rva00180023(const HierarchyPrototypeRef &source)
{
	operator=(source);
}
