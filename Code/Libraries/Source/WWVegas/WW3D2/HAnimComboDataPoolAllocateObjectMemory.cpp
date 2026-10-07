// cl: /DNDEBUG /MD /EHsc
// ObjectPoolClass<HAnimComboDataClass,256>::Allocate_Object_Memory,
// retail 0x001963A0, 198 bytes.
//
// hanim.cpp's DEFINE_AUTO_POOL(HAnimComboDataClass,256) twin of the pools
// landed at 0x00610680 (MultiListNodeClass) and 0x0071AED0 (GridLinkClass):
// same FastCriticalSectionClass lock, same BFME byte allocator at 0x000307F0,
// same spin() pin. The 20-byte element stands in for the combo entry; retail's
// block request of 0x1404 bytes (256 elements plus the link word) fixes that
// size and nothing else about the class.

typedef unsigned int uint32;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimComboDataClass
{
	char m_bfmeBody[20];
};

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

// The one-word lock is the measured BFME pool lock at 0x0006577F.
#include "../WWLib/bfme_pool_critical_section.h"

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

template HAnimComboDataClass * ObjectPoolClass<HAnimComboDataClass,256>::Allocate_Object_Memory(void);
