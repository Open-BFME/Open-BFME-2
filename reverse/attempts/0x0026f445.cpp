// ??1UpgradeCenter@@UAE@XZ
// partial score=0.8 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1UpgradeCenter@@UAE@XZ, retail 0x0026F445..0x0026F4F4 (175 bytes, EH);
// pinned until now as the opaque ??1Rva0026F445@@UAE@XZ. Zero Hour's
// UpgradeCenter::~UpgradeCenter (Upgrade.cpp) deletes the chain of upgrade
// templates (vtable 0x00BFABB8, constructor 0x0026F419); retail also
// deletes and clears a pointer vector at +0x18 that Zero Hour does not
// have, frees its buffer and runs ~SubsystemInterface. The list link sits
// at +0x64 of an UpgradeTemplate.
#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free

enum ObjectID { INVALID_ID = 0 };

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[0x0C - 4];
};

class UpgradeTemplate
{
public:
	virtual ~UpgradeTemplate();
	UpgradeTemplate *friend_getNext() const { return m_next; }
private:
	char m_pad04[0x64 - 4];
	UpgradeTemplate *m_next; // +0x64
};

class Polymorph
{
public:
	virtual ~Polymorph();
};

class UpgradeCenter : public SubsystemInterface
{
public:
	virtual ~UpgradeCenter();
private:
	UpgradeTemplate *m_upgradeList; // +0x0C
	char m_pad10[0x18 - 0x10];
	_STL::vector<ObjectID> m_extra; // +0x18
};

UpgradeCenter::~UpgradeCenter()
{
	while (m_upgradeList)
	{
		UpgradeTemplate *next = m_upgradeList->friend_getNext();
		::delete m_upgradeList;
		m_upgradeList = next;
	}
	_STL::vector<void *> &vec = *(_STL::vector<void *> *)&m_extra;
	for (unsigned int i = 0; i < vec.size(); ++i)
		::delete (UpgradeTemplate *)(*(void ***)&vec)[i];
	vec.erase(vec.begin(), vec.end());
}
