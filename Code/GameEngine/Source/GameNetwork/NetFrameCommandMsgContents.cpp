// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@NetFrameCommandMsg@@UAE?AVAsciiString@@XZ, retail 0x004D5C2B, 147 bytes.
// NetFrameCommandMsg contents slot 3: base NetCommandMsg::getContentsAsAsciiString plus
// ", logicFrame=%d, clientFrame=%d, totalCommands=%d" over the three dwords at
// +0x1C/+0x20/+0x24 (the frame command's frame, player frame and command
// count, as NetPacket's frame arm and sendFrameInfo name them).
// Evidence: the format string at 0x00C602FC, base 0x004D5B4C, format 0x00038150,
// the empty-string fallback, and the 0x28-byte frame message layout.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D5C2B(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

#include "../../Include/GameNetwork/NetFrameCommandMsg.h"

AsciiString NetFrameCommandMsg::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, logicFrame=%d, clientFrame=%d, totalCommands=%d", GetStr004D5C2B(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), getFrame(), getPlayerFrame(), getCommandCount());
	return result;
}
