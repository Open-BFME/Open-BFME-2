// cl: /DNDEBUG /MD
// ?Rva002C05AFSet@@YAXPAVRva003140C8DwordField@@PBVImage@@@Z @0x002C05AF 26B: conditional enabled-image123 set via dword-field window
// Evidence: sibling Rva002C055F 0x002C055F same shape same flags; callers 0x002C3CA0 0x002C3F8A 0x002C42A9 0x002C4B08; callees rowed get 0x003140C8 and GadgetButtonSetEnabledImage123 0x002C045D; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow;
class Image;
void __cdecl GadgetButtonSetEnabledImage123_Rva002C045D(GameWindow *win, const Image *image);
void __cdecl Rva002C05AFSet(Rva003140C8DwordField *holder, const Image *image)
{
	int v = holder->get();
	if (v)
		GadgetButtonSetEnabledImage123_Rva002C045D((GameWindow *)v, image);
}
