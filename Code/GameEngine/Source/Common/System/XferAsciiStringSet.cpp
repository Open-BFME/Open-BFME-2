// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00058DC6Xfer@@YAPAVXfer@@PAV1@PAV?$set@VAsciiString@@U?$less@VAsciiString@@@_STL@@V?$allocator@VAsciiString@@@3@@_STL@@@Z retail 0x00058DC6 231B
// Target evidence: native 0x00058DC6..0x00058EAD cdecl (RET 0) and its
// WorldBuilder debug twin 0x007B49F0: version {1 1} via slot 0x28, "std::set"
// (+0x2C) then the node count (+0x78); saving (+0x08) walks the tree nodes
// with _M_increment 0x00024250 and transfers each key through slot 0x6C;
// loading throws XferException(4 "Set must be empty on load") (ctor
// 0x0060C36E, _CxxThrowException) unless empty, then reads count strings and
// inserts each through the rowed set<AsciiString>::insert 0x0005897D; the
// value string is released through 0x00036410. The WB twin's named locals
// (version, count, end, node, value) give the declaration order.
// Donor structure: the matched set<int> transfers in XferSetDrawableID.cpp
// (0x000BC559); this is their AsciiString instantiation. Genuine STLport
// places the discarded insert result in the exception temporary's slot,
// which hand-made STL views did not. The free-function name is
// address-derived; the caller is MilesAudioManager::xfer 0x0005E3E5.
#include "ascii_string.h"
#include <set>

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> Lk6AsciiSetTree::iterator Lk6AsciiSetTree::insert_unique(Lk6AsciiSetTree::iterator, const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
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

#include "../../../Include/Common/XferException.h"

// Retail's tree node construction calls the out-of-line copy 0x0002C485.
namespace _STL {
template <> void _Construct<AsciiString, AsciiString>(AsciiString *, const AsciiString &);
}

typedef _STL::set<AsciiString> AsciiStringSet;

Xfer *Rva00058DC6Xfer(Xfer *xfer, AsciiStringSet *set)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	UnsignedInt count = set->size();
	(*xfer == "std::set") == count;

	if (xfer->IsStoring())
	{
		AsciiStringSet::iterator end = set->end();
		AsciiStringSet::iterator node = set->begin();
		while (node != end)
		{
			*xfer == const_cast<AsciiString &>(*node);
			++node;
		}
	}
	else
	{
		if (!set->empty())
		{
			throw XferException(4, "Set must be empty on load");
		}

		AsciiString value;
		while (count--)
		{
			*xfer == value;
			set->insert(value);
		}
	}
	return xfer;
}
