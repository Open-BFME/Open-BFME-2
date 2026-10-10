// cl: /O1 /Ob2 /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Replaces the generated ArmorStore destructor copy at native148B84..148BBD.
// Target: caller NameKeyGenerator destructor148BC2 uses a20B reverse index
// at2BF4C; this body clears buckets through the real shared1DBCDC worker and
// releases bucket storage through30830. Both calls and complete EH are verified.
// Template spelling/payload are the existing address-derived14918D view;
// its eight-byte opaque value is donor inference, not recovered target layout.
// The shared clear worker only unlinks/frees nodes with trivially destructible
// values. Its ArmorTable spelling is retained from the established provider.
#include <hash_map>
struct Rva0014918DElement {char bytes[8];};
enum NameKeyType {NAMEKEY_INVALID=0,NAMEKEY_MAX=1<<23,FORCE_NAMEKEYTYPE_LONG=0x7fffffff};
namespace rts { template<class T>struct hash {unsigned operator()(const T&v)const{return (unsigned)v;} }; }
class ArmorTemplate {float values[38];};
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmorPair;
typedef _STL::hashtable<ArmorPair,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmorPair>,_STL::equal_to<NameKeyType>,_STL::allocator<ArmorPair> > ArmorTable;
namespace _STL {template<> void ArmorTable::clear();}
typedef _STL::pair<const int,Rva0014918DElement> ReversePair;
typedef _STL::hashtable<ReversePair,int,_STL::hash<int>,_STL::_Select1st<ReversePair>,_STL::equal_to<int>,_STL::allocator<ReversePair> > ReverseTable;
namespace _STL {template<> __declspec(noinline) ReverseTable::~hashtable(){reinterpret_cast<ArmorTable*>(this)->clear();}}

template ReverseTable::~hashtable();
