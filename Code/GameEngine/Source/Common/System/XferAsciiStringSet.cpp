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

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion &version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString &value);
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

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
	xfer->xferVersion(version);

	UnsignedInt count = set->size();
	xfer->xferTypeName("std::set").xferUnsignedInt(count);

	if (xfer->isSaving())
	{
		AsciiStringSet::iterator end = set->end();
		AsciiStringSet::iterator node = set->begin();
		while (node != end)
		{
			xfer->xferAsciiString(const_cast<AsciiString &>(*node));
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
			xfer->xferAsciiString(value);
			set->insert(value);
		}
	}
	return xfer;
}
