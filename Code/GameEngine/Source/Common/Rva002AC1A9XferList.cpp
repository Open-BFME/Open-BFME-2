// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva002AC1A9XferList@@YAPAVXfer@@PAV1@PAV?$list@FV?$allocator@F@_STL@@@_STL@@@Z @0x002AC1A9 200B: free list<short> Xfer helper version {1 1} via slot 0x28 size via slot 0x2C/0x78 IsSaving via slot 0x08 saving walks shorts via slot 0x80 loading checks empty via FormatText 0x0060C36E plus Throw 0x00629094 then reloads via slot 0x80 plus rowed push_back 0x002AC00C.
// Evidence: leaf lane every callee rowed or pinned; same skeleton as rowed xferListInt 0x00206861 194B and Rva00460216XferList 0x00460216 194B; count via 0x78 saving element via 0x80; caller 0x002B203B; prev Rva002AC04EAlloc next Rva002AC340Ctor.
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
	virtual Xfer &xferVersion(XferVersion *version);
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
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedShort(UnsignedInt *value);
	virtual Xfer &xferInt(int *value);
	virtual Xfer &xferShort(short *value);
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

typedef _STL::list<short> ListShort;

Xfer *Rva002AC1A9XferList(Xfer *xfer, ListShort *list)
{
	UnsignedInt count;
	union
	{
		XferVersion version;
		int versionPad;
	};
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	count = list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		ListShort::_Node *sentinel = list->_M_node._M_data;
		ListShort::_Node *node = (ListShort::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			xfer->xferShort(&node->_M_data);
			node = (ListShort::_Node *)node->_M_next;
		}
	}
	else
	{
		if (!list->empty())
		{
			throw XferException(4, "List must be empty on load");
		}

		short value;
		while (count != 0)
		{
			--count;
			xfer->xferShort(&value);
			list->push_back(value);
		}
	}
	return xfer;
}
