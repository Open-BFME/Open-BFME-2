// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D6661@Rva004D65DC@@QAE?AVAsciiString@@XZ, retail 0x004D6661, 167 bytes.
// Rva004D65DC (type 6, AsciiStrings +0x1c/+0x20) contents slot 3 of 0x00860530:
// base NetCommandMsg::rva004D5B4C plus ", authToken=%s, authKey=%s".
// Identity from vtable slot 3, ctor 0x004D65DC layout, setter 0x004D662D (+0x20),
// dtor 0x004D6708, format "%s, authToken=%s, authKey=%s" at 0x00860540,
// callee base 0x004D5B4C, format 0x00038150, empty fallback g_Rva0107301CEmptyString.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D6661(const AsciiString &s)
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

class Rva004D65DC : public NetCommandMsg
{
public:
	AsciiString rva004D6661();
private:
	AsciiString m_authKey;
	AsciiString m_authToken;
};

AsciiString Rva004D65DC::rva004D6661()
{
	AsciiString result;
	result.format("%s, authToken=%s, authKey=%s", GetStr004D6661(((NetCommandMsg *)this)->rva004D5B4C()), GetStr004D6661(m_authToken), GetStr004D6661(m_authKey));
	return result;
}
