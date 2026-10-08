// cl: /DNDEBUG /MD /EHsc
// Holders whose constructor only runs the out-of-line constructor of the
// member at +0 and returns this. Callees are matched rows; holder names are
// opaque (address-named) since retail gives no caller-side identity.

class ObjectCreationList
{
public:
	ObjectCreationList();
	char m_pad[0x10];
};

namespace D3DXTex
{
class CLockVolume
{
public:
	CLockVolume();
	char m_pad[0x10];
};
}

class LadderPref;
enum NameKeyType {};
class ModuleFactory
{
public:
	class ModuleTemplate;
};

namespace _STL
{
template <class T> struct less;
template <class T> struct hash;
template <class T> struct equal_to;
template <class T> class allocator;
template <class A, class B> struct pair;
template <class K, class V, class C, class A> class map
{
public:
	map();
	char m_pad[0xc];
};
template <class P> struct _Select1st;
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
public:
	void clear();
	char m_pad[0x10];
};
template <class V, class H, class E, class A> class hash_set
{
public:
	hash_set();
	char m_pad[0x20];
};
}

// Native 0x001F88A8, 12B.
struct Rva001F88A8Holder
{
	Rva001F88A8Holder();
	ObjectCreationList m_list;
};
Rva001F88A8Holder::Rva001F88A8Holder() {}

// Native 0x00332CEF, 12B; callee 0x00326BE6 folds the
// CLockVolume and AsciiString constructors; member type is unproven.
struct Rva00332CEFHolder
{
	Rva00332CEFHolder();
	D3DXTex::CLockVolume m_member;
};
Rva00332CEFHolder::Rva00332CEFHolder() {}

// Native 0x0033C959, 12B.
struct Rva0033C959Holder
{
	Rva0033C959Holder();
	_STL::map<long, LadderPref, _STL::less<long>,
		_STL::allocator<_STL::pair<const long, LadderPref> > > m_map;
};
Rva0033C959Holder::Rva0033C959Holder() {}

// Native 0x005C46C8, 12B.
struct Rva005C46C8Holder
{
	Rva005C46C8Holder();
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType>,
		_STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > > m_map;
};
Rva005C46C8Holder::Rva005C46C8Holder() {}

// Native 0x0005B6FC, 12B.
struct Rva0005B6FCHolder
{
	Rva0005B6FCHolder();
	_STL::hash_set<int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<int> > m_set;
};
Rva0005B6FCHolder::Rva0005B6FCHolder() {}

// Native 0x003027F5, 16B: the map constructor, then zero at +0x0C.
struct Rva003027F5Holder
{
	Rva003027F5Holder();
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType>,
		_STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > > m_map;
	int m_0c;
};
Rva003027F5Holder::Rva003027F5Holder() : m_0c(0) {}

// Native 0x0023FD63, 14B: clear the int->int tree at +0, then set +0x10.
struct Rva0023FD63Holder
{
	void reset();
	_STL::_Rb_tree<int, _STL::pair<const int, int>,
		_STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>,
		_STL::allocator<_STL::pair<const int, int> > > m_tree;
	bool m_dirty;
};
void Rva0023FD63Holder::reset()
{
	m_tree.clear();
	m_dirty = true;
}

class PSPlayerAllStats
{
public:
	PSPlayerAllStats(int id);
	char m_pad[0x10];
};

// Native 0x005567D1, 17B: PSPlayerAllStats(0) at +8, the leading words untouched.
struct Rva005567D1Holder
{
	Rva005567D1Holder();
	int m_00;
	int m_04;
	PSPlayerAllStats m_stats;
};
Rva005567D1Holder::Rva005567D1Holder() : m_stats(0) {}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// Natives 0x000B3F43, 0x005E7461 and 0x005F0624, 15B each: release the
// reference embedded at +0x28, +0x24 or +0x04 of the pointee, when present.
struct Rva000B3F43Ref
{
	void release();
	char *m_target;
};
void Rva000B3F43Ref::release()
{
	if (m_target)
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)(m_target + 0x28));
}

struct Rva005E7461Ref
{
	void release();
	char *m_target;
};
void Rva005E7461Ref::release()
{
	if (m_target)
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)(m_target + 0x24));
}

struct Rva005F0624Ref
{
	void release();
	char *m_target;
};
void Rva005F0624Ref::release()
{
	if (m_target)
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)(m_target + 4));
}
