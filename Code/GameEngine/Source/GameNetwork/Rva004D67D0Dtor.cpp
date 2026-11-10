// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva004D67D0@@MAE@XZ retail 0x004D67D0 54B.
// Dtor: vptr 0x00860560 then Wide releaseBuffer at +0x24 then vptr 0x00860130.
// Evidence: caller 0x004D67B4 deleting dtor plus layout Rva004D67D0 ints +0x1c/+0x20 UnicodeString +0x24 plus vtable pair.
// ??0Rva004D67D0@@QAE@XZ retail 0x004D674D 103B.
// Ctor: base ctor, vptr 0x00860560, both ints zeroed, the UnicodeString
// built from an empty AsciiString temp (EH states 1 and 3), then type 30 at
// +0x14. Callers: the NetPacket type-30 reader 0x00592208 and its writer.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
class AsciiString;

// Retail base vtable 0x860130: deleting dtor, getSortNumber, a bool slot,
// getContentsAsAsciiString; matches NetCommandMsgCtor.cpp's view.
class NetCommandMsg
{
public:
	NetCommandMsg();
protected:
	virtual ~NetCommandMsg();
public:
	virtual Int getSortNumber();
	virtual Bool vslot08() { return false; }
	virtual AsciiString getContentsAsAsciiString();
protected:
	char m_pad04[0x14 - 0x04];
	int m_commandType;
	int m_referenceCount;
};
inline NetCommandMsg::~NetCommandMsg() {}

class Rva004D67D0 : public NetCommandMsg
{
public:
	Rva004D67D0();
	virtual AsciiString getContentsAsAsciiString();
protected:
	virtual ~Rva004D67D0();
private:
	int m_action;
	int m_reason;
	UnicodeString m_filename;
};

Rva004D67D0::Rva004D67D0() : m_action(0), m_reason(0), m_filename(AsciiString(""))
{
	m_commandType = 30;
}

Rva004D67D0::~Rva004D67D0()
{
}
