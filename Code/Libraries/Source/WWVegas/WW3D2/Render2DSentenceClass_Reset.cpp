// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// ?Reset@Render2DSentenceClass@@UAEXXZ at 0x00155A20 173B: BFME2 thread-guarded Reset.
// Donor: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp Render2DSentenceClass::Reset.
// Evidence: callees Release_Pending_Surfaces 0x00154F70 and Reset_Sentence_Data 0x00154F10 (rowed),
// thread Lock 0x0011F520 / Assert 0x00120F50 (rowed), renderer erase 0x001558D0 (rowed Gen_0093E730::rva001558D0),
// renderer dtor pin 0x00119D00, CurSurface release via ops slot 2, Cursor at +0x60, MonoSpaced +0x80, ParseHotKey +0xAD.

class SurfaceClass;

struct SurfaceOps
{
	void (__stdcall *unused)(SurfaceClass *surface);
	void (__stdcall *add_ref)(SurfaceClass *surface);
	void (__stdcall *release_ref)(SurfaceClass *surface);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	SurfaceOps *ops;
};

// pinned dtor at 0x00119D00 (opaque SEH dtor); true identity likely Render2DClass dtor via RendererDataStruct.
class Rva00119D00
{
public:
	virtual ~Rva00119D00();
};

void __cdecl operator delete(void *p);

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

// Renderers vector: 8-byte {renderer, surface} records with COM second word,
// same layout as Gen_0093E730 whose erase (rva001558D0) retail reuses here.
struct RendererDataStruct
{
	Rva00119D00 *Renderer;
	SurfaceClass *Surface;
};

class Gen_0093E730
{
public:
	virtual bool Equal(const Gen_0093E730 &that) const;
	virtual bool Unused();
	virtual bool Resize(int size, const RendererDataStruct *array = 0);

	int Count() const { return active_count; }
	RendererDataStruct &operator[](int index) { return vector[index]; }
	bool rva001558D0(int index);

private:
	RendererDataStruct *vector;
	int vector_max;
	bool is_valid;
	bool is_allocated;
	char pad[2];
	int active_count;
	int growth_step;
};

class Vector2
{
public:
	float X;
	float Y;
	void Set(float x, float y) { X = x; Y = y; }
};

class Vector2i
{
public:
	int X;
	int Y;
};

struct RectClass
{
	int Left;
	int Top;
	int Right;
	int Bottom;
};

// upstream layout: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:
	virtual ~Render2DSentenceClass();
	virtual void Reset();

private:
	void Release_Pending_Surfaces();
	void Reset_Sentence_Data();

	unsigned char m_sentenceData[0x18];
	unsigned char m_pendingSurfaces[0x18];
	Gen_0093E730 m_renderers; // +0x34
	void *m_font; // +0x4C
	Vector2 m_baseLocation; // +0x50
	Vector2 m_location; // +0x58
	Vector2 m_cursor; // +0x60
	Vector2i m_textureOffset; // +0x68
	int m_textureStartX; // +0x70
	int m_currTextureSize; // +0x74
	int m_textureSizeHint; // +0x78
	SurfaceClass *m_curSurface; // +0x7C
	bool m_monoSpaced; // +0x80
	char m_pad81[3];
	float m_wrapWidth; // +0x84
	bool m_centered; // +0x88
	char m_pad89[3];
	RectClass m_clipRect; // +0x8C
	RectClass m_drawExtents; // +0x9C
	bool m_isClippedEnabled; // +0xAC
	bool m_parseHotKey; // +0xAD
	bool m_useHardWordWrap; // +0xAE
};

void Render2DSentenceClass::Reset()
{
	BFMEDX8DeviceLock guard;
	if (m_curSurface != 0) {
		m_curSurface->ops->release_ref(m_curSurface);
		m_curSurface = 0;
	}
	while (m_renderers.Count() > 0) {
		Rva00119D00 *renderer = m_renderers[0].Renderer;
		if (renderer != 0) {
			renderer->Rva00119D00::~Rva00119D00();
			::operator delete(renderer);
		}
		m_renderers.rva001558D0(0);
	}
	m_cursor.Set(0.0f, 0.0f);
	m_monoSpaced = false;
	m_parseHotKey = false;
	Release_Pending_Surfaces();
	Reset_Sentence_Data();
}
