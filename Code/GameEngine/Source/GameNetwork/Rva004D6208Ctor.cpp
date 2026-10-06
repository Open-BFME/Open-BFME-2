// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ??0Rva004D6208@@QAE@XZ retail 0x004D61BB 77B.
// Ctor: base NetCommandMsg plus vptr 0x860484 plus Ascii +0x1c plus array ptr +0x20 plus int +0x24 plus type 0x13 plus clear via 0x36410 pin.
// Evidence: vtable 0x860484 plus dtor 0x004D6208 plus callers 0x004D19A1 0x00592324 plus Image clear-after-null precedent.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};
class NetCommandMsg
{
public:
	NetCommandMsg();
protected:
	inline virtual ~NetCommandMsg() {}
protected:
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};
#include "ascii_string.h"
class Rva004D6208 : public NetCommandMsg
{
public:
	Rva004D6208();
private:
	AsciiString m_str1c;
	unsigned char *m_data20;
	int m_24;
};
Rva004D6208::Rva004D6208() : NetCommandMsg(), m_str1c(), m_data20(0)
{
	m_commandType = (NetCommandType)0x13;
	m_str1c.clear();
	m_24 = 0;
}
