// cl: /DNDEBUG /MD
// ?Rva002C0669Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C0669 27B: conditional disabled-color-1 set via dword-field window
// Evidence: siblings Rva002C0619 0x002C0619 push 0 and Rva002C05C9 0x002C05C9 push 1 same shape same flags; callers 0x002C3D05 0x002C3FEF; callees rowed get 0x003140C8 and winSetDisabledColor 0x00314445; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow
{
public:
	int winSetDisabledColor(int a, int b);
};
void __cdecl Rva002C0669Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetDisabledColor(1, color);
}
