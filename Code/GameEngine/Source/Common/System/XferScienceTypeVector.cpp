// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00398280Xfer@@YAPAVXfer@@PAV1@PAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z @0x00398280 204B evidence: donor XferAsciiStringVector.cpp same xferVersion xferTypeName std-vector xferUnsignedInt isSaving shape; callees rowed XferObjectID 0x003060B2 reserve 0x002A1410 push_back 0x002E01C6 _bfmeFormatText 0x0060C36E plus pin _CxxThrowException 0x00629094; strings std-vector and Vector-must-be-empty-on-load; callers 0x00548AC2 0x003994C5.
// Free-function honest Rva name with Xfer verb; container ScienceType per rowed reserve/push_back rows; elements xferred via rowed XferObjectID with ObjectID cast (both 4B).
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

enum ScienceType
{
	SCIENCE_0 = 0
};

enum ObjectID
{
	OBJECTID_0 = 0
};

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


extern void __cdecl XferObjectID(Xfer *xfer, enum ObjectID *id);

typedef _STL::vector<ScienceType> ScienceTypeVector;

Xfer *Rva00398280Xfer(Xfer *xfer, ScienceTypeVector *vec)
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
			XferObjectID(xfer, (ObjectID *)cur);
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
			XferObjectID(xfer, (ObjectID *)&vec->back());
		}
	}
	return xfer;
}

// Target [0x003F5A72,0x003F5B3E) is a complete cdecl vector transfer.
// Version {1,1}, 4-byte element stride, count, reserve/push-back and both
// element calls are independently read from retail. The calls reach the
// rowed LivingWorldPlayerID helper at 0x002034C4. The existing ScienceType
// vector is a compiler ABI view of the measured 12-byte vector and 4-byte
// elements here; the original container type and function spelling are unknown.
// Source guide: the verified 0x00398280 vector-transfer implementation above.
extern void __cdecl XferLivingWorldPlayerID(Xfer *xfer, int *id);

Xfer *Rva003F5A72Xfer(Xfer *xfer, void *storage)
{
	ScienceTypeVector *vec = static_cast<ScienceTypeVector *>(storage);
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
			XferLivingWorldPlayerID(xfer, (int *)cur);
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
			XferLivingWorldPlayerID(xfer, (int *)&vec->back());
		}
	}
	return xfer;
}

// Native [0x001ECA2D,0x001ECAF9), complete 204-byte cdecl transfer.
// Independently measured slots/count/stride/reserve/push-back match the guide
// above. Both element calls reach 0x00306232, whose verified ScienceType
// label and ScienceStore name roundtrip establish this vector's element kind.
// The entry uses an address-derived spelling; its original name is unknown.
extern Xfer *Rva00306232XferScience(Xfer *xfer, ScienceType *science);

Xfer *Rva001ECA2DXfer(Xfer *xfer, void *storage)
{
	ScienceTypeVector *vec = static_cast<ScienceTypeVector *>(storage);
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
			Rva00306232XferScience(xfer, cur);
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
			Rva00306232XferScience(xfer, &vec->back());
		}
	}
	return xfer;
}
