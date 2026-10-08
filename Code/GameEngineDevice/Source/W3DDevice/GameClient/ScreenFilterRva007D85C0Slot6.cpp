// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// Slot 6 (vftable 0x007CF348) of the screen filter the ledger calls
// Rva007D85C0: drop the pixel shader (device slot 107), unbind texture stage
// 0 through Zero Hour's inline Set_DX8_Texture and invalidate the cached
// render states. ScreenHilightFilter's vftable shares the body at 0x007CF32C,
// so it may be a common base's method; the slot is proven, the name is not.

struct IDirect3DBaseTexture8
{
	virtual long __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct IDirect3DDevice8;

typedef long (__stdcall *BfmeSetTextureFn)(IDirect3DDevice8 *, unsigned long, IDirect3DBaseTexture8 *);
typedef long (__stdcall *BfmeSetShaderFn)(IDirect3DDevice8 *, void *);

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture);
	static void Invalidate_Cached_Render_States(void);
protected:
	static IDirect3DDevice8 *D3DDevice;
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned int texture_changes;
};

extern unsigned int number_of_DX8_calls;

static inline void *deviceSlot(int slot)
{
	return (*(void ***)DX8Wrapper::_Get_D3D_Device8())[slot];
}

// Zero Hour's inline DX8Wrapper::Set_DX8_Texture.
__forceinline void DX8Wrapper::Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
{
	if (Textures[stage] == texture)
		return;
	if (Textures[stage])
		Textures[stage]->Release();
	Textures[stage] = texture;
	if (Textures[stage])
		Textures[stage]->AddRef();
	((BfmeSetTextureFn)deviceSlot(65))(_Get_D3D_Device8(), stage, texture);
	number_of_DX8_calls++;
	texture_changes++;
}

class Rva007D85C0
{
public:
	virtual void rva000FB0BC();
};

// ?rva000FB0BC@Rva007D85C0@@UAEXXZ @0x000FB0BC
void Rva007D85C0::rva000FB0BC()
{
	((BfmeSetShaderFn)deviceSlot(107))(DX8Wrapper::_Get_D3D_Device8(), 0);
	number_of_DX8_calls++;
	DX8Wrapper::Set_DX8_Texture(0, 0);
	DX8Wrapper::Invalidate_Cached_Render_States();
}
