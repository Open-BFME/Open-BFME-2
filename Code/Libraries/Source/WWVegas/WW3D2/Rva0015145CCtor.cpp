// cl: /EHsc /DNDEBUG /MD
//
// ??0Rva0015145C@@QAE@ABVHierarchyPrototypeRef@@@Z, retail 0x0015145C, 49 bytes.
// Copy ctor for Rva0015145C (single HierarchyPrototype* at +0): nulls it then
// assigns via rowed BfmeResetShaderRef::operator= 0x0015142A taking the
// layout-compatible HierarchyPrototypeRef. Caller 0x0015152B factory proves
// ctor plus LINK BONUS. Flags mirror siblings plus EHsc for prolog.
struct BfmeResetAnyRef
{
	void *pointer;
};

struct BfmeResetShaderRef
{
	void *pointer;
	BfmeResetShaderRef &operator=(const BfmeResetAnyRef &rhs);
};

class HierarchyPrototype
{
public:
	void Release_Ref();
};

class HierarchyPrototypeRef
{
public:
	HierarchyPrototypeRef() : m_object(0) {}
	~HierarchyPrototypeRef();
	HierarchyPrototype *m_object;
};

class Rva0015145C
{
public:
	Rva0015145C(const HierarchyPrototypeRef &source);
private:
	HierarchyPrototypeRef m_ref; // +0
};

Rva0015145C::Rva0015145C(const HierarchyPrototypeRef &source)
	: m_ref()
{
	*(BfmeResetShaderRef *)this = *(const BfmeResetAnyRef *)&source;
}
