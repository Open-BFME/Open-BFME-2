// cl: /DNDEBUG /MD /EHsc
// ?rva004AB1F5@WallUpgradeUpdate@@SAPAVModule@@PAVObject@@@Z @0x004AB1F5 81B: static WallUpgradeUpdate lookup over an Object guards a function-local NameKeyType for WallUpgradeUpdate through TheNameKeyGenerator then returns obj findModule key (matched row 0x0028B6D6). Plain ret proves static member not thiscall. Class from pool string at 0x007F4F30. Callers at 0x0027614A 0x0028D0AF 0x004B6ECC. Recipe CastleMemberBehaviorFind precedent 81B.

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
};

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class WallUpgradeUpdate;
};

class WallUpgradeUpdate
{
public:
	static Module *rva004AB1F5(Object *obj);
};

Module *WallUpgradeUpdate::rva004AB1F5(Object *obj)
{
	static NameKeyType TheWallUpgradeUpdateKey =
		TheNameKeyGenerator->nameToKey("WallUpgradeUpdate");
	return obj->findModule(TheWallUpgradeUpdateKey);
}
