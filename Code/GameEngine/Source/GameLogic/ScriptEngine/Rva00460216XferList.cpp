// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva00460216XferList@@YAPAVXfer@@PAV1@PAV?$list@HV?$allocator@H@_STL@@@_STL@@@Z @0x00460216 (194B): free list<int> Xfer helper, same skeleton as rowed xferListInt @0x00206861 but elements via slot 0x7C (xferInt) and no trailing count dec.
// Evidence: unlock lane every callee rowed or pinned; callers 0x004606AE 0x0049FA7A 0x0049FC44; unblocks 0x00460586 0x0049F91A; donor BFME1 ScriptEngine/XferListInt.cpp same skeleton.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// LINK: single-node insert binds the verified native STLport owner at RVA
// 0x005925E2; keep the out-of-line call without emitting a competing copy.
namespace _STL {
template <> list<int>::iterator list<int>::insert(iterator position, const int &x);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "../../Common/System/XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferException.h"


typedef _STL::list<int> ListInt;

Xfer *Rva00460216XferList(Xfer *xfer, ListInt *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->operator==(reinterpret_cast<Xfer::Version &>(version));

	UnsignedInt count = list->size();
	xfer->operator==("std::list").operator==(count);

	if (xfer->IsStoring())
	{
		ListInt::_Node *sentinel = list->_M_node._M_data;
		ListInt::_Node *node = (ListInt::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			xfer->operator==(node->_M_data);
			node = (ListInt::_Node *)node->_M_next;
		}
	}
	else
	{
		if (!list->empty())
		{
			throw XferException(4, "List must be empty on load");
		}

		int value;
		while (count != 0)
		{
			--count;
			xfer->operator==(value);
			list->push_back(value);
		}
	}
	return xfer;
}
