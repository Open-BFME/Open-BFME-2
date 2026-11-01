// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// MeshInstancingManager subsystem view; the original C++ class/method names
// are unknown, so the destructor address remains its class name.
// Target identity: GameEngine::init names TheMeshInstancingManager and invokes
// ctor 0x0041FCEA on a 0x24-byte allocation. That ctor installs primary vtable
// VA 0x00C3B914 and a secondary interface vtable VA 0x00C3B910 at +0xC, then
// constructs the 20-byte table at +0x10. The secondary base is one pure slot
// (base vtable VA 0x00C1C780); native lookup 0x0041FB69 is its override.
// SubsystemInterface's existing target header supplies its verified 12-byte
// layout and 14 primary virtual slots. Native slots 1/9/10 identify init/reset/
// update; reset and update both target the already-owned RET at RVA 0x000B3FD0.
// Destructor 0x0041FB13..0x0041FB61 (78B) unregisters the interface, destroys
// the table through its real 0x0041FA59 owner, then destroys SubsystemInterface.
// Lookup 0x0041FB69..0x0041FC37 (206B) returns node+8 for the whole name, then
// retries the prefix before the first dot, otherwise returning 1. AsciiString
// key +4 and scalar value +8 are native accesses; STLport's two-word iterator
// is a source-shape inference, independently verified against the full body.
// Reference BFME1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe and ZH sweeps
// supplied no viable named donor for this subsystem. Real C++ reconstruction.

#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <string.h>
#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
unsigned int __stdcall Rva00055041AsciiHash(const AsciiString *name);
struct MeshInstancingAsciiHashView
{
    unsigned operator()(const AsciiString &name) const
    {
        return Rva00055041AsciiHash(&name);
    }
};
typedef _STL::hash_map<AsciiString, int, MeshInstancingAsciiHashView> MeshNameMap;
// Emit only the real default constructor and its dependent helpers. Pin admission
// checks this complete chain against the existing folded retail owners.
template _STL::hash_map<AsciiString, int, MeshInstancingAsciiHashView>::hash_map();
typedef _STL::pair<const AsciiString, int> MeshNamePair;
typedef _STL::_Ht_iterator<
    MeshNamePair, _STL::_Nonconst_traits<MeshNamePair>, AsciiString,
    _STL::hash<AsciiString>, _STL::_Select1st<MeshNamePair>,
    _STL::equal_to<AsciiString>, _STL::allocator<MeshNamePair> > MeshNameIterator;
typedef MeshNameIterator::_Node MeshNameNode;
typedef bool Bool;
#include "subsystem_interface.h"
// bfme link decl-only begin
namespace _STL { template <> _STL::_OKToMemCpy<void *,void *> _IsOKToMemCpy<void *,void *>(void * *,void * *); }
namespace _STL { template <> template <> void * * vector<void *,_STL::allocator<void *> >::_M_allocate_and_copy<void * *>(unsigned int,void * *,void * *); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::_Vector_base(_STL::allocator<void *> const &); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::vector(_STL::allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::~vector(); }
namespace _STL { template <> void * & vector<void *,_STL::allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_fill_insert(void * *,unsigned int,void * const &); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_insert_overflow(void * *,void * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_set(void * *,void * *,void * *); }
namespace _STL { template <> _STL::__true_type _OKToMemCpy<void *,void *>::_Ret(); }
namespace _STL { template <> void * * _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> void * * allocator<void *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void * * vector<void *,_STL::allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *,_STL::allocator<void *> >::capacity() const; }
namespace _STL { template <> void _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::deallocate(void * *,unsigned int); }
namespace _STL { template <> void __node_alloc<1,0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<void *>::deallocate(void * *,unsigned int) const; }
namespace _STL { template <> void * * vector<void *,_STL::allocator<void *> >::end(); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::insert(void * *,unsigned int,void * const &); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *,_STL::allocator<void *> >::size() const; }
// bfme link decl-only end
class Rva00056F61 { public: __declspec(nothrow) void *rva00056F61(const AsciiString *); };
#include "../../../Include/GameLogic/Rva000427195.h"
class Rva0041FA59 : public MeshNameMap
{
public:
    Rva0041FA59() {}
    ~Rva0041FA59();
    MeshNameIterator find(const AsciiString &key)
    {
        return MeshNameIterator(static_cast<MeshNameNode *>(reinterpret_cast<Rva00056F61 *>(this)->rva00056F61(&key)),
            reinterpret_cast<MeshNameIterator::_Hashtable *>(this));
    }
    MeshNameIterator end() { return MeshNameIterator(0,reinterpret_cast<MeshNameIterator::_Hashtable *>(this)); }
// The inherited hash_map occupies the same native twenty-byte table.
};
class MeshInstancingInterfaceView { public: virtual int rva0041FB69(const char *) = 0; };
void Rva0018C0F1Clear();
class FXShaderGeometry
{
public:
	static void RegisterInstancingManager(void *interfaceView);
};
class Rva0041FB13 : public SubsystemInterface, public MeshInstancingInterfaceView
{
public:
    Rva0041FB13();
    virtual ~Rva0041FB13();
    virtual void init() { reinterpret_cast<Rva000427195 *>(&table)->rva003A2A41(); }
    virtual void reset() {}
    virtual void update() {}
    virtual int rva0041FB69(const char *arg);
private:
    Rva0041FA59 table;
};
Rva0041FB13::Rva0041FB13()
{
    FXShaderGeometry::RegisterInstancingManager(static_cast<MeshInstancingInterfaceView *>(this));
}
Rva0041FB13::~Rva0041FB13() { Rva0018C0F1Clear(); }

int Rva0041FB13::rva0041FB69(const char *arg)
{
    if (!arg)
        return 1;

    MeshNameIterator found = table.find(arg);
    if (found != table.end())
        return found->second;

    char *dot = strchr(arg, '.');
    if (dot) {
        AsciiString prefix(arg, 0, static_cast<int>(dot - arg));
        found = table.find(prefix.str());
        if (found != table.end())
            return found->second;
    }
    return 1;
}

// GameEngine::init stores this primary-base pointer at native RVA A03134;
// its retail initial data is four zero bytes. The secondary interface is
// registered separately by FXShaderGeometry::RegisterInstancingManager.
Rva0041FB13 *TheMeshInstancingManager = 0;

typedef char MeshInstancingSubsystemSize[(sizeof(Rva0041FB13) == 0x24) ? 1 : -1];
