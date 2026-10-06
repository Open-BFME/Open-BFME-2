// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /Oy- /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1CreateCrateDieModuleData@@UAE@XZ, retail 0x00257355, 72 bytes.
// Target evidence: the audited scalar deleting dtor 0x00257339 calls this
// body (registration CreateCrateDie -> factory 0x0025739D -> ctor
// 0x002572EE). It installs the derived vtable 0x00BF40A8, clears the
// crate-name list at +0x38 in the body (0x00239D49, state 1), destroys it
// (_List_base dtor 0x002FECBC, state 0), then the inlined trivial bases end with the Snapshot vtable
// 0x00BBB554 store. Layout and list type from the matched ctor TU; flags
// copied from it.
#include <list>

#include "Common/Snapshot.h"

#include "ascii_string.h"

// The Die-family intermediate adds no destructible members; its dtor is
// trivial here and stores no vptr of its own in retail.
class __declspec(novtable) DestroyDieModuleData : public Snapshot
{
public:
	virtual ~DestroyDieModuleData() {}

private:
	unsigned char m_pad[0x38 - 4];
};

class CreateCrateDieModuleData : public DestroyDieModuleData
{
public:
	virtual ~CreateCrateDieModuleData();

private:
	_STL::list<AsciiString> m_crateNameList; // +0x38
};

CreateCrateDieModuleData::~CreateCrateDieModuleData()
{
	m_crateNameList.clear();
}
