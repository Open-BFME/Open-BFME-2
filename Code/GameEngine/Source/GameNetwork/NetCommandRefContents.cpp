// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0058B8BA@NetCommandRef@@QAE?AVAsciiString@@XZ @0x0058B8BA 142B: NetCommandRef
// contents string, "%s, relay=0x%X" over the referenced message's contents.
// Target evidence: directly after ~NetCommandRef 0x0058B8AE; slot-3 virtual call
// (getContentsAsAsciiString, as NetGameCommandMsg's vtable 0x008601E4 slot 3) on
// the message at +0x0 into a returned temporary, its str() with the "" literal
// fallback, the relay byte at +0xC, format literal 0x00870A10, AsciiString::format
// 0x00038150, releaseBuffer 0x00036410 and the StringBase copy 0x000365F0 for the
// return. Donor shape: Open-BFME-1 game/GameEngine/Source/Common/BfmeOrderDescribeZT.cpp
// (BFME 0x00676290, same literal and layout); no caller or name survives in
// either image, so the method keeps an address name.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();
	virtual void *getObjectMemoryPool();
	virtual int getSortNumber();
	virtual AsciiString getContentsAsAsciiString();
};

class NetCommandRef
{
public:
	AsciiString rva0058B8BA();

private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

AsciiString NetCommandRef::rva0058B8BA()
{
	AsciiString text;
	text.format("%s, relay=0x%X", m_msg->getContentsAsAsciiString().str(), m_relay);
	return text;
}
