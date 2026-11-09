// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@NetAckStage2CommandMsg@@UAE?AVAsciiString@@XZ, retail 0x004D5F1D, 151 bytes.
// NetAckStage2CommandMsg contents slot 3 of 0x00860214: base
// NetCommandMsg::getContentsAsAsciiString plus ", commandID=%d, originalPlayer=%d, origExeSID=%d, originalExecFrame=%d".
// Identity from vtable slot 3, ctor 0x004D5741 layout +0x1c word +0x1e byte +0x20 +0x24,
// format 0x008603E8, callee base 0x004D5B4C, format 0x00038150,
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


__forceinline const char *GetStr004D5F1D(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

class NetAckStage2CommandMsg : public NetCommandMsg
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

AsciiString NetAckStage2CommandMsg::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, commandID=%d, originalPlayer=%d, origExeSID=%d, originalExecFrame=%d", GetStr004D5F1D(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), m_commandID, m_originalPlayerID, m_20, m_24);
	return result;
}

void NetAckStage2CommandMsg::setCommandID(UnsignedShort commandID)
{
	m_commandID = commandID;
}

void NetAckStage2CommandMsg::setOriginalPlayerID(UnsignedByte originalPlayerID)
{
	m_originalPlayerID = originalPlayerID;
}
