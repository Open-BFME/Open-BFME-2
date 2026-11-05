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

#include "../../Include/GameLogic/TAiData.h"

TAiData::~TAiData()
{
	NodeF4 *curF4 = reinterpret_cast<NodeF4 *>(m_sideInfo);
	m_sideInfo = 0;
	while (curF4 != 0) {
		NodeF4 *del = curF4;
		curF4 = curF4->m_next;
		void *block = del->deldtor(0);
		::operator delete(block);
	}
	NodeFC *curFC = reinterpret_cast<NodeFC *>(m_namedLists);
	m_namedLists = 0;
	while (curFC != 0) {
		NodeFC *del = curFC;
		curFC = curFC->m_next;
		void *block = del->deldtor(0);
		::operator delete(block);
	}
	NodeF8 *curF8 = reinterpret_cast<NodeF8 *>(m_sideBuildLists);
	m_sideBuildLists = 0;
	while (curF8 != 0) {
		NodeF8 *del = curF8;
		curF8 = curF8->m_next;
		void *block = del->deldtor(0);
		::operator delete(block);
	}
}
