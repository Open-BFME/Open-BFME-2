// Cold-slice global-int returners without vtable carriage (twin-free TU).
//
// Same discipline as ConstZeroGetters.cpp (opaque address-derived names for
// unclaimed leaves with no callers, no branch sources and no .rdata vtable
// slot) but for the 6-byte shape (mov eax,[global] / ret). Each follows a ret
// (prev C3/C2/CC) and is followed by a function start, so the boundary is
// proven. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 6-byte shape).
//
// The G00xxxxxx externs are address-derived placeholders (DIR32 sites the
// verifier fills from retail) and carry no type information beyond int.

struct IDirect3D8;

// 0x00DB5FD4/0x00DB5FD8 are the data ledger's DX8Wrapper::ResolutionWidth
// and ResolutionHeight (dx8wrapper.cpp's protected statics, @@1): a minimal
// view of the real class reads them through an inline accessor.
class DX8Wrapper {
public:
	static __forceinline int Get_Device_Resolution_Width() { return ResolutionWidth; }
	static __forceinline int Get_Device_Resolution_Height() { return ResolutionHeight; }
	static __forceinline int Get_Texture_Bit_Depth() { return TextureBitDepth; }
	static __forceinline IDirect3D8 *Get_D3D8() { return D3DInterface; }
protected:
	static int ResolutionWidth;
	static int ResolutionHeight;
	static int TextureBitDepth;			// 0x009B5FE0
	static IDirect3D8 *D3DInterface;	// 0x009EDA30
};

// 0x009B5F9C is the data ledger's WW3D::TextureFilter (ww3d.cpp's private
// static, @@0).
class WW3D {
public:
	static __forceinline int Get_Texture_Filter() { return TextureFilter; }
private:
	static int TextureFilter;
};

// ?Rva000752F2Get@@YAHXZ @ 0x000752F2 (6B): returns global at 0x9EDA30.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva000752F2Get(void)
{
	return (int)DX8Wrapper::Get_D3D8();
}

// ?Rva00116E20Get@@YAHXZ @ 0x00116E20 (6B): returns global at 0x9B5FD4.
// Follows int3 (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00116E20Get(void)
{
	return DX8Wrapper::Get_Device_Resolution_Width();
}

// ?Rva00116E30Get@@YAHXZ @ 0x00116E30 (6B): returns global at 0x9B5FD8.
// Follows int3 (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00116E30Get(void)
{
	return DX8Wrapper::Get_Device_Resolution_Height();
}

// ?getTextureBitDepth@@YAHXZ @ 0x00117C30 (6B): returns global at 0x9B5FE0.
// Follows int3 (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int getTextureBitDepth(void)
{
	return DX8Wrapper::Get_Texture_Bit_Depth();
}

// ?getTextureFilter@@YAHXZ @ 0x0011C450 (6B): returns global at 0x9B5F9C.
// Follows int3 (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int getTextureFilter(void)
{
	return WW3D::Get_Texture_Filter();
}

// ?Rva0011D200Get@@YAHXZ @ 0x0011D200 (6B): returns global at 0x9EDA9C.
// Follows int3 (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
extern int G009EDA9C;
// G009EDA9C: matched references place it at VA 0xdeda9c (zero-filled .bss).
int G009EDA9C;
int Rva0011D200Get(void)
{
	return G009EDA9C;
}

// ?Rva0011D210Get@@YAHXZ @ 0x0011D210 (6B): returns global at 0x9EDAA0.
// Follows int3 (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
extern int G009EDAA0;
// G009EDAA0: matched references place it at VA 0xdedaa0 (zero-filled .bss).
int G009EDAA0;
int Rva0011D210Get(void)
{
	return G009EDAA0;
}

// ?Rva0011D220Get@@YAHXZ @ 0x0011D220 (6B): returns global at 0x9EDAA4.
extern int G009EDAA4;
// G009EDAA4: matched references place it at VA 0xdedaa4 (zero-filled .bss).
int G009EDAA4;
int Rva0011D220Get(void)
{
	return G009EDAA4;
}

// ?Rva0011D230Get@@YAHXZ @ 0x0011D230 (6B): returns global at 0x9EDAA8.
extern int G009EDAA8;
// G009EDAA8: matched references place it at VA 0xdedaa8 (zero-filled .bss).
int G009EDAA8;
int Rva0011D230Get(void)
{
	return G009EDAA8;
}

// ?Rva0011D240Get@@YAHXZ @ 0x0011D240 (6B): returns global at 0x9EDAAC.
extern int G009EDAAC;
// G009EDAAC: matched references place it at VA 0xdedaac (zero-filled .bss).
int G009EDAAC;
int Rva0011D240Get(void)
{
	return G009EDAAC;
}
