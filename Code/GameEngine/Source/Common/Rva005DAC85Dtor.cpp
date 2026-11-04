// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva005DAC85@@UAE@XZ @0x005DAC85 59B evidence: vtable VA 0x008765F8 at +0; StringBase char releaseBuffer at +0x3C via 0x00036410; base Rva0055B0CC dtor pin at 0x0055B0CC; unblocks deleting dtor 0x005DADD1

#include "ascii_string.h"

class Xfer;

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void Slot6(void *arg1, bool arg2);
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void Rva0055AED6(Xfer *xfer, void *arg2);
protected:
	char m_pad04[0x2C - 0x04];
};

// The +0x3C string is destroyed by its own inline ~AsciiString (the
// releaseBuffer worker 0x00036410) before the base dtor runs.
class Rva005DAC85 : public Rva0055B0CC
{
public:
	void updatePriority();
	virtual ~Rva005DAC85();
	char m_pad2C[0x10];
private:
	AsciiString m_3C; // +0x3C
	void *m_40; // +0x40
};

Rva005DAC85::~Rva005DAC85()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot4@Rva0055B0CC@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot7@Rva0055B0CC@@UAEXXZ=?friend_setNext@Upgrade@@QAEXPAV1@@Z")
#pragma comment(linker, "/alternatename:?slot11@Rva0055B0CC@@UAEXXZ=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?Slot6@Rva0055B0CC@@UAEXPAX_N@Z=?registerWithBuilder@AIBuildable@@UAEXPAX_N@Z")
#pragma comment(linker, "/alternatename:?slot10@Rva0055B0CC@@UAEXXZ=?rva005DAF59@AIBuildableUnit@@QAEMPAVPlayer@@@Z")
#pragma comment(linker, "/alternatename:?slot1@Rva0055B0CC@@UAEXXZ=?rva0055AFA3@Rva0055B0CC@@QAEXXZ")
#pragma comment(linker, "/alternatename:?slot2@Rva0055B0CC@@UAEXXZ=?rva0055B0B9@Rva0055B0B9@@QBEMXZ")
#pragma comment(linker, "/alternatename:?slot3@Rva0055B0CC@@UAEXXZ=?addNeed@AIBuildableUnit@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?slot5@Rva0055B0CC@@UAEXXZ=?updatePriority@Rva005DAC85@@QAEXXZ")
#pragma comment(linker, "/alternatename:?slot8@Rva0055B0CC@@UAEXXZ=?rva003A36D3@Rva003A36D3@@UAEMH@Z")
#pragma comment(linker, "/alternatename:?slot9@Rva0055B0CC@@UAEXXZ=?rva005DAEDF@AIBuildableUnit@@QAEMPAVPlayer@@@Z")
