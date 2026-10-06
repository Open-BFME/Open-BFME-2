// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// BehaviorModule::loadPostProcess: Zero Hour's body only forwards to its
// bases' empty loadPostProcess, so retail folds it into the shared empty
// ret at 0x000B3FD0, where callers pin it.

class BehaviorModule
{
protected:
	virtual void loadPostProcess(void);
};

void BehaviorModule::loadPostProcess(void)
{
}
