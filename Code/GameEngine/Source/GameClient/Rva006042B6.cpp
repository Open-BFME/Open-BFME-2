// ?rva006042B6@Win32BIGFileSystem@@UAE_NPBD0H@Z
// partial score=0.99 date=2026-10-04
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva006042B6@Win32BIGFileSystem@@UAE_NPBD0H@Z @0x006042B6 149B: vslot 8 of vtable 0x00C7A94C (class Win32BIGFileSystem). Enumerates files via ArchiveFileSystem slot 6 then ORs helper slot 5 per file. Evidence: vtable slot 8; callees rowed set ctor 0x000D3A71 increment 0x00024250 tree dtor 0x0002CC38; globals TheArchiveFileSystem g_Rva0107301CEmptyString.
#include <set>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &left, const AsciiString &right) const;
};

// Retail calls the rowed BfmeStringNoCaseLess tree destructor at 0x0002CC38
// from this body's cleanup, establishing the set's comparator type. Its
// no-case set and tree constructors compile byte-exact at 0x000D3A71 and
// 0x002F0BF4 respectively; those target-supported aliases are pinned in
// reverse/symbols.csv.

bool operator<(const AsciiString &left, const AsciiString &right);

extern const char g_Rva0107301CEmptyString[];

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void a1();
	virtual void a2();
	virtual void a3();
	virtual void a4();
	virtual void a5();
	virtual void getFiles(int x0, const char *a1, const char *empty, const char *a2, _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > &out, int x5);
};

extern ArchiveFileSystem *TheArchiveFileSystem;

class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual bool helper(const char *s, int extra);
	virtual void v6();
	virtual void v7();
	virtual bool rva006042B6(const char *a1, const char *a2, int extra);
};

bool Win32BIGFileSystem::rva006042B6(const char *a1, const char *a2, int extra)
{
	_STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > files;
	TheArchiveFileSystem->getFiles(0, a1, "", a2, files, 0);
	bool result = false;
	for (_STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> >::iterator it = files.begin(); it != files.end(); ++it)
	{
		const AsciiString &a = *it;
		const char *t = *(const char **)&a;
		const char *s = t ? t + 8 : g_Rva0107301CEmptyString;
		result |= helper(s, extra);
	}
	return result;
}
