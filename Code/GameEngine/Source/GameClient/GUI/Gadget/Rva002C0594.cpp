// cl: /DNDEBUG /MD
// ?Rva002C0594Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C0594 27B: conditional enabled-border-color set via dword-field window
// Evidence: sibling Rva002C0579 0x002C0579 same shape same flags; callers 0x002C3C8B 0x002C3F75; callees rowed get 0x003140C8 and winSetEnabledBorderColor 0x003143FF; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow
{
public:
	int winSetEnabledBorderColor(int a, int b);
};
void __cdecl Rva002C0594Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetEnabledBorderColor(0, color);
}
