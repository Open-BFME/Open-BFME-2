// cl: /O1 /DNDEBUG /MD

// ?loadD3DCursorTextures@W3DMouse@@AAE_NW4MouseCursor@@@Z, retail 0x000999CE,
// 417 bytes. BFME2's cursor-texture loader: same algorithm as BFME1
// W3DMouse::loadD3DCursorTextures (single-frame branch plus %04d loop) but
// BFME2-new layout and glue — the texture table is a global of counted
// holders, cursor info rides in 84-byte records behind the vptr, and textures
// arrive through the cached free loader (no WW3DAssetManager instance).

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *fmt, ...);

#define NULL 0

class TextureBaseClass
{
public:
	void Release_Ref();
};

// The surface behind a cursor slot is a COM object: slot 0 QueryInterface,
// slot 1 AddRef, slot 2 Release. Declared TU-locally (not via the shared DX8
// shim) because this TU reaches the ref-count slots through ecx. The virtuals
// are __stdcall like real COM, so the surface pointer rides the stack.
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
	~W3DRadarResetSurface();
	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &rhs);
};

class BFME2ParticleTextureHandle
{
public:
	TextureBaseClass *Ptr;

	~BFME2ParticleTextureHandle()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
};

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);

struct CursorTextureSlot
{
	TextureBaseClass *Ptr;

	void operator=(const BFME2ParticleTextureHandle &rhs);
	W3DRadarResetSurface Get_Surface_Level();
};

class AsciiString
{
	char *m_data;

public:
	const char *str() const { return m_data ? (const char *)(m_data + 8) : (const char *)""; }
};

enum MouseCursor
{
	MOUSECURSOR_NONE = 0
};

enum
{
	MAX_2D_CURSOR_ANIM_FRAMES = 21,
	MAX_CURSORS = 64
};

struct MouseCursorInfo
{
	char pad00[0x30];
	AsciiString textureName;
	char pad38[0x1C];
	int numFrames;
};

CursorTextureSlot cursorTextures[MAX_CURSORS][MAX_2D_CURSOR_ANIM_FRAMES];

class W3DMouse
{
	void *m_vftable;
	MouseCursorInfo m_cursorInfo[MAX_CURSORS];
	char m_pad[0x6028 - 4 - MAX_CURSORS * sizeof(MouseCursorInfo)];
	W3DRadarResetSurface m_currentD3DSurface[MAX_2D_CURSOR_ANIM_FRAMES];
	char m_hotSpot[8];
	int m_currentFrames;

	bool loadD3DCursorTextures(MouseCursor cursor);
};

// ??4W3DRadarResetSurface@@QAEAAV0@ABV0@@Z, retail 0x00072381, 43 bytes.
// COM ref-counted surface assignment: AddRef the incoming surface, release
// the held one, then store.
W3DRadarResetSurface &W3DRadarResetSurface::operator=(const W3DRadarResetSurface &rhs)
{
	if (rhs.m_surface != NULL)
		rhs.m_surface->AddRef();
	if (m_surface != NULL)
		m_surface->Release();
	m_surface = rhs.m_surface;
	return *this;
}

// ??1BFME2ParticleTextureHandle@@QAE@XZ present-unmatched
bool W3DMouse::loadD3DCursorTextures(MouseCursor cursor)
{
	if (cursor == MOUSECURSOR_NONE || cursorTextures[cursor][0].Ptr)
		return true;

	int animFrames = m_cursorInfo[cursor].numFrames;
	if (!animFrames)
		return false;

	const char *baseName = m_cursorInfo[cursor].textureName.str();
	char frameName[64];

	if (animFrames > MAX_2D_CURSOR_ANIM_FRAMES)
		animFrames = MAX_2D_CURSOR_ANIM_FRAMES;

	m_currentFrames = 0;

	if (animFrames == 1)
	{
		sprintf(frameName, "%s.tga", baseName);
		cursorTextures[cursor][0] = BFME2LoadParticleTexture(frameName, 0, 0);
		m_currentD3DSurface[0] = cursorTextures[cursor][0].Get_Surface_Level();
		m_currentFrames = 1;
	}
	else
	{
		for (int i = 0; i < animFrames; i++)
		{
			sprintf(frameName, "%s%04d.tga", baseName, i);
			if ((cursorTextures[cursor][i] = BFME2LoadParticleTexture(frameName, 0, 0), cursorTextures[cursor][i].Ptr) != NULL)
			{
				m_currentD3DSurface[m_currentFrames] = cursorTextures[cursor][i].Get_Surface_Level();
				m_currentFrames++;
			}
		}
	}
	return true;
}
