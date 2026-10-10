// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?read_Rva0018AF70@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z @0x0018AF70 272B
// MeshModelClass::read_Rva0018AF70, retail 0x0018AF70 (272 bytes):
// Chunk 0x50 reader in read_chunks (MeshModelReadChunks.cpp:144) beside
// read_textures 0x0018AE50 and read_texture_stage 0x0018B080. Creates an
// FXShaderSetup (new 0x34, ctor 0x001525FB), Load_W3D 0x00152E4D, Add_Ref at
// +4, vector Add with Resize slot 2, Release, Close_Chunk/Open_Chunk loop.
// Vector at context+0xF4 with DynamicVectorClass layout (Vector+0x4,
// VectorMax+0x8, ActiveCount+0x10, GrowthStep+0x14) as in ReadTextures.
// Complete native extent: RET8 at 0018B07D ends0018B080, 272 bytes.
// Queue269 stopped before that RET. Existing read_chunks caller proves the
// object/ChunkLoad/context ABI, but original chunk reader name is unknown.
// Volatile qualification belongs only to the local parameter definition;
// its existing declaration is unchanged. Native reloads context from the
// argument slot each loop, so cload stays in EBP and the vector view in ESI.
// This closes the older bank's persistent-context EBP versus cload swap.
// The vector algorithm is the clean WWLib DynamicVectorClass Add pattern;
// constructor and Load_W3D bind existing FXShaderSetup owners. No new pins.
#ifndef NULL
#define NULL 0
#endif

class ChunkLoadClass
{
public:
	bool Open_Chunk();
	bool Close_Chunk();
};

class FXShaderSetup;

class RefCountClass
{
	friend struct BfmeFXShaderRefOps;
public:
	RefCountClass() : NumRefs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

	int NumRefs;
};

// TU-local copies of refcount.h's RefCountClass::Add_Ref and Release_Ref, which retail's reader
// inlines. As members of this view they emitted this /O2 unit's COMDAT copies, which are not the
// bodies the link keeps (Release_Ref's retail body is 0x005D1A7D), so the unit could not link; the
// struct keeps the inlined code and emits no copy.
struct BfmeFXShaderRefOps {
	static __forceinline void Add_Ref(RefCountClass *ref) { ref->NumRefs++; }
	static __forceinline void Release_Ref(RefCountClass *ref)
	{
		if (--ref->NumRefs == 0)
			ref->Delete_This();
	}
};

class FXShaderSetup : public RefCountClass
{
public:
	FXShaderSetup();
	bool Load_W3D(ChunkLoadClass &cload);

protected:
	virtual ~FXShaderSetup();

private:
	char m_pad[0x34 - 8];
};

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
	char m_pad000[0xF4];
	DynamicVectorClass<FXShaderSetup *> m_shaderVec; // +0xF4
};

class MeshModelClass
{
protected:
	bool read_Rva0018AF70(ChunkLoadClass &cload, MeshLoadContextClass *context);
};

bool MeshModelClass::read_Rva0018AF70(ChunkLoadClass &cload, MeshLoadContextClass * volatile context)
{
	if (!cload.Open_Chunk())
		return true;
	do {
		FXShaderSetup *shader = new FXShaderSetup;
		if (!shader->Load_W3D(cload)) {
			BfmeFXShaderRefOps::Release_Ref(shader);
			return false;
		}
		BfmeFXShaderRefOps::Add_Ref(shader);
		context->m_shaderVec.Add(shader);
		BfmeFXShaderRefOps::Release_Ref(shader);
		cload.Close_Chunk();
	} while (cload.Open_Chunk());
	return true;
}
