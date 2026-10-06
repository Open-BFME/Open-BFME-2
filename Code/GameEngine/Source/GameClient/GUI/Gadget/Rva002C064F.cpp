// cl: /DNDEBUG /MD
// ?Rva002C064FSet@@YAXPAVRva003140C8DwordField@@PBVImage@@@Z @0x002C064F 26B: conditional disabled-image123 set via dword-field window
// Evidence: siblings Rva002C055F 0x002C055F Rva002C05AF 0x002C05AF Rva002C05FF 0x002C05FF same shape same flags; callers 0x002C3CF9 0x002C3FE3 0x002C433C 0x002C4B9B; callees rowed get 0x003140C8 and GadgetButtonSetDisabledImage123 0x002C04B1; int row really a GameWindow* (DispDwordField family is width-only)
class Rva003140C8DwordField
{
public:
	int get() const;
};
class GameWindow;
class Image;
void __cdecl GadgetButtonSetDisabledImage123_Rva002C04B1(GameWindow *win, const Image *image);
void __cdecl Rva002C064FSet(Rva003140C8DwordField *holder, const Image *image)
{
	int v = holder->get();
	if (v)
		GadgetButtonSetDisabledImage123_Rva002C04B1((GameWindow *)v, image);
}
