// cl: /DNDEBUG /MD
// ?Rva002C0724Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C0724 27B: conditional hilite-border-color-1 set via dword-field window
// Evidence: siblings Rva002C06D4 0x002C06D4 push 0 and Rva002C0709 0x002C0709 push 1 same shape same flags; caller 0x002C3D73; callees rowed get 0x003140C8 and winSetHiliteBorderColor 0x003144D8; int row really a GameWindow* (DispDwordField family is width-only)
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
void __cdecl Rva002C0724Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetHiliteBorderColor(1, color);
}
