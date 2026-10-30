// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?addRevivableUnit@UnitRevivalTracker@@QAEXABURva002E2D10Record@@PAVPlayer@@@Z @0x0037F38F 15B
// Evidence: unlock lane; forwards member +4 vector push_back 0x002E2D10;
// ret 8 with an unused second slot: the Player, as in WorldBuilder's
// signature; caller 0x001EC8C0 and the callers in PlayerNewMapBFME2.cpp and
// ScriptActions_livingWorldRegion.cpp pass one.
class Xfer;
#include <vector>

class Player;

// The record is the rowed UnitRevivalEntry (copy ctor 0x002E134C); the
// address-derived name is only the parameter's view. The member vector is the
// tracker's UnitRevivalEntry vector, whose push_back is the rowed 0x002E2D10.
class UnitRevivalEntry
{
public:
    UnitRevivalEntry();
    UnitRevivalEntry(const UnitRevivalEntry &that);
    ~UnitRevivalEntry();
    UnitRevivalEntry &operator=(const UnitRevivalEntry &that);

private:
    char m_bytes[0xD8];
};
struct Rva002E2D10Record;

namespace _STL { template <> void vector<UnitRevivalEntry,allocator<UnitRevivalEntry> >::push_back(UnitRevivalEntry const &); }

class UnitRevivalTracker
{
public:
    void addRevivableUnit(const Rva002E2D10Record &item, Player *player);

protected:
    virtual void xfer(Xfer *xfer);

private:
    _STL::vector<UnitRevivalEntry> m_entries; // +0x04
    Player *m_player; // +0x10
};

void UnitRevivalTracker::addRevivableUnit(const Rva002E2D10Record &item, Player *)
{
    m_entries.push_back(reinterpret_cast<const UnitRevivalEntry &>(item));
}
