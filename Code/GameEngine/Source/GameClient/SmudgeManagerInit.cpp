// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// SmudgeManager::init: the base smudge manager has nothing to set up; its
// vtable slot is pinned at the shared empty ret at 0x000B3FD0.

class SmudgeManager
{
public:
	virtual void init(void);
};

void SmudgeManager::init(void)
{
}
