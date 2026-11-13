// ?rva00601A8D@Rva00601BBCHelper@@QAEXXZ
// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The 0x34-byte helper BFME 2 added to INI at +0x838 (INI_ctor.cpp):
//   ??0Rva00601BBCHelper@@QAE@XZ   0x00601BBC  constructor
//   ??1Rva00601BBCHelper@@UAE@XZ   0x00601BF3  destructor
//   ??_GRva00601BBCHelper@@UAEPAXI@Z 0x00602056 scalar deleting destructor
// Layout from these bodies: a one-slot vtable (0x00C7A6B0, slot 0 the
// deleting destructor), a 0x18-byte member at +4 built by the rowed
// Rva00524415 constructor (two vectors) and torn down by 0x00601AE9, and two
// four-byte-element vectors at +0x1C and +0x28 whose storage is freed
// directly. The constructor runs the once-only table init 0x006016C9; the
// destructor first clears everything through 0x00601A8D. The class's identity
// (a token/lexer table, by its ctype-table init) is not established, so the
// names stay address-derived; the callees are pinned.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
}

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
}

void Rva006016C9Init() throw();

// ?rva00601C53@@YAXPAXH000@Z @0x00601C53 1027B worker (unrowed): __cdecl 5-param
// (outer, flag, m_1C, m_28, &m_04); address-derived ABI from the native call; semantic identity remains unknown.
void __cdecl rva00601C53(void *outer, int flag, void *vec1, void *vec2, void *member);

struct Rva00524415
{
	Rva00524415();
	~Rva00524415();
	char m_body[0x18];
};

#include "../../Include/Common/Rva00601BBCHelper.h"

class Rva00601B30 {public:void clear();char storage[0x18];};
void Rva00601BBCHelper::rva00601A8D(){
 ((Rva00601B30*)&m_04)->clear();
 _STL::vector<int>& blocks=m_28;
 for(unsigned int i=0;i<blocks.size();++i){
  _ReadWriteBarrier();
		if(blocks[i]){
   delete[] (char*)blocks[i];
   blocks[i]=0;
  }
 }
 _STL::vector<void*>& pointers=(_STL::vector<void*>&)blocks;
 pointers.erase(pointers.begin(),pointers.end());
 _STL::vector<void*>& keys=(_STL::vector<void*>&)m_1C;
 keys.erase(keys.begin(),keys.end());
}
