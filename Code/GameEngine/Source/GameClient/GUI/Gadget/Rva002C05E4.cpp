// cl: /DNDEBUG /MD
// ?Rva002C05E4Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C05E4 27B: conditional enabled-border-color-1 set via dword-field window
// Evidence: sibling Rva002C0594 0x002C0594 same shape same flags push 1 not 0; callers 0x002C3CB2 0x002C3F9C; callees rowed get 0x003140C8 and winSetEnabledBorderColor 0x003143FF; int row really a GameWindow* (DispDwordField family is width-only)
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
void __cdecl Rva002C05E4Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetEnabledBorderColor(1, color);
}
