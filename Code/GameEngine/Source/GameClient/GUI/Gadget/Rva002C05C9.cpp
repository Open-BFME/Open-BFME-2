// cl: /DNDEBUG /MD
// ?Rva002C05C9Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C05C9 27B: conditional enabled-color-1 set via dword-field window
// Evidence: sibling Rva002C0579 0x002C0579 same shape same flags push 1 not 0; callers 0x002C3CA9 0x002C3F93; callees rowed get 0x003140C8 and winSetEnabledColor 0x003143DD; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow
{
public:
	int winSetEnabledColor(int a, int b);
};
void __cdecl Rva002C05C9Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetEnabledColor(1, color);
}
