// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// "_OnPageLoaded" of the tribute screen (AptTributePageCallbacks.cpp) and
// its static page factory. They live apart because this body's inlined page
// release tests the slot before reloading it (cmp [page],0, then a reload
// for the call), which only a volatile read reproduces; out of line that
// destructor is not retail's 0x005F8F96, so the screen's other methods keep
// the plain one and link with the page map's rowed STL copies.

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

// The page map's mapped value (AptTributePageCallbacks.cpp).
#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef0051030C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef0051030C() : m_ptr(0) {}
	TreeHintRef0051030C(TargetRef00217D4C *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	TreeHintRef0051030C(const TreeHintRef0051030C &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	TreeHintRef0051030C &operator=(const TreeHintRef0051030C &other);
	// The second read is kept apart from the null test (retail: cmp [page],0
	// then a reload for the release call).
	__forceinline ~TreeHintRef0051030C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(*(TargetRef00217D4C *volatile *)&m_ptr);
	}
};

class Rva00510D0C
{
public:
	void OnPageLoaded(const char *params);

private:
	typedef _STL::map<AsciiString, TreeHintRef0051030C> PageMap;
	unsigned char m_pad000[0x274];
	int m_level;
	unsigned char m_pad278[0x27C - 0x278];
	PageMap m_pages; // +0x27C, pages by name
};

// The two page kinds, named by their rowed destructors. Their constructors
// are pinned by the factory below; both forward the level and path to the
// rowed refcounted base.
class Rva005105D7 : public TargetRef00217D4C
{
public:
	Rva005105D7(int level, const AsciiString &path);
	unsigned char m_pad08[0xD0 - 0x08];
};

class Rva00510CC3 : public TargetRef00217D4C
{
public:
	Rva00510CC3(int level, const AsciiString &path);
	unsigned char m_pad08[0x28 - 0x08];
};

class Rva0050EE23;
int __cdecl rva0050F841(Rva0050EE23 *a, const char *b);
namespace AptUtils { const char *__cdecl SkipLevelN(const char *path); }
bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *path); }

// map::operator[] stays the out-of-line instance retail calls (rowed 0x00511087):
// a declaration-only explicit specialization suppresses this unit's inline copy.
namespace _STL
{
template <> Rva00510D0C::PageMap::mapped_type &Rva00510D0C::PageMap::operator[](const AsciiString &key);
}

static TreeHintRef0051030C Rva00510D98CreatePage(const AsciiString &type, int level, const AsciiString &name)
{
	if (rva0050F841((Rva0050EE23 *)&type, "StatusPage") == 0)
		return TreeHintRef0051030C(new Rva005105D7(level, AsciiString(AptUtils::SkipLevelN(name.str()))));
	if (rva0050F841((Rva0050EE23 *)&type, "TributePage") == 0)
		return TreeHintRef0051030C(new Rva00510CC3(level, AsciiString(AptUtils::SkipLevelN(name.str()))));
	return TreeHintRef0051030C();
}

// The page references' assignment is the ICF-folded 43-byte counted-pointer
// assignment 0x002174A4, rowed under the Apt handle templates; the call is
// spelled through that rowed twin (no new name for the address).
class AptCommandMap;
template <class T> class AptRef
{
public:
	AptRef &operator=(const AptRef &other);
	void *m_ptr;
};
typedef AptRef<AptCommandMap> TreeHintRefAssignTwin;

void Rva00510D0C::OnPageLoaded(const char *params)
{
	AsciiString name;
	if (!Rva004128F0GetParam(params, "name", name))
		return;
	int level = AptUtils::LevelIndexFromTarget(name.str());
	if (level == m_level)
	{
		AsciiString type;
		if (Rva004128F0GetParam(params, "type", type))
		{
			TreeHintRef0051030C page = Rva00510D98CreatePage(type, level, name);
			if (page.m_ptr)
				reinterpret_cast<TreeHintRefAssignTwin &>(m_pages[name]) = reinterpret_cast<const TreeHintRefAssignTwin &>(page);
		}
	}
}
