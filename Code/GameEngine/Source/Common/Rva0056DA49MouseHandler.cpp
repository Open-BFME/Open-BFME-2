// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0056DA49@Rva0056DA49@@QAEHIII@Z, retail 0x0056DA49 (208 bytes, RET
// 0x0C): slot 2 of the Apt window table 0x0086DB3C (deleting destructor
// ??_GRva0056D915 in slot 1, the rowed 0x1B dispatcher 0x0056D9C1 in slot 3).
// The mouse half of the window's input: the packed position argument is
// split into x (low word) and y (high word) and handed with the third argument
// to the cursor tracker at +0x27C: button presses (messages 5, 9, 0x0D) to
// 0x005C9B0C, releases (6, 0x0A, 0x0E) to 0x005C9B31, both with the button
// the message names; a move (0x18) to 0x005C9ADD. All three answer handled.
// Message 0x12 resets the tracker (0x005C9B56) and, like anything else, is
// not handled.
//
// ?WindowMsgButtonToInGameUIButton@@YAHI@Z, retail 0x0056DA0F (41 bytes):
// the file-static button mapping (WorldBuilder name; left 0, right 1, middle
// 2). Kept out of line, cl 7.1 passes its message in EAX.
// Address-derived names; this view emits no vtable.
struct Rva0056DA49Point
{
	int x;
	int y;
};

#include "../../Include/GameLogic/Module/Obj005C9B0C.h"
class Rva005C9B76
{
public:
	int rva005C9ADD(int point, int extra);
	void rva005C9B56(int value);
};

#pragma auto_inline(off)
static int WindowMsgButtonToInGameUIButton(unsigned int msg)
{
	switch (msg)
	{
	case 5:
	case 6:
		return 0;
	case 9:
	case 10:
		return 1;
	case 13:
	case 14:
		return 2;
	}
	return 0;
}
#pragma auto_inline(on)

// Retail 0x0056DA38: a message's packed screen position (low word x, high
// word y) as a file static; the handler inlines it three times and cl keeps
// this register-convention copy (position in EAX, point in ECX).
static void packedToPoint(unsigned int pos, Rva0056DA49Point *point)
{
	point->x = pos & 0xFFFF;
	point->y = pos >> 16;
}

class Rva0056DA49
{
public:
	int rva0056DA49(unsigned int msg, unsigned int pos, unsigned int extra);
private:
	unsigned char m_pad000[0x27C];
	unsigned char m_tracker[4];	// +0x27C
};

int Rva0056DA49::rva0056DA49(unsigned int msg, unsigned int pos, unsigned int extra)
{
	Rva0056DA49Point point;
	switch (msg)
	{
	case 5:
	case 9:
	case 0x0D:
		packedToPoint(pos, &point);
		((Obj005C9B0C *)m_tracker)->rva005C9B0C((int)&point, extra, WindowMsgButtonToInGameUIButton(msg));
		return 1;
	case 6:
	case 0x0A:
	case 0x0E:
		packedToPoint(pos, &point);
		((Obj005C9B0C *)m_tracker)->rva005C9B31((int)&point, extra, WindowMsgButtonToInGameUIButton(msg));
		return 1;
	case 0x18:
		packedToPoint(pos, &point);
		((Rva005C9B76 *)m_tracker)->rva005C9ADD((int)&point, extra);
		return 1;
	case 0x12:
		((Rva005C9B76 *)m_tracker)->rva005C9B56(0);
		break;
	}
	return 0;
}
