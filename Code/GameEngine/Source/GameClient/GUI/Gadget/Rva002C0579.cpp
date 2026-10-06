// cl: /DNDEBUG /MD
// ?Rva002C0579Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C0579 27B: conditional enabled-color set via dword-field window
// Evidence: sibling Rva002C055F family same holder same flags; callers 0x002C3C82 0x002C3F6C; callees rowed get 0x003140C8 and winSetEnabledColor 0x003143DD; int row really a GameWindow* (DispDwordField family is width-only)
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
void __cdecl Rva002C0579Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetEnabledColor(0, color);
}
