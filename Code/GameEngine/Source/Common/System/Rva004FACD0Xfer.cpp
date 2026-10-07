// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva004FACD0Xfer@@YAPAVXfer@@PAV1@PAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z @0x004FACD0 204B evidence: same 204B shape as rowed XferScienceTypeVector 0x00398280 same xferVersion xferTypeName std-vector xferUnsignedInt isSaving; callees rowed Rva004E12D7Parse 0x004E12D7 reserve 0x002A1410 push_back 0x002E01C6 _bfmeFormatText 0x0060C36E plus pin _CxxThrowException 0x00629094; strings std-vector and Vector-must-be-empty-on-load; caller 0x004FAF73.
// Free-function honest Rva name with Xfer verb; container ScienceType per rowed reserve/push_back rows; elements via rowed Rva004E12D7Parse.
// Use the existing retail max<unsigned int> provider at 0x13740.
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ScienceType
{
	SCIENCE_0 = 0
};
// The same ScienceType vector's native overflow is rowed at 0x148D00.
namespace _STL {
template <> void vector<ScienceType, allocator<ScienceType> >::_M_insert_overflow(
    ScienceType *, const ScienceType &, const __false_type &, unsigned int, bool);
template <> void vector<ScienceType, allocator<ScienceType> >::push_back(const ScienceType &);
}

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
	virtual void xferAsciiString(void *value);
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


extern void __cdecl Rva004E12D7Parse(void *ini, void *dest);

typedef _STL::vector<ScienceType> ScienceTypeVector;

Xfer *Rva004FACD0Xfer(Xfer *xfer, ScienceTypeVector *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);

	UnsignedInt count = (UnsignedInt)vec->size();
	xfer->xferTypeName("std::vector").xferUnsignedInt(count);

	if (xfer->isSaving()) {
		ScienceType *end = vec->end();
		ScienceType *cur = vec->begin();
		while (cur != end) {
			Rva004E12D7Parse(xfer, cur);
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		vec->reserve(count);
		ScienceType value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			Rva004E12D7Parse(xfer, &vec->back());
		}
	}
	return xfer;
}
