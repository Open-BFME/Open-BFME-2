// Rva0011C0F0Finish.cpp -- ??0Render2DClass@@QAE@XZ
// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
//
// The BFME2 Render2DClass constructor, retail 0x0011C0F0 (202 bytes). The class
// and its flags come from the already-landed
// Code/Libraries/Source/WWVegas/WW3D2/Render2DClassConstructor.cpp, whose
// Render2DClass body is still present-unmatched -- this is that body.
//
// Retail's store sequence fixes the BFME2 layout, which differs from the
// reference header's: BFME2 dropped the W3D virtual glue, so this class has no
// vtable pointer and every member is stored inline. Reading the stores:
//
//   +0x00  Shader.Value = 2                  (ShaderState default, as upstream)
//   +0x04  CoordinateScale  = (1.0f, 1.0f)   (the compiler literal 0xBBB8D8)
//   +0x0C  CoordinateOffset = (0.0f, 0.0f)
//   +0x14  ArrayA = {0, 0, 0, 16}
//   +0x24  ArrayB = {0, 0, 0, 16}
//   +0x34  Batches = empty vector head        (three null pointers)
//   +0x40  Texture = 0
//   +0x44  CurrentBatch = -1
//   +0x48  IsDirty = true
//
// The batch vector's stride is 0x74 -- the ProxyClass size -- which 0x00119F00
// (Reset, called below) walks; the same vector and the same offsets are already
// recovered in Render2DClassReset.cpp, so this is the layout that file proves.
// The reference header's DynamicVectorClass would seat a vtable pointer, which
// retail does not store, so the batch head is modelled as a plain three-pointer
// class here.
//
// Reset is called non-virtically with this in ecx, which is why retail passes
// esi straight through. The three members whose destructors may throw -- the two
// raw arrays, the batch vector and the texture ref -- are what make retail's
// frame an SEH one, so MSVC 7.1 installs the scope-table handler and keeps the
// two unwind temporaries at [esp+8] (the in-progress `this`) and [esp+0x14] (the
// state byte). That byte reads 0 after ArrayA, then jumps straight to 3 once the
// batch vector and the texture ref are both live, which is why all three are
// modelled as single cleanup-relevant classes rather than as bare fields: the
// count and the store position are what the bytes pin. The three globals at
// 0x00DEC4A0-range are stored in descending address order and the three at
// 0x00DB5FBC-range in ascending, the same statement order the reference donor
// uses for its five g_bfme*EB slots; they are declared address-derived here
// because nothing else names them.
//
// stlport

class ShaderState
{
public:
	ShaderState() : Value(2) {}
	int Value;
};

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

class Render2DRawArray
{
public:
	Render2DRawArray() : Data(0), Size(0), Count(0), GrowthStep(16) {}
	~Render2DRawArray();

	void *Data;
	int Size;
	int Count;
	int GrowthStep;
};

class ProxyClass
{
public:
	char data[0x74];
};

// 0x00119F00 (Reset) reads [this+0x34] as the batch base pointer, [this+0x38] as
// the active end and [this+0x3C] as the capacity end, stepping 0x74 --
// ProxyClass's size -- per element; Render2DClassReset.cpp already recovers
// this vector head at this offset. Its constructor and destructor may throw,
// which is what makes retail's frame an SEH one.
class BatchVector
{
public:
	BatchVector() : Begin(0), End(0), Capacity(0) {}
	~BatchVector();

	void *Begin;
	void *End;
	void *Capacity;
};

// Render2DClassReset.cpp proves the four bytes at +0x40 are a pointer it reads
// as `Texture ? -1 : 0`, not an opaque tag, so retail seats the pointer here.
class TextureRef
{
public:
	TextureRef() : Pointer(0) {}
	~TextureRef();

	void *Pointer;
};

extern int G00DEC4A8;
extern int G00DEC4A4;
extern int G00DEC4A0;
extern int G00DB5FBC;
extern int G00DB5FC0;
extern int G00DB5FC4;

class Render2DClass
{
public:
	Render2DClass();
	void Reset();

private:
	ShaderState Shader;
	Vector2 CoordinateScale;
	Vector2 CoordinateOffset;
	Render2DRawArray ArrayA;
	Render2DRawArray ArrayB;
	BatchVector Batches;
	TextureRef Texture;
	int CurrentBatch;
	bool IsDirty;
};

// Rva0011C0F0Finish.cpp -- ??0Render2DClass@@QAE@XZ
Render2DClass::Render2DClass() :
	CoordinateScale(1.0f, 1.0f),
	CoordinateOffset(0.0f, 0.0f),
	CurrentBatch(-1),
	IsDirty(true)
{
	Reset();
	G00DEC4A8 = 0;
	G00DEC4A4 = 0;
	G00DEC4A0 = 0;
	G00DB5FBC = 7;
	G00DB5FC0 = 2;
	G00DB5FC4 = 5;
}