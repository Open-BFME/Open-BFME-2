// cl: /O1 /GX /MD /DNDEBUG
// stlport
//
// ??1FireWeaponUpdateModuleData@@UAE@XZ, retail 0x0048BC46, 117 bytes. Virtual dtor for
// the rowed base ctor 0x0048BC03 (vtable 0x00C4C110, slot0 deleting dtor
// 0x0048C098 calls this). Shape follows FireWeaponUpdate dtor 0x0048BD11:
// vptr store plus watch-list drain loop (per value: AsciiString teardown via
// folded 0x36410 plus operator delete 0x2FD60 plus list<int>::remove 0x47BAF7)
// plus implicit list-base dtor 0x4EC395 plus inline Snapshot restore to
// 0xBBB554. List at +8 with unk dword at +4 and three flag bytes at
// +0xC/+0xD/+0xE per the ctor TU (news 0x10 via factory 0x24CF56). The 0x18
// nugget's first member is the AsciiString (WeaponName per table 0xC4C0C0),
// so its teardown folds to the StringBase spelling at the same address.

#include <list>

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class FireWeaponUpdateModuleData : public Snapshot
{
public:
	virtual ~FireWeaponUpdateModuleData();

private:
	int m_unk04; // +4
	_STL::list<int> m_list; // +8
	bool m_flag0c; // +0xC
	bool m_flag0d; // +0xD
	bool m_flag0e; // +0xE
};

FireWeaponUpdateModuleData::~FireWeaponUpdateModuleData()
{
	_STL::list<int> *trackedList = &m_list;
	_STL::list<int>::iterator it = trackedList->begin();
	while (it != trackedList->end()) {
		int trackedValue = *it;
		++it;
		if (trackedValue != 0) {
			((AsciiString *)trackedValue)->~AsciiString();
			::operator delete((void *)trackedValue);
		}
		trackedList->remove(trackedValue);
	}
}
