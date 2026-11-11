// cl: /MD
// ?Rva005CD762Get@@YGEPAX@Z @0x005CD762 41B: stdcall uchar always-1 wrapper checking rowed get 0x005CCB3E then rowed Peek_Texture 0x005CCB37 vs 1 then rowed 0x005CCB63; evidence rows and ret-4 with mov-al-1
#include "../../Include/Common/Rva005CCB3EByteChaseField.h"

class TextureClass;
#include "../../../Libraries/Source/WWVegas/WW3D2/Font3DInstanceClass.h"

class Rva005CCB63
{
public:
	void rva005CCB63();
};

unsigned char __stdcall Rva005CD762Get(void *p)
{
	if (((Rva005CCB3EByteChaseField *)p)->get() != 0)
		return 1;
	if (((Font3DInstanceClass *)p)->Peek_Texture() != (TextureClass *)1)
		return 1;
	((Rva005CCB63 *)p)->rva005CCB63();
	return 1;
}
