// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ZH registry setter semantics; retail6C8C60/6C8E50 copy their first
// HKLM call arguments inline through the rowed two-argument string range
// initializer8D00. Their HKCU copies use the rowed copy constructor9170.
// Minimal STLport ABI follows stlport_narrow_string_range_ctors.cpp.
namespace _STL {
void __cdecl free(void *);
template<class T> class char_traits {};
template<class T> class allocator {};
template<class Pointer,class Value,class Alloc> class _STLP_alloc_proxy : public Alloc {
public:
    _STLP_alloc_proxy(const Alloc &a,Pointer data):Alloc(a),_M_data(data) {}
    Pointer _M_data;
};
template<class CharT,class Alloc> class _String_base {
public:
    _String_base(const Alloc &a):_M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
    ~_String_base() { if(_M_start) free(_M_start); }
    CharT *_M_start,*_M_finish;
    _STLP_alloc_proxy<CharT *,CharT,Alloc> _M_end_of_storage;
};
struct RegistryRangeCopyTag {};
template<class CharT,class Traits,class Alloc> class basic_string : public _String_base<CharT,Alloc> {
public:
    __declspec(noinline) basic_string(const basic_string &s):_String_base<CharT,Alloc>(Alloc()) {
        _M_range_initialize(s._M_start,s._M_finish);
    }
    __forceinline basic_string(const basic_string &s,RegistryRangeCopyTag):_String_base<CharT,Alloc>(Alloc()) {
        _M_range_initialize(s._M_start,s._M_finish);
    }
    ~basic_string() {}
    const CharT *c_str() const { return _M_start; }
    template<class It> void _M_range_initialize(It,It);
};
typedef basic_string<char,char_traits<char>,allocator<char> > NStr;
}
struct HKEY__;
typedef HKEY__ *HKEY;
#define HKEY_CURRENT_USER ((HKEY)0x80000001)
#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)
_STL::NStr buildGameRegistryPath(const char *);
bool setStringInRegistry(HKEY,_STL::NStr,_STL::NStr,_STL::NStr);
bool setUnsignedIntInRegistry(HKEY,_STL::NStr,_STL::NStr,unsigned int);
bool SetStringInRegistry(_STL::NStr path,_STL::NStr key,_STL::NStr val) {
    _STL::NStr fullPath=buildGameRegistryPath(path.c_str());
    if(setStringInRegistry(HKEY_LOCAL_MACHINE,
        _STL::NStr(fullPath,_STL::RegistryRangeCopyTag()),
        _STL::NStr(key,_STL::RegistryRangeCopyTag()),
        _STL::NStr(val,_STL::RegistryRangeCopyTag()))) return true;
    return setStringInRegistry(HKEY_CURRENT_USER,fullPath,key,val);
}
bool SetUnsignedIntInRegistry(_STL::NStr path,_STL::NStr key,unsigned int val) {
    _STL::NStr fullPath=buildGameRegistryPath(path.c_str());
    if(setUnsignedIntInRegistry(HKEY_LOCAL_MACHINE,
        _STL::NStr(fullPath,_STL::RegistryRangeCopyTag()),
        _STL::NStr(key,_STL::RegistryRangeCopyTag()),val)) return true;
    return setUnsignedIntInRegistry(HKEY_CURRENT_USER,fullPath,key,val);
}
