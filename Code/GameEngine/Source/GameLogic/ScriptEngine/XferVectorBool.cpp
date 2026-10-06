// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva0060C253Xfer@@YAPAVXfer@@PAV1@PAV?$vector@_NV?$allocator@_N@_STL@@@_STL@@@Z @0x0060C253 283B free vector<bool> Xfer helper version {1,1} via slot 0x28 size via slot 0x2C/0x78 isSaving via slot 0x08 saving walks bits via slot 0x90 loading checks empty via FormatText 0x0060C36E plus Throw 0x00629094 then reserve 0x0060C1C0 plus rowed push_back.
// Evidence: chain lane every callee rowed or pinned; skeleton mirrors landed XferListInt 0x00206861; caller 0x004EF0C3.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

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
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void xferBool(Bool *value);
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


typedef _STL::vector<bool> VectorBool;

struct XferHead
{
	XferVersion version;
	UnsignedInt count;
};

Xfer *Rva0060C253Xfer(Xfer *xfer, VectorBool *vec)
{
	XferHead head;
	head.version.m_version = 1;
	head.version.m_currentVersion = 1;
	xfer->xferVersion(&head.version);

	head.count = vec->size();
	xfer->xferTypeName("std::vector").xferUnsignedShort(&head.count);

	if (xfer->isSaving())
	{
		VectorBool::iterator last = vec->end();
		VectorBool::iterator first = vec->begin();
		for (; first != last; ++first)
		{
			Bool b = *first;
			xfer->xferBool(&b);
		}
	}
	else
	{
		if (!vec->empty())
		{
			throw XferException(4, "Vector must be empty on load");
		}

		vec->reserve(head.count);
		Bool value;
		while (head.count != 0)
		{
			--head.count;
			xfer->xferBool(&value);
			vec->push_back(value);
		}
	}
	return xfer;
}
