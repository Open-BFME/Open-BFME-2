// cl: /Oy- /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?freeD3DAssets@W3DMouse@@AAEXXZ, retail 0x00098FF1, 102 bytes.
// Ghidra boundary 0x98FF1/102. Target loops over the current 21 surface
// holders at this+0x6028, then clears the contiguous cursor texture holder
// table from 0xDE4B40 to 0xDE5DA0 in 21-slot groups.

// CursorTextureSlot is a class in retail (reverse/class_contracts/CursorTextureSlot.json, key by bytes),
// so this view spells the class-key the definition of cursorTextures mangles with.
#include "../../../../GameEngine/Include/Common/CursorTextureSlot.h"

enum
{
	MAX_2D_CURSOR_ANIM_FRAMES = 21,
	NUM_MOUSE_CURSORS = 56
};

extern CursorTextureSlot cursorTextures[][MAX_2D_CURSOR_ANIM_FRAMES];

#include "../../../../GameEngine/Include/Common/W3DRadarResetSurface.h"

struct MouseCursorInfo
{
	char pad00[0x30];
	char *textureName;
	char pad38[0x1C];
	int numFrames;
};
typedef char CursorInfoStride[(sizeof(MouseCursorInfo) == 0x54) ? 1 : -1];

#include "../../../../Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h"

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
			W3DRadarResetSurface emptySurface;
			m_currentD3DSurface[i] = emptySurface;
		}
	}

	for (int cursor = 0; cursor < NUM_MOUSE_CURSORS; ++cursor) {
		for (int frame = 0; frame < MAX_2D_CURSOR_ANIM_FRAMES; ++frame) {
			reinterpret_cast<BfmeResetTextureRef &>(cursorTextures[cursor][frame]).clear();
		}
	}
}
