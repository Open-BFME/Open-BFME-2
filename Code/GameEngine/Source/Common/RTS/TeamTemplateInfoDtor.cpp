// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc
// TeamTemplateInfo dtor at 0x0039EAED. The target cleans seven 0x18-byte
// records, ten narrow strings and a 32-entry string array before restoring
// Snapshot's vtable. The loader and sibling xfer TUs independently establish
// the 0x1EC size and Snapshot base. The four-byte array element's descriptive
// address name comes from the direct helper call at 0x0048BA39; its remaining
// semantics are only the AsciiString cleanup proven by the target.
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

class __declspec(novtable) TeamTemplateInfo : public Snapshot
{
public:
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

// ?~TeamTemplateInfo@TeamTemplateInfo@@UAE@XZ present-unmatched
TeamTemplateInfo::~TeamTemplateInfo()
{
}
