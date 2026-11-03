// FILE: OpaqueRefElement4.h ///////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 OpaqueRefElement4, a four-byte owning handle to an OpaqueRefCounted.
//
// Target facts:
//  - This class has no retail virtual functions and no base: no body stores a
//    table, and the rowed scalar deleting destructor ??_GOpaqueRefElement4@@QAEPAXI@Z
//    (0x00051B1E) is non-virtual (Q).
//  - sizeof 4: TerrainRoadType's constructor 0x002DB1CA passes element size 4 and
//    count 4 to ??_L for its arrays at +0x64 and +0xD4 (0x002DB22A..0x002DB236).
//  - +0x00 is the only field: operator= 0x00239099 AddRefs the source's pointee
//    (kernel32 InterlockedIncrement of +4 through IAT 0x00BBA214), calls
//    ?Release_Ref@OpaqueRefCounted@@QAEXXZ (0x00050ED3) on the old pointer and
//    stores the new one.
//  - Struct key: the ledger rows mangle U (??4 at 0x00239099, rva00239057 at
//    0x00239057, the TerrainRoadType setters 0x002DB44F and 0x002DB463).
//  - The default constructor nulls +0 and is inline: 0x00051DF9 inlines it
//    (`and [ebp-10h], 0`). Its out-of-line copy is the ICF-folded nulling body
//    0x00326BE6, reached only as the ??_L argument (0x002DB22F, 0x002DB276).
//  - The destructor releases a non-null pointee and is inline: ??_G 0x00051B1E
//    and 0x001EC349 inline it. Its out-of-line copy is the 12-byte body 0x0010F149
//    (pinned ??1OpaqueRefElement4@@QAE@XZ), the ??_M argument (0x002DB35D,
//    0x002DB399) and the callee of unwind funclets.
//  - operator= (0x00239099) and rva00239057 (0x00239057, the same store without
//    the self check) are rowed and called out of line.
// Zero Hour has no such class. The class name and the field name `referent` are
// this project's neutral spellings, the ones the registered
// BfmeAudioEventPrefix136.h and its includers use; neither is an original name.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef BFME2_OPAQUEREFELEMENT4_H
#define BFME2_OPAQUEREFELEMENT4_H

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

struct OpaqueRefElement4
{
	OpaqueRefElement4() : referent(0) {}
	~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
	OpaqueRefElement4 &rva00239057(const OpaqueRefElement4 *other);

	OpaqueRefCounted *referent;
};

#endif
