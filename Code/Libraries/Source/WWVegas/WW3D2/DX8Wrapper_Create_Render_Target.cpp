// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
// DX8Wrapper::Create_Render_Target retail 0x0011E120 (289 B).
// Donor: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/
// Rva00905140CreateRenderTarget.cpp (BFME 1 0x00905140), which already
// returns the four-byte owning texture handle by hidden pointer and builds
// the texture in a stack handle. BFME 2 drifts from it in three places, all
// read from retail: the format table check is against 0x76 entries at
// DX8Caps+0x1B9, a supported format first calls the device's
// EvictManagedResources (D3D9 slot 5, counted), and the size math is integer:
// the power of two is clamped by unsigned compares (cmova) against the
// D3DCAPS9 MaxTextureWidth/Height at caps+0x58/+0x5C instead of going
// through float. The handle is BFME 2's RefCountPtr<TextureClass> (16-bit
// count at +4, rowed release at 0x0061ED10, see
// W3DTerrainTexturePtrGetters.cpp); the six-argument refill at 0x00131DFC
// (new TextureClass(width, height, format, MIP_LEVELS_1, POOL_DEFAULT,
// render target) into the handle) keeps its address-derived row name.

int __cdecl Find_POT(int size);

enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };

// The device keeps its D3D8 type name but is a Direct3D 9 device
// (EvictManagedResources slot 5, GetDisplayMode slot 8), cast at each call.
#include <d3d9.h>

struct IDirect3DDevice8;
#define DEVICE9 (reinterpret_cast<IDirect3DDevice9 *>(D3DDevice))

extern unsigned number_of_DX8_calls;

class DX8Caps
{
public:
	const D3DCAPS9 &Get_DX8_Caps() const { return Caps; }
	__declspec(dllimport) __forceinline bool Support_Render_To_Texture_Format(WW3DFormat format) const
	{
		return format >= 0 && format < 0x76 && SupportRenderToTextureFormat[format];
	}

private:
	int MaxDisplayWidth;
	int MaxDisplayHeight;
	D3DCAPS9 Caps;
	unsigned char m_layoutGap[0x1B9 - 8 - sizeof(D3DCAPS9)];
	bool SupportRenderToTextureFormat[0x76];
};

class TextureClass
{
public:
	__declspec(dllimport) __forceinline void Add_Ref() { ++m_refCount; }
	void Release_Ref();

private:
	void *m_vtable;
	unsigned short m_refCount;
};

template <class T> class RefCountPtr
{
public:
	__declspec(dllimport) __forceinline RefCountPtr() : m_ptr(0) {}
	__declspec(dllimport) __forceinline RefCountPtr(const RefCountPtr &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}
	~RefCountPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

private:
	T *m_ptr;
};

// The handle refill at 0x00131DFC, rowed under its address-derived name.
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva00131DFC.h"

#include "DX8WrapperClass.h"

// ?Create_Render_Target@DX8Wrapper@@SA?AV?$RefCountPtr@VTextureClass@@@@HHW4WW3DFormat@@@Z
RefCountPtr<TextureClass> DX8Wrapper::Create_Render_Target(int width, int height, WW3DFormat format)
{
	number_of_DX8_calls++;

	// Use the current display format if format isn't specified
	if (format == WW3D_FORMAT_UNKNOWN) {
		D3DDISPLAYMODE mode;
		DEVICE9->GetDisplayMode(0, &mode);
		number_of_DX8_calls++;
		format = (WW3DFormat)mode.Format;
	}

	// If render target format isn't supported return NULL
	if (!CurrentCaps->Support_Render_To_Texture_Format(format)) {
		return RefCountPtr<TextureClass>();
	}

	DEVICE9->EvictManagedResources();
	number_of_DX8_calls++;

	//	Note: We're going to force the width and height to be powers of two and equal
	const D3DCAPS9 &dx8caps = CurrentCaps->Get_DX8_Caps();
	int size = width;
	if (height > 0 && height < width) {
		size = height;
	}
	unsigned int poweroftwosize = Find_POT(size);
	if (poweroftwosize > dx8caps.MaxTextureWidth) {
		poweroftwosize = dx8caps.MaxTextureWidth;
	}
	if (poweroftwosize > dx8caps.MaxTextureHeight) {
		poweroftwosize = dx8caps.MaxTextureHeight;
	}

	RefCountPtr<TextureClass> tex;
	reinterpret_cast<Rva00131DFC *>(&tex)->rva00131DFC(
		(void *)poweroftwosize, (void *)poweroftwosize, (void *)format, (void *)1, 0, 1);
	return tex;
}
