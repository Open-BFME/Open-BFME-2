// cl: /DNDEBUG /MD /GX
//
// StatusBitsUpgradeIfEldestKindof mux slot 2 (vtable 0x00C579D8 at +0x10),
// retail 0x004B4AFF (125 bytes): false unless the eldest-of-kind helper at
// +0x1C (the pinned StatusBitsEldestFrame, whose 0x00485C19 walks the
// controlling Player's teams; pinned by address) finds our Object eldest for
// the module data's eldest-kind block (a base at +0x138 of the module data,
// so a null data pointer stays null) under this module's cached name key;
// otherwise the UpgradeMux slot-2 base 0x004CE2B0. Named by the base's
// address.
typedef bool Bool;
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
class Object;
class Rva00406F9C;
struct Rva004B4AFFDataHead
{
	unsigned char m_pad00[0x138];
};
struct Rva00485C19Data
{
	int m_00;
};
struct StatusBitsUpgradeIfEldestKindofModuleData : public Rva004B4AFFDataHead, public Rva00485C19Data
{
};
struct StatusBitsEldestFrame
{
	Bool rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key);
private:
	int m_cachedFrame;
};
class ModuleData;
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
// UpgradeMux's base body at 0x004CE2B0 is rowed as Rva004CE2B0::rva004CE2B0.
class Rva004CE2B0
{
public:
	Bool rva004CE2B0(Rva00406F9C *arg);
};
class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void m01() = 0;
	virtual Bool rva004CE2B0(Rva00406F9C *arg);
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMux
{
protected:
	unsigned char m_pad14[0x1C - 0x14];
};
class StatusBitsUpgradeIfEldestKindof : public UpgradeModule
{
public:
	virtual Bool rva004CE2B0(Rva00406F9C *arg);
private:
	StatusBitsEldestFrame m_eldestFrame;	// +0x1C
};
Bool StatusBitsUpgradeIfEldestKindof::rva004CE2B0(Rva00406F9C *arg)
{
	static NameKeyType TheStatusBitsUpgradeIfEldestKindofKey =
		TheNameKeyGenerator->nameToKey("StatusBitsUpgradeIfEldestKindof");
	const StatusBitsUpgradeIfEldestKindofModuleData *data =
		(const StatusBitsUpgradeIfEldestKindofModuleData *)m_moduleData;
	Object *obj = m_object;
	if (m_eldestFrame.rva00485C19(obj, data, &TheStatusBitsUpgradeIfEldestKindofKey))
		return ((Rva004CE2B0 *)((char *)this + 0x10))->rva004CE2B0(arg); // the UpgradeMux base at +0x10, no null test
	return false;
}
