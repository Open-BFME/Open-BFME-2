// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Served native 129-byte body 0x565085..0x565106: iterate 12-byte records
// at +0x2C/+0x30; look up a named owner, resolve its region, then forward both
// with literal one to the already rowed 0x2B2702. All three callees are rowed.
// Class and method names are WorldBuilder's (LivingWorldCampaignAct::MoveArmies).
// Native argument addresses prove four-byte AsciiString fields at +4/+8.
#include "ascii_string.h"

struct Rva002E1948Entry;
class Rva002B48E1
{
public:
    Rva002E1948Entry *rva002B48E1(const AsciiString &name);
};
class Rva002104B6
{
public:
    void *rva002104B6(void *name);
};
class Rva002B2702
{
public:
    void rva002B2702(void *owner, void *region, int extra);
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva00565085LogicView
{
    unsigned char prefix[0xB0];
    Rva002104B6 *regions;
};

struct Rva00565085Record
{
    int unknown;
    AsciiString ownerName;
    AsciiString regionName;
};

struct Rva00565085Vector
{
    // ?Rva00565085Vector::size absent-from-retail
    unsigned size() const { return end - begin; }
    // ?Rva00565085Vector::operator[] absent-from-retail
    Rva00565085Record &operator[](unsigned index) const { return begin[index]; }
    Rva00565085Record *begin;
    Rva00565085Record *end;
    Rva00565085Record *storage;
};

class LivingWorldCampaignAct
{
public:
    void MoveArmies();
private:
    unsigned char prefix[0x2C];
    Rva00565085Vector records;
};

// ?MoveArmies@LivingWorldCampaignAct@@QAEXXZ
void LivingWorldCampaignAct::MoveArmies()
{
    for (unsigned i = 0; i < records.size(); ++i)
    {
        Rva00565085Record *record = &records[i];
        Rva002E1948Entry *owner = reinterpret_cast<Rva002B48E1 *>(
            TheLivingWorldLogic)->rva002B48E1(record->ownerName);
        if (owner)
        {
            void *region = reinterpret_cast<Rva00565085LogicView *>(
                TheLivingWorldLogic)->regions->rva002104B6(&record->regionName);
            if (region)
                reinterpret_cast<Rva002B2702 *>(TheLivingWorldLogic)->
                    rva002B2702(owner, region, 1);
        }
    }
}
