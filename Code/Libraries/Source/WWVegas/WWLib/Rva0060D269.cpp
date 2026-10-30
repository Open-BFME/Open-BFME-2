// cl: /O1 /G6 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_CSTD_FUNCTION_IMPORTS
// stlport
//
// ?rva0060D269@Rva0060D269@@QAEAAIABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z @ 0x0060D269, 128 bytes.
// Dedicated TU: the XferSave owner TU carries /MD rows and a different
// class view; the R1 member-visibility lever needs the visible
// __declspec(noinline) Rva0060CAEA::rva0060CB61 definition here (the
// rowed 0x60CB61 body in stlport_string_find_0060CAEA.cpp is identical).
namespace _STL { void __cdecl free(void *); }
#include <string>
#include <vector>
#include <hash_map>
// Inline _String_base<char>'s dtor everywhere so this unit emits no copy of
// its own; the kept retail copy serves any out-of-line call.
namespace _STL { template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_String_base<char, allocator<char> >::~_String_base() { _M_deallocate_block(); } }
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// bfme link decl-only end
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
struct Rva0060CAEANode { void *next; _STL::string key; unsigned int value; };
struct Rva0060CAEAIterator { Rva0060CAEANode *cur; const void *table;
 Rva0060CAEAIterator(Rva0060CAEANode*c,const void*t):cur(c),table(t){} };
struct Rva0060CAEABuckets
{
	void **_M_start;
	void **_M_finish;
	void **_M_end;

	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}
	void *operator[](unsigned int n) const
	{
		return _M_start[n];
	}
};

class Rva0060CAEA
{
public:
	Rva0060CAEANode *rva0060CAEA(const _STL::string &key) const throw();
	Rva0060CAEAIterator rva0060CB61(const _STL::string &key);
private:
	int m_00; // +0x00
	Rva0060CAEABuckets m_buckets; // +0x04
};
class Rva0060D269 { public: unsigned int &rva0060D269(const _STL::string&); };
typedef _STL::pair<const _STL::string,unsigned int> XferNamePair;
typedef _STL::hashtable<XferNamePair,_STL::string,_STL::hash<_STL::string>,
 _STL::_Select1st<XferNamePair>,_STL::equal_to<_STL::string>,_STL::allocator<XferNamePair> > XferNameTable;
namespace _STL { template<> XferNamePair &XferNameTable::_M_insert(const XferNamePair&); }
unsigned int &Rva0060D269::rva0060D269(const _STL::string &key) {
 Rva0060CAEANode *node;
 { Rva0060CAEAIterator it=((Rva0060CAEA*)this)->rva0060CB61(key); node=it.cur; }
 return !node ? ((XferNameTable*)this)->_M_insert(XferNamePair(key,0)).second : node->value;
}

// Actual rowed member ?rva0060CB61@Rva0060CAEA@@QAE?AURva0060CAEAIterator@@ABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z at 0x0060CB61 from Code/Libraries/Source/WWVegas/WWLib/stlport_string_find_0060CAEA.cpp.
inline __declspec(noinline) Rva0060CAEAIterator Rva0060CAEA::rva0060CB61(const _STL::string &key)
{
	return Rva0060CAEAIterator(rva0060CAEA(key), this);
}
