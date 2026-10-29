// ?Rva0046EFDBXfer@@YAPAVXfer@@PAV1@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z
// partial score=0.90 date=2026-09-30
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
// ?Rva0046EFDBXfer@@YAPAVXfer@@PAV1@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z @0x0046EFDB 202B
// Xfer helper for vector<const ModuleData*> with version {1,1} via slot 0x28 size via slot 0x2C/0x78 isSaving via slot 0x08 per-element via slot 0x70 reserve 0x002B712E push_back 0x004DFCB0 FormatText 0x0060C36E Throw 0x00629094 strings "std::vector" "Vector must be empty on load" caller 0x00475632.
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

class ModuleData;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../Include/Common/BfmeXfer.h"

// Retail ThrowInfo names the 8-byte XferException class and its rowed
// copy constructor and destructor (see System/XferException.cpp).
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};


typedef _STL::vector<const ModuleData *> ModuleDataVector;

Xfer *Rva0046EFDBXfer(Xfer *xfer, ModuleDataVector *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == (Xfer::Version &)version;

	UnsignedInt count = vec->size();
	xfer->operator==("std::vector").operator==(count);

	if (xfer->IsStoring()) {
		ModuleDataVector::iterator last = vec->end();
		ModuleDataVector::iterator first = vec->begin();
		for (; first != last; ++first)
			*xfer == (float &)((const ModuleData *&)*first);
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		vec->reserve(count);
		while (count != 0) {
			--count;
			const ModuleData *moduleData;
			vec->push_back(moduleData);
			*xfer == (float &)vec->back();
		}
	}
	return xfer;
}
