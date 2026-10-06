// cl: /Oy- /MD /EHsc /DNDEBUG
//
// ?releaseD3DCursorTextures@W3DMouse@@AAE_NW4MouseCursor@@@Z, retail
// 0x00098F52, 111 bytes. Ghidra boundary 0x98F52/111. The neighboring
// target-side cursor loader establishes the 0x54-byte cursor-info records,
// the global CursorTextureSlot table, and current-surface array at +0x6028.
// This release path clears the current surface and its corresponding texture
// holder for each of the 21 animation frames.

struct TextureBaseClass
{
	void Release_Ref();
};

struct CursorTextureSlot
{
	TextureBaseClass *Ptr;
	void operator=(const CursorTextureSlot &rhs);
};

enum MouseCursor
{
	MOUSECURSOR_NONE = 0
};

enum
{
	MAX_2D_CURSOR_ANIM_FRAMES = 21,
	MAX_CURSORS = 56
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
	MouseCursorInfo m_cursorInfo[MAX_CURSORS];
	char m_pad[0x6028 - 4 - MAX_CURSORS * sizeof(MouseCursorInfo)];
	W3DRadarResetSurface m_currentD3DSurface[MAX_2D_CURSOR_ANIM_FRAMES];

	bool releaseD3DCursorTextures(MouseCursor cursor);
};

bool W3DMouse::releaseD3DCursorTextures(MouseCursor cursor)
{
	if (cursor == MOUSECURSOR_NONE || !cursorTextures[cursor][0].Ptr)
		return true;

	for (int i = 0; i < MAX_2D_CURSOR_ANIM_FRAMES; ++i) {
		{
			W3DRadarResetSurface emptySurface(0);
			m_currentD3DSurface[i] = emptySurface;
		}
		reinterpret_cast<BfmeResetTextureRef &>(cursorTextures[cursor][i]).clear();
	}
	return true;
}
