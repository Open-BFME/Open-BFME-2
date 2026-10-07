// cl: /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ~Render2DClass, retail 0x00119D00 (101 bytes), the destructor matching the
// constructor at 0x0011C0F0 (Rva0011C0F0Finish.cpp). Layout as that file and
// Render2DClassReset.cpp prove it: two 16-byte raw arrays at +0x14 and +0x24,
// the vector<ProxyClass> batch list at +0x34 and the texture handle at +0x40.
//
// The member destructors run in reverse: the texture handle releases through
// 0x0061ED10 under EH state 2, the batch vector's out-of-line destructor
// (0x00119C00, Render2DClassReset.cpp) under state 1, then each raw array
// frees its storage through the msvcr71 free import. /EHsc is what drops the
// state stores before those two frees: the import is extern "C" and so counts
// as nothrow, unlike the game free the vector reaches under /GX.

#include <vector>

extern "C" __declspec(dllimport) void __cdecl free(void *pointer);

class TextureBaseClass
{
public:
	void Release_Ref();
};

template<class T>
class RefCountPtr
{
public:
	~RefCountPtr()
	{
		if (Referent)
			Referent->Release_Ref();
	}

	T *Referent;
};

class Render2DRawArray
{
public:
	~Render2DRawArray() { free(Data); }

	void *Data;
	int Size;
	int Count;
	int GrowthStep;
};

class ProxyClass
{
public:
	~ProxyClass();

	RefCountPtr<TextureBaseClass> Texture;
	int RangeA[7];
	int RangeB[7];
	int RangeC[7];
	int RangeD[7];
};

class Render2DClass
{
public:
	~Render2DClass();

private:
	int Shader;
	float CoordinateScale[2];
	float CoordinateOffset[2];
	Render2DRawArray ArrayA;
	Render2DRawArray ArrayB;
	std::vector<ProxyClass> Batches;
	RefCountPtr<TextureBaseClass> Texture;
	int CurrentBatch;
	bool IsDirty;
};

Render2DClass::~Render2DClass()
{
}
