// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva0040E269Xfer@@YAPAVXfer@@PAV1@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z @0x0040E269 (202B):
// Free Xfer vector<const ModuleData*> helper version {1,1} via slot 0x28,
// size via slot 0x2C/0x78, isSaving via slot 0x08, saving walks pointer
// elements via slot 0x7C, loading checks empty via FormatText 0x0060C36E plus
// Throw 0x00629094 then reserve 0x002B712E plus push_back 0x004DFCB0.
// Mirrors landed Rva003F2C0CXfer 0x003F2C0C (same 202B, same recipe, element
// via slot 0x50 there). Element method name follows that precedent
// (element-type-derived, virtual so the gate does not resolve it).
// Evidence: unlock lane, strings "std::vector" and
// "Vector must be empty on load", all callees rowed or pinned.
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

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class ModuleData;

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
	virtual void xferModuleData(const ModuleData *&value);
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


typedef _STL::vector<const ModuleData *> ModuleDataPtrVector;

Xfer *Rva0040E269Xfer(Xfer *xfer, ModuleDataPtrVector *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = (UnsignedInt)vec->size();
	xfer->xferTypeName("std::vector").xferUnsignedShort(&count);

	if (xfer->isSaving()) {
		const ModuleData **end = vec->end();
		const ModuleData **cur = vec->begin();
		while (cur != end) {
			xfer->xferModuleData(*cur);
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		vec->reserve(count);
		const ModuleData *value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			xfer->xferModuleData(vec->back());
		}
	}
	return xfer;
}
