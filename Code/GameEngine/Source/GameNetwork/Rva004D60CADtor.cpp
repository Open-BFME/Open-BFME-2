// cl: /DNDEBUG /MD /EHsc /DBFME_STRINGBASE_PUBLIC_DTOR
// ??1Rva004D60CA@@MAE@XZ retail 0x004D60E3 54B.
// Dtor lane: vptr 0x860464 then Wide releaseBuffer at +0x1c then vptr 0x860130.
// Evidence: ctor 0x004D60CA plus setter 0x004D6187 plus vtable 0x860464.

#include "../../../../reference/shims/bfme2_ascii/string_base.h"

#include "../../Include/Common/ScalarTypes.h"

class AsciiString;

// Retail base vtable 0x860130: deleting dtor, getSortNumber, a bool slot,
// getContentsAsAsciiString; matches NetCommandMsgCtor.cpp's view.
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
private:
	char m_pad04[0x1c - 0x04];
};

class Rva004D60CA : public NetCommandMsg
{
protected:
	virtual ~Rva004D60CA();
private:
	StringBase<unsigned short> m_str1c;
};

Rva004D60CA::~Rva004D60CA()
{
}
