// cl: /O1 /Oi /G7 /arch:SSE /EHs /MD /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// BFME1 donor874e38488 SidesListCtorThunk.cpp supplies the constructor
// structure; retail32EE24..32EF22 independently establishes BFME2 offsets,
// arrays20 of60B, 28B teams and 28B auxiliary records. Snapshot and subsystem
// base layouts agree with existing target xfer/clear/copy bodies.
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <map>
#include <list>
#include "ascii_string.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../Libraries/Include/Lib/BfmeE16.h"
// Storage deallocation cannot throw; keep the STLport cleanup inline.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline _Vector_base<BfmeE16, allocator<BfmeE16> >::~_Vector_base()
{ if (this->_M_start != 0) this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); }
template <> __declspec(dllimport) __forceinline vector<BfmeE16, allocator<BfmeE16> >::~vector()
{ _Destroy(this->_M_start, this->_M_finish); }
}
// Suppress this TU's non-retail copy of ??$_Destroy@PAUBfmePod128@@@_STL@@YAXPAUBfmePod128@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod128;
namespace _STL { template <> void _Destroy<BfmePod128 *>(BfmePod128 *,BfmePod128 *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAUBfmePod128@@@_STL@@YAXPAUBfmePod128@@0ABU__false_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod128;
namespace _STL { template <> void __destroy_aux<BfmePod128 *>(BfmePod128 *,BfmePod128 *,__false_type const &); }
#include "../../../Include/Common/Rva00330757Member.h"

__forceinline Rva00330757Member::~Rva00330757Member()
{
    if (field00) free(field00);
}
struct BfmePod128 { ~BfmePod128(); int a[32]; };
struct BfmeE8 { int a[2]; };
class SidesInfo {
public:
    SidesInfo();
    ~SidesInfo();
private:
    char m_data[0x60];
};
class TeamsInfoRec {
public:
    TeamsInfoRec();
    ~TeamsInfoRec();
private:
    char m_data[0x1C];
};
class Rva001976F0 {
public:
    Rva001976F0();
    ~Rva001976F0();
private:
    int m_key;
    _STL::vector<BfmePod128> m_first;
    _STL::vector<BfmePod128> m_second;
};
class SidesList : public SubsystemInterface, public Snapshot, public Rva00330757Member {
public:
    SidesList();
    virtual ~SidesList();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void DoXfer(Xfer *);
    void clear();
private:
    _STL::list<AsciiString> m_list;
    _STL::map<int,_STL::vector<BfmePod128> > m_castleBuildLists;
    _STL::map<int,_STL::vector<_STL::vector<BfmeE8> > > m_castlePaths;
    int m_numSides;
    SidesInfo m_sides[20];
    int m_numSkirmishSides;
    SidesInfo m_skirmishSides[20];
    TeamsInfoRec m_teams;
    TeamsInfoRec m_skirmishTeams;
    bool m_cleared;
    Rva001976F0 m_extra[20];
};
typedef char SidesListSize[sizeof(SidesList)==0x11B0?1:-1];
// Native secondary Snapshot table C0DA88 slot 1 holds the shared empty
// post-load hook at 4B3FD0; the slot takes no arguments and accesses no state.
void SidesList::LoadPostProcess() {}

SidesList::SidesList() : m_numSides(0),m_numSkirmishSides(0),m_cleared(true)
{
    clear();
}

// The auxiliary record constructor is the typed twin of the rowed 32C19D.
Rva001976F0::Rva001976F0() {}

// Retail posts the slot-zero member callback with the complete SidesList owner.
class Rva00281A15Listener { public: virtual void notify(void *); };
#include "../../../Include/Common/SidesListNotifier.h"
void SidesListNotifier::post(void (Rva00281A15Listener::*callback)(void *), void *owner)
{
    // The retail callback record stores the four-byte member-pointer representation.
    Post p;
    memcpy(&p.callback, &callback, sizeof(p.callback));
    p.owner=owner;
    dispatch(&p);
}
// ?SidesList::~SidesList present-unmatched
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline SidesList::~SidesList()
{
    reinterpret_cast<SidesListNotifier *>(static_cast<Rva00330757Member *>(this))->post(&Rva00281A15Listener::notify, this);
}

// ?bfmeAnchorSidesListDtor absent-from-retail
void bfmeAnchorSidesListDtor(SidesList *sidesList)
{
	sidesList->SidesList::~SidesList();
}

// Native 0x0077B9F6 is the complete 11-byte list-member cleanup at +0x20.
// The exact 240-byte destructor and complete EH graph bind this action to
// the existing STLport list<AsciiString> destructor at 0x00207F08.

// Native SidesList action 0x77ba01 is a complete 11-byte map-member cleanup
// of parent 0x32ec63; the exact parent and EH graph bind its
// standard template destructor through the independently proved wrapper fold.

// Native SidesList action 0x77ba0c is a complete 11-byte map-member cleanup
// of parent 0x32ec63; the exact parent and EH graph bind its
// standard template destructor through the independently proved wrapper fold.

// Native SidesList action 0x77bace is a complete 11-byte map-member cleanup
// of parent 0x32ee24; the exact parent and EH graph bind its
// standard template destructor through the independently proved wrapper fold.

// Native SidesList action 0x77bad9 is a complete 11-byte map-member cleanup
// of parent 0x32ee24; the exact parent and EH graph bind its
// standard template destructor through the independently proved wrapper fold.

// Native 0x0077BAC3 is the complete 11-byte constructor list-member action.
// The whole 254-byte parent and its exact EH graph bind the +0x20 lifetime
// and existing list destructor; the next actual action starts at 0x0077BACE.

// Native SidesList action 0x77b9ce is the complete 20-byte C++
// lifetime action of parent 0x32ec63, bound by the whole native
// exception graph; its separately retired assembly copy is no longer needed.

// Native SidesList action 0x77ba17 is the complete 22-byte C++
// lifetime action of parent 0x32ec63, bound by the whole native
// exception graph; its separately retired assembly copy is no longer needed.

// Native SidesList action 0x77bae4 is the complete 22-byte C++
// lifetime action of parent 0x32ee24, bound by the whole native
// exception graph; its separately retired assembly copy is no longer needed.
