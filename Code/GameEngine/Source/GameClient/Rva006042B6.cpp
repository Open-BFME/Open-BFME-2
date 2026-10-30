// ?rva006042B6@Win32BIGFileSystem@@UAE_NPBD0H@Z
// partial score=0.99 date=2026-10-04
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva006042B6@Win32BIGFileSystem@@UAE_NPBD0H@Z @0x006042B6 149B: vslot 8 of vtable 0x00C7A94C (class Win32BIGFileSystem). Enumerates files via ArchiveFileSystem slot 6 then ORs helper slot 5 per file. Evidence: vtable slot 8; callees rowed set ctor 0x000D3A71 increment 0x00024250 tree dtor 0x0002CC38; globals TheArchiveFileSystem g_Rva0107301CEmptyString.
#include <set>
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<AsciiString,_STL::allocator<AsciiString> >::_Rb_tree_base(_STL::allocator<AsciiString> const &); }
// bfme link decl-only end

struct BfmeStringNoCaseLess
{
public:
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};

// Retail calls the rowed BfmeStringNoCaseLess tree destructor at 0x0002CC38
// from this body's cleanup, establishing the set's comparator type. Its
// no-case set and tree constructors compile byte-exact at 0x000D3A71 and
// 0x002F0BF4 respectively; those target-supported aliases are pinned in
// reverse/symbols.csv.

bool operator<(const AsciiString &left, const AsciiString &right);

extern const char g_Rva0107301CEmptyString[];

class File;
class AsciiString;
struct BfmeStringNoCaseLess;
namespace _STL {
template <class T> class allocator;
template <class K, class C, class A> class set;
}

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual File *openFile(const char *filename, int access, int unk);
	virtual void A4();
	virtual bool doesFileExist(const char *filename) const;
	virtual void getFiles(int x0, const char *a1, const char *empty, const char *a2, _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > &out, int x5);
};

extern ArchiveFileSystem *TheArchiveFileSystem;

struct BfmeCStringLess
{
	bool operator()(const char *a, const char *b) const;
};
typedef _STL::set<const char *, BfmeCStringLess> BigFileNameSet;
typedef _STL::map<const char *, BigFileNameSet, BfmeCStringLess> BigDirectoryMap;

class Win32BIGFileSystem
{
public:
	Win32BIGFileSystem();
	virtual ~Win32BIGFileSystem();
	virtual void init(bool flag);
	virtual void V2();
	virtual void V3();
	virtual void V4();
	virtual bool helper(const char *s, int extra);
	virtual void V6();
	virtual void V7();
	virtual bool rva006042B6(const char *path, const char *filter, int extra);
	virtual void getFileListInDirectory(const AsciiString &currentDirectory, const AsciiString &originalDirectory,
		const AsciiString &searchName, _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > &filenameList, bool searchSubdirectories) const;	// slot 9

private:
	BigDirectoryMap m_directories;	// +0x04
};

bool Win32BIGFileSystem::rva006042B6(const char *path, const char *filter, int extra)
{
	_STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > files;
	TheArchiveFileSystem->getFiles(0, path, "", filter, files, 0);
	bool result = false;
	for (_STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> >::iterator it = files.begin(); it != files.end(); ++it)
	{
		const AsciiString &asciiString = *it;
		const char *t = *(const char **)&asciiString;
		const char *s = t ? t + 8 : g_Rva0107301CEmptyString;
		result |= helper(s, extra);
	}
	return result;
}
