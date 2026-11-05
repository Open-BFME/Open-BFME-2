// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva002B8DFC@Rva002BA8F1Logic@@QAEXPAVXfer@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z
// Player-id sibling of rva002B8D06 (same skeleton, same erase/reserve/push_back callees): ids go through the
// rowed XferLivingWorldPlayerID 0x002034C4 and resolve through the rowed find 0x002B51F8; the saved id is read at +0x14 of each entry.
// Evidence: retail frame and callees read at the REL32s; skeleton from the rowed rva002B8D06.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

typedef unsigned char UnsignedByte;
typedef bool Bool;


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

#include "../../../../GameEngine/Include/Common/BfmeXfer.h"
class Xfer::Version
{ public:
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class ModuleData;

namespace _STL {
template<> void vector<const ModuleData *>::reserve(unsigned int);
}
#include "../../../../GameEngine/Include/Common/ModuleData.h"

// Opaque record offsets; keep the canonical ModuleData pointer in the ABI.
struct Rva002B8DFCRecordView
{
	char m_pad[0x14];
	int m_playerID;
};

class Rva002E2903Player;

#include "../../../../GameEngine/Include/GameLogic/Rva002BA8F1Logic.h"

void XferLivingWorldPlayerID(Xfer *xfer, int *value);

void Rva002BA8F1Logic::rva002B8DFC(Xfer *xfer, _STL::vector<const ModuleData *> *vec)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	(*xfer == version);

	if (xfer->IsLoading()) {
		int count;
		(*xfer == count);
		((_STL::vector<void *> *)vec)->erase(((_STL::vector<void *> *)vec)->begin(), ((_STL::vector<void *> *)vec)->end());
		vec->reserve(count);
		for (int i = 0; i < count; ++i) {
			int armyID;
			XferLivingWorldPlayerID(xfer, &armyID);
			const ModuleData *found = (const ModuleData *)find(armyID, 0);
			if (found != 0) {
				vec->push_back(found);
			}
		}
	} else {
		int count = (int)vec->size();
		(*xfer == count);
		for (int i = 0; i < count; ++i) {
			int armyID = reinterpret_cast<const Rva002B8DFCRecordView *>((*vec)[i])->m_playerID;
			XferLivingWorldPlayerID(xfer, &armyID);
		}
	}
}
