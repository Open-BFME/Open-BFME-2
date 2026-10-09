// ??1Rva001E287F@@QAE@XZ
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_NO_CSTD_FUNCTION_IMPORTS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// Native1E287F..1E28B8 is a 20-byte pointer hash-table destructor.
// The prior Armor-template gen-alias obscured its distinct EH identity.
// Existing Armor clear is used only for its verified payload-neutral ABI.
#include <vector>
// Only the existing clear provider's decoration is reused. It touches the
// bucket array, node links and element count, with no mapped-value destructor.
enum NameKeyType { NAMEKEY_INVALID=0 };
class ArmorTemplate;
namespace rts { template<class T> struct hash; }
namespace _STL {
 template<class T> struct _Select1st;
 template<class T> struct equal_to;
 template<class V,class K,class H,class E,class Eq,class A>
 class hashtable { public: void clear(); };
}
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmorPair;
typedef _STL::hashtable<ArmorPair,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmorPair>,_STL::equal_to<NameKeyType>,_STL::allocator<ArmorPair> > NativeClearTable;
namespace _STL {void free(void *);}
struct FxOwnedVector {
 void **first,**last,**limit;
 ~FxOwnedVector(){if(first)_STL::free(first);}

};
struct Rva001E287F {
 unsigned unknown00;FxOwnedVector buckets04;unsigned count10;
 ~Rva001E287F();
 void clear(){reinterpret_cast<NativeClearTable *>(this)->clear();}
};
Rva001E287F::~Rva001E287F(){clear();}

typedef char FxHashStorageSizeCheck[sizeof(Rva001E287F)==0x14 ? 1 : -1];
