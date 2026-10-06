// cl: /DNDEBUG /MD
// ?Rva002C0619Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C0619 27B: conditional disabled-color set via dword-field window
// Evidence: siblings Rva002C05FF 0x002C05FF and Rva002C064F 0x002C064F same shape same flags; callers 0x002C3CD8 0x002C3FC2; callees rowed get 0x003140C8 and winSetDisabledColor 0x00314445; int row really a GameWindow* (DispDwordField family is width-only)
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
void __cdecl Rva002C0619Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetDisabledColor(0, color);
}
