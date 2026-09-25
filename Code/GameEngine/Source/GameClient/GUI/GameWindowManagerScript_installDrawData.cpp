// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?installDrawData_Rva003157BE@@YAXPAVGameWindow@@0PAUWinDrawData@@11@Z,
// retail 0x003157BE, 128 bytes.
// Dedicated TU.
//
// Draw-data installer used by createGadget (retail 0x00316518) for the
// slider, listbox and combobox arms. Copies the enabled/disabled/hilite
// draw-data arrays (0x6C bytes each) into the target window's instance
// block at +0x18/+0x84/+0xF0. Each array comes from the file's static
// triple, unless the extra sibling window is present, in which case the
// matching array is forwarded from the sibling's instance block instead.
//
// BFME2 facts (all retail-measured):
// - the instance block is reached through the opaque disp8 lea getter at
//   0x00314046 (lea [ecx+0x30]); the holder class is redeclared here with
//   the identical decoration so the calls stay direct E8. The suspected
//   identity is GameWindow::winGetInstanceData, stated as comment only.
// - memcpy is a plain extern (no dllimport) so the calls stay direct E8
//   to the thunk at 0x006291A8.

typedef unsigned int UnsignedInt;

#ifndef NULL
#define NULL 0
#endif

class GameWindow;
struct WinDrawData;

// Opaque holder for the 0x00314046 lea getter (see Disp8LeaFieldGetters.cpp
// for the owning definition). Re-spelled here, not redefined.
class Rva00314046LeaField
{
public:
	void *get() const;
};

// Minimal instance-block model: only the three draw-data arrays this body
// touches exist. Layout witness: memcpy destinations at +0x18/+0x84/+0xF0,
// each 0x6C bytes.
struct WinInstanceData
{
	unsigned char m_pad00[0x18];
	unsigned char m_enabledDrawData[0x6C];
	unsigned char m_disabledDrawData[0x6C];
	unsigned char m_hiliteDrawData[0x6C];
};

extern "C" void *memcpy(void *dst, const void *src, UnsignedInt n);

// ?installDrawData_Rva003157BE@@YAXPAVGameWindow@@0PAUWinDrawData@@11@Z
static void installDrawData_Rva003157BE(GameWindow *win, GameWindow *extra, WinDrawData *a, WinDrawData *b, WinDrawData *c)
{
	WinInstanceData *extraData;
	WinInstanceData *winData;

	if (!win)
		return;

	winData = (WinInstanceData *)((Rva00314046LeaField *)win)->get();
	if (extra)
		extraData = (WinInstanceData *)((Rva00314046LeaField *)extra)->get();
	else
		extraData = NULL;

	memcpy(winData->m_enabledDrawData,
		extraData ? (const void *)extraData->m_enabledDrawData : (const void *)a, 0x6C);
	memcpy(winData->m_disabledDrawData,
		extraData ? (const void *)extraData->m_disabledDrawData : (const void *)b, 0x6C);
	memcpy(winData->m_hiliteDrawData,
		extraData ? (const void *)extraData->m_hiliteDrawData : (const void *)c, 0x6C);
}

static const void *s_installDrawDataAnchor = (const void *)installDrawData_Rva003157BE;
