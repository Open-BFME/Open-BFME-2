// cl: /EHsc /MD
// ??0Rva00136001@@QAE@ABVHierarchyPrototypeRef@@@Z @ 0x00136001 (49 bytes).
// SEH owner copy ctor zeroes holder then assigns through rowed rva00135E86 at
// 0x00135E86 which validates texture class ids; same 49B SEH shape as HTree
// ctor 0x0017FBED and HAnim ctor 0x0014CED0; caller factory 0x00136032.
class TextureClass;
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

// Complete native 49B constructors at 0x18095B and 0x180BE0 zero the
// one-pointer owner, then call the existing BOX-tag assignment 0x180815
// or AGGR-tag assignment 0x180AF9. Their factories below both receive the
// matched registry lookup's one-pointer result. RefCountPtr<TextureClass>
// describes the established WORD-at4 counted-resource ABI; the original
// wrapper and prototype types are unknown.
struct BfmeResetAnyRef { void *pointer; };
struct BfmeResetTextureRef {
 void *pointer;
 void clear();
 BfmeResetTextureRef &rva00180815(const BfmeResetAnyRef &rhs);
};
class Rva00180AF9 {
public:
 Rva00180AF9 *rva00180AF9(const RefCountPtr<TextureClass> &other);
};
class Rva0018095B {
public:
 Rva0018095B(const HierarchyPrototypeRef &rhs);
private:
 RefCountPtr<TextureClass> m_value;
};
class Rva00180BE0 {
public:
 Rva00180BE0(const HierarchyPrototypeRef &rhs);
private:
 RefCountPtr<TextureClass> m_value;
};
Rva0018095B::Rva0018095B(const HierarchyPrototypeRef &rhs)
{
 ((BfmeResetTextureRef *)this)->rva00180815(*(const BfmeResetAnyRef *)&rhs);
}
Rva00180BE0::Rva00180BE0(const HierarchyPrototypeRef &rhs)
{
 ((Rva00180AF9 *)this)->rva00180AF9(*(const RefCountPtr<TextureClass> *)&rhs);
}
