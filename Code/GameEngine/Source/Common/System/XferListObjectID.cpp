// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
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
};

enum ObjectID
{
	INVALID_ID = 0
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


void XferObjectID(Xfer *xfer, ObjectID *objectID);

typedef _STL::list<int> ListInt;

Xfer *Rva0036ABAFXfer(Xfer *xfer, ListInt *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving())
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
