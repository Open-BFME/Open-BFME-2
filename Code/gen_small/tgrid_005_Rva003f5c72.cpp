// cl: -EHsc /Os -Ireference/open-bfme-1/game/gen_small
// stlport

// ?erase@?$vector@UGen_p48cd@@V?$allocator@UGen_p48cd@@@_STL@@@_STL@@QAEPAUGen_p48cd@@PAU3@@Z
// retail 0x003F5C72, 55 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/gen_small/tgrid_005.cpp (reference/open-bfme-1): the donor preamble and
// this one vector<Gen_p48cd> instantiation (the donor's other containers
// omitted). The synthetic payload reproduces the layout and lifecycle only;
// the function is the STLport vector erase idiom over a 48-byte
// copy-constructible payload.
#include <vector>

struct Gen_p48cd { int a[12]; Gen_p48cd(); Gen_p48cd(const Gen_p48cd&); ~Gen_p48cd(); Gen_p48cd& operator=(const Gen_p48cd&); };
bool operator==(const Gen_p48cd&, const Gen_p48cd&);
bool operator<(const Gen_p48cd&, const Gen_p48cd&);

template class _STL::vector<Gen_p48cd >;
