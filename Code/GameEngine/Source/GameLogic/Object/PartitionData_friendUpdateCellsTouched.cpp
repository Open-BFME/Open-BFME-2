// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: PartitionData::friend_updateCellsTouched, retail 0x008F8BF0,
// 37 bytes. The canonical Zero Hour header exposes this public zero-argument
// facade over private updateCellsTouched(). BFME augments it by removing the
// object from an intrusive dirty list before rebuilding the touched cells.
//
// Retail +0x14 is a pointer to the link that currently names this node, and
// +0x18 is the following node. Rewriting the former makes removal work for
// either the list head or a predecessor's next link; the following node then
// inherits that backlink. The cleared backlink records that this node is no
// longer linked.

namespace ShroudManager
{
	class Data
	{
	public:
		void UpdateCellsTouched();
	};
}

#include "../../../Include/GameLogic/PartitionData.h"

// ?friend_updateCellsTouched@PartitionData@@QAEXXZ
inline void PartitionData::friend_updateCellsTouched()
{
	if (m_prevDirty != 0)
	{
		*m_prevDirty = m_nextDirty;
		if (m_nextDirty != 0)
			m_nextDirty->m_prevDirty = m_prevDirty;
		m_prevDirty = 0;
	}
	((ShroudManager::Data *)this)->UpdateCellsTouched();
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmePartitionDataInlineAnchor@@YAXPAVPartitionData@@@Z absent-from-retail
void _bfmePartitionDataInlineAnchor(PartitionData *partitionData)
{
    partitionData->friend_updateCellsTouched();
}
#pragma inline_depth()
