// cl: /O1 /EHsc /MD
// HAnimPrototypeOwner copy ctor (retail 0x0014CED0, 49 bytes).
// Zeroes the prototype holder, then assigns from the source ref through the
// rowed operator= at 0x0014CDE4 (which validates the MINA FourCC).
// The holder is a RefCountPtr so the assign call sits inside an unwind region
// (single EH state, SEH prolog); its inline default ctor sources the early
// `and [esi],0` ahead of the frame save of `this`. The sibling assign TU
// spells the same word as a raw pointer; both views are 4 bytes at +0x00.
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
class HAnimPrototypeOwner
{
public:
	HAnimPrototypeOwner(const HierarchyPrototypeRef &source);
	HAnimPrototypeOwner &operator=(const HierarchyPrototypeRef &source);
private:
	RefCountPtr<HierarchyPrototype> m_prototype;
};
HAnimPrototypeOwner::HAnimPrototypeOwner(const HierarchyPrototypeRef &source)
{
	operator=(source);
}
