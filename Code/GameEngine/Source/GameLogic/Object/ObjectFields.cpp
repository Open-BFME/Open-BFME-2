// Trimmed port of Open-BFME-1
// Code/GameEngine/Source/GameLogic/Object/ObjectFields.cpp (near-miss donor:
// ?makeDirty@PartitionData@@QAEXXZ @0x008F7B30, 27B). Only the served body is
// carried here; the donor's siblings (setScriptStatus, footprint helpers)
// have unserved BFME2 addresses and stay out.
// Diff vs donor: the dirty flag sits at +0x118 in BFME2 (vs +0xDC in BFME1);
// everything else (owner/head/tail layout, helper call, store-1) is identical.

#include <stddef.h>

class PartitionData;

/// Declared with no data members: makeDirty only calls through the pointer,
// never touches its fields, so the layout doesn't need repeating here.
#include "../../../Include/GameLogic/Module/PartitionDirtyListOwner.h"

/// PartitionData stand-in: BFME makeDirty() takes no argument.
#include "../../../Include/GameLogic/PartitionData.h"

// ?makeDirty@PartitionData@@QAEXXZ
__declspec( noinline ) void PartitionData::makeDirty( void )
{
	if( m_prevDirty == NULL )
	{
		m_owner->prependDirtyModule( this );
	}
	m_isDirty = 1;
}
