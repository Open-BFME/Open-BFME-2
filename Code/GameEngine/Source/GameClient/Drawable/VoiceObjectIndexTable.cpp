// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native 0x004D9FB9..0x004D9FF2 is the 57-byte object-index destructor
// called by pickAndPlayUnitVoiceResponse at 0x004DBE9F. The caller builds a
// pointer-to-index map: node+4 is Object*, node+8 is its selection ordinal.
// Bucket storage is the three-pointer member at +4; count is at +0x10.
// Clear1DBCDC walks next pointers and frees nodes without payload teardown;
// the complete72B Rva004DFC20::clear view independently proves that ABI.
// Automatic bucket cleanup reproduces the native unwind graph, with
// exactly 57 B of code and the native EH cleanup at +4.
// The bucket member is typed off vector<void*> so this TU emits no competing
// copy of the /Od ~vector<void*> that stlport_vector_voidptr_alloc.cpp owns.
// Full boundary and wrapper4DA13F are
// independently witnessed by retail and the live Ghidra xrefs.
// This address owns a separate destructor from ArmorStore's3609BE and
// ThreatFinderManager's3ED1BE. Retire the old ArmorTemplate object-symbol
// alias; do not bind the voice caller to that unrelated template name.
// Original application class name is unknown. The existing opaque hash-map
// constructor4DAADE initializes the containing map in the caller reconstruction.
namespace _STL { void __cdecl free(void *); }
#include "../../../Include/Common/Rva004DFC20.h"
namespace _STL {
template<class T> class allocator {};
template<class T, class A> class vector {
public:
 T *begin,*end,*storage;
 __forceinline ~vector(){if(begin) _STL::free(begin);}
};
}
struct Rva004D9FB9Node;
class Rva004D9FB9ObjectIndex {
public:
 unsigned m_functors;
 _STL::vector<Rva004D9FB9Node *,_STL::allocator<Rva004D9FB9Node *> > m_buckets;
 unsigned m_num_elements;
 __declspec(noinline) ~Rva004D9FB9ObjectIndex();
};
__declspec(noinline) Rva004D9FB9ObjectIndex::~Rva004D9FB9ObjectIndex() {
 reinterpret_cast<Rva004DFC20*>(this)->clear();
}
