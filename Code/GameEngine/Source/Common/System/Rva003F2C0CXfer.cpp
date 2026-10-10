// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva003F2C0CXfer@@YAPAVXfer@@PAV1@PAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@@Z @0x003F2C0C (202B):
// Free Xfer vector<BfmeE8> helper version {1,1} via slot 0x28, size via slot
// 0x2C/0x78, isSaving via slot 0x08, saving walks 8B elements via slot 0x50,
// loading checks empty via FormatText 0x0060C36E plus Throw 0x00629094 then
// reserve 0x0030B876 plus push_back 0x00539A2E. Mirrors landed XferVectorBool
// 0x0060C253 and XferAsciiStringVector 0x0005A170. Caller 0x003F308C.
// Evidence: unlock lane, all callees rowed or pinned, unblocks 0x003F3054.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct BfmeE8 { int a; int b; };

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
	virtual void xferE8(BfmeE8 &value);
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


typedef _STL::vector<BfmeE8> VectorE8;

Xfer *Rva003F2C0CXfer(Xfer *xfer, VectorE8 *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = (UnsignedInt)vec->size();
	xfer->xferTypeName("std::vector").xferUnsignedShort(&count);

	if (xfer->isSaving()) {
		BfmeE8 *end = vec->end();
		BfmeE8 *cur = vec->begin();
		while (cur != end) {
			xfer->xferE8(*cur);
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		vec->reserve(count);
		BfmeE8 value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			xfer->xferE8(vec->back());
		}
	}
	return xfer;
}
