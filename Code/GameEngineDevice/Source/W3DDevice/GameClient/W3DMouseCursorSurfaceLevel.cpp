// cl: /O1 /Oy- /MD /EHsc /DNDEBUG /arch:SSE

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
	void Rva00116990(float a, float b, float c);
};

struct CursorTextureSlot
{
	void *Ptr;

	W3DRadarResetSurface Get_Surface_Level(void);
	W3DRadarResetSurface Get_Surface_Level(int level);
	void FillLevelSurfaces(void);
};

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
static const GUID IID_TexSurface = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };

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
		float a;
		float b;
		float c;
		switch (level)
		{
		case 1:
			a = 1.0f;
			b = 0.0f;
			c = 0.0f;
			break;
		case 2:
			a = 0.0f;
			b = 1.0f;
			c = 0.0f;
			break;
		case 3:
			a = 0.0f;
			b = 0.0f;
			c = 1.0f;
			break;
		default:
			a = 1.0f;
			b = 1.0f;
			c = 0.0f;
			break;
		}
		Get_Surface_Level(level).Rva00116990(a, b, c);
	}
}
