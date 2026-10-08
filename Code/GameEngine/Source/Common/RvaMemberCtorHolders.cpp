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
