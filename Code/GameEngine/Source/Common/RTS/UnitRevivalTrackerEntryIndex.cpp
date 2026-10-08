// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP=
// WB F60ED0 is the unnamed tracker lookup called by ProductionUpdate's
// named GetEntryToProcess (1203E30). Native37EE4C..37EEB9 is complete109B,
// ret12. Existing AIBuildableUnit callers pass ThingTemplate pointers to the
// established pinned ABI. The name at +64 is compared with each 216-byte
// entry's +D4 string; +A4 is the production ID. A -1 filter selects the
// Nth matching name, otherwise the ID selects the entry. Return -1 on miss.
// These offsets and both independent counters are target facts. The helper's
// original name remains unknown; the existing address-derived owner is kept.
// Canonical string contract plus separate filter branches reproduces the
// native flags directly; incrementing index before pointer matches the loop.
// BF1 ba7ddda UnitRevivalTracker.cpp recovers a different 96-byte record path;
// no same-body donor found. Direct field access avoids a competing getter.
#include "ascii_string.h"

class ThingTemplate
{
public:
    char unknown00[0x64];
    AsciiString name;
};

struct RevivalIndexEntry
{
    char unknown00[0xA4];
    int productionID;
    char unknownA8[0x2C];
    AsciiString name;
};

class Rva0037EE4C
{
public:
    int rva0037EE4C(const ThingTemplate *, int, int);
    void *unknown00;
    RevivalIndexEntry *begin, *end;
};

int Rva0037EE4C::rva0037EE4C(const ThingTemplate *key, int filter, int wanted)
{
    int index = 0, matching = 0;
    for (RevivalIndexEntry *entry = begin; entry != end; ++index, ++entry)
    {
        if (entry->name == key->name)
        {
            if (filter == -1)
            {
                if (matching == wanted)
                    return index;
            }
            else
            {
                if (filter == entry->productionID)
                    return index;
            }
            ++matching;
        }
    }
    return -1;
}
