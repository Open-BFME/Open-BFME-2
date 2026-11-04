// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Clean C++ reconstruction of MaterialInfoClass::MaterialInfoClass().
// The vertex-material vector is WWLib/vector.h's DynamicVectorClass; its
// constructor expands inline and the unwind funclet calls its destructor.

extern "C" const void *__identifier("??_7?$DynamicVectorClass@VBfmeHandleCX@@@@6B@")[];

class VertexMaterialClass;
#include "vector.h"

class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
			Referent = 0;
		}
	}

private:
	T *Referent;
};

typedef RefCountPtr<TextureClass> TextureVectorCell;

class TextureVectorBaseCtorShim
{
public:
	__declspec(noinline) TextureVectorBaseCtorShim(int, TextureVectorCell const *);
	virtual ~TextureVectorBaseCtorShim();

private:
	TextureVectorCell *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

class TextureVector : public TextureVectorBaseCtorShim
{
public:
	__declspec(dllimport) __forceinline TextureVector()
		: TextureVectorBaseCtorShim(0, 0)
	{
		*(unsigned int *)((unsigned char *)this + 0x10) = 0;
		*(unsigned int *)this = ((unsigned int)__identifier("??_7?$DynamicVectorClass@VBfmeHandleCX@@@@6B@"));
		*(unsigned int *)((unsigned char *)this + 0x14) = 10;
	}
	~TextureVector();

private:
	unsigned char m_data[8];
};

// Retail links the size-optimized RefCountClass helpers from hlod.cpp.
#pragma optimize("gsy", on)
class RefCountClass
{
public:
	RefCountClass() : Count(1) {}
	virtual void Delete_This() { delete this; }

protected:
	virtual ~RefCountClass() {}

private:
	int Count;
};

#pragma optimize("", on)

class MaterialInfoClass : public RefCountClass
{
public:
	MaterialInfoClass();
	virtual ~MaterialInfoClass();

private:
	DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
	TextureVector Textures;
};

MaterialInfoClass::MaterialInfoClass()
{
}
