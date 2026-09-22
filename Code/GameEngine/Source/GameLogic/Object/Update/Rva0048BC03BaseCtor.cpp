// cl: /O1 /GX /MD /DNDEBUG
//
// ??0Rva0048BC03Base@@QAE@XZ, retail 0x0048BC03, 67 bytes. Framed
// single-state EH ctor: folded vtable 0x00C4C110 plus one float-list
// member at +8 through the folded _List_base (0x4EC36C, float-spelling
// alias pin) plus three flag bytes at +0xC/+0xD/+0xE. Unknown dword at +4
// kept as explicit pad. Recipe follows FloodUpdateModuleDataCtor (landed):
// the member models the _List_base subobject directly with a declared-only
// ctor so the implicit init emits the out-of-line base call; the empty base
// with declared-only dtor arms the single EH state with zero code; the
// explicit allocator temporary needs a user-defined empty allocator ctor,
// else MSVC value-initializes the one-byte stack slot with a stosb retail
// never emits. Row supersedes the pin; the OilSpill TU keeps resolving
// through the row.

struct FloatMember;

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
	unsigned char m_data[4];
};

}

class Rva0048BC03BaseBase
{
public:
	~Rva0048BC03BaseBase();
};

class Rva0048BC03Base : public Rva0048BC03BaseBase
{
public:
	Rva0048BC03Base();

private:
	const void *m_vtable; // +0
	unsigned char m_unk04[4]; // +4
	_STL::_List_base<float, _STL::allocator<float> > m_list; // +8
	bool m_flag0c; // +0xC
	bool m_flag0d; // +0xD
	bool m_flag0e; // +0xE
};

// ??0Rva0048BC03Base@@QAE@XZ @0x0048BC03
Rva0048BC03Base::Rva0048BC03Base()
	: m_vtable(reinterpret_cast<const void *>(0x00C4C110))
	, m_list(_STL::allocator<float>())
{
	m_flag0c = false;
	m_flag0d = false;
	m_flag0e = false;
}
