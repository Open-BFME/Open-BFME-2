// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ??0Win32BIGFileSystem@@QAE@XZ @0x0060453B 55B: ctor stores vtable VA 0x00C7A94C, map at +4, base init 0x00602635. Evidence: caller 0x00600723 new(0x10) stores to G00A06E54 slot; callees rowed.
class __declspec(novtable) Rva00602635VTableInstall
{
public:
	Rva00602635VTableInstall *init();
	Rva00602635VTableInstall() { init(); }
	virtual ~Rva00602635VTableInstall();
};

enum NameKeyType
{
	NK_Dummy = 0
};

class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		int m_dummy;
	};
};

namespace _STL
{
template <typename T> struct less
{
};
template <typename T> class allocator
{
};
template <typename A, typename B> struct pair
{
	A first;
	B second;
};
template <typename K, typename V, typename C, typename A> class map
{
public:
	map();
};
}

class Win32BIGFileSystem : public Rva00602635VTableInstall
{
public:
	Win32BIGFileSystem();
	virtual ~Win32BIGFileSystem();
private:
	_STL::map<enum NameKeyType, class ModuleFactory::ModuleTemplate, struct _STL::less<enum NameKeyType>, class _STL::allocator<struct _STL::pair<const enum NameKeyType, class ModuleFactory::ModuleTemplate> > > m_map;
};

Win32BIGFileSystem::Win32BIGFileSystem()
{
}
