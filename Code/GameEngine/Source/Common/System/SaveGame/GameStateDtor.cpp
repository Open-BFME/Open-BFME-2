// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
// ??1GameState@@UAE@XZ @0x002DE58D 180B: GameState destructor (was ??1Rva002DE58D). Identity: vtable
// 0x00C0402C#0 (scalar deleting dtor at 0x002DF2DA calls it), member offsets shared
// with Rva002DEE9AOwner (E0C/E10/E14/E18 in Rva002DEE9AClear.cpp), save-info member
// 0xDE8 bytes at +0x24 (BfmeSubobject0022CE19 row at 0x002DD1E9), Snapshot base at +0xC
// (restores vtable 0x00BBB554), SubsystemInterface dtor row at 0x001B4E74.
// Callers: 0x002DF03C, ??_G at 0x002DF2DA, unwind at 0x007783D4.

// Native ctor2DE4E6 and registration2DE34B establish five four-byte
// SnapshotBlock lists. CameraMarker is only the existing certified folded
// ABI view here: both payloads are a non-owning pointer then AsciiString.
// The source does not identify the real entries as CameraMarker objects.
// List::~list at295983 is an admitted whole-byte/relocation twin of the
// SnapshotBlock list specialization already rowed by GameStateConstructor.
struct CameraMarker;

// Use the constructor-proven fourteen-slot subsystem view and four-slot
// Snapshot name interface. The +0xC Snapshot adjustment is unchanged.
typedef bool Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

namespace _STL
{
template <class _Tp, class _Alloc>
class _List_base
{
public:
	void clear();
	~_List_base();
private:
	void *_M_head;
};

// Four-byte list wrapper; its native destructor is the five-byte tail
// wrapper at295983. The list-base destructor is a separate23B body at2A1BEB.
template <class _Tp, class _Alloc>
class list : public _List_base<_Tp, _Alloc>
{
public:
	~list();
};
template <class _Tp> class allocator;
// list<int>'s destructor is retail's tail thunk 0x00200667 (the unwind
// funclets 0x00778390/0x0077839E jump to it); the normal path expands it
// into the base destructor call 0x004EC395.
template <>
class list<int, allocator<int> > : public _List_base<int, allocator<int> >
{
};
}

class BfmeSubobject0022CE19
{
public:
	virtual ~BfmeSubobject0022CE19();
private:
	char m_pad[0xDE8 - 4];
};

class Rva002DE311Owner
{
public:
	void rva002DE311();
};

class GameState : public SubsystemInterface, public Snapshot
{
public:
	virtual ~GameState();
	virtual void init();
	virtual void reset();
	virtual void update();
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
private:
	_STL::list<CameraMarker, _STL::allocator<CameraMarker> > m_cameraLists[5];
	BfmeSubobject0022CE19 m_saveInfo;
	_STL::list<int, _STL::allocator<int> > m_intListA;
	_STL::list<int, _STL::allocator<int> > m_intListB;
	unsigned m_wordE14; // Native constructor stores at +0xE14.
	bool m_flagE18; // Native constructor stores at +0xE18.
};

typedef char GameStateListExtent[sizeof(_STL::list<CameraMarker, _STL::allocator<CameraMarker> >)==4 ? 1 : -1];

typedef char GameStateExtent[sizeof(GameState) == 0xE1C ? 1 : -1];

// ??1GameState@@UAE@XZ
GameState::~GameState()
{
	_STL::list<CameraMarker, _STL::allocator<CameraMarker> > *cameraLists = m_cameraLists;
	for (int i = 0; i < 5; ++i)
		cameraLists[i].clear();

	m_intListA.clear();
	m_intListB.clear();
	// Same GameState object: Rva002DEE9AOwner shares the E0C/E10/E14/E18 layout
	// (Rva002DEE9AClear.cpp); call its pinned clearer by its row name.
	((Rva002DE311Owner *)this)->rva002DE311();
}
