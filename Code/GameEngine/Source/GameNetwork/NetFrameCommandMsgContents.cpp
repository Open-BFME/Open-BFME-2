// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@NetFrameCommandMsg@@UAE?AVAsciiString@@XZ, retail 0x004D5C2B, 147 bytes.
// NetFrameCommandMsg contents slot 3: base NetCommandMsg::rva004D5B4C plus
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


__forceinline const char *GetStr004D5C2B(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class NetCommandMsg
{
public:
	AsciiString rva004D5B4C();
protected:
	virtual ~NetCommandMsg();
private:
	virtual MemoryPool *getObjectMemoryPool();
public:
	virtual Int getSortNumber();
	virtual AsciiString getContentsAsAsciiString();
protected:
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

class NetFrameCommandMsg : public NetCommandMsg
{
public:
	virtual AsciiString getContentsAsAsciiString();
	UnsignedInt getFrame() const { return m_frame; }
	UnsignedInt getPlayerFrame() const { return m_playerFrame; }
	UnsignedInt getCommandCount() const { return m_commandCount; }
private:
	UnsignedInt m_frame;
	UnsignedInt m_playerFrame;
	UnsignedInt m_commandCount;
};

AsciiString NetFrameCommandMsg::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, logicFrame=%d, clientFrame=%d, totalCommands=%d", GetStr004D5C2B(((NetCommandMsg *)this)->rva004D5B4C()), getFrame(), getPlayerFrame(), getCommandCount());
	return result;
}
