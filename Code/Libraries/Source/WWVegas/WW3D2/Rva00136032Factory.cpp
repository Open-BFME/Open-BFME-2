// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Rva00136032_MakeOwner@@YA?AVRva00136001@@PBD@Z @ 0x00136032 (94 bytes).
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

// ?Rva00136032_MakeOwner@@YA?AVRva00136001@@PBD@Z
Rva00136001 Rva00136032_MakeOwner(const char *name)
{
	if (name == 0)
	{
		Rva00136001 empty;
		return empty;
	}
	return Rva00136001(Rva0061F230_GetPrototype(name));
}
