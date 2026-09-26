// cl: /DNDEBUG /MD -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader
// BFME1 donor at 0x00825D80; the BFME1 body was ICF-folded across four names.
// Target owner remains address-named because BFME2 evidence does not select one alias.
// Retail clears 137 dwords through the owner pointer at 0x006918B0.
#include <string.h>

struct Rva006918B0Owner
{
    unsigned short *m_counters;
    void clearStats();
};

void Rva006918B0Owner::clearStats()
{
    memset(m_counters, 0, 274 * sizeof(unsigned short));
}
