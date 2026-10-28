// cl: /DNDEBUG /MD
// ?Rva002C069FSet@@YAXPAVRva003140C8DwordField@@PBVImage@@@Z @0x002C069F 26B: conditional hilite-image set via dword-field window
// Evidence: siblings Rva002C055F 0x002C055F Rva002C05AF 0x002C05AF Rva002C05FF 0x002C05FF Rva002C064F 0x002C064F same shape same flags; callers 0x002C3D2A 0x002C4014 0x002C43B8 0x002C4C17; callees rowed get 0x003140C8 and GadgetButtonSetHiliteImage 0x002C04DB; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow;
class Image;
void __cdecl GadgetButtonSetHiliteImage_Rva002C04DB(GameWindow *win, const Image *image);
void __cdecl Rva002C069FSet(Rva003140C8DwordField *holder, const Image *image)
{
	int v = holder->get();
	if (v)
		GadgetButtonSetHiliteImage_Rva002C04DB((GameWindow *)v, image);
}
