// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native331CAA..331CBA16B RET4 and331CBA..331CE341B RET8.
// Target passes the address of the wrapper's by-value key to the existing
// list-remove provider2ABFC3, which independently reads only its first word.
// The outer loop proves12B records, key0 and list8, vector begin/end4/8;
// original owner/record identities remain unresolved. STLport list removal
// is the semantic reference; provider element name kept only at call boundary.
#include <list>
struct BfmePod12 { int a[3]; };
namespace _STL { template<> void list<BfmePod12>::remove(const BfmePod12 &); }
struct Rva00331CAAListOwner {
    int key, opaque04;
    _STL::list<BfmePod12> entries;
    __declspec(noinline) void removeEntry(int entry);
};
void Rva00331CAAListOwner::removeEntry(int entry) {
    entries.remove(reinterpret_cast<const BfmePod12 &>(entry));
}
class Rva00331CBAVectorOwner {
    int opaque00;
    Rva00331CAAListOwner *begin, *end, *capacity;
public:
    void removeFromMatching(int entry, int key);
};
void Rva00331CBAVectorOwner::removeFromMatching(int entry, int key) {
    for (Rva00331CAAListOwner *node=begin; node!=end; ++node)
        if (node->key == key) node->removeEntry(entry);
}
