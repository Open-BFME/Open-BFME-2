// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?xferAsciiStringVector@@YAPAVXfer@@PAV1@PAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z retail 0x0005A170 241B
// Evidence: unlock lane; donor is the rowed XferUnicodeStringVector.cpp 0x0005CD41
// (same 241B shape); callees rowed reserve 0x00057E02 plus pin push_back
// 0x0002DBE6 plus releaseBuffer 0x00036410 plus _bfmeFormatText 0x0060C36E
// plus pin _CxxThrowException 0x00629094; strings "std::vector" and
// "Vector must be empty on load"; callers 0x0005E934 0x002CED3F 0x0049FD94
// 0x004E3A02.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "ascii_string.h"


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


namespace _STL {
template <> void _Construct<AsciiString, AsciiString>(AsciiString *, const AsciiString &);
}

typedef _STL::vector<AsciiString> AsciiStringVector;

Xfer *xferAsciiStringVector(Xfer *xfer, AsciiStringVector *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);

	UnsignedInt count = (UnsignedInt)vec->size();
	xfer->xferTypeName("std::vector").xferUnsignedInt(count);

	if (xfer->isSaving()) {
		AsciiString *end = vec->end();
		AsciiString *cur = vec->begin();
		while (cur != end) {
			xfer->xferAsciiString(*cur);
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		vec->reserve(count);
		AsciiString value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			xfer->xferAsciiString(vec->back());
		}
		--count;
	}
	return xfer;
}
