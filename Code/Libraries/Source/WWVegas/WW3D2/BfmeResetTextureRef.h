// Target facts (game.dat RVAs): constructor 0x00180649 zeros the pointer at +0 and calls 0x001805AE; destructor 0x0017098D reads that pointer and tail-calls 0x0061ED10. Neither installs a vptr; this owner has no virtual functions or virtual bases. At 0x0007BAFA and 0x0007BB07, clear receives adjacent owners at +0x14 and +0x18: sizeof is 4. Factory 0x00180692 initializes the empty result with one zero dword.
// The ledger proves clear (0x0004D75B), operator=(BfmeResetAnyRef) (0x00131D99), rva001805AE (0x001805AE), rva00180815 (0x00180815), Release_Device_Resources (0x00132CAD), Recreate_Device_Resources (0x00132CD9) and operator bool() const (0x00615580). The three assignments call slot +0x34 on the referenced resource, testing TEX, TRAP and BOX respectively; that table belongs to the resource, not this owner.
// The assignment and factory return manglings spell this owner as a struct. Its pointer's concrete type and the original retail class name are unproven; void * preserves the four-byte storage without imposing a resource view. No retail base-constructor call or inherited storage is required by these bodies. All rowed methods remain out of line.

#pragma once

struct BfmeResetAnyRef;

struct BfmeResetTextureRef
{
    BfmeResetTextureRef() : pointer(0) {}
    BfmeResetTextureRef(const BfmeResetAnyRef &rhs);
    ~BfmeResetTextureRef();

    BfmeResetTextureRef &operator=(const BfmeResetAnyRef &rhs);
    BfmeResetTextureRef &rva001805AE(const BfmeResetAnyRef &rhs);
    BfmeResetTextureRef &rva00180815(const BfmeResetAnyRef &rhs);
    operator bool() const;

    void clear();
    void Release_Device_Resources();
    void Recreate_Device_Resources();

    void *pointer;
};
