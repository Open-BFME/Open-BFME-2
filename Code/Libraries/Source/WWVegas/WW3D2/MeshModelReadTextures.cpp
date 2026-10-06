// cl: /DNDEBUG /MD /EHsc
//
// ?read_textures@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018AE50 (284 bytes).
// BFME1 meshmdlio.cpp read_textures port with BFME2 rewrites (all
// retail-measured from the 0x0018AE50 body):
// - bool (AL) returns; Load_Texture returns an owning BfmeHandleCX by value
//   (hidden-pointer call sites), not a raw pointer.
// - EH frame (/EHsc) for the handle temporaries.
// - Textures vector at context+0x10C with the same vptr-led
//   DynamicVectorClass layout as the landed MeshModelReadShaders.cpp unit
//   (VectorMax at +0x8, IsAllocated at +0xD, ActiveCount at +0x10,
//   GrowthStep at +0x14, virtual Resize at slot 2).
// - TextureClass refcount is a WORD at +4 (Add_Ref inlines to addw);
//   releases go to the matched TextureBaseClass::Release_Ref.
// Dedicated TU: the enum-typed meshmdlio.cpp cannot take rows (PostProcess
// precedent). Load_Texture resolves via the harvested pin.

#ifndef NULL
#define NULL 0
#endif

class ChunkLoadClass
{
public:
	bool Open_Chunk(void);
};

class TextureClass
{
public:
	void Add_Ref(void)
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : p(0) {}
	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p) p->Add_Ref();
	}
	~BfmeHandleCX(void)
	{
		if (p) p->Release_Ref();
	}
	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p) other.p->Add_Ref();
		if (p) p->Release_Ref();
		p = other.p;
		return *this;
	}

	TextureClass *p;
};

BfmeHandleCX Load_Texture(ChunkLoadClass &cload);

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
	BfmeHandleCX newtex = ::Load_Texture(cload);
	while (newtex.p != 0) {
		context->Add_Texture(newtex);
		newtex = ::Load_Texture(cload);
	}
	return true;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDoBJE@BfmeSubBJE@@QAE_NPAX@Z=?Add@?$DynamicVectorClass@VBfmeHandleCX@@@@QAE_NABVBfmeHandleCX@@@Z")
