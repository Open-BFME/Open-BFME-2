// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva004A9660@Rva004A9660@@QAEIPAVObject@@@Z @0x004A9660 181B.
// Worker supply-dock delay. Two function-local name keys,
// SupplyWarehouseDockUpdate then SupplyCenterDockUpdate. findModule's
// result is only a null test. Delays are module-data +0x78 and +0x74
// through the pointer at this-0x3E4. findModule is the protected row
// at 0x0028B6D6, so the call goes through the derived type.

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
};

class Rva004A9660 : public Object
{
public:
	unsigned int rva004A9660(Object *dock);
};

unsigned int Rva004A9660::rva004A9660(Object *dock)
{
	static NameKeyType key_warehouse =
		TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
	if (static_cast<Rva004A9660 *>(dock)->findModule(key_warehouse) != 0)
		return *(unsigned int *)(*(char **)((char *)this - 0x3E4) + 0x78);
	static NameKeyType key_center =
		TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
	if (static_cast<Rva004A9660 *>(dock)->findModule(key_center) != 0)
		return *(unsigned int *)(*(char **)((char *)this - 0x3E4) + 0x74);
	return 0;
}
