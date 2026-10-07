// ?allocateGeometry006e@Render2DClass@@AAEPAUBfmeRenderVertex@@IIPAPAKPAK@Z
// partial score=1.0 date=2026-10-07
// cl: /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Render2DClass's geometry allocator, retail 0x0011BD80 (875 bytes). Every
// Add_* primitive calls it (0x0004272E, 0x000428DC, 0x00042AE3, 0x00042D16,
// 0x0004571D): it reserves vertexCount 44-byte vertices and indexCount 16-bit
// indices, hands back the index pointer and the base vertex index packed twice
// into one dword, and books the indices against the active texture batch.
// The name is the BFME 1 donor's (Render2DClassAddQuadColor.cpp), whose callers
// already reach it through the symbols.csv pin; the original spelling is unknown.
//
// Target facts read from the body: with no batch selected (+0x44 < 0) and a
// texture set (+0x40) while texturing is on (+0x48), it looks for a batch
// holding that texture from index 1 up, appending a fresh ProxyClass when none
// does (push_back inlined; the copy constructor 0x00119A80 and
// _M_insert_overflow 0x00119D80 are calls). The batch's four per-shader ranges
// are indexed by +0x00: RangeA first vertex, RangeB first index, RangeC the
// vertex heading the shader's last run (-1 for none) and RangeD its index
// total. A run head's three spare vertex dwords (+0x0C..+0x14) chain to the
// next run and hold the run's index start and count, so indices that follow
// the last run directly extend it instead of opening a new one.
//
// The vertex array grows through its out-of-line Add (0x00118CC0); the index
// array's Add is expanded here, reallocating through the msvcr71 import, which
// is why this unit keeps the CRT's dllimport declarations (no /D_CRTIMP=).
// Layout as Render2DClassReset.cpp and Rva0011C0F0Finish.cpp prove it.

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row);
// this unit-local overload offers the link no second copy, as in
// Render2DClassReset.cpp.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <stdlib.h>

class TextureBaseClass
{
public:
	void Add_Ref() { ++RefCount; }
	void Release_Ref();

	int Unknown00;
	unsigned short RefCount;
	unsigned short Unknown06;
};

// BFME 2's owning texture handle (16-bit count at +4, release 0x0061ED10).
template<class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	~RefCountPtr()
	{
		if (Referent)
			Referent->Release_Ref();
	}
	RefCountPtr &operator=(const RefCountPtr &rhs)
	{
		if (rhs.Referent)
			rhs.Referent->Add_Ref();
		if (Referent)
			Referent->Release_Ref();
		Referent = rhs.Referent;
		return *this;
	}

	T *Referent;
};

// One 0x74-byte texture batch: the texture handle and four seven-entry
// per-shader ranges.
class ProxyClass
{
public:
	ProxyClass() {}

	RefCountPtr<TextureBaseClass> Texture;
	int RangeA[7];
	int RangeB[7];
	int RangeC[7];
	int RangeD[7];
};

typedef unsigned long BfmeUInt32;

struct BfmeRenderVertex
{
	float x;
	float y;
	float z;
	int NextRun;
	int IndexStart;
	int IndexCount;
	BfmeUInt32 color;
	float u;
	float v;
	unsigned char m_unmodelled_24[0x08];
};

// The 16-byte raw array of 44-byte vertices at +0x14. An index past the
// active count reads the first element.
class Render2DRawArray
{
public:
	void *rva00118CC0(int count);
	BfmeRenderVertex &operator[](unsigned int index)
	{
		if (index >= Count)
			return Data[0];
		return Data[index];
	}

	BfmeRenderVertex *Data;
	unsigned int Size;
	unsigned int Count;
	int GrowthStep;
};

// The same raw array over 16-bit indices at +0x24, whose Add retail expands.
class Render2DIndexArray
{
public:
	unsigned short *Add(unsigned int count)
	{
		if (count == 0 || count >= 0x80000000u)
			return 0;
		Count += count;
		if (Count <= Size)
			return Data + (Count - count);
		Size = Count + GrowthStep;
		Data = (unsigned short *)realloc(Data, Size * sizeof(unsigned short));
		if (Data == 0)
			return 0;
		return Data + (Count - count);
	}

	unsigned short *Data;
	unsigned int Size;
	unsigned int Count;
	int GrowthStep;
};

class Render2DClass
{
private:
	BfmeRenderVertex *allocateGeometry006e(
		unsigned int vertexCount,
		unsigned int indexCount,
		BfmeUInt32 **indices,
		BfmeUInt32 *baseVertexPair);

	int Shader;
	float CoordinateScale[2];
	float CoordinateOffset[2];
	Render2DRawArray Vertices;
	Render2DIndexArray Indices;
	std::vector<ProxyClass> Batches;
	RefCountPtr<TextureBaseClass> Texture;
	int CurrentBatch;
	bool IsTextured;
	unsigned char Tail[3];
};

BfmeRenderVertex *Render2DClass::allocateGeometry006e(
	unsigned int vertexCount,
	unsigned int indexCount,
	BfmeUInt32 **indices,
	BfmeUInt32 *baseVertexPair)
{
	*baseVertexPair = (Vertices.Count << 16) | Vertices.Count;
	if (CurrentBatch < 0 && IsTextured && Texture.Referent) {
		unsigned int i;
		for (i = 1; i < Batches.size(); ++i) {
			if (Batches[i].Texture.Referent == Texture.Referent)
				break;
		}
		if (i == Batches.size()) {
			ProxyClass batch;
			batch.Texture = Texture;
			for (int k = 0; k < 7; ++k) {
				batch.RangeB[k] = -1;
				batch.RangeC[k] = -1;
				batch.RangeA[k] = -1;
				batch.RangeD[k] = 0;
			}
			Batches.push_back(batch);
		}
		CurrentBatch = i;
	}
	ProxyClass &batch = Batches[(IsTextured && Texture.Referent) ? CurrentBatch : 0];
	BfmeRenderVertex *vertices = (BfmeRenderVertex *)Vertices.rva00118CC0(vertexCount);
	*indices = (BfmeUInt32 *)Indices.Add(indexCount);
	batch.RangeD[Shader] += indexCount;
	if (batch.RangeC[Shader] >= 0) {
		int last = batch.RangeC[Shader];
		if (Vertices[last].IndexStart + Vertices[last].IndexCount == Indices.Count) {
			Vertices[last].IndexCount += indexCount;
			return vertices;
		}
		// Retail reads the count before the bounds-checked access.
		unsigned int count = Vertices.Count;
		Vertices[last].NextRun = count - vertexCount;
	} else {
		batch.RangeA[Shader] = Vertices.Count - vertexCount;
		batch.RangeB[Shader] = Indices.Count - indexCount;
	}
	vertices->NextRun = 0;
	vertices->IndexStart = Indices.Count - indexCount;
	vertices->IndexCount = indexCount;
	batch.RangeC[Shader] = Vertices.Count - vertexCount;
	return vertices;
}
