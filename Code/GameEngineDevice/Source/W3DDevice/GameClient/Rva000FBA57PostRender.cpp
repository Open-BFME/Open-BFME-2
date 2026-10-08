// cl: /O1 /Oy /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/shims/bfmestages /Ireference/shims/sweep /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Retail 0x000FBA57, vtable slot 3 of the object installed by 0x000FBA4A.
// BFME1's ScreenBWFilter::postRender is the semantic donor. Retail confirms
// its endRenderToTexture -> mode setup -> texture binding -> viewport quad ->
// reset sequence. BFME2 supplies the viewport-size argument used for UV scale.
#include "Lib/Coord2D.h"

struct D3DXVECTOR4
{
	float x;
	float y;
	float z;
	float w;

	D3DXVECTOR4() {}
	D3DXVECTOR4(float xValue, float yValue, float zValue, float wValue)
		: x(xValue), y(yValue), z(zValue), w(wValue) {}
};

class IDirect3DTexture8;
struct IDirect3DBaseTexture8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct IDirect3DTexture8 : IDirect3DBaseTexture8
{
};

struct IDirect3DDevice8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
#define RVA000FBA57_D3D_SLOT(n) virtual void slot##n() = 0;
	RVA000FBA57_D3D_SLOT(03) RVA000FBA57_D3D_SLOT(04) RVA000FBA57_D3D_SLOT(05)
	RVA000FBA57_D3D_SLOT(06) RVA000FBA57_D3D_SLOT(07) RVA000FBA57_D3D_SLOT(08)
	RVA000FBA57_D3D_SLOT(09) RVA000FBA57_D3D_SLOT(10) RVA000FBA57_D3D_SLOT(11)
	RVA000FBA57_D3D_SLOT(12) RVA000FBA57_D3D_SLOT(13) RVA000FBA57_D3D_SLOT(14)
	RVA000FBA57_D3D_SLOT(15) RVA000FBA57_D3D_SLOT(16) RVA000FBA57_D3D_SLOT(17)
	RVA000FBA57_D3D_SLOT(18) RVA000FBA57_D3D_SLOT(19) RVA000FBA57_D3D_SLOT(20)
	RVA000FBA57_D3D_SLOT(21) RVA000FBA57_D3D_SLOT(22) RVA000FBA57_D3D_SLOT(23)
	RVA000FBA57_D3D_SLOT(24) RVA000FBA57_D3D_SLOT(25) RVA000FBA57_D3D_SLOT(26)
	RVA000FBA57_D3D_SLOT(27) RVA000FBA57_D3D_SLOT(28) RVA000FBA57_D3D_SLOT(29)
	RVA000FBA57_D3D_SLOT(30) RVA000FBA57_D3D_SLOT(31) RVA000FBA57_D3D_SLOT(32)
	RVA000FBA57_D3D_SLOT(33) RVA000FBA57_D3D_SLOT(34) RVA000FBA57_D3D_SLOT(35)
	RVA000FBA57_D3D_SLOT(36) RVA000FBA57_D3D_SLOT(37) RVA000FBA57_D3D_SLOT(38)
	RVA000FBA57_D3D_SLOT(39) RVA000FBA57_D3D_SLOT(40) RVA000FBA57_D3D_SLOT(41)
	RVA000FBA57_D3D_SLOT(42) RVA000FBA57_D3D_SLOT(43) RVA000FBA57_D3D_SLOT(44)
	RVA000FBA57_D3D_SLOT(45) RVA000FBA57_D3D_SLOT(46) RVA000FBA57_D3D_SLOT(47)
	RVA000FBA57_D3D_SLOT(48) RVA000FBA57_D3D_SLOT(49) RVA000FBA57_D3D_SLOT(50)
	RVA000FBA57_D3D_SLOT(51) RVA000FBA57_D3D_SLOT(52) RVA000FBA57_D3D_SLOT(53)
	RVA000FBA57_D3D_SLOT(54) RVA000FBA57_D3D_SLOT(55) RVA000FBA57_D3D_SLOT(56)
	RVA000FBA57_D3D_SLOT(57) RVA000FBA57_D3D_SLOT(58) RVA000FBA57_D3D_SLOT(59)
	RVA000FBA57_D3D_SLOT(60) RVA000FBA57_D3D_SLOT(61) RVA000FBA57_D3D_SLOT(62)
	RVA000FBA57_D3D_SLOT(63) RVA000FBA57_D3D_SLOT(64)
	virtual long __stdcall SetTexture(unsigned, IDirect3DBaseTexture8 *) = 0;
	RVA000FBA57_D3D_SLOT(66) RVA000FBA57_D3D_SLOT(67) RVA000FBA57_D3D_SLOT(68)
	RVA000FBA57_D3D_SLOT(69) RVA000FBA57_D3D_SLOT(70) RVA000FBA57_D3D_SLOT(71)
	RVA000FBA57_D3D_SLOT(72) RVA000FBA57_D3D_SLOT(73) RVA000FBA57_D3D_SLOT(74)
	RVA000FBA57_D3D_SLOT(75) RVA000FBA57_D3D_SLOT(76) RVA000FBA57_D3D_SLOT(77)
	RVA000FBA57_D3D_SLOT(78) RVA000FBA57_D3D_SLOT(79) RVA000FBA57_D3D_SLOT(80)
	RVA000FBA57_D3D_SLOT(81) RVA000FBA57_D3D_SLOT(82)
	virtual long __stdcall DrawPrimitiveUP(unsigned, unsigned, const void *, unsigned) = 0;
	RVA000FBA57_D3D_SLOT(84) RVA000FBA57_D3D_SLOT(85) RVA000FBA57_D3D_SLOT(86)
	RVA000FBA57_D3D_SLOT(87) RVA000FBA57_D3D_SLOT(88)
	virtual long __stdcall SetVertexShader(unsigned long) = 0;
#undef RVA000FBA57_D3D_SLOT
};

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static __forceinline void Set_DX8_Texture(unsigned stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 16) {
			IDirect3DDevice8 *device = _Get_D3D_Device8();
			device->SetTexture(stage, texture);
			number_of_DX8_calls++;
			return;
		}
		if (Textures[stage] == texture)
			return;
		if (Textures[stage])
			Textures[stage]->Release();
		Textures[stage] = texture;
		if (Textures[stage])
			Textures[stage]->AddRef();
		IDirect3DDevice8 *device = _Get_D3D_Device8();
		device->SetTexture(stage, texture);
		number_of_DX8_calls++;
		texture_changes++;
	}

protected:
	// Existing data-ledger owners: DX8Wrapper::Textures, texture_changes and
	// D3DDevice. number_of_DX8_calls is the existing global owner.
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned texture_changes;
	static IDirect3DDevice8 *D3DDevice;
};

class W3DShaderManager
{
public:
	static IDirect3DTexture8 *endRenderToTexture();
};

class View
{
public:
	// Retail call offsets are 0x3c, 0x44 and 0x4c. BFME1's filter donor
	// identifies the respective operations as width, height and origin.
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual int getWidth() = 0;
	virtual void slot40() = 0;
	virtual int getHeight() = 0;
	virtual void slot48() = 0;
	virtual void getOrigin(int *, int *) = 0;
};

extern View *TheTacticalView;

class Rva000FBA4A
{
public:
	virtual int slot00() = 0;
	virtual int slot04() = 0;
	virtual bool slot08(bool *, int) = 0;
	virtual bool rva000FBA57(int mode, int unused1, int unused2,
		Coord2D *viewportSize);
	virtual void slot10() = 0;
	virtual int set(int mode) = 0;
	virtual void reset() = 0;
};

// Address-derived class identity is retained. Retail vtable 0x00BCF364 is
// installed by 0x000FBA4A; its slot 3 is this body. The WB ScreenBWFilter name
// and BFME1 postRender are donor/name leads, not a target class-name claim.
bool Rva000FBA4A::rva000FBA57(int mode, int unused1, int unused2,
	Coord2D *viewportSize)
{
	IDirect3DTexture8 *texture = W3DShaderManager::endRenderToTexture();
	if (!texture)
		return false;
	if (!set(mode))
		return false;

	IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
	DX8Wrapper::Set_DX8_Texture(0, (IDirect3DBaseTexture8 *)texture);

	struct TransLitTexVertex
	{
		D3DXVECTOR4 position;
		unsigned long color;
		float u;
		float v;
	} vertices[4];

	int x;
	int y;
	int width;
	int height;
	TheTacticalView->getOrigin(&x, &y);
	width = TheTacticalView->getWidth();
	height = TheTacticalView->getHeight();

	vertices[0].position = D3DXVECTOR4(x + width - 0.5f, y + height - 0.5f, 0.0f, 1.0f);
	vertices[0].u = (float)(x + width) / viewportSize->x;
	vertices[0].v = (float)(y + height) / viewportSize->y;
	vertices[1].position = D3DXVECTOR4(x + width - 0.5f, y - 0.5f, 0.0f, 1.0f);
	vertices[1].u = (float)(x + width) / viewportSize->x;
	vertices[1].v = (float)y / viewportSize->y;
	vertices[2].position = D3DXVECTOR4(x - 0.5f, y + height - 0.5f, 0.0f, 1.0f);
	vertices[2].u = (float)x / viewportSize->x;
	vertices[2].v = (float)(y + height) / viewportSize->y;
	vertices[3].position = D3DXVECTOR4(x - 0.5f, y - 0.5f, 0.0f, 1.0f);
	vertices[3].u = (float)x / viewportSize->x;
	vertices[3].v = (float)y / viewportSize->y;
	vertices[0].color = 0xffffffff;
	vertices[1].color = 0xffffffff;
	vertices[2].color = 0xffffffff;
	vertices[3].color = 0xffffffff;

	DX8Wrapper::_Get_D3D_Device8()->SetVertexShader(0x144);
	++number_of_DX8_calls;
	device->DrawPrimitiveUP(5, 2, vertices, sizeof(TransLitTexVertex));
	reset();
	return true;
}
