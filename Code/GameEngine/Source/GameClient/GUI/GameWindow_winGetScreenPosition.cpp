// cl: /O1 /DNDEBUG /MD
// ?winGetScreenPosition@GameWindow@@QAEHPAH0@Z
// retail 0x00313B3C, 51 bytes. Dedicated TU.
//
// Ported from Open-BFME-1
// Code/GameEngine/Source/GameClient/GUI/GameWindowFields.cpp (which matches
// 58B there): walk the parent chain accumulating the region origin. The
// retail loop falls through with eax holding the null parent (which equals
// WIN_ERR_OK), so there is no explicit return-value setup.

typedef int Int;
typedef int WinErr;

#ifndef NULL
#define NULL 0
#endif

static const WinErr WIN_ERR_OK = 0;
static const WinErr WIN_ERR_INVALID_PARAMETER = -3;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	Int winGetPosition(Int *x, Int *y);

private:
	unsigned char m_unreconstructed_000[0x0C];
	ICoord2D m_size;				// +0x0C
	IRegion2D m_region;				// +0x14 (lo+hi, 0x10 bytes)
	unsigned char m_unreconstructed_024[0x200 - 0x24];
	GameWindow *m_parent;			// +0x200
};

// ?winGetScreenPosition@GameWindow@@QAEHPAH0@Z
Int GameWindow::winGetScreenPosition(Int *x, Int *y)
{
	GameWindow *parent = m_parent;

	*x = m_region.lo.x;
	*y = m_region.lo.y;

	while (parent) {
		*x += parent->m_region.lo.x;
		*y += parent->m_region.lo.y;
		parent = parent->m_parent;
	}

	// Retail falls through with eax holding the null parent (which equals
	// WIN_ERR_OK), so return it directly instead of materializing the
	// constant (which would cost an xor).
	return (Int)parent;
}

// ?winGetSize@GameWindow@@QAEHPAH0@Z, retail 0x00313BC6 (38B). Same BFME1
// file, verbatim port: null-checked size fetch with -3/0 codes.
Int GameWindow::winGetSize(Int *width, Int *height)
{
	if (width == NULL || height == NULL) {
		return WIN_ERR_INVALID_PARAMETER;
	}

	*width = m_size.x;
	*height = m_size.y;

	return WIN_ERR_OK;
}

// ?winGetPosition@GameWindow@@QAEHPAH0@Z, retail 0x00313AE4 (38B). Twin of
// winGetSize over the region origin at +0x14/+0x18: null-checked position
// fetch with -3/0 codes. Called by the Slide/Spiral animate-window bodies.
Int GameWindow::winGetPosition(Int *x, Int *y)
{
	if (x == NULL || y == NULL) {
		return WIN_ERR_INVALID_PARAMETER;
	}

	*x = m_region.lo.x;
	*y = m_region.lo.y;

	return WIN_ERR_OK;
}
