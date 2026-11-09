// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/moduledata /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// LivingWorldRegionConnection copy ctor.
//
// ??0LivingWorldRegionConnection@@QAE@ABV0@@Z (retail 0x003F247D, 83
// bytes): installs the vtable at 0x00C36E48, copies the region name
// through the pinned StringBase<char> copy at 0x000365F0, copies the
// count word, then copies the detour-point vector through the 0x004334D7
// helper. Two EH states (string, then vector) exactly as retail. Serves
// the vector push/grow path (0x003F309A/0x003F2B0B) which builds new
// elements through the 0x003F2980 construct helper below.
//
// The vector<BfmeE8> helpers this unit emits use retail's raw allocator
// (bfmealloc: deallocate is a direct _free at 0x00030830), as every other
// BfmeE8 unit's copies and the rowed copy constructor at 0x004334D7 do.

#include <vector>

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "Common/Snapshot.h"

class Xfer;

#include "ascii_string.h"


struct BfmeE8
{
	float x;
	float y;
};

class LivingWorldRegionConnection : public Snapshot
{
public:
	LivingWorldRegionConnection(const LivingWorldRegionConnection &that);
	virtual ~LivingWorldRegionConnection();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);

private:
	AsciiString m_regionName; // +0x04
	int m_numberAllowed; // +0x08
	_STL::vector<BfmeE8> m_detourPoints; // +0x0C
};

typedef char LivingWorldRegionConnectionSizeCheck[sizeof(LivingWorldRegionConnection) == 0x18 ? 1 : -1];

// ??0LivingWorldRegionConnection@@QAE@ABV0@@Z @0x3F247D
LivingWorldRegionConnection::LivingWorldRegionConnection(const LivingWorldRegionConnection &that)
	: m_regionName(that.m_regionName), m_numberAllowed(that.m_numberAllowed), m_detourPoints(that.m_detourPoints)
{
}
