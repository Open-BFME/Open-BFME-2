// cl: /DNDEBUG /MD /EHsc
// probe: ObjectPoolClass<MultiListNodeClass,256>::Allocate_Object_Memory
// retail 0x00610680, 198 bytes.

typedef unsigned int uint32;

// BFME replaced STLport's allocator with one raw byte allocator that every
// instantiation folds onto (see reference/shims/bfmealloc/stl/_alloc.h); the
// pool's own operator new call was patched to route through the same
// allocator, called as __cdecl (bytes, hint). Pinned at 0x000307F0.
namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
	static char *allocate(unsigned int n, const void *hint = 0);
};
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListNodeClass
{
	char m_bfmeBody[20];
};

// The one-word lock is the measured BFME pool lock at 0x0006577F.
#include "bfme_pool_critical_section.h"

template<class T,int BLOCK_SIZE = 64>
class ObjectPoolClass
{
public:
	T *		Allocate_Object_Memory(void);

protected:

	T	*		FreeListHead;
	uint32 *	BlockListHead;
	int		FreeObjectCount;
	int		TotalObjectCount;
	BFMEPoolCriticalSection ObjectPoolCS;

};

template<class T,int BLOCK_SIZE>
T * ObjectPoolClass<T,BLOCK_SIZE>::Allocate_Object_Memory(void)
{
	BFMEPoolCriticalSection::LockClass lock(ObjectPoolCS);

	if ( FreeListHead == 0 ) {

		uint32 * tmp_block_head = BlockListHead;
		BlockListHead = (uint32*)_STL::allocator<char>::allocate( sizeof(T) * BLOCK_SIZE + sizeof(uint32 *));
		*(void **)BlockListHead = tmp_block_head;

		FreeListHead = (T*)(BlockListHead + 1);
		for ( int i = 0; i < BLOCK_SIZE; i++ ) {
			*(T**)(&(FreeListHead[i])) = &(FreeListHead[i+1]);
		}
		*(T**)(&(FreeListHead[BLOCK_SIZE-1])) = 0;

		FreeObjectCount += BLOCK_SIZE;
		TotalObjectCount += BLOCK_SIZE;
	}

	T * obj = FreeListHead;
	FreeListHead = *(T**)(FreeListHead);
	FreeObjectCount--;

	return obj;
}

template MultiListNodeClass * ObjectPoolClass<MultiListNodeClass,256>::Allocate_Object_Memory(void);
