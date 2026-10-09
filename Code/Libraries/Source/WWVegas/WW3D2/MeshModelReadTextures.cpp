// cl: /DNDEBUG /MD /EHsc /ICode/GameEngineDevice/Source/W3DDevice/GameClient
//
// ?read_textures@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018AE50 (284 bytes).
// BFME1 meshmdlio.cpp read_textures port with BFME2 rewrites (all
// retail-measured from the 0x0018AE50 body):
// - bool (AL) returns; Load_Texture returns an owning BFME2ParticleTextureHandle by value
//   (hidden-pointer call sites), not a raw pointer.
// - EH frame (/EHsc) for the handle temporaries.
// - Textures vector at context+0x10C with the same vptr-led
//   DynamicVectorClass layout as the landed MeshModelReadShaders.cpp unit
//   (VectorMax at +0x8, IsAllocated at +0xD, ActiveCount at +0x10,
//   GrowthStep at +0x14, virtual Resize at slot 2).
// - TextureClass refcount is a WORD at +4 (Add_Ref inlines to addw);
//   releases go to the matched TextureBaseClass::Release_Ref.
// Dedicated TU: the enum-typed meshmdlio.cpp cannot take rows (PostProcess
// precedent). The loader and caller share the counted return type.
// BfmeHandleCX remains the established vector element ABI; both handles own
// one texture pointer with the same WORD acquisition and release sequence.

#ifndef NULL
#define NULL 0
#endif

class ChunkLoadClass
{
public:
	bool Open_Chunk(void);
};

#include "BFME2ParticleTextureHandles.h"
class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : p(0) {}
	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p) ++p->m_refCount;
	}
	~BfmeHandleCX(void)
	{
		if (p) p->Release_Ref();
	}
	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p) ++other.p->m_refCount;
		if (p) p->Release_Ref();
		p = other.p;
		return *this;
	}

	TextureClass *p;
};

__forceinline void Assign_Texture(BFME2ParticleTextureHandle &to, const BFME2ParticleTextureHandle &from) {
 if(from.Ptr) ++from.Ptr->m_refCount;
 if(to.Ptr) to.Ptr->Release_Ref();
 to.Ptr=from.Ptr;
}
BFME2ParticleTextureHandle Load_Texture(ChunkLoadClass &cload);

template <class T> class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
	virtual bool operator==(const DynamicVectorClass<T> &) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear(void);
	virtual int ID(T const *ptr);
	virtual int ID(T const &ptr);

	int Length(void) const { return VectorMax; }
	int Count(void) const { return ActiveCount; }
	T &operator[](int index) { return Vector[index]; }

	bool Add(T const &object)
	{
		if (ActiveCount >= Length()) {
			if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
				if (!Resize(Length() + GrowthStep)) {
					return false;
				}
			} else {
				return false;
			}
		}
		(*this)[ActiveCount++] = object;
		return true;
	}

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
	int ActiveCount;
	int GrowthStep;
};

class MeshLoadContextClass
{
public:
	int __forceinline Add_Texture(const BfmeHandleCX &tex)
	{
		int index = Textures.Count();
		Textures.Add(tex);
		return index;
	}

private:
	char m_pad0[0x10C];

public:
	DynamicVectorClass<BfmeHandleCX> Textures;
};

class MeshModelClass
{
protected:
	virtual ~MeshModelClass();
	bool read_textures(ChunkLoadClass &cload, MeshLoadContextClass *context);
};

// ?read_textures@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_textures(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	BFME2ParticleTextureHandle newtex = ::Load_Texture(cload);
	while (newtex.Ptr != 0) {
		context->Add_Texture(reinterpret_cast<const BfmeHandleCX &>(newtex));
		Assign_Texture(newtex, ::Load_Texture(cload));
	}
	return true;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDoBJE@BfmeSubBJE@@QAE_NPAX@Z=?Add@?$DynamicVectorClass@VBfmeHandleCX@@@@QAE_NABVBfmeHandleCX@@@Z")
