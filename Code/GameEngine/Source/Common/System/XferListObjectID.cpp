// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva0036ABAFXfer@@YAPAVXfer@@PAV1@PAV?$list@HV?$allocator@H@_STL@@@_STL@@@Z @0x0036ABAF 196B
// Free list-ObjectID Xfer helper: version {1,1} via slot 0x28 then size via slot 0x2C/0x78
// then IsStoring via slot 0x08; saving walks nodes via rowed XferObjectID 0x003060B2,
// loading checks empty via FormatText 0x0060C36E plus Throw 0x00629094 then reloads
// via XferObjectID plus rowed list<int> push_back 0x0005548F. Donor is BFME1
// Code/GameEngine/Source/GameLogic/ScriptEngine/XferListInt.cpp (same skeleton with
// xferInt element); callers include 0x0036AC73 plus 0x0044F996 0x004F579C 0x00460586.

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

#include "XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

enum ObjectID
{
	INVALID_ID = 0
};

#include "../../../Include/Common/XferException.h"


void XferObjectID(Xfer *xfer, ObjectID *objectID);

typedef _STL::list<int> ListInt;

Xfer *Rva0036ABAFXfer(Xfer *xfer, ListInt *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	UnsignedInt count = list->size();
	(*xfer == "std::list") == count;

	if (xfer->IsStoring())
	{
		ListInt::_Node *sentinel = list->_M_node._M_data;
		ListInt::_Node *node = (ListInt::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			XferObjectID(xfer, (ObjectID *)&node->_M_data);
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
			XferObjectID(xfer, (ObjectID *)&value);
			list->push_back(value);
		}
		--count;
	}
	return xfer;
}
