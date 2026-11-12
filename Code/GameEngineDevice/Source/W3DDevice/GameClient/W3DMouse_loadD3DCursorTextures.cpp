// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// platformsdk

// ?loadD3DCursorTextures@W3DMouse@@AAE_NW4MouseCursor@@@Z, retail 0x000999CE,
// 417 bytes. BFME2's cursor-texture loader: same algorithm as BFME1
// W3DMouse::loadD3DCursorTextures (single-frame branch plus %04d loop) but
// BFME2-new layout and glue — the texture table is a global of counted
// holders, cursor info rides in 84-byte records behind the vptr, and textures
// arrive through the cached free loader (no WW3DAssetManager instance).

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
	void rva000723AC();
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

#include "../../../Include/W3DDevice/GameClient/TextureAsset.h"

#include "../../../../GameEngine/Include/Common/CursorTextureSlot.h"

#include <stdio.h>
#include <windows.h>
#include "ascii_string.h"

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
inline W3DRadarResetSurface &W3DRadarResetSurface::operator=(const W3DRadarResetSurface &rhs)
{
	if (rhs.m_surface != NULL)
		rhs.m_surface->AddRef();
	if (m_surface != NULL)
		m_surface->Release();
	m_surface = rhs.m_surface;
	return *this;
}

// This operator is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeW3DRadarResetSurfaceAssignInlineAnchor@@YAXXZ absent-from-retail
void _bfmeW3DRadarResetSurfaceAssignInlineAnchor()
{
	W3DRadarResetSurface *surface = static_cast<W3DRadarResetSurface *>(0);
	*surface = *surface;
}
#pragma inline_depth()

// ?rva000723AC@W3DRadarResetSurface@@QAEXXZ, RVA 0x000723AC, 20B. Release the
// held COM surface if present and null it. Evidence: caller 0x724AE clears
// +0x08 via rowed BfmeResetTextureRef::clear then tail-jumps here for +0x0c;
// same AddRef/Release slots as operator= at 0x72381 in this TU.
void W3DRadarResetSurface::rva000723AC()
{
	if (m_surface) {
		m_surface->Release();
		m_surface = 0;
	}
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
		cursorTextures[cursor][0] = TextureAsset::Get(frameName, 0, 0);
		m_currentD3DSurface[0] = cursorTextures[cursor][0].Get_Surface_Level();
		m_currentFrames = 1;
	}
	else
	{
		for (int i = 0; i < animFrames; i++)
		{
			sprintf(frameName, "%s%04d.tga", baseName, i);
			if ((cursorTextures[cursor][i] = TextureAsset::Get(frameName, 0, 0), cursorTextures[cursor][i].Ptr) != NULL)
			{
				m_currentD3DSurface[m_currentFrames] = cursorTextures[cursor][i].Get_Surface_Level();
				m_currentFrames++;
			}
		}
	}
	return true;
}
