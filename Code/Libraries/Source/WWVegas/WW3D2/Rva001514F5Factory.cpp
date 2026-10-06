// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Rva001514F5_MakeOwner@@YA?AVRva0015145C@@PBD@Z @ 0x001514F5 (94 bytes).
// Registry-owner factory (mixed named-return plus temporary-return recipe,
// as the landed 0x0017FC1E/0x0014CF01 factories). Owner copy ctor pinned at
// 0x0015145C.

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

class Rva0015145C
{
public:
	Rva0015145C() : m_prototype(0) {}
	Rva0015145C(const HierarchyPrototypeRef &source);
	~Rva0015145C()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};

extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

// ?Rva001514F5_MakeOwner@@YA?AVRva0015145C@@PBD@Z
Rva0015145C Rva001514F5_MakeOwner(const char *name)
{
	if (name == 0)
	{
		Rva0015145C empty;
		return empty;
	}
	return Rva0015145C(Rva0061F230_GetPrototype(name));
}
