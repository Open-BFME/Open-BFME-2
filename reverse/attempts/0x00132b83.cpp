// ?Get_Texture_Memory_Usage@?$RefCountPtr@VTextureClass@@@@QBEIXZ
// partial score=0.97 date=2026-09-26
// model=muse-spark (supersedes 0.9 of 2026-09-25)
//
// Retail 0x00132B83 (79B). Pin consistent (Record_Texture_End 0x12A054 caller,
// 79B ghidra extent). 77/79 bytes: only two diffs remain.
// 1. Retail homes the +0x14 fetch in edi (push edi; mov edi,[esi+0x14]) then
//    copies to esi (mov esi,edi) for the computation, keeping edi for the
//    +0x44 mip check; every source spelling tried keeps a single home (esi).
//    Two named locals coalesce; a second tex->Desc fetch reloads instead of
//    copying (Variant E, 86B); tex=sub reassignment coalesces too.
// 2. Retail imul eax,eax,6 vs ours lea+shl: MSVC 7.1 strength-reduces x*=6
//    under /O1//O2//Os//Ox (isolated probe); single imul needs /Og-, which
//    deoptimizes everything else. *=, =x*6, 6*x, switch all give lea.
// Refuted: separated *= statements (81B, compiler reorders imuls, +0x4 phantom),
// Yoda 6*x, switch-on-Kind (78B), inline Get_Desc accessor, by-value helper
// variants are N/A here (no helper; single-expression multiply chain).
// Sibling tail at 0x131B25 runs the same chain plus add eax,0x58 (head unknown).
// Next ideas: find what forces the live-range split (a later tex use with no
// code trace?), or the true +0x14 holder type (reassignment needs same type).

// NOTE 2026-09-26: a sibling converged independently to 0.96 (same address,
// /O1 /MD /DNDEBUG flags, separated *= statements, surface/dims split pointers,
// inverted mip check `!= 1`, div tail via named `unsigned three = 3` with
// `mem *= 4; mem /= three`). Both agree the edi+esi dual-home is the wall.
// Kept here is the 0.97 single-expression body; try grafting their named-three
// div and split-pointer ideas onto it if the wall persists.
// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
//
// ?Get_Texture_Memory_Usage@?$RefCountPtr@VTextureClass@@@@QBEIXZ -- retail
// 0x00132B83, 79 bytes. The handle answers for its referent: null or
// uninitialized textures use nothing; otherwise the cached surface
// description gives bits-per-pixel times extents (in bytes), times six for
// the six-face kind, times four thirds unless a single mip level is stored.
// Get_Bits_Per_Pixel (0x00131A9D) is rowed __fastcall; Is_Initialized rides
// virtual slot 0x28. Only the fields this body touches are modeled.

// WW3DFormat numbering proven by the rowed Get_Bits_Per_Pixel body.
enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN		= 0,
	WW3D_FORMAT_R8G8B8		= 20,
	WW3D_FORMAT_A8R8G8B8	= 21,
	WW3D_FORMAT_X8R8G8B8	= 22,
	WW3D_FORMAT_R5G6B5		= 23,
	WW3D_FORMAT_X1R5G5B5	= 24,
	WW3D_FORMAT_A1R5G5B5	= 25,
	WW3D_FORMAT_A4R4G4B4	= 26,
	WW3D_FORMAT_R3G3B2		= 27,
	WW3D_FORMAT_A8			= 28,
	WW3D_FORMAT_A8R3G3B2	= 29,
	WW3D_FORMAT_X4R4G4B4	= 30,
	WW3D_FORMAT_A8P8		= 40,
	WW3D_FORMAT_P8			= 41,
	WW3D_FORMAT_L8			= 50,
	WW3D_FORMAT_A8L8		= 51,
	WW3D_FORMAT_A4L4		= 52,
	WW3D_FORMAT_DXT1		= 0x31545844,
	WW3D_FORMAT_DXT2		= 0x32545844,
	WW3D_FORMAT_DXT3		= 0x33545844,
	WW3D_FORMAT_DXT4		= 0x34545844,
	WW3D_FORMAT_DXT5		= 0x35545844,
};

unsigned __fastcall Get_Bits_Per_Pixel(WW3DFormat format);

// Surface description cached on the texture; only the fields this body
// touches are modeled. Width/Height/Depth order follows the multiply chain.
struct TextureDesc
{
	unsigned Unused00[3];	// +0x00
	unsigned Kind;			// +0x0c (2 selects the six-face path)
	unsigned Unused10[6];	// +0x10
	unsigned Depth;			// +0x28
	unsigned Height;		// +0x2c
	unsigned Width;			// +0x30
	unsigned Unused34[4];	// +0x34
	unsigned MipLevelCount;	// +0x44 (1 stores no mip chain)
	unsigned Unused48;		// +0x48
	WW3DFormat Format;		// +0x4c
};

class TextureClass
{
	// Is_Initialized rides virtual slot 0x28; earlier slots are unproven.
	virtual void Unused00();
	virtual void Unused01();
	virtual void Unused02();
	virtual void Unused03();
	virtual void Unused04();
	virtual void Unused05();
	virtual void Unused06();
	virtual void Unused07();
	virtual void Unused08();
	virtual void Unused09();
public:
	virtual bool Is_Initialized() const;
private:
	unsigned UnusedHead[4];	// +0x04..+0x10 (unproven head)
public:
	TextureDesc *Desc;		// +0x14
};

template<class T>
class RefCountPtr
{
public:
	T *Pointer;
	unsigned Get_Texture_Memory_Usage() const;
};

unsigned RefCountPtr<TextureClass>::Get_Texture_Memory_Usage() const
{
	const TextureClass *tex = Pointer;
	if (tex == 0)
		return 0;
	if (!tex->Is_Initialized())
		return 0;
	const TextureDesc *desc = tex->Desc;
	unsigned bytes = Get_Bits_Per_Pixel(desc->Format) * desc->Width * desc->Height * desc->Depth / 8;
	if (desc->Kind == 2)
		bytes *= 6;
	if (desc->MipLevelCount == 1)
		return bytes;
	return bytes * 4 / 3;
}
