// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva00592496Read@@YAPAVRva004D64F5@@HPAI@Z @0x00592496 (138B):
// NetCommandMsg Rva004D64F5 deserializer: new plus null-terminated string
// via byte loop plus AsciiString temp. Evidence: new 0x20 plus ctor 0x4D64F5,
// copy loop to [ebp-0x110], StringBase char ctor 0x37BA0, setter 0x4D65F9;
// callers 0x5928EB 0x5941AC; chain from 0x004D64F5.
void *__cdecl operator new(unsigned int size);

#include "ascii_string.h"


class Rva004D64F5
{
public:
	Rva004D64F5();
	void rva004D65F9(AsciiString s);
private:
	char m_pad[0x20];
};

class Rva004D64F5 *__cdecl Rva00592496Read(int base, unsigned int *cursor)
{
	Rva004D64F5 *obj = new Rva004D64F5;
	char buf[256];
	char *dst = buf;
	while (((const char *)base)[*cursor] != 0) {
		*dst = ((const char *)base)[*cursor];
		++dst;
		++*cursor;
	}
	++*cursor;
	*dst = 0;
	obj->rva004D65F9(AsciiString(buf));
	return obj;
}
