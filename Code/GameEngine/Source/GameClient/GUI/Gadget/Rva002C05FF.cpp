// cl: /DNDEBUG /MD
// ?Rva002C05FFSet@@YAXPAVRva003140C8DwordField@@PBVImage@@@Z @0x002C05FF 26B: conditional disabled-image set via dword-field window
// Evidence: siblings Rva002C055F 0x002C055F and Rva002C05AF 0x002C05AF same shape same flags; callers 0x002C3CCC 0x002C3FB6 0x002C4324 0x002C4B83; callees rowed get 0x003140C8 and GadgetButtonSetDisabledImage 0x002C0487; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow;
class Image;
void __cdecl GadgetButtonSetDisabledImage_Rva002C0487(GameWindow *win, const Image *image);
void __cdecl Rva002C05FFSet(Rva003140C8DwordField *holder, const Image *image)
{
	int v = holder->get();
	if (v)
		GadgetButtonSetDisabledImage_Rva002C0487((GameWindow *)v, image);
}
