// cl: /DNDEBUG /MD /EHsc
// platformsdk
//
// ?read_vertex_materials@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018AD40 (237 bytes).
// BFME1 meshmdlio.cpp read_vertex_materials port with BFME2 rewrites (all
// retail-measured from the 0x0018AD40 body):
// - bool (AL) returns with a `bool ok` local and `!= true` checks.
// - EH frame (/EHsc): operator new at 0x2FDA0 may fail, so the body has an
//   fs prologue with scope table plus a state slot.
// - VertexMaterialClass is 0x6C bytes (vptr + RefCount at +0x4).
// - Add_Ref/Release_Ref are TU-local inlines around the refcount; the
//   disposal is a virtual slot-0 call taken only when the count reaches
//   zero (both the Load-fail and the success paths release inline, and
//   the fail path returns ok).
// - Add_Vertex_Material is a TU-local inline (Add_Ref plus indexed vector
//   Add, result ignored) over the DynamicVectorClass at context+0xC4 with
//   the same vptr-led layout as the landed MeshModelReadShaders.cpp unit
//   (VectorMax at +0x8, IsAllocated at +0xD, ActiveCount at +0x10,
//   GrowthStep at +0x14, virtual Resize at slot 2).
// Dedicated TU: the enum-typed meshmdlio.cpp cannot take rows (PostProcess
// precedent). New resolves via its matched row, the ctor via its matched
// row, Load_W3D via the harvested pin.

#include <windows.h>

class ChunkLoadClass
{
public:
	unsigned long Read(void *dst, unsigned long size);
	unsigned long Cur_Chunk_Length();
	unsigned long Cur_Chunk_ID();
	bool Open_Chunk();
	bool Close_Chunk();
	unsigned long Seek(unsigned long pos);
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

class VertexMaterialClass
{
public:
	VertexMaterialClass();
	bool Load_W3D(ChunkLoadClass &cload);
	void Add_Ref() { ++RefCount; }
	void Release_Ref() { if (--RefCount == 0) Dispose(); }
	// LINK: same-body helpers under TU-unique names (identical inlined
	// bytes). This TU's copies lose (first-copy); the three call sites below
	// inline them but still emit loser COMDATs. Rebinding there emits only
	// unique (trivially kept) copies. No flags touched.
	void bfme_add_ref() { ++RefCount; }
	void bfme_release() { if (--RefCount == 0) Dispose(); }
	virtual void Dispose(void);

private:
	int RefCount;
	char m_pad[0x6C - 8];
};

class MeshLoadContextClass
{
public:
	int __forceinline Add_Vertex_Material(VertexMaterialClass *vmat)
	{
		vmat->bfme_add_ref();
		int index = VertexMaterials.Count();
		VertexMaterials.Add(vmat);
		return index;
	}

private:
	char m_pad0[0xC4];

public:
	DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
};

class MeshModelClass
{
protected:
	virtual ~MeshModelClass();
	bool read_vertex_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
};

// ?read_vertex_materials@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_vertex_materials(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	while (cload.Open_Chunk()) {
		VertexMaterialClass *vmat = new VertexMaterialClass();
		bool ok = vmat->Load_W3D(cload);
		if (ok != true) {
			vmat->bfme_release();
			return ok;
		}
		context->Add_Vertex_Material(vmat);
		vmat->bfme_release();
		cload.Close_Chunk();
	}
	return true;
}
