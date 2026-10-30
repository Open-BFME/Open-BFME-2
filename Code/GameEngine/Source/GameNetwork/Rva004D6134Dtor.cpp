// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva004D6134@@MAE@XZ, retail 0x004D6151, 54 bytes. Protected virtual
// dtor for Rva004D6134 (vtable 0x860474, base NetCommandMsg vtable 0x860130):
// stores derived vptr, destroys wide-string member at +0x1C via the rowed
// releaseBuffer at 0x00036E70, reinstalls base vptr. Member at +0x1C is a
// 4-byte StringBase<ushort> nulled inline in the ctor 0x004D6134
// (NetCommandMsgCtor.cpp). The EH funclet calls the base dtor out of line,
// so this unit, like Rva004D60CADtor.cpp, stays apart from the ctor unit.
// ??_GRva004D6134@@MAEPAXI@Z, retail 0x004D6A9D, 28 bytes: slot 0 of
// 0x860474, calls the dtor above then global operator delete.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef bool Bool;

class AsciiString;

// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable, so the wide teardown stays a call to the rowed
// releaseBuffer at 0x00036E70.
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

// Retail vtable 0x860130: deleting dtor, getSortNumber, the bool slot and
// getContentsAsAsciiString (see NetCommandMsgCtor.cpp).
class NetCommandMsg
{
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
	int m_commandType;
	Int m_referenceCount;
};

class Rva004D6134 : public NetCommandMsg
{
protected:
	virtual ~Rva004D6134();
private:
	StringBase<unsigned short> m_1c;
	unsigned int m_20;
};

Rva004D6134::~Rva004D6134()
{
}
