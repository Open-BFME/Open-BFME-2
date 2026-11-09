// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@NetAckBothCommandMsg@@UAE?AVAsciiString@@XZ, retail 0x004D5DEF, 151 bytes.
// NetAckBothCommandMsg contents slot 3 of 0x008601F4: base
// NetCommandMsg::getContentsAsAsciiString plus ", commandID=%d, origPlayer=%d, origExeSID=%d, origExeFrame=%d".
// Identity from vtable slot 3, ctor 0x004D568F layout +0x1c word +0x1e byte +0x20 +0x24,
// format 0x00860360, callee base 0x004D5B4C, format 0x00038150,
// and empty fallback g_Rva0107301CEmptyString.
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


__forceinline const char *GetStr004D5DEF(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	// Slot 3 of this class's vftable, where NetCommandMsg declares
	// getContentsAsAsciiString: the override.
	virtual AsciiString getContentsAsAsciiString();
	// ICF-folded with every same-shape setter (0x004D59AC / 0x004D576C).
	void setCommandID(UnsignedShort commandID);
	void setOriginalPlayerID(UnsignedByte originalPlayerID);
private:
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	char m_pad1F;
	UnsignedInt m_20;
	UnsignedInt m_24;
};

AsciiString NetAckBothCommandMsg::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, commandID=%d, origPlayer=%d, origExeSID=%d, origExeFrame=%d", GetStr004D5DEF(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), m_commandID, m_originalPlayerID, m_20, m_24);
	return result;
}

void NetAckBothCommandMsg::setCommandID(UnsignedShort commandID)
{
	m_commandID = commandID;
}

void NetAckBothCommandMsg::setOriginalPlayerID(UnsignedByte originalPlayerID)
{
	m_originalPlayerID = originalPlayerID;
}
