// cl: /DNDEBUG /MD
// ?Rva002C055FSet@@YAXPAVRva003140C8DwordField@@PBVImage@@@Z @0x002C055F 26B: conditional enabled-image set via dword-field window
// Evidence: neighbours GadgetButtonImageHelpers 0x002C0505 and Rva002C08EF 0x002C08EF same flags; callers 0x002C3C79 0x002C3F63 0x002C4291 0x002C4AF0; callees rowed get 0x003140C8 and GadgetButtonSetEnabledImage 0x002C0433; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow;
class Image;
void __cdecl GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *win, const Image *image);
void __cdecl Rva002C055FSet(Rva003140C8DwordField *holder, const Image *image)
{
	int v = holder->get();
	if (v)
		GadgetButtonSetEnabledImage_Rva002C0433((GameWindow *)v, image);
}
