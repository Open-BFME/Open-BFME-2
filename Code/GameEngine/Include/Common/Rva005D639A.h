// Opaque owner retained from the matched destructor at RVA 0x005D639A.
// Constructor 0x005D66E7 constructs the 12-byte vector base at +4 before
// installing vtable 0x00875B8C. Automatic base destruction reproduces the
// existing 21-byte destructor. Contract: reverse/class_contracts/Rva005D639A.json.
#ifndef BFME_RVA005D639A_H
#define BFME_RVA005D639A_H

#include <vector>
struct BfmeE8;

class Rva005D639A : public _STL::vector<BfmeE8>
{
public:
    Rva005D639A();
    virtual ~Rva005D639A();
};

#endif
