// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva0059100AGet@@YAHPAVCDDrive@@@Z @0x0059100A 44B. Free __cdecl size helper:
// copies CDDrive::getPath AsciiString via rowed 0x002D9BA6 into dead arg home
// [ebp+8], reads header length word at m_data+4, releases via temp dtor ->
// rowed releaseBuffer 0x00036410, returns len+0x13. Caller 0x00592A01.
#include "ascii_string.h"

class CDDrive
{
public:
	virtual AsciiString getPath();
};

int __cdecl Rva0059100AGet(CDDrive *p)
{
	CDDrive *o = p;
	int len = o->CDDrive::getPath().getLength();
	return len + 0x13;
}
