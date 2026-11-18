// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??0Rva004D62A9@@QAE@XZ retail 0x004D62A9 78B.
// Ctor: base NetCommandMsg plus vptr 0x860494 plus Ascii +0x1c plus word +0x20 plus byte +0x22 plus type 0x15 plus clear via 0x36410 pin.
// Evidence: vtable 0x860494 plus callers 0x004D2DE6 0x005923EE plus Rva004D6208 ctor precedent.
#include "../../Include/Common/ScalarTypes.h"



class AsciiString;
enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};
#include "../../Include/GameNetwork/NetCommandMsg.h"
inline NetCommandMsg::~NetCommandMsg() {}
#include "ascii_string.h"
class Rva004D62A9 : public NetCommandMsg
{
public:
	Rva004D62A9();
	virtual ~Rva004D62A9();
private:
	AsciiString m_str1c;
	UnsignedShort m_20;
	bool m_22;
};
Rva004D62A9::Rva004D62A9() : NetCommandMsg(), m_str1c()
{
	m_commandType = (NetCommandType)0x15;
	m_str1c.clear();
	m_20 = 0;
	m_22 = false;
}

// ??1Rva004D62A9@@UAE@XZ @0x004D62F7 54B
// Evidence: vptr 0x860494 then releaseBuffer at +0x1c then vptr 0x860130; caller 0x004D6AD8 for ??_G.
Rva004D62A9::~Rva004D62A9() {}
