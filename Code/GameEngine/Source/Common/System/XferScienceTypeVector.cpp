// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00398280Xfer@@YAPAVXfer@@PAV1@PAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z @0x00398280 204B evidence: donor XferAsciiStringVector.cpp same xferVersion xferTypeName std-vector xferUnsignedInt isSaving shape; callees rowed XferObjectID 0x003060B2 reserve 0x002A1410 push_back 0x002E01C6 _bfmeFormatText 0x0060C36E plus pin _CxxThrowException 0x00629094; strings std-vector and Vector-must-be-empty-on-load; callers 0x00548AC2 0x003994C5.
// Free-function honest Rva name with Xfer verb; container ScienceType per rowed reserve/push_back rows; elements xferred via rowed XferObjectID with ObjectID cast (both 4B).
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

// Native 0x005334DB..0x005335B0 transfers four-byte records through the
// rowed 0x00531F79 helper, which transfers two adjacent unsigned shorts.
// The fields and their zero initialization are independently visible in
// this body and the rowed record append wrapper at 0x005335B0.
struct Rva005334A4Element
{
	unsigned short x;
	unsigned short y;
};

namespace _STL
{
template <> void vector<Rva005334A4Element, allocator<Rva005334A4Element> >::push_back(const Rva005334A4Element &);
}

class Rva00532844Vector
{
	Rva005334A4Element *start, *finish, *end;
public:
	void reserve(unsigned int n);
};

class Rva00531F79;
extern Rva00531F79 *Rva00531F79Chain(Rva00531F79 *, unsigned short *);

Xfer *Rva005334DBXfer(Xfer *xfer, void *storage)
{
	_STL::vector<Rva005334A4Element> *vec = static_cast<_STL::vector<Rva005334A4Element> *>(storage);
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);

	UnsignedInt count = (UnsignedInt)vec->size();
	xfer->xferTypeName("std::vector").xferUnsignedInt(count);

	if (xfer->isSaving()) {
		Rva005334A4Element *end = vec->end();
		Rva005334A4Element *cur = vec->begin();
		while (cur != end) {
			Rva00531F79Chain((Rva00531F79 *)xfer, (unsigned short *)cur);
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		((Rva00532844Vector *)vec)->reserve(count);
		Rva005334A4Element value;
		value.x = 0;
		value.y = 0;
		while (count != 0) {
			--count;
			vec->push_back(value);
			Rva00531F79Chain((Rva00531F79 *)xfer, (unsigned short *)&vec->back());
		}
	}
	return xfer;
}
