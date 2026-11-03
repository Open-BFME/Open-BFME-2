// Canonical BFME2 AIBaseBuilder. Target facts below use RVAs, except tables marked VA.
// Target facts: constructor 0x005070E9 calls Rva00506B1B's constructor 0x00506B1B at +0, stores its owner argument at +8 (0x0050710A), installs VA 0x00C63FAC (0x00507114), and constructs a twelve-byte vector at +0x0C through 0x00211E58. It writes three floats at +0x18/+0x1C/+0x20, clears byte +0x24, and writes three floats at +0x28/+0x2C/+0x30 from VA 0x00DD0870 before replacing the last triple through 0x00506CF5. AIBuilder constructs this member at +4 (0x004EC443..0x004EC44B) and the next member at +0x38 (0x004EC455..0x004EC458); this bounds sizeof(AIBaseBuilder) to 0x34. The parent constructor installs VA 0x00C63F9C and clears byte +4 (0x00506B1D..0x00506B23), giving its four-byte-aligned size 8. Its nonvirtual helper 0x00506B2F tests that byte and dispatches slot 1. The vector's pointer storage is exposed below without defining its container operations; 0x00506BDC and 0x00506C64 read begin/end at +0x0C/+0x10, and constructor/destructor evidence bounds its third word to +0x14.
// Target facts: VA 0x00C63F9C has deleting destructor 0x00506B3B and two purecall entries (0x0003B810); VA 0x00C63FAC has deleting destructor 0x00507506, v1 0x00506BDC, and v2 0x005071A1, followed by string data at VA 0x00C63FB8. Destructor 0x005071DD first restores VA 0x00C63FAC (0x005071EE), calls v2, frees the vector, then calls the parent's vptr reset 0x00506B28 at 0x00507218. The different tables belong to derived and base destruction respectively; there is no fourth slot. The parent's byte +4 is distinct from AIBaseBuilder's byte +0x24. Ordinary methods retain the ledger's out-of-line declarations: rva00506B74 (0x00506B74), rva00506B96 (0x00506B96), rva00506BF7 (0x00506BF7), rva00506C39 (0x00506C39), getBase (0x00506C64), notifyBuildingDestroyed (0x00506FE9), rva0050722A (0x0050722A), DoXfer (0x005073D6), and postInit (0x00507522). The two Coord3D spans are also transferred by 0x005073D6. No donor declaration proves additional member names.
#ifndef BFME2_CANONICAL_AIBASEBUILDER_H
#define BFME2_CANONICAL_AIBASEBUILDER_H

#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "Rva00506B1B.h"

class Object;
class Rva005AD9C0Hit;
class Rva005ADA40;
class Xfer;

class AIBaseBuilder : public Rva00506B1B
{
public:
    AIBaseBuilder(void *owner);
    virtual ~AIBaseBuilder();
    virtual void v1();
    virtual void v2();

    bool rva00506B74(Coord3D *point);
    void rva00506B96(const Coord3D *point);
    Rva005AD9C0Hit *rva00506BF7(void *arg);
    bool rva00506C39(void *arg);
    Rva005ADA40 *getBase(unsigned int index);
    void notifyBuildingDestroyed(Object *object);
    void rva0050722A(Coord3D *point);
    void DoXfer(Xfer *xfer);
    void postInit();

    void *field08;
    Rva005ADA40 **field0C;
    Rva005ADA40 **field10;
    Rva005ADA40 **field14;
    Coord3D field18;
    bool field24;
    Coord3D field28;
};

#endif
