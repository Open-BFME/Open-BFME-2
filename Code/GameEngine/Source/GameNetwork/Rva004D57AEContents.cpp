// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D6040@Rva004D57AE@@QAE?AVAsciiString@@XZ, retail 0x004D6040, 138 bytes.
// Rva004D57AE (type 11, dword +0x1c) contents: base
// NetCommandMsg::rva004D5B4C plus ", destroyPlayer=%d" with the +0x1c dword.
// Identity from vtable slot 3 of 0x00860234, format "%s, destroyPlayer=%d" at
// 0x0086044C, callee base 0x004D5B4C, format 0x00038150, and empty fallback
// g_Rva0107301CEmptyString.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D6040(const AsciiString &s)
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

class Rva004D57AE : public NetCommandMsg
{
public:
	AsciiString rva004D6040();
private:
	unsigned int m_1c;
};

AsciiString Rva004D57AE::rva004D6040()
{
	AsciiString result;
	result.format("%s, destroyPlayer=%d", GetStr004D6040(((NetCommandMsg *)this)->rva004D5B4C()), m_1c);
	return result;
}
