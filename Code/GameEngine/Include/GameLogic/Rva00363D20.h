/* Target facts (addresses are RVAs):
The ledger rows Rva00363D20::rva00363D20 (0x00363D20) and Rva00363D20::rva00363D74 (0x00363D74) read a node pointer at +0 and a position at +4, then follow the node successor at +8 and sum segment distances. HordeContain::_updatePosition calls 0x00363D20 at 0x004719F1 with a Path query result (Rva003642DFResult) as this, so this surrogate spells the same layout under the ledger's class name.
Not registered yet; the identity merge with Rva003642DFResult is left to the naming process.
*/

#pragma once
#ifndef BFME2_RVA00363D20_H
#define BFME2_RVA00363D20_H

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct Rva00363D20Head;

class Rva00363D20
{
public:
    double rva00363D20();
    double rva00363D74();

private:
    Rva00363D20Head *m_head;
    Coord3D m_start;
};

#endif
