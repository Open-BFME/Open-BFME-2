// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Rva00180054_MakeOwner@@YA?AVRva00180023@@PBD@Z @ 0x00180054 (94 bytes).
// Registry-owner factory (mixed named-return plus temporary-return recipe,
// as the landed 0x0017FC1E/0x0014CF01 factories). Owner copy ctor pinned at
// 0x00180023.

class HierarchyPrototype
{
public:
	void Release_Ref();
};

// Match the existing counted-registry release provider and shared texture view.
#include "../../../../GameEngineDevice/Source/W3DDevice/GameClient/BFME2ParticleTextureHandles.h"
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

class Rva00180023
{
public:
	Rva00180023() : m_prototype(0) {}
	Rva00180023(const HierarchyPrototypeRef &source);
	~Rva00180023()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};

extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

// ?Rva00180054_MakeOwner@@YA?AVRva00180023@@PBD@Z
Rva00180023 Rva00180054_MakeOwner(const char *name)
{
	if (name == 0)
	{
		Rva00180023 empty;
		return empty;
	}
	return Rva00180023(Rva0061F230_GetPrototype(name));
}

extern "C" char GenBase009EB7D0_vtbl;
class __declspec(novtable) GenBase009EB7D0
{
public:
	__declspec(noinline) GenBase009EB7D0();
	virtual void handle();
private:
	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};
class EmptyBase0017FF77
{
public:
	EmptyBase0017FF77() {}
	~EmptyBase0017FF77();
};
class StringClass
{
public:
	StringClass(const char *name, bool flag);
	~StringClass() { Free_String(); }
private:
	void Free_String();
	char *m_Buffer;
};
class Rva0017FF77 : public GenBase009EB7D0, public EmptyBase0017FF77
{
public:
	Rva0017FF77(const char *name, int a, int b);
private:
	int m_14;
	StringClass m_str18;
	int m_1c;
	int m_20;
};
bool __cdecl Render_Obj_Exists(const char *name);
void *__cdecl operator new(unsigned int size);
void __cdecl Add_Prototype(void *p);

void __cdecl Rva001800B2Create(const char *name, int a, int b)
{
	if (name == 0)
		return;
	if (Render_Obj_Exists(name))
		return;
	Rva0017FF77 *p = new Rva0017FF77(name, a, b);
	Add_Prototype(p);
}
