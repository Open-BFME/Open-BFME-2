// cl: /MD
// stlport
// ?rva004268F6@Rva004266A1@@QAEEH@Z @0x004268F6 30B
// Flag2 getter on the same 8-byte record vector at +4 as Rva004266A1::rva004266A1.
// Bounds check calls the rowed rva004266A1 then returns vec[index].flag2 (+6) else 0.
// Same recipe as Rva0042680DGetter (+5) differing only by verified offset.
#include <vector>
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct Rva004266A1Rec { AsciiString text; unsigned char flag0; unsigned char flag1; unsigned char flag2; };
struct Rva004266A1 { char pad[4]; _STL::vector<Rva004266A1Rec> vec; bool rva004266A1(int index); unsigned char rva004268F6(int index); };
unsigned char Rva004266A1::rva004268F6(int index)
{
    if (!rva004266A1(index))
        return 0;
    return vec[index].flag2;
}
