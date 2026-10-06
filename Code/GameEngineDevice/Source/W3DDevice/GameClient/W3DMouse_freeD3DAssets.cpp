// cl: /Oy- /MD /EHsc /DNDEBUG
//
// ?freeD3DAssets@W3DMouse@@AAEXXZ, retail 0x00098FF1, 102 bytes.
// Ghidra boundary 0x98FF1/102. Target loops over the current 21 surface
// holders at this+0x6028, then clears the contiguous cursor texture holder
// table from 0xDE4B40 to 0xDE5DA0 in 21-slot groups.

struct TextureBaseClass
{
	void Release_Ref();
};

struct CursorTextureSlot
{
	TextureBaseClass *Ptr;
	void operator=(const CursorTextureSlot &rhs);
};

enum
{
	MAX_2D_CURSOR_ANIM_FRAMES = 21,
	NUM_MOUSE_CURSORS = 56
};

extern CursorTextureSlot cursorTextures[][MAX_2D_CURSOR_ANIM_FRAMES];

struct IDirect3DSurface8
{
	virtual long __stdcall QueryInterface() = 0;
	virtual unsigned __stdcall AddRef() = 0;
	virtual unsigned __stdcall Release() = 0;
};

class W3DRadarResetSurface
{
	IDirect3DSurface8 *m_surface;

public:
	W3DRadarResetSurface(IDirect3DSurface8 *surface) : m_surface(surface) {}
	~W3DRadarResetSurface();
	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &rhs);
};

struct MouseCursorInfo
{
	char pad00[0x30];
	char *textureName;
	char pad38[0x1C];
	int numFrames;
};
typedef char CursorInfoStride[(sizeof(MouseCursorInfo) == 0x54) ? 1 : -1];

struct BfmeResetTextureRef
{
	TextureBaseClass *pointer;
	void clear();
};

class W3DMouse
{
	void *m_vftable;
	MouseCursorInfo m_cursorInfo[NUM_MOUSE_CURSORS];
	char m_pad[0x6028 - 4 - NUM_MOUSE_CURSORS * sizeof(MouseCursorInfo)];
	W3DRadarResetSurface m_currentD3DSurface[MAX_2D_CURSOR_ANIM_FRAMES];

	void freeD3DAssets(void);
};

void W3DMouse::freeD3DAssets(void)
{
	for (int i = 0; i < MAX_2D_CURSOR_ANIM_FRAMES; ++i) {
		{
			W3DRadarResetSurface emptySurface(0);
			m_currentD3DSurface[i] = emptySurface;
		}
	}

	for (int cursor = 0; cursor < NUM_MOUSE_CURSORS; ++cursor) {
		for (int frame = 0; frame < MAX_2D_CURSOR_ANIM_FRAMES; ++frame) {
			reinterpret_cast<BfmeResetTextureRef &>(cursorTextures[cursor][frame]).clear();
		}
	}
}
