// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /DNDEBUG /MD
//
// ??_GTeamTemplateInfo@@UAEPAXI@Z, retail 0x003A287B (28 bytes): slot 0
// of vtable 0x00C1AE70, whose slot-2 name getter returns "TeamTemplateInfo" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x0039EAED and then the global operator delete when bit 0 of
// the flags is set. A class's compiler-generated deleting destructor calls
// that class's destructor, so the callee is TeamTemplateInfo::~TeamTemplateInfo (pinned in
// reverse/symbols.csv; its SEH body does not re-store the vtable).
// BFME 2 sibling TUs also define this as a Snapshot-derived class; this view
// gives the deleting wrapper the same class layout and virtual inheritance.
// BFME 2's form frees through the global operator delete.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;

#include "ascii_string.h"
#include "Common/Snapshot.h"

class Rva0039EA9C
{
public:
	~Rva0039EA9C();
private:
	int m_00, m_04, m_08;
	AsciiString m_0c, m_10;
	int m_14;
};

class Rva0048BA39StringElement
{
public:
	~Rva0048BA39StringElement();
private:
	AsciiString m_string;
};

class TeamTemplateInfo : public Snapshot
{
public:
	TeamTemplateInfo(EmitVtableTag *);
	virtual ~TeamTemplateInfo();
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	Rva0039EA9C m_units[7]; // +0x04
	char m_padac[0xC0 - 0xAC];
	AsciiString m_stringC0, m_stringC4, m_stringC8;
	char m_padcc[4];
	AsciiString m_stringD0, m_stringD4, m_stringD8, m_stringDC;
	char m_pade0[0x100 - 0xE0];
	AsciiString m_string100, m_string104;
	char m_pad108[8];
	AsciiString m_string110;
	char m_pad114[4];
	Rva0048BA39StringElement m_items118[32];
	char m_pad198[0x1EC - 0x198];
};

typedef char TeamTemplateInfoSizeCheck[(sizeof(TeamTemplateInfo) == 0x1EC) ? 1 : -1];

// ?<TeamTemplateInfo::TeamTemplateInfo> absent-from-retail
TeamTemplateInfo::TeamTemplateInfo(EmitVtableTag *)
{
}
