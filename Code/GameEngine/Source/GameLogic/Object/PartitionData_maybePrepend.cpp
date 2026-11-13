// cl: /Ob0

class PartitionData;

#include "../../../Include/GameLogic/Module/PartitionDirtyListOwner.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
#include "../../../Include/GameLogic/PartitionData.h"

void PartitionData::maybePrepend()
{
	if (!m_prevDirty)
		m_owner->prependDirtyModule(this);
}
