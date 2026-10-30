// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2 /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0TerrainLogic@@QAE@XZ, retail 0x00283FAA..0x0028417C (466 bytes, EH,
// ret 0): TerrainLogic's constructor. Identity: it installs the vtable
// 0x00BFB2C8 whose slot-2 name getter returns "TerrainLogic" (the rowed
// ??_GTerrainLogic at 0x00285177 is its slot 0), and its only caller is the
// W3DTerrainLogic constructor 0x00062A7E. Bases (tables and unwind targets
// from retail, EH funclets 0x00773C57..0x00773CDE): Snapshot (0x00BBB554,
// unwind 0x0055F72C), SubsystemInterface at +4 (rowed ctor/dtor), and two
// listener interfaces at +0x10/+0x14 sharing the root table 0x00BC6F34
// (unwind 0x004EE006). Members, in the order retail builds them: three
// cleared words +0x24..+0x2C, a vector at +0x30, 1 at +0x48, an AsciiString
// at +0x4C, four owning holders +0x50..+0x5C each given a new 0x20-byte
// Rva002834C4 (rowed ctor; holder dtor 0x002833E7), the beacon-path list at
// +0x64, the waypoint-ID cache at +0x56C, a vector at +0x578. The body clears the
// remaining words, zeroes the 64 records at +0x68, fills the 1250-word table
// at +0x588 with -1, registers the two listener bases with the +0x54 and +0x58
// objects (rowed append 0x005A0B4C) and creates the +0x584 Rva00283081
// (rowed ctor) with 100.0f and the identity callback 0x000D1D26 (defined and
// rowed here). Member meanings beyond these offsets are not established.
// ABI reconciliation with the now-exact destructor: canonical Snapshot name
// slot and SubsystemInterface; real loadMap/reset/init/update declarations;
// four-slot listener roots with nonvirtual destructors. Callback ownership is
// established by the native tables BC5848/BC5838. Distinct root types are
// structural views of the folded interfaces; native member offsets, all ctor
// bytes and the full constructor EH graph are preserved.
// Match the game deallocator and its EH contract, as in buildBeacons.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *) throw(...); }
#define free _STL::free
#include <map>
#include <list>
#include <vector>
#undef free
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// As in the verified buildBeacons unit, keep deallocation inlined. The
// integer vector uses the same null-checked game free. This avoids
// competing out-of-line allocator copies without changing caller bytes.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int *p, size_t) const
{ if (p != 0) _STL::free((void *)p); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<int *, int, allocator<int> >::deallocate(int *p, size_t n)
{ allocator<int>::deallocate(p, n); }
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<Coord3D> >::deallocate(_List_node<Coord3D> *p, size_t) const
{ if (p != 0) _STL::free((void *)p); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<Coord3D> *, _List_node<Coord3D>, allocator<_List_node<Coord3D> > >::deallocate(_List_node<Coord3D> *p, size_t n)
{ allocator<_List_node<Coord3D> >::deallocate(p, n); }
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

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);			// 0x005A0B4C
};

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
int __cdecl Rva000D1D26Identity(int value)
{
	return value;
}

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



TerrainLogic::TerrainLogic()
	: m_24(0), m_28(0), m_2C(0), m_48(1),
	  m_50(new Rva002834C4), m_54(new Rva002834C4), m_58(new Rva002834C4), m_5C(new Rva002834C4)
{
	m_1914 = false;
	m_3C = 0;
	m_60 = false;
	for (Int i = 0; i < 64; ++i)
	{
		m_records[i].m_00 = 0;
		m_records[i].m_04[0] = 0.0f;
		m_records[i].m_04[1] = 0.0f;
		m_records[i].m_04[2] = 0.0f;
		m_records[i].m_04[3] = 0.0f;
	}
	m_568 = 0;
	m_40 = 0;
	m_18 = 0;
	m_44 = false;
	m_1C = 0;
	m_20 = 0;
	for (Int j = 0; j < 1250; ++j)
		m_588[j] = -1;
	m_1910 = 0;
	m_1918 = 0.0f;
	((Rva005A0B4CList *)m_54.m_ptr)->append((Rva002BA8F1Listener *)static_cast<TerrainLogicListenerA *>(this));
	((Rva005A0B4CList *)m_58.m_ptr)->append((Rva002BA8F1Listener *)static_cast<TerrainLogicListenerB *>(this));
	m_584 = new Rva00283081(100.0f, (int)&Rva000D1D26Identity);
}

// ??0Rva00062A7EProduct@@QAE@XZ, retail 0x00062A7E..0x00062AC4 (70 bytes):
// W3DTerrainLogic's constructor (pinned under its address name; the factory
// slot 14 of vtable 0x00BC25E0 calls it after new 0x1924, and its destructor
// is the rowed W3DTerrainLogic). Zero Hour's body exactly: m_mapMinZ(0),
// m_mapMaxZ(1), m_mapData = NULL, over this unit's TerrainLogic layout (the
// ported Zero Hour unit's header places the members elsewhere). Its own
// tables 0x00BC5890/+4 0x00BC5858; the two listener tables fold with
// TerrainLogic's.
// Retain the actual derived overrides after reconciling the base API.
// Native BC5890 primary slots1..4 are62E4A /62AF1 /62E2F /63153.
// Native BC5858 secondary slots1/9/10 are62B17 /62B44 /62B97;
// they must not silently inherit the base TerrainLogic implementations.
// This address-derived constructor view still needs its existing W3D method
// names reconciled with their providers before it links.
class W3DTerrainLogic : public TerrainLogic
{
public:
	W3DTerrainLogic();
	virtual ~W3DTerrainLogic();
	virtual bool loadMap(const AsciiString &, ChunkInputStream *, bool, bool);
	virtual void init();
	virtual void reset();
	virtual void update();

protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	Real m_mapMinZ;										// +0x191C
	Real m_mapMaxZ;										// +0x1920
};


// Native getWaypointByID28333F and xfer identify the +56C waypoint-ID cache.
// Its ctor chain is 33C432 -> 1F068F -> 1F0534; retain the typed providers
// here with the constructor member and its native teardown chain.
class Waypoint;
typedef _STL::pair<const unsigned int, Waypoint *> TerrainWaypointPair;
typedef _STL::_Rb_tree_base<TerrainWaypointPair, _STL::allocator<TerrainWaypointPair> > TerrainWaypointTreeBase;
template TerrainWaypointTreeBase::_Rb_tree_base(const _STL::allocator<TerrainWaypointPair> &);

typedef _STL::_Rb_tree<unsigned int, TerrainWaypointPair, _STL::_Select1st<TerrainWaypointPair>, _STL::less<unsigned int>, _STL::allocator<TerrainWaypointPair> > TerrainWaypointTree;
template TerrainWaypointTree::_Rb_tree(const _STL::less<unsigned int> &, const _STL::allocator<TerrainWaypointPair> &);
