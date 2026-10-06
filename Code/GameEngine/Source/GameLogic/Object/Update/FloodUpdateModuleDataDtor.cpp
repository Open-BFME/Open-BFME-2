// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /Ireference/shims/moduledata
// stlport
//
// ??1FloodUpdateModuleData@@UAE@XZ, retail 0x0048DFB1, 113 bytes. Virtual dtor for
// the rowed ctor 0x0048DF7A (vtable 0x00C4C8C0, slot0 deleting dtor 0x0048E13F
// calls this). Shape follows FireWeaponUpdateModuleDataDtor 0x0048BC46:
// vptr store plus list drain loop (per value: AsciiString teardown via folded
// 0x36410 plus operator delete 0x2FD60) plus clear 0x23DAA5 plus implicit
// list-base dtor 0x4EC395 plus Snapshot base restore to 0xBBB554. List at
// +8 with unk dword at +4 per the ctor TU (news 0x14 via factory 0x24D17A).
// The heap entries' first member is the AsciiString, so its teardown folds to
// the StringBase spelling at the same address.

#include <list>
#include "Common/Snapshot.h"

#include "ascii_string.h"

class FloodUpdateModuleData : public Snapshot
{
public:
	virtual ~FloodUpdateModuleData();

private:
	int m_unk04; // +4
	_STL::list<int> m_list; // +8
};

FloodUpdateModuleData::~FloodUpdateModuleData()
{
	_STL::list<int> *trackedList = &m_list;
	_STL::list<int>::iterator it = trackedList->begin();
	while (it != trackedList->end()) {
		int trackedValue = *it;
		if (trackedValue != 0) {
			((AsciiString *)trackedValue)->~AsciiString();
			::operator delete((void *)trackedValue);
		}
		++it;
	}
	trackedList->clear();
}
