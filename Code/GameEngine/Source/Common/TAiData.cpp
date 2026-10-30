// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /Ireference/shims/moduledata
// ??1TAiData@@UAE@XZ @0x002FDF72 201B: ModuleData-style dtor with vtable
// 0x008071E4 then Snapshot base restore 0x00BBB554; three intrusive lists at
// +0xF4 (next +0x1BC) +0xFC (next +0x10) +0xF8 (next +0xC) each destructed via
// virtual slot 0 with flags 0 then scalar delete 0x0002FD60; three AsciiStrings
// at +0xDC/+0xE0/+0xE4 via rowed releaseBuffer 0x00036410. Evidence: EH prolog
// 0xB7907D states 3-2-1-0, callers 0x002FE044, prev GameClient/next Namers,
// PillageModuleDataDtor precedent for Snapshot+novtable shape.
#include "ascii_string.h"

#include <new>

struct NodeF4
{
	virtual void *deldtor(unsigned int flags);
	char m_pad[0x1BC - 4];
	NodeF4 *m_next;
};

struct NodeFC
{
	virtual void *deldtor(unsigned int flags);
	char m_pad[0x10 - 4];
	NodeFC *m_next;
};

struct NodeF8
{
	virtual void *deldtor(unsigned int flags);
	char m_pad[0x0C - 4];
	NodeF8 *m_next;
};

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

class TAiData : public Snapshot
{
public:
	virtual ~TAiData();
	virtual const char *GetSnapshotName() const;
	virtual void loadPostProcess();
protected:
	virtual void xfer(Xfer *);
private:
	char m_pad04[0xD8];
	AsciiString m_DC;
	AsciiString m_E0;
	AsciiString m_E4;
	char m_padE8[0x0C];
	NodeF4 *m_F4;
	NodeF8 *m_F8;
	NodeFC *m_FC;
};

TAiData::~TAiData()
{
	NodeF4 *curF4 = m_F4;
	m_F4 = 0;
	while (curF4 != 0) {
		NodeF4 *del = curF4;
		curF4 = curF4->m_next;
		void *block = del->deldtor(0);
		::operator delete(block);
	}
	NodeFC *curFC = m_FC;
	m_FC = 0;
	while (curFC != 0) {
		NodeFC *del = curFC;
		curFC = curFC->m_next;
		void *block = del->deldtor(0);
		::operator delete(block);
	}
	NodeF8 *curF8 = m_F8;
	m_F8 = 0;
	while (curF8 != 0) {
		NodeF8 *del = curF8;
		curF8 = curF8->m_next;
		void *block = del->deldtor(0);
		::operator delete(block);
	}
}
