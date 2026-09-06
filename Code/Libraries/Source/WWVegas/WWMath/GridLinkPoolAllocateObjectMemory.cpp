// cl: /G7 /DNDEBUG /MD /EHsc
// ObjectPoolClass<GridLinkClass,256>::Allocate_Object_Memory,
// retail 0x0071AED0, 198 bytes.
//
// gridcull.cpp's DEFINE_AUTO_POOL(GridLinkClass,256) twin of
// MultiListNodeClass's pool landed at 0x00610680 in
// ObjectPoolAllocateObjectMemory.cpp - same FastCriticalSectionClass, same
// BFME byte allocator at 0x000307F0, same spin() pin (0x0006577F).

typedef unsigned int uint32;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/gridcull.h
class GridLinkClass
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mutex.h
class FastCriticalSectionClass
{
	unsigned Flag;

public:
	FastCriticalSectionClass() : Flag(0) {}

	class LockClass
	{
		FastCriticalSectionClass& cs;
	public:
		LockClass(FastCriticalSectionClass& critical_section) : cs(critical_section)
		{
			spin(&cs.Flag);
		}

		~LockClass()
		{
			cs.Flag=0;
		}

	private:
		static void __fastcall spin(unsigned *flag);		// pinned 0x0006577F

		LockClass &operator=(const LockClass&);
		LockClass(const LockClass&);
	};

	friend class LockClass;
};

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
	FastCriticalSectionClass ObjectPoolCS;

};

template<class T,int BLOCK_SIZE>
T * ObjectPoolClass<T,BLOCK_SIZE>::Allocate_Object_Memory(void)
{
	FastCriticalSectionClass::LockClass lock(ObjectPoolCS);

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

template GridLinkClass * ObjectPoolClass<GridLinkClass,256>::Allocate_Object_Memory(void);
