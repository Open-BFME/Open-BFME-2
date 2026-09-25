// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Texture surface memory-size queries (BFME2-new surface layout).
//
// The surface struct below is directly witnessed by retail 0x00131B1F: format
// at +0x4C (feeds rowed Get_Bits_Per_Pixel 0x00131A9D), dimensions at
// +0x28/+0x2C/+0x30, a type tag at +0x0C (2 selects the six-face upscale) and
// a level count at +0x44 (anything but 1 selects the 4/3 mipmap upscale).
// Its true BFME2 name is unknown, so the struct carries the address-derived
// Rva name; the +0x58 trailer on the query is likewise unexplained.
//
// Codegen notes (all load-bearing, all proven by probe):
// - /G7: plain /O1 lowers `mem *= 6` to lea+shl; /G7 keeps imul eax,eax,6.
// - The multiply chain must hang off the unnamed call result (a pure
//   temporary chain): naming the bits-per-pixel value first makes MSVC
//   reassociate to dims-first plus a mov ecx,eax spill.

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN = 0,
};

unsigned __fastcall Get_Bits_Per_Pixel(WW3DFormat format);

struct Rva00131B1FSurface
{
	int m_pad00[3]; // +0x00..0x0B
	int m_type0C; // +0x0C: 2 selects the *6 upscale
	int m_pad10[6]; // +0x10..0x27
	int m_dim28; // +0x28
	int m_dim2C; // +0x2C
	int m_dim30; // +0x30
	int m_pad34[4]; // +0x34..0x43
	int m_mip44; // +0x44: 1 skips the *4/3 upscale
	int m_pad48; // +0x48..0x4B
	int m_format4C; // +0x4C: WW3DFormat for Get_Bits_Per_Pixel

	unsigned Get_Memory_Size() const;
};

// ?Get_Memory_Size@Rva00131B1FSurface@@QBEIXZ -- retail 0x00131B1F, 56 bytes.
// thiscall method on the surface struct (retail mov esi,ecx, no guard).
unsigned Rva00131B1FSurface::Get_Memory_Size() const
{
	unsigned mem = Get_Bits_Per_Pixel((WW3DFormat)m_format4C)
		* m_dim30 * m_dim2C * m_dim28 >> 3;
	if (m_type0C == 2)
		mem *= 6;
	if (m_mip44 != 1)
		mem = mem * 4 / 3;
	return mem + 0x58;
}
