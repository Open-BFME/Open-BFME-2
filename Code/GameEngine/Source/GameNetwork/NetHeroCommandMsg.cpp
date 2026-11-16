// cl: /O1 /DNDEBUG /MD /EHsc
// ??1NetHeroCommandMsg@@UAE@XZ @0x004D5902 35B: dtor freeing array member +0x24 then restoring base vtable.
// Target evidence: mov eax [esi+0x24] test je; vtable 0x00860264 then delete[] 0x0002FD80 and [esi+0x24]=0 then vtable 0x00860130; caller 0x004D5B17 for its deleting dtor; donor ctor NetCommandMsgCtor.cpp.
#include <new>
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};
class AsciiString;
typedef bool Bool;

#include "../../Include/GameNetwork/NetCommandMsg.h"
inline NetCommandMsg::~NetCommandMsg() {}
class NetHeroCommandMsg : public NetCommandMsg
{
public:
	virtual ~NetHeroCommandMsg();
private:
	unsigned int m_1c; // +0x1C
	unsigned short m_20; // +0x20
	char *m_24; // +0x24 array pointer
	unsigned int m_28; // +0x28
};
inline NetHeroCommandMsg::~NetHeroCommandMsg()
{
	if (m_24)
	{
		delete[] m_24;
		m_24 = 0;
	}
}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva004D58DEDtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeRva004D58DEDtorInlineAnchor()
{
    static_cast<NetHeroCommandMsg *>(0)->NetHeroCommandMsg::~NetHeroCommandMsg();
}
#pragma inline_depth()
