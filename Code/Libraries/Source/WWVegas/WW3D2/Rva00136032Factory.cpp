// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Get@RenderAsset@@SA?AVRva00136001@@PBD@Z @ 0x00136032 (94 bytes).
// Registry-owner factory (mixed named-return plus temporary-return recipe,
// as the landed 0x0017FC1E/0x0014CF01 factories). Owner copy ctor pinned at
// 0x00136001.

class HierarchyPrototype
{
public:
	void Release_Ref();
};

class TextureClass
{
public:
	void Release_Ref();
};

class HierarchyPrototypeRef
{
public:
	~HierarchyPrototypeRef()
	{
		if (m_object != 0)
			((TextureClass *)m_object)->Release_Ref();
	}

private:
	HierarchyPrototype *m_object;
};

class Rva00136001
{
public:
	Rva00136001() : m_prototype(0) {}
	Rva00136001(const HierarchyPrototypeRef &source);
	~Rva00136001()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};

extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

// ?Get@RenderAsset@@SA?AVRva00136001@@PBD@Z
class RenderAsset
{
public:
	static Rva00136001 Get(const char *name);
};
// WorldBuilder RenderAsset::Get, WB VA 0x009B38F0 (callgraph lead, score 2.0).
Rva00136001 RenderAsset::Get(const char *name)
{
	if (name == 0)
	{
		Rva00136001 empty;
		return empty;
	}
	return Rva00136001(Rva0061F230_GetPrototype(name));
}

// Complete native 94B factories at 0x18098C and 0x180C11 preserve the
// null-name empty result, matched registry lookup 0x61F230, their own
// rowed owner constructors, and temporary WORD-ref release 0x61ED10.
// Layout and ownership follow the verified factory above. Original
// concrete wrapper and prototype types remain unknown.

class Rva0018095B
{
public:
	Rva0018095B() : m_prototype(0) {}
	Rva0018095B(const HierarchyPrototypeRef &source);
	~Rva0018095B()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};


Rva0018095B Rva0018098C_MakeOwner(const char *name)
{
 if(name==0){ Rva0018095B empty; return empty; }
 return Rva0018095B(Rva0061F230_GetPrototype(name));
}

class Rva00180BE0
{
public:
	Rva00180BE0() : m_prototype(0) {}
	Rva00180BE0(const HierarchyPrototypeRef &source);
	~Rva00180BE0()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};


Rva00180BE0 Rva00180C11_MakeOwner(const char *name)
{
 if(name==0){ Rva00180BE0 empty; return empty; }
 return Rva00180BE0(Rva0061F230_GetPrototype(name));
}

// Native18067A..1806D8 cdecl94B, hidden return plus nullable name.
// The rowed49B constructor180649 consumes a one-pointer BfmeResetAnyRef;
// this wrapper obtains that pointer from the independently rowed211B
// registry lookup61F230. The returned temporary is released through the
// independently rowed36B resource release61ED10. No original owner name
// is inferred from the sibling136032 factory used as a lifetime guide.
// AsResetRef is an inline ABI view of that proven single pointer; it adds
// no ownership operation. The result's null branch writes its pointer0.
struct BfmeResetTagged;
#include "BfmeResetAnyRef.h"
// Use the established holder release spelling from dx8wrapper.cpp.
// Its nullable destructor must be the same byte-and-relocation copy.
#include "BfmeResetResource.h"
class Rva00180649Base
{
public:
 void *pointer;
 Rva00180649Base() : pointer(0) {}
 ~Rva00180649Base() { if (pointer) ((BfmeResetResource *)pointer)->Release_Ref(); }
};
struct BfmeResetTextureRef : Rva00180649Base
{
 // LINK: the default ctor's COMDAT loses to the first-in-order copy; the one local
 // uses a TU-unique no-init ctor (same empty body). No flags touched.
 struct BfmeNoInitFactory {};
 BfmeResetTextureRef(BfmeNoInitFactory) {}
 BfmeResetTextureRef() {}
 BfmeResetTextureRef(const BfmeResetAnyRef &rhs);
};
static __forceinline const BfmeResetAnyRef &AsResetRef(const HierarchyPrototypeRef &source)
{ return reinterpret_cast<const BfmeResetAnyRef &>(source); }
BfmeResetTextureRef Rva0018067A_MakeOwner(const char *name)
{
 if (!name) { BfmeResetTextureRef empty((BfmeResetTextureRef::BfmeNoInitFactory())); return empty; }
 return BfmeResetTextureRef(AsResetRef(Rva0061F230_GetPrototype(name)));
}
