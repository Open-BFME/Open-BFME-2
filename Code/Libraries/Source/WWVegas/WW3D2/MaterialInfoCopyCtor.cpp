// cl: /DNDEBUG /MD /EHsc /Ob2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// BFME1 MaterialInfoCopyCtor.cpp, adapted to BFME2 RVA 0x16FFD0 (351B).
// Uses the layout and vector vtable identities already established by
// MaterialInfoClassCtor.cpp. Upstream matinfo.cpp clones vertex materials;
// retail spells Clone out as default construction plus assignment, allocating
// 0x6c bytes. Texture handles are copied via the base-vector assignment.
// The vertex-material vector is WWLib/vector.h's DynamicVectorClass: its
// inline constructor and Add expand here, and the unwind funclet calls its
// virtual destructor at 0x0016F580.

extern "C" const void *__identifier("??_7?$DynamicVectorClass@VBfmeHandleCX@@@@6B@")[];

class VertexMaterialClass {
public:
 VertexMaterialClass();
 VertexMaterialClass &operator=(const VertexMaterialClass &);
 char storage[0x6c];
};
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

// Declaration-only view for the existing target assignment at 0x16F610.
// Its four-byte refcounted handles and vector layout agree with this call;
// the donor TextureVectorCell name is not asserted as a target type identity.
class ProxyClass;
template <> class VectorClass<ProxyClass>
{
public:
 VectorClass<ProxyClass> &operator=(const VectorClass<ProxyClass> &);
};

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
	__forceinline TextureVector()
		: TextureVectorBaseCtorShim(0, 0)
	{
		*(unsigned int *)this = ((unsigned int)__identifier("??_7?$DynamicVectorClass@VBfmeHandleCX@@@@6B@"));
  GrowthStep = 10;
  ActiveCount = 0;
	}
 ~TextureVector();
 TextureVector &operator=(const TextureVector &other) {
  ((VectorClass<ProxyClass> &)*this) = (const VectorClass<ProxyClass> &)other;
  ActiveCount = other.ActiveCount;
  GrowthStep = other.GrowthStep;
  return *this;
 }

private:
	int ActiveCount, GrowthStep;
};

// The kept RefCountClass helpers come from size-optimized hlod.cpp, as
// in MaterialInfoClassCtor.cpp. Keep the copy-constructor body at /O2.
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
	MaterialInfoClass(const MaterialInfoClass &);
	virtual ~MaterialInfoClass();

private:
	DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
	TextureVector Textures;
};

MaterialInfoClass::MaterialInfoClass(const MaterialInfoClass &src)
{
 for (int i=0; i<src.VertexMaterials.Count(); ++i) {
  VertexMaterialClass *old = src.VertexMaterials[i];
  VertexMaterialClass *material = new VertexMaterialClass();
  *material = *old;
  VertexMaterials.Add(material);
 }
 Textures = src.Textures;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmeCreated_0035B680@@QAE@PAVGen_0035B680@@@Z=??0MaterialInfoClass@@QAE@ABV0@@Z")
