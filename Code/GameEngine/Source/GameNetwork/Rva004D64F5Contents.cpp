// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D650E@Rva004D64F5@@QAE?AVAsciiString@@XZ, retail 0x004D650E, 152 bytes.
// Rva004D64F5 (type 5, AsciiString +0x1c) contents: base
// NetCommandMsg::rva004D5B4C plus ", challenge=%s" with the +0x1c string.
// Identity from vtable slot 3 of 0x0086050C, format "%s, challenge=%s" at
// 0x0086051C, callee base 0x004D5B4C, format 0x00038150, and empty fallback
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


__forceinline const char *GetStr004D650E(const AsciiString &s)
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

class Rva004D64F5 : public NetCommandMsg
{
public:
	AsciiString rva004D650E();
private:
	AsciiString m_1c;
};

AsciiString Rva004D64F5::rva004D650E()
{
	AsciiString result;
	result.format("%s, challenge=%s", GetStr004D650E(((NetCommandMsg *)this)->rva004D5B4C()), GetStr004D650E(m_1c));
	return result;
}
