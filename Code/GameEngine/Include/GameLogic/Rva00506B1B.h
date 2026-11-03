// Canonical BFME2 Rva00506B1B, the 8-byte base of AIBaseBuilder. Target facts use RVAs, except tables marked VA.
// Target facts: constructor 0x00506B1B installs VA 0x00C63F9C and clears byte +4 (0x00506B1D..0x00506B23); that table has deleting destructor 0x00506B3B and two purecall entries (0x0003B810).
// Target facts: helper 0x00506B2F tests byte +4 and dispatches slot 1; AIBaseBuilder's destructor resets the vptr through 0x00506B28.
#ifndef BFME2_CANONICAL_RVA00506B1B_H
#define BFME2_CANONICAL_RVA00506B1B_H

class Rva00506B1B
{
public:
    Rva00506B1B();
    virtual ~Rva00506B1B();
    virtual void v1() = 0;
    virtual void v2() = 0;
    void rva00506B2F();
    bool field04;
};

typedef char Rva00506B1BSizeCheck[sizeof(Rva00506B1B) == 0x8 ? 1 : -1];

#endif
