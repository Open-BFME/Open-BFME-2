// cl: /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2 retail's Render2D layout uses an STLport vector of 0x74-byte ProxyClass
// records. The live 1.06.2429.30210 snapshot has the same .text as the audited
// image; Ghidra shows Reset clearing Batches at +0x34, appending one initialized
// ProxyClass, then selecting CurrentBatch from Texture at +0x40.
//
// Reset (0x00119F00) and the vector<ProxyClass> machinery it instantiates sit
// together at 0x00118E00..0x0011A040, and every caller of them is in this
// Render2D unit (0x00118800..0x0011C1C0): push_back 0x00119EC0 and its
// _M_insert_overflow 0x00119D80, clear 0x00119D70 / _M_clear 0x00119CC0,
// operator[] 0x00119A60, the member-wise copy constructor 0x00119A80 (handle
// AddRef, one rep movsd per range) and its _Construct / uninitialized_copy /
// uninitialized_fill_n / allocate helpers. None is folded with another type's.
// The STLport allocator is BFME 2's (bytes, hint) pair (bfmealloc shim), whose
// tag arguments are by value, as __copy_ptrs 0x00119BB0 is mangled.
// Reset writes the init loops itself: a forceinline helper spends the inline
// budget and leaves push_back's copy constructor out of line, unlike retail.
// /GX rather than /EHsc: ~vector (0x00119C00) leaves its EH state (-1) before
// the storage free, so that free is a call that may throw; under /EHsc the C
// free counts as nothrow and the store is dropped. ~Render2DClass, which frees
// its raw arrays through the msvcr71 import, is Render2DClassDestructor.cpp.

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
// Keep STLport allocation calls native while the raw index array uses
// imported realloc. Declare that one CRT import separately below.
#define realloc bfmeUnusedReallocDeclaration
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <string.h>
#include <stdlib.h>
#undef realloc
extern "C" __declspec(dllimport) void *__cdecl realloc(void *, size_t);

class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();

	int Unknown00;
	unsigned short RefCount;
	unsigned short Unknown06;
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


class Render2DRawArray
{
public:
	void Reset_Active() { Count = 0; }
    void *rva00118CC0(int count);
    BfmeRenderVertex &operator[](unsigned int index) {
        if (index >= Count) return Data[0];
        return Data[index];
    }

	BfmeRenderVertex *Data;
	unsigned int Size;
	unsigned int Count;
	int GrowthStep;
};

// BFME 2's owning texture handle: copy adds a reference, destruction and
// reassignment release the old one (16-bit count at +4, release 0x0061ED10).
template<class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			++Referent->RefCount;
	}
	~RefCountPtr()
	{
		if (Referent)
			Referent->Release_Ref();
	}
	RefCountPtr &operator=(const RefCountPtr &rhs)
	{
		if (rhs.Referent)
			++rhs.Referent->RefCount;
		if (Referent)
			Referent->Release_Ref();
		Referent = rhs.Referent;
		return *this;
	}

	T *Referent;
};

// One 0x74-byte texture batch: the texture handle and four seven-entry
// ranges. Retail copy-constructs it member by member (0x00119A80: the handle,
// then one rep movsd per range).
class ProxyClass
{
public:
	ProxyClass() {}
	ProxyClass &operator=(ProxyClass const &other);

	RefCountPtr<TextureBaseClass> Texture;
	int RangeA[7];
	int RangeB[7];
	int RangeC[7];
	int RangeD[7];
};

inline ProxyClass &ProxyClass::operator=(ProxyClass const &other)
{
	Texture = other.Texture;
	for (int i = 0; i < 7; ++i)
		RangeA[i] = other.RangeA[i];
	for (int j = 0; j < 7; ++j)
		RangeB[j] = other.RangeB[j];
	for (int k = 0; k < 7; ++k)
		RangeC[k] = other.RangeC[k];
	for (int l = 0; l < 7; ++l)
		RangeD[l] = other.RangeD[l];
	return *this;
}

template<class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass();
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];

public:
	int Length() const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(int size = 0, T const *array = 0);
	virtual ~DynamicVectorClass();
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

	__forceinline bool Add(T const &object, int count)
	{
		if (count >= Length())
		{
			if ((IsAllocated || !VectorMax) && GrowthStep > 0)
			{
				if (!Resize(Length() + GrowthStep))
					return false;
			}
			else
			{
				return false;
			}
		}
		(*this)[ActiveCount++] = object;
		return true;
	}

	int Count() const { return ActiveCount; }

protected:
	int ActiveCount;
	int GrowthStep;
};

class Render2DIndexArray
{
public:
    void Reset_Active() { Count = 0; }
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
public:
	void Reset();
private:
    BfmeRenderVertex *allocateGeometry006e(unsigned int vertexCount,
        unsigned int indexCount, BfmeUInt32 **indices, BfmeUInt32 *baseVertexPair);
	int Shader;
	float CoordinateScale[2];
	float CoordinateOffset[2];
	Render2DRawArray ArrayA;
	Render2DIndexArray ArrayB;
	std::vector<ProxyClass> Batches;
	RefCountPtr<TextureBaseClass> Texture;
	int CurrentBatch;
	bool IsDirty;
	unsigned char Tail[3];
};

void Render2DClass::Reset()
{
	ArrayA.Reset_Active();
	ArrayB.Reset_Active();
	Batches.clear();
	ProxyClass batch;
	for (int i = 0; i < 7; ++i) {
		batch.RangeB[i] = -1;
		batch.RangeC[i] = -1;
		batch.RangeA[i] = -1;
	}
	for (int j = 0; j < 7; ++j)
		batch.RangeD[j] = 0;
	Batches.push_back(batch);
	CurrentBatch = Texture.Referent ? -1 : 0;
}

template void std::_Destroy<ProxyClass *>(ProxyClass *, ProxyClass *);
template void std::vector<ProxyClass>::push_back(const ProxyClass &);
template void std::vector<ProxyClass>::clear();
template std::vector<ProxyClass>::~vector();
template ProxyClass &std::vector<ProxyClass>::operator[](unsigned int);
template ProxyClass *std::__uninitialized_fill_n(ProxyClass *, unsigned int, const ProxyClass &, const std::__false_type &);
template ProxyClass *std::__uninitialized_copy(ProxyClass *, ProxyClass *, ProxyClass *, const std::__false_type &);
template class std::allocator<ProxyClass>;

// ProxyClass's assignment operator is a header inline in copier units. This
// anchor retains its matched row body here, but the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeProxyClassAssignInlineAnchor@@YAXPAVProxyClass@@@Z absent-from-retail
void _bfmeProxyClassAssignInlineAnchor(ProxyClass *proxy)
{
	proxy->ProxyClass::operator=(*proxy);
}
#pragma inline_depth()

// Native allocator 0x0011BD80..0x0011C0EB (875 bytes), banked in BFME2
// 2bbec0d919. Add_* callers at 0x4272E; 0x428DC; 0x42AE3; 0x42D16;
// 0x4571D reserve 44-byte vertices and 16-bit indices through this ABI.
// The donor-derived name is already established by Render2DClassAddQuadColor.
// Native frame FuncInfo 0x00909034 and its unwind funclet also verify exactly.
// A handle copy increments the native word at +4 directly; this avoids
// emitting a competing /G7 Add_Ref copy beside retail's /G6 provider.
BfmeRenderVertex *Render2DClass::allocateGeometry006e(
	unsigned int vertexCount,
	unsigned int indexCount,
	BfmeUInt32 **indices,
	BfmeUInt32 *baseVertexPair)
{
	*baseVertexPair = (ArrayA.Count << 16) | ArrayA.Count;
	if (CurrentBatch < 0 && IsDirty && Texture.Referent) {
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
	ProxyClass &batch = Batches[(IsDirty && Texture.Referent) ? CurrentBatch : 0];
	BfmeRenderVertex *vertices = (BfmeRenderVertex *)ArrayA.rva00118CC0(vertexCount);
	*indices = (BfmeUInt32 *)ArrayB.Add(indexCount);
	batch.RangeD[Shader] += indexCount;
	if (batch.RangeC[Shader] >= 0) {
		int last = batch.RangeC[Shader];
		if (ArrayA[last].IndexStart + ArrayA[last].IndexCount == ArrayB.Count) {
			ArrayA[last].IndexCount += indexCount;
			return vertices;
		}
		// Retail reads the count before the bounds-checked access.
		unsigned int count = ArrayA.Count;
		ArrayA[last].NextRun = count - vertexCount;
	} else {
		batch.RangeA[Shader] = ArrayA.Count - vertexCount;
		batch.RangeB[Shader] = ArrayB.Count - indexCount;
	}
	vertices->NextRun = 0;
	vertices->IndexStart = ArrayB.Count - indexCount;
	vertices->IndexCount = indexCount;
	batch.RangeC[Shader] = ArrayA.Count - vertexCount;
	return vertices;
}
