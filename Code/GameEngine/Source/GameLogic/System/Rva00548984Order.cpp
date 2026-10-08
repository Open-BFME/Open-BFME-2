// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3. Target 0x00548984..0x00548A09 removes one object ID
// from an order, optionally repeats on its cloned order, and unregisters
// and globally deletes an order whose object-ID vector becomes empty.
// WB 0x013455E0 independently supplies the operation/callsite lead;
// the original method name is unknown. Retail accesses prove vector +4,
// order ID +0x10, clone ID +0x14 and cleanup vcall +0x18.
// The legacy void* argument spelling carries a 32-bit object-ID word;
// no object is dereferenced through that argument.
// The emitted ObjectID search/compaction and order-pointer map erase
// are full-byte-and-relocation twins of existing generic STLport bodies.
#include <vector>
#include <algorithm>
#include <hash_map>
enum ObjectID { INVALID_ID = 0 };
enum NameKeyType { NK_NONE = 0 };
// Use the verified vector erase provider. The inline bucket accessor
// convention below is the existing stlport_hash_map_int.cpp convention;
// all three accessors inline and emit no imported call or conflicting copy.
namespace _STL {
template <> ObjectID *vector<ObjectID>::erase(ObjectID *, ObjectID *);
template <> __declspec(dllimport) __forceinline void **vector<void *>::begin() { return _M_start; }
template <> __declspec(dllimport) __forceinline unsigned int vector<void *>::size() const { return _M_finish - _M_start; }
template <> __declspec(dllimport) __forceinline void *&vector<void *>::operator[](unsigned int n) { return _M_start[n]; }
}
class ArmorTemplate;
class Rva00355B61 { public: const ArmorTemplate *rva00355155(NameKeyType) const; };
class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;
class Rva00548984 {
public:
    virtual ~Rva00548984();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6(void *);
    void rva00548984(void *object, int recursive);
private:
    _STL::vector<ObjectID> objects04;
    int id10;
    int clone14;
};
typedef _STL::hash_map<int, Rva00548984 *> OrderMap;
struct OrderManagerMapView { char opaque[0x10]; OrderMap orders10; };
void Rva00548984::rva00548984(void *object, int recursive)
{
    slot6(object);
    objects04.erase(_STL::remove(objects04.begin(), objects04.end(), reinterpret_cast<const ObjectID &>(object)), objects04.end());
    if (recursive == 1 && clone14) {
        Rva00548984 *clone = (Rva00548984 *)((Rva00355B61 *)TheAiOrdersManager)->rva00355155((NameKeyType)clone14);
        if (clone)
            clone->rva00548984(object, recursive);
    }
    if (objects04.empty()) {
        ((OrderManagerMapView *)TheAiOrdersManager)->orders10.erase(id10);
        ::delete this;
    }
}
