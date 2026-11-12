// cl: /Oy- /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep

// ?Get_Surface_Level@CursorTextureSlot@@QAE?AVW3DRadarResetSurface@@XZ,
// retail 0x00132D70, 25 bytes. Zero-level forwarder: the cursor loader keeps
// the per-slot leveled fetcher (0x0013289D) as the worker and exposes the
// common case (mip level 0) under the BFME1 Get_Surface_Level spelling.
//
// ?Get_Surface_Level@CursorTextureSlot@@QAE?AVW3DRadarResetSurface@@H@Z,
// retail 0x0013289D, 236 bytes. Leveled worker: nulls the holder on a
// negative level, a null slot, a null/unflagged frame, a failed surface
// query or a null surface; otherwise asks the surface for the level item,
// logs a nonzero status, wraps the item in the counted thing (whose inline
// destructor reuses the rowed holder release), releases both surfaces and
// copy-constructs the holder out. Slot identities from retail evidence:
// slot 0x28 is Is_Initialized (bool, per the DebugStatistics texture-state
// view sibling), the remaining TexObject/ISurface8 slots stay numeric.

class W3DRadarResetSurface
{
public:
	void *m_surface;

	W3DRadarResetSurface() {}
	W3DRadarResetSurface(void *surface) : m_surface(surface) {}
	W3DRadarResetSurface(const W3DRadarResetSurface &other);
	~W3DRadarResetSurface();
};

// The holder's level-fill callee is the rowed SurfaceClass::TintSurface
// (0x00116990, SurfaceByteSize.cpp); the holder is passed as its this.
#include "../../../../Libraries/Source/WWVegas/WW3D2/W3DSurfaceClass.h"

#include "../../../../GameEngine/Include/Common/CursorTextureSlot.h"

// ?Get_Surface_Level@CursorTextureSlot@@QAE?AVW3DRadarResetSurface@@XZ
W3DRadarResetSurface CursorTextureSlot::Get_Surface_Level(void)
{
	return Get_Surface_Level(0);
}

// ---- leveled worker (probe v1) ----

struct BfmeItemDC;
class BfmeThingDC
{
public:
	BfmeThingDC(BfmeItemDC *item);
	~BfmeThingDC()
	{
		((W3DRadarResetSurface *)this)->W3DRadarResetSurface::~W3DRadarResetSurface();
	}
};

void Log_DX8_ErrorCode(unsigned int code);

struct GUID
{
	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
};
// Native VA CE0AD8 is IID_IDirect3DTexture9, established by its complete
// 16 bytes and Texture9 GetSurfaceLevel at slot18 (0x48). The legacy
// ISurface8 label below is a numeric COM view, not a D3D8 identity claim.
// Keep the existing _IID_TexSurface datum and its sole ownership.
static const GUID IID_TexSurface = { 0x85C31227, 0x3DE5, 0x4F00,
    { 0x9B, 0x3A, 0xF1, 0x1A, 0xC3, 0x8C, 0x18, 0xB5 } };

struct ISurface8
{
	virtual int __stdcall QueryInterface(const GUID &iid, void **out) = 0;
	virtual unsigned __stdcall AddRef() = 0;
	virtual unsigned __stdcall Release() = 0;
	virtual void __stdcall Slot_03() = 0;
	virtual void __stdcall Slot_04() = 0;
	virtual void __stdcall Slot_05() = 0;
	virtual void __stdcall Slot_06() = 0;
	virtual void __stdcall Slot_07() = 0;
	virtual void __stdcall Slot_08() = 0;
	virtual void __stdcall Slot_09() = 0;
	virtual void __stdcall Slot_10() = 0;
	virtual void __stdcall Slot_11() = 0;
	virtual void __stdcall Slot_12() = 0;
	virtual int __stdcall Slot_13() = 0;
	virtual void __stdcall Slot_14() = 0;
	virtual void __stdcall Slot_15() = 0;
	virtual void __stdcall Slot_16() = 0;
	virtual void __stdcall Slot_17() = 0;
	virtual unsigned __stdcall Slot_48(int level, ISurface8 **out) = 0;
};

struct Level14
{
	char m_pad00[8];
	ISurface8 *m_ptr08;
	int m_flag0C;
};

struct TexObject
{
	virtual void Slot_00() = 0;
	virtual void Slot_01() = 0;
	virtual void Slot_02() = 0;
	virtual void Slot_03() = 0;
	virtual void Slot_04() = 0;
	virtual void Slot_05() = 0;
	virtual void Slot_06() = 0;
	virtual void Slot_07() = 0;
	virtual void Slot_08() = 0;
	virtual void Slot_09() = 0;
	virtual bool Is_Initialized() = 0;
	virtual void Slot_2C() = 0;

	char m_pad04[0x10];
	Level14 *m_field14;
};

#define NULL 0

// ?Get_Surface_Level@CursorTextureSlot@@QAE?AVW3DRadarResetSurface@@H@Z
W3DRadarResetSurface CursorTextureSlot::Get_Surface_Level(int level)
{
	if (level < 0)
		return W3DRadarResetSurface(NULL);
	TexObject *tex = (TexObject *)Ptr;
	if (tex == NULL)
		return W3DRadarResetSurface(NULL);
	bool initialized;
	initialized = tex->Is_Initialized();
	if (initialized == false)
		tex->Slot_2C();
	if (tex->m_field14->m_ptr08 == NULL || tex->m_field14->m_flag0C != 0)
		return W3DRadarResetSurface(NULL);
	ISurface8 *surface = NULL;
	if (tex->m_field14->m_ptr08->QueryInterface(IID_TexSurface, (void **)&surface) < 0 || surface == NULL)
		return W3DRadarResetSurface(NULL);
	ISurface8 *item = NULL;
	unsigned err = surface->Slot_48(level, &item);
	if (err != 0)
		Log_DX8_ErrorCode(err);
	BfmeThingDC thing((BfmeItemDC *)item);
	if (item != NULL)
		item->Release();
	surface->Release();
	return (const W3DRadarResetSurface &)thing;
}

// ?FillLevelSurfaces@CursorTextureSlot@@QAEXXZ, retail 0x00132989, 266 bytes.
// Probe v1: per-level surface fill over the slot texture.
void CursorTextureSlot::FillLevelSurfaces(void)
{
	TexObject *tex = (TexObject *)Ptr;
	if (tex == NULL)
		return;
	if (!tex->Is_Initialized())
		return;
	Level14 *frame = tex->m_field14;
	if (frame->m_ptr08 == NULL)
		return;
	int count = frame->m_ptr08->Slot_13();
	for (int level = 1; level < count; level++)
	{
		float red;
		float green;
		float blue;
		switch (level)
		{
		case 1:
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
			break;
		case 2:
			red = 0.0f;
			green = 1.0f;
			blue = 0.0f;
			break;
		case 3:
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;
			break;
		default:
			red = 1.0f;
			green = 1.0f;
			blue = 0.0f;
			break;
		}
		((SurfaceClass *)&Get_Surface_Level(level))->TintSurface(red, green, blue);
	}
}
