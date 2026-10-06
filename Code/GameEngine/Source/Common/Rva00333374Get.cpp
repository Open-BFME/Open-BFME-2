// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ?Rva00333374Get@@YA?AVAsciiString@@PBURva00333374IdOwner@@@Z, retail 0x00333374, 93B.
// Free AsciiString(Object id) via "ObjID#%08x": stack temp format through rowed
// AsciiString::format 0x00038150 then RVO copy through pinned StringBase<char>
// copy 0x000365F0 and temp teardown through rowed releaseBuffer 0x00036410.
// Twin of rowed ?Rva00222834Get@@YA?AVAsciiString@@H@Z @0x00222834 (90B "%d")
// plus 3B for the +0x74 id load; callers 0x00333E5B/0x00333F37/0x00334003 prove
// hidden-return RVO shape. Object m_id at +0x74 (Object_setID.cpp). Honest
// free-function name; donor Rva00222834Get.cpp.
#include "ascii_string.h"


struct Rva00333374IdOwner
{
	unsigned char m_pad[0x74];
	int m_id; // +0x74
};

AsciiString Rva00333374Get(const Rva00333374IdOwner *p)
{
	AsciiString tmp;
	tmp.format("ObjID#%08x", p->m_id);
	return tmp;
}
