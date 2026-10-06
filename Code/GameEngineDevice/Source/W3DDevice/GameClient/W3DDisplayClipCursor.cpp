// cl: /DNDEBUG /MD /EHsc
// ?clipCursorToClient@@YAXXZ, retail 0x000430C8, 98 bytes.
#pragma optimize("y", off)
// Ported from Open-BFME-1
// (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayClipCursor.cpp,
// their matched 113B row). Retail-measured deltas: the application window
// handle lives at 0x00DDE024 (re-read per use, like TheDisplay); the frame is
// 0x18 with esi/edi saved. Identity proven by the three user32 imports
// (GetClientRect + ClientToScreen + ClipCursor) in BFME1's order.

struct BfmeRect
{
	long left;
	long top;
	long right;
	long bottom;
};

struct BfmePoint
{
	long x;
	long y;
};

// Retail address 0x00DDE024; patched from retail like any extern (no pin).
extern void *ApplicationHWnd;

extern "C" __declspec(dllimport) int __stdcall GetClientRect(void *window, BfmeRect *rect);
extern "C" __declspec(dllimport) int __stdcall ClientToScreen(void *window, BfmePoint *point);
extern "C" __declspec(dllimport) int __stdcall ClipCursor(const BfmeRect *rect);

void clipCursorToClient(void)
{
	BfmeRect rect;
	GetClientRect(ApplicationHWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	BfmePoint point;
	point.x = rect.left;
	point.y = rect.top;
	ClientToScreen(ApplicationHWnd, &point);
	rect.left = point.x;
	rect.top = point.y;
	rect.right = point.x + width;
	rect.bottom = point.y + height;
	ClipCursor(&rect);
}
