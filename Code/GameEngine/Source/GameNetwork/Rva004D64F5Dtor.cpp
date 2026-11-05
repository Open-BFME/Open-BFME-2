// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva004D64F5@@UAE@XZ @0x004D65A6 54B
// Dtor: vptr 0x86050C then releaseBuffer at +0x1c then vptr 0x860130; caller 0x004D6AF4 for ??_G.
// Same recipe as Rva004D62A9 dtor at 0x004D62F7 (AsiiString at +0x1c, base NetCommandMsg, no base call).
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef bool Bool;
class AsciiString;
enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};
class NetCommandMsg
{
public:
	NetCommandMsg();
protected:
	virtual ~NetCommandMsg() {}
public:
	virtual Int getSortNumber();
	virtual Bool vslot08() { return false; }
	virtual AsciiString getContentsAsAsciiString();
protected:
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};
#include "ascii_string.h"
class Rva004D64F5 : public NetCommandMsg
{
public:
	virtual ~Rva004D64F5();
private:
	AsciiString m_str1c;
public:
	// retail vftable slot: the rowed override
	virtual AsciiString getContentsAsAsciiString();
};

inline Rva004D64F5::~Rva004D64F5() {}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva004D64F5DtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeRva004D64F5DtorInlineAnchor()
{
    static_cast<Rva004D64F5 *>(0)->Rva004D64F5::~Rva004D64F5();
}
#pragma inline_depth()
