// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// ?DoXfer@LocomotorSet@@UAEXPAVXfer@@@Z, retail 0x001E8730, 413 bytes.
// Target identity: WorldBuilder names 0x005E8730 LocomotorSet::DoXfer in
// Locomotor.cpp (lines 3753-3765); its target body xfers the LocomotorSet
// vector and scalar fields. The BFME1 GeneralsMD donor calls this operation
// LocomotorSet::xfer and supplies the save/load order and error behavior.
// Target-specific: Version(1,2) and a trailing bool at object +0x15 are read
// from retail; the GeneralsMD layout ends at m_downhillOnly +0x14.
// Retail's call at 0x005E888E targets the 49-byte pointer-vector insertion
// helper at RVA 0x004DFCB0, already matched under vector<const ModuleData *>.
// The call uses the same 4-byte pointer reference ABI; the Locomotor* field
// identity and its three-pointer layout are established separately by target
// accesses at +0x04/+0x08/+0x0C.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN
#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Preserve the rowed growth helper's allocator call and inline cleanup.
class ModuleData;
namespace _STL { template <> const ModuleData **allocator<const ModuleData *>::allocate(size_t, const void *) const; }

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
typedef unsigned short UnsignedShort;
typedef bool Bool;

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}
	unsigned char m_current;
	unsigned char m_minimum;
};

class Locomotor : public Snapshot
{
public:
	virtual ~Locomotor();
	AsciiString getTemplateName() const;
};

class LocomotorTemplate;
class ModuleData;
class LocomotorStore
{
public:
	LocomotorTemplate *findLocomotorTemplate(int);
	Locomotor *newLocomotor(const LocomotorTemplate *, Bool);
};
extern LocomotorStore *TheLocomotorStore;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &);
};
extern NameKeyGenerator *TheNameKeyGenerator;


typedef std::vector<Locomotor *> LocomotorVector;
// This only names the already-matched generic pointer-vector insertion body.
typedef std::vector<const ModuleData *> ModuleDataPointerVector;
class LocomotorSet : public Snapshot
{
public:
	virtual void DoXfer(Xfer *xfer);

private:
	LocomotorVector m_locomotors;             // +0x04
	int m_validLocomotorSurfaces;             // +0x10
	Bool m_downhillOnly;                      // +0x14
	Bool m_targetVersionTwoFlag;              // +0x15
};

// Retail ThrowInfo names the 8-byte XferException class and its rowed
// copy constructor and destructor (see Common/System/XferException.cpp).
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

static __forceinline LocomotorTemplate *requireLocomotorTemplate(LocomotorTemplate *lt)
{
	if (lt == 0) {
		throw XferException(5, 0);
	}
	return lt;
}

void LocomotorSet::DoXfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	Locomotor **vectorState = reinterpret_cast<Locomotor **>(&m_locomotors);
	UnsignedShort count = static_cast<UnsignedShort>(vectorState[1] - vectorState[0]);
	*xfer == count;

	if (xfer->IsStoring()) {
		for (LocomotorVector::iterator it = m_locomotors.begin(); it != m_locomotors.end(); ++it) {
			Locomotor *loco = *it;
			AsciiString name = loco->getTemplateName();
			*xfer == name;
			*xfer == *loco;
		}
	} else {
		if (vectorState[0] != vectorState[1])
		{
			throw XferException(4, 0);
		}

		for (UnsignedShort i = 0; i < count; ++i) {
			AsciiString name;
			*xfer == name;
			LocomotorTemplate *lt = TheLocomotorStore->findLocomotorTemplate(
				TheNameKeyGenerator->nameToKey(name));
			Locomotor *loco = TheLocomotorStore->newLocomotor(
				requireLocomotorTemplate(lt), false);
			*xfer == *loco;
			reinterpret_cast<ModuleDataPointerVector *>(&m_locomotors)->push_back(
				*reinterpret_cast<const ModuleData * const *>(&loco));
		}
	}

	*xfer == m_validLocomotorSurfaces;
	*xfer == m_downhillOnly;
	if (version.m_minimum >= 2)
		*xfer == m_targetVersionTwoFlag;
}
