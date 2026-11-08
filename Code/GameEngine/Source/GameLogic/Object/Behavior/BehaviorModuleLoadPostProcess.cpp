// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// BehaviorModule::loadPostProcess: Zero Hour's body only forwards to its
// bases' empty loadPostProcess, so retail folds it into the shared empty
// ret at 0x000B3FD0, where callers pin it.

// BehaviorModule's loadPostProcess is defined below; no BehaviorModule-derived table is emitted here.
#define BFME_BEHAVIORMODULE_LOADPOSTPROCESS
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

void BehaviorModule::loadPostProcess(void)
{
}
