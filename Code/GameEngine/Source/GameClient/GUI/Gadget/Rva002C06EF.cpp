// cl: /DNDEBUG /MD
// ?Rva002C06EFSet@@YAXPAVRva003140C8DwordField@@PBVImage@@@Z @0x002C06EF 26B: conditional hilite-image123 set via dword-field window
// Evidence: siblings Rva002C055F 0x002C055F Rva002C05AF 0x002C05AF Rva002C05FF 0x002C05FF Rva002C064F 0x002C064F Rva002C069F 0x002C069F same shape same flags; callers 0x002C3D5B 0x002C43CC 0x002C4C2B; callees rowed get 0x003140C8 and GadgetButtonSetHiliteImage123 0x002C0505; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow;
class Image;
void __cdecl GadgetButtonSetHiliteImage123_Rva002C0505(GameWindow *win, const Image *image);
void __cdecl Rva002C06EFSet(Rva003140C8DwordField *holder, const Image *image)
{
	int v = holder->get();
	if (v)
		GadgetButtonSetHiliteImage123_Rva002C0505((GameWindow *)v, image);
}
