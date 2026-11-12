// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
// Retail runs the 16-byte base constructor at 0x007E86B0 here (vftable
// 0x01129358 plus a zeroed word at +4), not the 9-byte vptr-only body the
// ledger carries as ??0Snapshot@@QAE@XZ. SnapshotDupReplica is the
// TU-local spelling functions.csv already records as that body's object
// symbol.
#include "../../Include/Common/SnapshotDupReplica.h"

class Rva007F4DA0 : public SnapshotDupReplica
{
	int m_04;
	char m_08;
	char m_gap[0x1B];
	int m_24;

public:
	Rva007F4DA0();
};

inline Rva007F4DA0::Rva007F4DA0()
{
	m_08 = 0;
	m_24 = 0;
	m_04 = 1;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva007F4DA0InlineAnchor@@YAXPAVRva007F4DA0@@@Z absent-from-retail
void _bfmeRva007F4DA0InlineAnchor(Rva007F4DA0 *p)
{
    p->Rva007F4DA0::Rva007F4DA0();
}
#pragma inline_depth()
