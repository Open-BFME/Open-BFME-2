// cl: /O1 /GX /MD /DNDEBUG
//
// ??0FloodUpdateModuleData@@QAE@XZ, retail 0x0048DF7A, 55 bytes. Framed
// single-state EH ctor: folded vtable 0x00C4C8C0 plus one std::list
// member at +8 through the rowed _List_base (0x4EC36C, FloodMember
// spelling alias pin). Unknown dword at +4 kept as explicit pad. Own
// table 0x00C4C9A8 holds the Flood fields; the FloodUpdate pool key at
// 0x48E0FA ends near the rowed proc; the factory at 0x24D17A news 0x14
// and calls this ctor as sole caller. Recipe: ClearanceTesting (init
// setup hoisting) over Topple (empty base with declared-only dtor arms
// the single EH state with zero code). Shape laws used: (1) the member
// models the _List_base subobject directly with a declared-only ctor so
// the implicit init emits the out-of-line base call (a full list member
// would route through an extra list() layer); FloodMember stays an
// incomplete struct since the base holds only node pointers. (2) the
// explicit allocator temporary in the init-list needs a user-defined
// empty allocator ctor, else MSVC value-initializes the one-byte stack
// slot with a stosb retail never emits. Row supersedes the pinned ctor.

struct FloodMember;

namespace _STL {

template<class _Tp>
class allocator
{
public:
	allocator() {}
};

template<class _Tp, class _Alloc>
class _List_base
{
public:
	_List_base(const _Alloc &a);
	~_List_base();

private:
	unsigned char m_data[0xC];
};

}

class FloodUpdateModuleDataBase
{
public:
	~FloodUpdateModuleDataBase();
};

class FloodUpdateModuleData : public FloodUpdateModuleDataBase
{
public:
	FloodUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned char m_unk04[4]; // +4
	_STL::_List_base<struct FloodMember, _STL::allocator<struct FloodMember> > m_list; // +8
};

// ??0FloodUpdateModuleData@@QAE@XZ @0x48DF7A
FloodUpdateModuleData::FloodUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4C8C0))
	, m_list(_STL::allocator<struct FloodMember>())
{
}
