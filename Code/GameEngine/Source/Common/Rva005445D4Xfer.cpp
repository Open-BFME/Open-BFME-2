// cl: /MD
// ?xfer@Rva005445D4@@UAEXPAVXfer@@@Z, retail 0x00544AD2, 65 bytes.
// Slot 3 of vtable 0x00869A20, class of ??0Rva005445D4@@QAE@PAVStateMachine@@@Z.
// Version(1,2) via slot 0x28 then ObjectID at +0x24 via rowed XferObjectID
// 0x003060B2 then uint at +0x20 via slot 0x78 when version>=2. Evidence:
// vslot slot 3; rowed XferObjectID 0x003060B2; ctor layout m_20/m_24.
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	OBJECTID_0 = 0
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"

extern void __cdecl XferObjectID(Xfer *xfer, enum ObjectID *id);

#include "../../Include/Common/StateMachine.h"

class Rva005445D4 : public State
{
public:
	virtual void xfer(Xfer *xfer);
private:
	UnsignedInt m_20;
	enum ObjectID m_24;
};

void Rva005445D4::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	*xfer == reinterpret_cast<Xfer::Version &>(version);
	XferObjectID(xfer, &m_24);
	if (version.m_currentVersion >= 2)
		*xfer == m_20;
}
