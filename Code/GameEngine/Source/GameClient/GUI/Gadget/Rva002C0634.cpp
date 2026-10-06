// cl: /DNDEBUG /MD
// ?Rva002C0634Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C0634 27B: conditional disabled-border-color set via dword-field window
// Evidence: siblings Rva002C0619 0x002C0619 and Rva002C064F 0x002C064F same shape same flags; callees rowed get 0x003140C8 and winSetDisabledBorderColor 0x0031446A; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow
{
public:
	int winSetDisabledBorderColor(int a, int b);
};
void __cdecl Rva002C0634Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetDisabledBorderColor(0, color);
}
