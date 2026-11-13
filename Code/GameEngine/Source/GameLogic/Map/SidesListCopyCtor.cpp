// ??0SidesList@@QAE@ABV0@@Z, retail 0x0032EF3E (364 B), EH EXACT.
// BFME2 SidesList copy constructor, byte-verified against retail. The class
// model follows the canonical SidesList view in SidesListCtor.cpp (base order
// SubsystemInterface, Snapshot, Rva00330757Member) and the BFME2 offsets retail
// proves: notifier subobject +0x10, list/maps +0x20/+0x24/+0x30, counts and
// SidesInfo arrays +0x3C/+0x40/+0x7C0/+0x7C4, TeamsInfoRec +0xF44/+0xF60,
// cleared byte +0xF7C and the 20 28-byte FactionBuildLists records at +0xF80.
// The array copies call the rowed std::copy providers (SidesInfo 0x32E8F9,
// SidesList::FactionBuildLists 0x32DD66) and the map constructors the rowed
// STLport instantiations at 0x413727.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
//
// Target-side copy layout for SidesList. The donor SidesList.h establishes the
// SubsystemInterface/Snapshot bases; retail 0x0032EF3E then proves the BFME2
// offsets: notifier subobject +0x10, list/maps +0x20/+0x24/+0x30, counts and
// SidesInfo arrays +0x3C/+0x40/+0x7C0/+0x7C4, TeamsInfoRec +0xF44/+0xF60,
// cleared byte +0xF7C, and the 20 28-byte records at +0xF80. The latter's
// two vector assignments call the rowed 128-byte vector operator= at 0x32C0E3.
// The donor class identity is supported by the base, matching SidesList method
// call sites, the two target vtables and the target member offsets. Extra-field
// semantics beyond the vector control blocks remain address-derived.

#include <algorithm>
#include <vector>
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include <map>
#include <list>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> void _List_base<AsciiString, allocator<AsciiString> >::clear(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$copy@PAVSidesInfo@@PAV1@@_STL@@YAPAVSidesInfo@@PAV1@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class SidesInfo;
namespace _STL { template <> SidesInfo * copy<SidesInfo *,SidesInfo *>(SidesInfo *,SidesInfo *,SidesInfo *); }
// Suppress this TU's non-retail copy of ??4?$vector@URva0032C0E3Element@@V?$allocator@URva0032C0E3Element@@@_STL@@@_STL@@QAEAAV01@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0032C0E3Element;
namespace _STL { template <> vector<Rva0032C0E3Element,allocator<Rva0032C0E3Element> > & vector<Rva0032C0E3Element,allocator<Rva0032C0E3Element> >::operator=(vector<Rva0032C0E3Element,allocator<Rva0032C0E3Element> > const &); }
// Suppress this TU's non-retail copy of ??1?$vector@UBfmePod128@@V?$allocator@UBfmePod128@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod128;
namespace _STL { template <> vector<BfmePod128, allocator<BfmePod128> >::~vector(); }
struct BfmePod128 { ~BfmePod128(); int a[32]; };
struct BfmeE8 { int a[2]; };
typedef _STL::map<int, _STL::vector<BfmePod128> > MapType0032EF3E;
typedef _STL::map<int, _STL::vector<_STL::vector<BfmeE8> > > MapType0032EF3E_B;

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

#include "../../../Include/Common/Rva00330757Member.h"
#include "../../../Include/Common/SidesListNotifier.h"

typedef MapType0032EF3E Rva0032D3D3Map;
typedef MapType0032EF3E_B Rva0032EAA1Map;

class SidesInfo
{
public:
	SidesInfo();
	SidesInfo(const SidesInfo &that);
	~SidesInfo();
	SidesInfo &operator=(const SidesInfo &that);

private:
	char m_body[0x60];
};

class TeamsInfoRec
{
public:
	TeamsInfoRec();
	TeamsInfoRec(const TeamsInfoRec &that);
	~TeamsInfoRec();
	void clear();

private:
	_STL::map<_STL::pair<AsciiString, AsciiString>, int> m_index;
	char m_pad0c[0x1C - 0x0C];	// +0x0C entry vector and two shorts, unused here
};

#include "../../../Include/GameLogic/Rva0032C0E3Element.h"
// POD cleanup stays inline, as in SidesListCopyCtors.cpp, so this unit does
// not compete with the rowed nontrivial destroy worker at 0x32B580.
namespace _STL {
template <> __declspec(dllimport) __forceinline void _Destroy(
    Rva0032C0E3Element *, Rva0032C0E3Element *) {}
}

class SidesList : public SubsystemInterface, public Snapshot, public SidesListNotifier
{
public:
	struct FactionBuildLists
	{
		int m_value;
		_STL::vector<Rva0032C0E3Element> m_first;
		_STL::vector<Rva0032C0E3Element> m_second;
	};
public:
	SidesList(const SidesList &that);
	virtual ~SidesList();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *xfer);

private:
	_STL::list<AsciiString> m_list;				// +0x20
	Rva0032D3D3Map m_map1;					// +0x24
	Rva0032EAA1Map m_map2;					// +0x30
	int m_numSides;							// +0x3C
	SidesInfo m_sides[20];					// +0x40
	int m_numSkirmishSides;					// +0x7C0
	SidesInfo m_skirmishSides[20];			// +0x7C4
	TeamsInfoRec m_teamrec;				// +0xF44
	TeamsInfoRec m_skirmishTeamrec;		// +0xF60
	bool m_cleared;							// +0xF7C
	char m_pad[3];
	FactionBuildLists m_extra[20];				// +0xF80
};

// Retail's copy<FactionBuildLists *> is the rowed range forwarder at 0x32DD66.
struct Rva0032DD66Input;
struct Rva0032DD66Output;
Rva0032DD66Output *__cdecl Rva0032DD66RangeForward(Rva0032DD66Input *first, Rva0032DD66Input *last, Rva0032DD66Output *result);

SidesList::SidesList(const SidesList &that)
	: SubsystemInterface(that),
	  SidesListNotifier(that),
	  m_list(),
	  m_map1(),
	  m_map2(),
	  m_numSides(that.m_numSides),
	  m_numSkirmishSides(that.m_numSkirmishSides),
	  m_teamrec(that.m_teamrec),
	  m_skirmishTeamrec(that.m_skirmishTeamrec),
	  m_cleared(that.m_cleared)
{
	std::copy(const_cast<SidesInfo *>(that.m_sides), const_cast<SidesInfo *>(that.m_sides) + that.m_numSides, m_sides);
	std::copy(const_cast<SidesInfo *>(that.m_skirmishSides), const_cast<SidesInfo *>(that.m_skirmishSides) + that.m_numSkirmishSides, m_skirmishSides);
	Rva0032DD66RangeForward(reinterpret_cast<Rva0032DD66Input *>(const_cast<FactionBuildLists *>(that.m_extra)), reinterpret_cast<Rva0032DD66Input *>(const_cast<FactionBuildLists *>(that.m_extra) + 20), reinterpret_cast<Rva0032DD66Output *>(m_extra));
}
