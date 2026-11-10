// DockUpdateModuleData: canonical declarations for the members 8 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_DOCKUPDATEMODULEDATA_H
#define CANONICAL_DOCKUPDATEMODULEDATA_H

class MultiIniFieldParse;

class DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

#endif // CANONICAL_DOCKUPDATEMODULEDATA_H
