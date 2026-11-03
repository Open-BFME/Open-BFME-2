/* Target facts (addresses are RVAs):
Rva003642DFResult has no virtual functions, vptr or polymorphic base in retail. Path::rva003642DF (0x003642DF) constructs its local at 0x003642FE by calling 0x00326BE6, whose complete six-byte body returns this and zeros only its first dword. This is a folded constructor, not a vtable store; no constructor or destructor table belongs to this value.
The result occupies 0x10 bytes: 0x00364335 and 0x0036449E copy it to the hidden return buffer through 0x0004254E, whose complete 31-byte body copies dwords at +0/+4/+8/+0x0C and returns this. The node pointer at +0 is stored at 0x00364345/0x0036434C and dereferenced at 0x003644C5/0x003644CD. The position at +4 is copied from the node's +0x0C/+0x10/+0x14 at 0x00364485..0x0036448D and interpolated as three floats at 0x003644C8..0x00364517. The distance call at 0x00364362 takes the selected node positions; m_node and m_pos describe these byte-proven roles, without asserting original source spelling.
The existing pins bind the default constructor to 0x00326BE6 and the copy constructor to 0x0004254E; both are called out of line above and are declared here without bodies. Path::rva00364521 (0x00364521) forwards the same hidden return buffer at 0x0036453F/0x00364544. The ledger spells both return types as a struct. There is no row or retail cleanup call establishing a nontrivial destructor or assignment for this value.
HordeContain::_updatePosition calls 0x00363D20 at 0x004719F1 with the returned value as this. That row is named Rva00363D20::rva00363D20; its body reads the node pointer at +0, the position at +4 and the node successor at +8 to sum segment distances. Its sibling 0x00363D74 uses the same layout. The declaration below preserves those ledger names, and remaining forwards to the rowed accessor.
*/

#pragma once
#ifndef BFME2_RVA003642DFRESULT_H
#define BFME2_RVA003642DFRESULT_H

#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "Rva00363D20.h"

struct Rva003642DFNode;

struct Rva003642DFResult
{
    Rva003642DFResult();
    Rva003642DFResult(const Rva003642DFResult &);

    double remaining() { return reinterpret_cast<Rva00363D20 *>(this)->rva00363D20(); }

    Rva003642DFNode *m_node;
    Coord3D m_pos;
};

#endif
