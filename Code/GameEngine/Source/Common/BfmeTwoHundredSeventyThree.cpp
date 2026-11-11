// cl: /DNDEBUG /MD /EHsc /Og-
// A block let go of through one of two paths according to how big it is. The
// small-block arm is STLport's node allocator, with the false-thread
// specialization's constant lock tests retained by this compiler mode.

void bfmeBigFreePM(void *at);

namespace _STL
{

#include "../../Include/Common/NodeAllocMutex.h"

template <bool __threads, int __inst>
class _Node_Alloc_Lock
{
	int m_dummy;
	int m_dummy2;

public:
	_Node_Alloc_Lock()
	{
		if (__threads)
			_S_lock._M_acquire_lock();
	}
	~_Node_Alloc_Lock()
	{
		if (__threads)
			_S_lock._M_release_lock();
	}

	static NodeAllocMutex _S_lock;
};

template <bool __threads, int __inst>
NodeAllocMutex _Node_Alloc_Lock<__threads, __inst>::_S_lock;

// The free-list table at 0x009DF530 is this static (defined by
// BfmeSmallAllocPR.cpp).
class _Node_alloc_obj;

template <bool __threads, int __inst>
class __node_alloc
{
public:
	static _Node_alloc_obj * volatile _S_free_list[16];
};

}

struct BfmeFreeListNode
{
	BfmeFreeListNode *m_next;
};

void bfmeSmallFreePM(void *at, unsigned int bytes)
{
	BfmeFreeListNode * volatile *my_free_list =
		(BfmeFreeListNode * volatile *)_STL::__node_alloc<false, 0>::_S_free_list + ((bytes - 1) >> 3);
	_STL::_Node_Alloc_Lock<false, 0> lock_instance;
	((BfmeFreeListNode *)at)->m_next = *my_free_list;
	*my_free_list = (BfmeFreeListNode *)at;
}

void bfmeFreePM(void *at, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeBigFreePM(at);
	else
		bfmeSmallFreePM(at, bytes);
}
