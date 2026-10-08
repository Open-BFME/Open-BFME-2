// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// ??1GameState@@UAE@XZ @0x002DE58D 180B: GameState destructor (was ??1Rva002DE58D). Identity: vtable
// 0x00C0402C#0 (scalar deleting dtor at 0x002DF2DA calls it), member offsets shared
// with Rva002DEE9AOwner (E0C/E10/E14/E18 in Rva002DEE9AClear.cpp), save-info member
// 0xDE8 bytes at +0x24 (BfmeSubobject0022CE19 row at 0x002DD1E9), Snapshot base at +0xC
// (restores vtable 0x00BBB554), GameEngineDeletingBase dtor row at 0x001B4E74.
// Callers: 0x002DF03C, ??_G at 0x002DF2DA, unwind at 0x007783D4.

struct CameraMarker;

namespace _STL
{
template <class _Tp>
class allocator
{
};

template <class _Tp, class _Alloc>
class _List_base
{
public:
	void clear();
	~_List_base();
private:
	void *_M_head;
};
}

class BfmeSubobject0022CE19
{
public:
	virtual ~BfmeSubobject0022CE19();
private:
	char m_pad[0xDE8 - 4];
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad[0xC - 4];
};

extern const void *const g_00BBB554[];

// Secondary base at +0xC: the deleting-dtor thunk at 0x002DE585 proves it.
// Inline dtor restores the Snapshot vtable (0x00BBB554), as retail does.
class Rva002DE58DBaseC
{
public:
	virtual ~Rva002DE58DBaseC() { *(const void **)this = g_00BBB554; }
	virtual void crc() = 0;
	virtual void xfer() = 0;
	virtual void loadPostProcess() = 0;
};

class Rva002DEE9AOwner
{
public:
	void rva002DE311();
};

class GameState : public GameEngineDeletingBase, public Rva002DE58DBaseC
{
public:
	virtual ~GameState();
private:
	_STL::_List_base<CameraMarker, _STL::allocator<CameraMarker> > m_cameraLists[5];
	BfmeSubobject0022CE19 m_saveInfo;
	_STL::_List_base<int, _STL::allocator<int> > m_intListA;
	_STL::_List_base<int, _STL::allocator<int> > m_intListB;
};

// ??1GameState@@UAE@XZ
GameState::~GameState()
{
	_STL::_List_base<CameraMarker, _STL::allocator<CameraMarker> > *cameraLists = m_cameraLists;
	for (int i = 0; i < 5; ++i)
		cameraLists[i].clear();

	m_intListA.clear();
	m_intListB.clear();
	// Same GameState object: Rva002DEE9AOwner shares the E0C/E10/E14/E18 layout
	// (Rva002DEE9AClear.cpp); call its pinned clearer by its row name.
	((Rva002DEE9AOwner *)this)->rva002DE311();
}
