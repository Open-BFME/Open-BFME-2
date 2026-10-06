// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Rva0014CF01_MakeOwner@@YA?AVHAnimPrototypeOwner@@PBD@Z @ 0x0014CF01
// (94 bytes). Registry-owner factory for animation prototypes: null name
// returns a default owner, otherwise a converting temporary. Mixed
// named-return plus temporary-return sources the single construction flag
// with direct hidden-slot construction (same recipe as the landed HTree
// factory 0x0017FC1E, whose re_log partial first mapped this family).

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

class HAnimPrototypeOwner
{
public:
	HAnimPrototypeOwner() : m_prototype(0) {}
	HAnimPrototypeOwner(const HierarchyPrototypeRef &source);
	~HAnimPrototypeOwner()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};

extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

// ?Rva0014CF01_MakeOwner@@YA?AVHAnimPrototypeOwner@@PBD@Z
HAnimPrototypeOwner Rva0014CF01_MakeOwner(const char *name)
{
	if (name == 0)
	{
		HAnimPrototypeOwner empty;
		return empty;
	}
	return HAnimPrototypeOwner(Rva0061F230_GetPrototype(name));
}
