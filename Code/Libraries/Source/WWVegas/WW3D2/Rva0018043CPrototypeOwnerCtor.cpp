// cl: /O1 /EHsc /MD
// Retail 0x0018043C is a Ghidra-bounded 49-byte constructor. Its factory
// caller at 0x0018046D passes a HierarchyPrototypeRef result to this body,
// and its direct call at 0x00180457 lands on the matched 50-byte assignment
// at 0x001803A1. That assignment verifies source type MESH at virtual slot
// +0x34. The owner type name remains address-derived; the reference wrapper
// layout follows the identical verified HAnim, HTree and HLod sibling ctors.
class HierarchyPrototype;

class HierarchyPrototypeRef
{
public:
	HierarchyPrototype *m_object;
};

template <typename T> class RefCountPtr
{
public:
	RefCountPtr() { m_object = 0; }
	~RefCountPtr();
	T *m_object;
};

class Rva0018043C
{
public:
	Rva0018043C(const HierarchyPrototypeRef &source);
	Rva0018043C &operator=(const HierarchyPrototypeRef &source);
private:
	RefCountPtr<HierarchyPrototype> m_prototype;
};

Rva0018043C::Rva0018043C(const HierarchyPrototypeRef &source)
{
	operator=(source);
}
