// cl: /O1 /DNDEBUG /MD /Ireference/shims/moduledata
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../Include/Common/Rva0007DF07.h"

#include "../../Include/GameLogic/CarryoverUnit.h"

#include "../../Include/Common/ArmySummaryEntry.h"

ArmySummaryEntry::~ArmySummaryEntry()
{
}

void ArmySummaryEntry::loadPostProcess()
{
}

const char *ArmySummaryEntry::GetSnapshotName() const
{
	return "ArmySummaryEntry";
}
