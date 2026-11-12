// Native 0x002A9725..0x002A97DB constructor; sizeof receiver 0x944.
// WB manager call graph and native vtables establish the receiver identity.
// Pointer vector spelling is the inherited opaque ABI view: native update
// proves AIGameTeam pointers, without establishing ModuleData as their type.
// Direct STLport map/hash members avoid temporary placement-construction
// cleanup states. All fields and calls are verified against this retail row.
// cl: /O1 /G7 /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_CRTIMP= /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <vector>
#include <map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <hash_map>
#include <new>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

#include <cstddef>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}
typedef bool Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Rva002A8D49 {public:Rva002A8D49();~Rva002A8D49();unsigned char data[0x8f8];};
#include "../../../Include/GameLogic/Rva002A9706Element.h"
namespace _STL {template<> struct hash<Rva002A9706Element>{unsigned operator()(const Rva002A9706Element&) const;};}
class Rva004E9337 {public:void rva004E9337();};
class ObjectCreationList {public:ObjectCreationList();__forceinline ~ObjectCreationList(){reinterpret_cast<Rva004E9337*>(this)->rva004E9337();}unsigned words[3];};
class ModuleData;
enum ObjectID {OBJECTID_INVALID=0};
class Rva002A8F24:public SubsystemInterface,public Snapshot {
public:Rva002A8F24();virtual ~Rva002A8F24();virtual void init(){}virtual void reset();virtual void update();virtual void loadPostProcess(){}virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 Rva002A8D49 data10;
 _STL::map<int,void*> collectors908;
 _STL::vector<const ModuleData*>teams914;
 _STL::hash_map<int,Rva002A9706Element> builders920;
 _STL::vector<ObjectID>heroIDs934;
 ObjectCreationList*owned940;
};
// bfme link decl-only begin
namespace _STL { template <> _STL::_OKToMemCpy<void *,void *> _IsOKToMemCpy<void *,void *>(void * *,void * *); }
namespace _STL { template <> template <> void * * vector<void *,_STL::allocator<void *> >::_M_allocate_and_copy<void * *>(unsigned int,void * *,void * *); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::_Vector_base(_STL::allocator<void *> const &); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::vector(_STL::allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
namespace _STL { template <> hashtable<_STL::pair<int const,Rva002A9706Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002A9706Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002A9706Element> > >::~hashtable(); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_fill_insert(void * *,unsigned int,void * const &); }
namespace _STL { template <> void hashtable<_STL::pair<int const,Rva002A9706Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002A9706Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002A9706Element> > >::_M_initialize_buckets(unsigned int); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_insert_overflow(void * *,void * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> unsigned int hashtable<_STL::pair<int const,Rva002A9706Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002A9706Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002A9706Element> > >::_M_next_size(unsigned int) const; }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_set(void * *,void * *,void * *); }
namespace _STL { template <> _STL::__true_type _OKToMemCpy<void *,void *>::_Ret(); }
namespace _STL { template <> void * * _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::allocate(unsigned int); }
namespace _STL { template <> void * * allocator<void *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> unsigned int vector<void *,_STL::allocator<void *> >::capacity() const; }
namespace _STL { template <> void hashtable<_STL::pair<int const,Rva002A9706Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002A9706Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002A9706Element> > >::clear(); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::insert(void * *,unsigned int,void * const &); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> hashtable<_STL::pair<int const,Rva002A9706Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002A9706Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002A9706Element> > >::hashtable(unsigned int,_STL::hash<int> const &,_STL::equal_to<int> const &,_STL::allocator<_STL::pair<int const,Rva002A9706Element> > const &); }
namespace _STL { template <> hash_map<int,Rva002A9706Element,_STL::hash<int>,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002A9706Element> > >::hash_map(); }
// bfme link decl-only end
Rva002A8F24::Rva002A8F24():owned940(0){owned940=new ObjectCreationList;}
