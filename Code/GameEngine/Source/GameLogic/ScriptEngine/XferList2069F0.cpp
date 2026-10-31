// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?xferList2069F0@@YAPAVXfer@@PAV1@PAV?$list@UBfmeFloat4Record00469C61@@V?$allocator@UBfmeFloat4Record00469C61@@@_STL@@@_STL@@@Z @0x002069F0 206B
// Free list Xfer helper (version {1,1}, "std::list", 16-byte records): saves by chaining each node payload at +8 through the rowed 0x00203DBE, loads by default-constructing a record, chaining into it and push_back (0x00206579). Evidence: retail frame and callees read at the REL32s; skeleton from the rowed xferListFloat4Record 0x00206861.
// Free list Xfer helper (version {1,1}, "std::list", 16-byte records): saves by chaining each node payload at +8 through the rowed 0x00203DBE, loads by default-constructing a record, chaining into it and push_back (0x00206579). Evidence: retail frame and callees read at the REL32s; skeleton from the rowed xferListInt 0x00206861.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

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

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};


class Rva00203DBEA;
void Rva00203DBEChain(Rva00203DBEA *a, void *b);

class Rva00690FF0Handle
{
public:
	Rva00690FF0Handle();
	void *m_ptr;
};

struct BfmeFloat4Record00469C61
{
	Rva00690FF0Handle m_head;
	char m_pad[12];
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _List_iterator<BfmeFloat4Record00469C61,_Nonconst_traits<BfmeFloat4Record00469C61> > list<BfmeFloat4Record00469C61,allocator<BfmeFloat4Record00469C61> >::insert(_List_iterator<BfmeFloat4Record00469C61,_Nonconst_traits<BfmeFloat4Record00469C61> >,BfmeFloat4Record00469C61 const &); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _Construct<BfmeFloat4Record00469C61,BfmeFloat4Record00469C61>(BfmeFloat4Record00469C61 *,BfmeFloat4Record00469C61 const &); }
bool operator==(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);
bool operator<(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);

typedef _STL::list<BfmeFloat4Record00469C61> ListFloat4Record;

Xfer *xferList2069F0(Xfer *xfer, ListFloat4Record *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->operator==(reinterpret_cast<Xfer::Version &>(version));

	UnsignedInt count = list->size();
	xfer->operator==("std::list").operator==(count);

	if (xfer->IsStoring())
	{
		ListFloat4Record::_Node *sentinel = list->_M_node._M_data;
		ListFloat4Record::_Node *node = (ListFloat4Record::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			Rva00203DBEChain((Rva00203DBEA *)xfer, (void *)&node->_M_data);
			node = (ListFloat4Record::_Node *)node->_M_next;
		}
	}
	else
	{
		if (!list->empty())
		{
			throw XferException(4, "List must be empty on load");
		}

		BfmeFloat4Record00469C61 value;
		while (count != 0)
		{
			--count;
			Rva00203DBEChain((Rva00203DBEA *)xfer, &value);
			list->push_back(value);
		}
		--count;
	}
	return xfer;
}
