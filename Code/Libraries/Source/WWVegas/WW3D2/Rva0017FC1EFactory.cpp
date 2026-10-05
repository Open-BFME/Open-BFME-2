// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// Mixed-path factory probe (0x0017FC1E 94B): null path returns a named
// default (NRV candidate with flag), else-path returns a converting
// temporary (RVO candidate, direct). Tests whether the mix yields
// direct-hidden-construction plus the single flag.

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

class HTreePrototypeOwner
{
public:
	HTreePrototypeOwner() : m_prototype(0) {}
	HTreePrototypeOwner(const HierarchyPrototypeRef &source);
	~HTreePrototypeOwner()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};

extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

// ?Rva0017FC1E_MakeOwner@@YA?AVHTreePrototypeOwner@@PBD@Z
HTreePrototypeOwner Rva0017FC1E_MakeOwner(const char *name)
{
	if (name == 0)
	{
		HTreePrototypeOwner empty;
		return empty;
	}
	return HTreePrototypeOwner(Rva0061F230_GetPrototype(name));
}
