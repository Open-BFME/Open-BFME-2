// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD /Ireference/shims/moduledata
//
// ??1BuildingBehaviorModuleData@@UAE@XZ, retail 0x004564E6, 58 bytes.
// ModuleData dtor: four-element window-name array at +0x08 torn down via
// ehvec ??_M (size 0xC count 4 array +8 element dtor DIR32-masked to retail
// 0x42CC70) then Snapshot base vtable 0x00BBB554 restored with no base call.
// Layout from rowed ctor 0x00456489 (vtable 0xC40798 table 0xC40748 factory
// 0x24ABAF news 0x38 gap +4 array +8). Shape follows BoneFX/LargeGroupBonus
// ModuleData dtors (TU-local Snapshot with inline BBB554 restore plus
// novtable derived suppressing the entry store retail lacks).

#include "ascii_string.h"

// Retail's 12-byte entries are vector<AsciiString>: the constructor at
// 0x00456489 uses the vector default-constructor closure (0x00256646),
// and this destructor passes the rowed vector destructor (0x0002CC70)
// to the EH vector destructor iterator. Match the constructor TU's view.
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A> class vector
{
public:
	vector(const A &a = A());
	~vector();

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}
typedef _STL::vector<AsciiString, _STL::allocator<AsciiString> > BuildingWindowName;

class Xfer;

#include "Common/Snapshot.h"

class __declspec(novtable) BuildingBehaviorModuleData : public Snapshot
{
public:
	virtual ~BuildingBehaviorModuleData();

private:
	int m_unused04;
	BuildingWindowName m_windows[4];
};

// ??1BuildingBehaviorModuleData@@UAE@XZ @0x004564E6
BuildingBehaviorModuleData::~BuildingBehaviorModuleData()
{
}
