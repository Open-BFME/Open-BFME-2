// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva00592520Read@@YAPAVRva004D65DC@@HPAI@Z @0x00592520 (194B):
// NetCommandMsg Rva004D65DC deserializer: new plus two null-terminated
// strings via byte loops plus AsciiString temps. Evidence: new 0x24 plus
// ctor 0x4D65DC, loops to [ebp-0x110], StringBase char ctor 0x37BA0 twice,
// setters 0x4D65F9 plus 0x4D662D; callers 0x5928FC 0x5941B8;
// chain from 0x004D662D.
void *__cdecl operator new(unsigned int size);

#include "ascii_string.h"


class Rva004D64F5
{
public:
	void rva004D65F9(AsciiString s);
};

class Rva004D65DC : public Rva004D64F5
{
public:
	Rva004D65DC();
	void rva004D662D(AsciiString s);
private:
	char m_pad[0x24];
};

class Rva004D65DC *__cdecl Rva00592520Read(int base, unsigned int *cursor)
{
	Rva004D65DC *obj = new Rva004D65DC;
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
	dst = buf;
	while (((const char *)base)[*cursor] != 0) {
		*dst = ((const char *)base)[*cursor];
		++dst;
		++*cursor;
	}
	++*cursor;
	*dst = 0;
	obj->rva004D662D(AsciiString(buf));
	return obj;
}
