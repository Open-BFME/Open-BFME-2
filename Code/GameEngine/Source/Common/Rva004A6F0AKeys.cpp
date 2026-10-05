// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva004A6F0A@Rva004A6F0A@@QAEHPAVObject@@@Z @0x004A6F0A 181B.
// Two function-static module keys. A SupplyWarehouseDockUpdate module
// returns the dword at [[this-0x3E0]+0x6C]; a SupplyCenterDockUpdate
// module returns the dword at [[this-0x3E0]+0x68].

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

class Module;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class Rva004A6F0A;
};

class Rva004A6F0A
{
public:
	int rva004A6F0A(Object *obj);
};

int Rva004A6F0A::rva004A6F0A(Object *obj)
{
	static NameKeyType keyWarehouse =
		TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
	if (obj->findModule(keyWarehouse) != 0)
		return *(int *)(*(char **)((char *)this - 0x3e0) + 0x6c);
	static NameKeyType keyCenter =
		TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
	if (obj->findModule(keyCenter) != 0)
		return *(int *)(*(char **)((char *)this - 0x3e0) + 0x68);
	return 0;
}
