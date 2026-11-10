// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2 /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native TerrainLogic::~TerrainLogic 28418A..284290: complete 262B.
// Identity: ctor283FAA installs BFB2C8; its deleting slot285177 calls this
// destructor. Canonical Snapshot and SubsystemInterface, listener subobjects
// +10/+14, and typed owned members follow the ctor and its exact EH graph.
// reset is called through the secondary subsystem entry (+4). The owned +584
// object is polymorphic, but this path explicitly invokes its nondeleting
// destructor283081 before global delete. Member/base destructors supply the
// remaining native teardown and all exception cleanups.
// Native root tables BC6F34 have four slots, no virtual destructor. Distinct
// structural root types preserve the two immediate table stores; their tables
// fold in retail. Listener names and opaque field names are our views, not
// recovered application names. Tables BC5848/BC5838 bind callbacks1/3 to
// 283C0F/2833A3 and 283C40/2833C5; slot2 remains pure. Full parent EH is exact.
// Wrappers285177/284182 now arise from the real destructor; the previous
// synthetic tag constructor is unnecessary.
// Match the game deallocator and its EH contract, as in buildBeacons.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *) throw(...); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseTerrainStorage(void *storage)
{
	_STL::free(storage);
}
#include <map>
#include <list>
#include <vector>
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// As in the verified buildBeacons unit, keep deallocation inlined. The
// integer vector uses the same null-checked game free. This avoids
// competing out-of-line allocator copies without changing caller bytes.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int *p, size_t) const
{ if (p != 0) releaseTerrainStorage((void *)p); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<int *, int, allocator<int> >::deallocate(int *p, size_t n)
{ allocator<int>::deallocate(p, n); }
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<Coord3D> >::deallocate(_List_node<Coord3D> *p, size_t) const
{ if (p != 0) releaseTerrainStorage((void *)p); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<Coord3D> *, _List_node<Coord3D>, allocator<_List_node<Coord3D> > >::deallocate(_List_node<Coord3D> *p, size_t n)
{ allocator<_List_node<Coord3D> >::deallocate(p, n); }
}
class Waypoint;
namespace _STL {
template <> inline
void allocator<_Rb_tree_node<pair<const unsigned int, Waypoint *> > >::deallocate(_Rb_tree_node<pair<const unsigned int, Waypoint *> > *p, size_t) const
{ if (p != 0) releaseTerrainStorage((void *)p); }
template <> inline
void allocator<_List_node<list<Coord3D> > >::deallocate(_List_node<list<Coord3D> > *p, size_t) const
{ if (p != 0) releaseTerrainStorage((void *)p); }
}


typedef int Int;
typedef float Real;

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

typedef bool Bool;
#include "subsystem_interface.h"

// Root tables BC6F34: empty RET4 followed by three pure callbacks.
class WaterHandle;
class TerrainLogicListenerRootA {
public:
 virtual void vslot0(int);
 virtual void vslot1(int, WaterHandle *) = 0;
 virtual void vslot2(void *, void *) = 0;
 virtual void vslot3(void *, void *) = 0;
 ~TerrainLogicListenerRootA() {}
};
class TerrainLogicListenerA : public TerrainLogicListenerRootA {
public:
 virtual void vslot1(int, WaterHandle *);
 virtual void vslot3(void *, void *);
 ~TerrainLogicListenerA();
};
class TerrainLogicListenerRootB {
public:
 virtual void vslot0(int);
 virtual void vslot1(int, WaterHandle *) = 0;
 virtual void vslot2(void *, void *) = 0;
 virtual void vslot3(void *, void *) = 0;
 ~TerrainLogicListenerRootB() {}
};
class TerrainLogicListenerB : public TerrainLogicListenerRootB {
public:
 virtual void vslot1(int, WaterHandle *);
 virtual void vslot3(void *, void *);
 ~TerrainLogicListenerB();
};

// Native getWaypointByID28333F stores Waypoint pointers keyed by unsigned ID
// at +56C; xfer clears that same cache through280AB6.
class Waypoint;

// Native buildBeacons283E9C accesses +64 as a list of coordinate lists.
// Node copy282843 and clear283002 confirm nested value ownership.
typedef _STL::list<Coord3D> TerrainBeaconPath;
struct Rva002BA8F1Listener;

#include "../../../Include/Common/Rva005A0B4CList.h"

class Rva002834C4
{
public:
	Rva002834C4() throw();								// 0x002834C4
private:
	unsigned char m_bytes[0x20];
};

class Rva002833E7Holder
{
public:
	Rva002833E7Holder(Rva002834C4 *ptr) : m_ptr(ptr) {}
	~Rva002833E7Holder();								// 0x002833E7
	Rva002834C4 *m_ptr;
};

class Rva00283081
{
public:
	Rva00283081(float f, int i) throw();
	virtual ~Rva00283081(); // 0x00283081; ctor 0x004DFC59
private:
	unsigned char m_bytes[0x20];
};

// The callback the +0x584 object receives: returns its argument.
int __cdecl Rva000D1D26Identity(int value);

struct TerrainLogicRecord
{
	Int m_00;
	Real m_04[4];
};

class TerrainLogic : public Snapshot, public SubsystemInterface,
	public TerrainLogicListenerA, public TerrainLogicListenerB
{
public:
	TerrainLogic();
	virtual ~TerrainLogic();
	virtual void reset();
	virtual bool loadMap(const AsciiString &, class ChunkInputStream *, bool, bool);
	virtual void init();
	virtual void update();

protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

protected:
	Int m_18;											// +0x18 (Zero Hour's m_mapData)

private:
	Int m_1C;											// +0x1C
	Int m_20;											// +0x20
	Int m_24;											// +0x24
	Int m_28;											// +0x28
	Int m_2C;											// +0x2C
	_STL::vector<Int> m_30;								// +0x30
	Int m_3C;											// +0x3C
	Int m_40;											// +0x40
	bool m_44;											// +0x44
	Int m_48;											// +0x48
	AsciiString m_4C;									// +0x4C
	Rva002833E7Holder m_50;								// +0x50
	Rva002833E7Holder m_54;								// +0x54
	Rva002833E7Holder m_58;								// +0x58
	Rva002833E7Holder m_5C;								// +0x5C
	bool m_60;											// +0x60
	_STL::list<TerrainBeaconPath> m_64;				// +0x64
	TerrainLogicRecord m_records[64];					// +0x68
	Int m_568;											// +0x568
	_STL::map<unsigned int, Waypoint *> m_56C;				// +0x56C
	_STL::vector<Int> m_578;							// +0x578
	Rva00283081 *m_584;									// +0x584
	Int m_588[1250];									// +0x588
	Int m_1910;											// +0x1910
	bool m_1914;										// +0x1914
	Real m_1918;										// +0x1918
};



TerrainLogicListenerA::~TerrainLogicListenerA() {}
TerrainLogicListenerB::~TerrainLogicListenerB() {}
void TerrainLogicListenerRootA::vslot0(int) {}
void TerrainLogicListenerRootB::vslot0(int) {}
void TerrainLogic::init() {}
TerrainLogic::~TerrainLogic()
{
	TerrainLogic::reset();
	Rva00283081 *owned = m_584;
	if (owned)
	{
		owned->Rva00283081::~Rva00283081();
		::operator delete(owned);
		m_584 = 0;
	}
}
