// StatusBitsUpgradeModuleData: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_STATUSBITSUPGRADEMODULEDATA_H
#define CANONICAL_STATUSBITSUPGRADEMODULEDATA_H

class INI;
class ModuleData;
class MultiIniFieldParse;

class StatusBitsUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *);
};

#endif // CANONICAL_STATUSBITSUPGRADEMODULEDATA_H
