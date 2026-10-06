// cl: /DNDEBUG /MD
// ?Rva002C0709Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C0709 27B: conditional hilite-color-1 set via dword-field window
// Evidence: siblings Rva002C0669 0x002C0669 and Rva002C06B9 0x002C06B9 same shape same flags push 1; caller 0x002C3D67; callees rowed get 0x003140C8 and winSetHiliteColor 0x003144B3; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow
{
public:
	int winSetHiliteColor(int a, int b);
};
void __cdecl Rva002C0709Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetHiliteColor(1, color);
}
