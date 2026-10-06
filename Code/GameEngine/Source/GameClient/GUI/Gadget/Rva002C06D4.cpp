// cl: /DNDEBUG /MD
// ?Rva002C06D4Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C06D4 27B: conditional hilite-border-color set via dword-field window
// Evidence: siblings Rva002C0634 0x002C0634 and Rva002C06B9 0x002C06B9 same shape same flags; callers 0x002C3D42 0x002C402C; callees rowed get 0x003140C8 and winSetHiliteBorderColor 0x003144D8; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow
{
public:
	int winSetHiliteBorderColor(int a, int b);
};
void __cdecl Rva002C06D4Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetHiliteBorderColor(0, color);
}
