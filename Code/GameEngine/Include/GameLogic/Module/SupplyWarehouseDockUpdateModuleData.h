// SupplyWarehouseDockUpdateModuleData: canonical declarations for the members 10 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_SUPPLYWAREHOUSEDOCKUPDATEMODULEDATA_H
#define CANONICAL_SUPPLYWAREHOUSEDOCKUPDATEMODULEDATA_H

class INI;
class ModuleData;
class MultiIniFieldParse;

class SupplyWarehouseDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *);
};

#endif // CANONICAL_SUPPLYWAREHOUSEDOCKUPDATEMODULEDATA_H
