// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?getProductionObject@ProductionEntry@@QBE_NXZ @0x00327C1B 20B
// Two-value disp8 bool getter: returns (m_value == 1 || m_value == 3) with
// m_value at +0x04. Evidence: frameless shape matches Disp8CmpBoolGetters
// siblings; 7 callers test al and walk +0x08/+0x10/+0x48 lists.

#include "../../Include/GameLogic/Module/ProductionEntry.h"

bool ProductionEntry::getProductionObject() const
{
	return m_type == 1 || m_type == 3;
}
