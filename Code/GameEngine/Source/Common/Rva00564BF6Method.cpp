// ?rva00564BF6@Rva00564BF6@@QAE?AUBfmePairWI@@XZ
// cl: /O1 /arch:SSE /G7 /MD /EHsc
// WB1439E70 constructs a returned aggregate through a hidden buffer.
// Native caller564EC0 constructs one result directly in its outgoing arguments.
// The empty destructor reproduces native evaluation order without extra cleanup.
#include "../../Include/Common/BfmePairWI.h"
class Rva00564BF6
{
public:
    BfmePairWI rva00564BF6();
private:
    char pad[0x10];
    BfmePairWI pair;
};

BfmePairWI Rva00564BF6::rva00564BF6()
{
    return pair;
}
