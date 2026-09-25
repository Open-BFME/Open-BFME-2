// cl: /O1 /EHsc /MD
// HTreePrototypeOwner copy ctor (retail 0x0017FBED, 49 bytes).
// Twin of the HAnim owner copy ctor: zeroes the prototype holder, then
// assigns from the source ref through the rowed operator= at 0x0017FB0F
// (which validates the HIER FourCC). Same RefCountPtr-holder mechanism for
// the single-state EH frame and the early zero ahead of the `this` save.
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
class HTreePrototypeOwner
{
public:
	HTreePrototypeOwner(const HierarchyPrototypeRef &source);
	HTreePrototypeOwner &operator=(const HierarchyPrototypeRef &source);
private:
	RefCountPtr<HierarchyPrototype> m_prototype;
};
HTreePrototypeOwner::HTreePrototypeOwner(const HierarchyPrototypeRef &source)
{
	operator=(source);
}
