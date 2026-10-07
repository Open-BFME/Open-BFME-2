// ?read_Rva0018AF70@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
// partial score=0.93 date=2026-10-07
// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?read_Rva0018AF70@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z @0x0018AF70 269B
// MeshModelClass::read_Rva0018AF70, retail 0x0018AF70 (269 bytes):
// Chunk 0x50 reader in read_chunks (MeshModelReadChunks.cpp:144) beside
// read_textures 0x0018AE50 and read_texture_stage 0x0018B080. Creates an
// FXShaderSetup (new 0x34, ctor 0x001525FB), Load_W3D 0x00152E4D, Add_Ref at
// +4, vector Add with Resize slot 2, Release, Close_Chunk/Open_Chunk loop.
// Vector at context+0xF4 with DynamicVectorClass layout (Vector+0x4,
// VectorMax+0x8, ActiveCount+0x10, GrowthStep+0x14) as in ReadTextures.
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
public:
	RefCountClass() : NumRefs(1) {}
	void Add_Ref() { NumRefs++; }
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

	int NumRefs;
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

bool MeshModelClass::read_Rva0018AF70(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	if (!cload.Open_Chunk())
		return true;
	do {
		FXShaderSetup *shader = new FXShaderSetup;
		if (!shader->Load_W3D(cload)) {
			shader->Release_Ref();
			return false;
		}
		shader->Add_Ref();
		context->m_shaderVec.Add(shader);
		shader->Release_Ref();
		cload.Close_Chunk();
	} while (cload.Open_Chunk());
	return true;
}
