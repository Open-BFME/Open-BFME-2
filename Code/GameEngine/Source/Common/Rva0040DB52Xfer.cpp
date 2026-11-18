// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?xfer@Rva0040DB52@@MAEXPAVXfer@@@Z retail 0x0040E6F6 132B
// Slot 3 xfer of Rva0040DB52 (vtable 0x008394CC): version {1,1} then +0x04 +0x0c(bool) +0x10(ModuleData) then isLoading erase of ScienceType vec at +0x14 and ptr vec at +0x20 then vector helpers.
// Evidence: chain lane calls 0x0040E269 now ready, vslot slot 3, callees erase ScienceType 0x00532803 erase voidptr 0x0031BD55 helpers 0x003F2394 0x0040E269 rowed.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "../../Include/Common/ScalarTypes.h"



class ModuleData;
enum ScienceType
{
	SCIENCE_INVALID = -1,
	SCIENCE_0 = 0
};

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
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"

#include "Common/Snapshot.h"

// vector<void*> begin/end/clear are expanded inline here; their out-of-line copies
// would differ from retail's. Declared imported and force-inlined, they are not emitted.
namespace _STL {
template <> void **vector<void *>::erase(void **first, void **last);
template <> ScienceType *vector<ScienceType>::erase(ScienceType *first, ScienceType *last);
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
void vector<void *>::clear() { erase(begin(), end()); }
}

Xfer *Rva003F2394Xfer(Xfer *xfer, _STL::vector<ScienceType> *vec);
Xfer *Rva0040E269Xfer(Xfer *xfer, _STL::vector<const ModuleData *> *vec);

class Rva0040DB52 : public Snapshot
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_04;
	char m_pad08[4];
	Bool m_0C;
	char m_pad0D[3];
	const ModuleData *m_10;
	_STL::vector<ScienceType> m_vec14;
	_STL::vector<void *> m_vec20;
};

void Rva0040DB52::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	(*xfer == reinterpret_cast<Xfer::Version &>(version));
	(*xfer == reinterpret_cast<Coord2D &>(m_04));
	(*xfer == m_0C);
	(*xfer == reinterpret_cast<int &>(m_10));
	if (xfer->IsLoading()) {
		m_vec14.clear();
		m_vec20.clear();
	}
	Rva003F2394Xfer(xfer, &m_vec14);
	Rva0040E269Xfer(xfer, reinterpret_cast<_STL::vector<const ModuleData *> *>(&m_vec20));
}
