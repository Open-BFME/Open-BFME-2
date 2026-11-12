// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// Native255474..25553A is the constructor called by the named 25553A factory.
// Its FuncInfo9185E4 has exactly four states: Snapshot (771CC8), filter+1C8
// (771CD0), and AsciiStrings+1D4/+1D8 (771CDE/771CEC). The masks and B8-byte
// nugget are trivial to destroy. Their sizes follow the rowed2542F3 member
// constructor, the factory's1DC allocation, and the target's own field accesses.
// The older bank's artificial mask destructors caused its early state-3 flush.
// Retail's constructor and destructor vtable agree on the same object; slot0
// at BF3640 names deleting destructor2560C7, which calls destructor2560E3.
// Original trailing string spellings and the remaining virtual API are unasserted.
#include <string.h>
#include "ascii_string.h"
#include "Common/Snapshot.h"

class BfmeFixedStorage0004543D {
public:
 BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
private:
 unsigned char data[28];
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

class Rva002542F3Member {
public: Rva002542F3Member();
private: unsigned char data[0xB8];
};
class Rva001EAE6FHelper {
public:
 // ?Rva001EAE6FHelper::Rva001EAE6FHelper present-unmatched
 Rva001EAE6FHelper() { clear80(); }
 Rva001EAE6FHelper *clear80();
private: unsigned char data[0x80];
};
class Rva00360D26Member {
public: Rva00360D26Member(); ~Rva00360D26Member();
private: unsigned int index;
};
#include "../../../../Include/GameLogic/Module/Rva003623E5Filter.h"
class InvisibilityUpdateModuleData : public Snapshot {
public:
 InvisibilityUpdateModuleData();
 __declspec(noinline) virtual ~InvisibilityUpdateModuleData();
private:
 unsigned int unused04;
 Rva002542F3Member nugget;
 unsigned int updatePeriod;
 Rva001EAE6FHelper requiredUpgrades;
 Rva001EAE6FHelper forbiddenUpgrades;
 bool broadcast;
 Rva00360D26Member filter;
 float broadcastRange;
 bool startsActive;
 AsciiString voice1D4;
 AsciiString voice1D8;
};
InvisibilityUpdateModuleData::InvisibilityUpdateModuleData()
 : updatePeriod(10), broadcast(false), broadcastRange(0.0f), startsActive(false)
{
 memset(&requiredUpgrades,0,0x80);
 memset(&forbiddenUpgrades,0,0x80);
 reinterpret_cast<Rva003623E5Filter *>(&filter)->applyFilter(
  *reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE));
}
