// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX-
// ?Rva00590FD4Get@@YAHPAVCDDrive@@@Z @0x00590FD4 54B leaf: free __cdecl size helper like Rva0059100AGet (44B) but returns getDataOffset+len+0x14
// evidence: same CDDrive::getPath via rowed 0x002D9BA6 into [ebp-4], same movzx word [eax+4] len, same releaseBuffer 0x00036410, plus NetWrapperCommandMsg::getDataOffset 0x00091A56 on same pointer (both mov ecx,[ebp+8] in retail) then lea eax,[eax+esi+0x14]; caller 0x005929F9; prev/next same ascii /O1 flags
#include "ascii_string.h"

class CDDrive
{
public:
	virtual AsciiString getPath();
};

class NetWrapperCommandMsg
{
public:
	unsigned int getDataOffset();
};

int __cdecl Rva00590FD4Get(CDDrive *p)
{
	CDDrive *o = p;
	int len = o->CDDrive::getPath().getLength();
	unsigned int off = ((NetWrapperCommandMsg *)o)->getDataOffset();
	return off + len + 0x14;
}
