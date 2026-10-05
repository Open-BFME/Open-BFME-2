// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?Rva00591036Get@@YAHPAVCDDrive@@@Z @0x00591036 44B. Free __cdecl size helper:
// copies CDDrive::getPath AsciiString via rowed 0x002D9BA6 into dead arg home
// [ebp+8], reads header length word at m_data+4, releases via temp dtor ->
// rowed releaseBuffer 0x00036410, returns len+0x10. Caller 0x00592A15.
// Sibling of 0x0059100A (+0x13) landed in Rva0059100AGet.cpp.
#include "ascii_string.h"

class CDDrive
{
public:
	virtual AsciiString getPath();
};

int __cdecl Rva00591036Get(CDDrive *p)
{
	CDDrive *o = p;
	int len = o->CDDrive::getPath().getLength();
	return len + 0x10;
}
