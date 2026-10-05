// cl: /O1 /DNDEBUG /MD /GX
//
// CreateObjectDieIfEldestKindof::onDie, retail 0x00485D11 (119 bytes): slot
// 0 of the class's +0x10 die-module interface table 0x00C4A810. Only when
// the eldest-of-kind helper at +0x14 (the pinned StatusBitsEldestFrame's
// 0x00485C19) finds our Object eldest for the module data's eldest-kind block
// (a base at +0x4C of the module data) under this module's cached name key
// does the CreateObjectDie onDie 0x00485C86 (slot 0 of CreateObjectDie's die
// table 0x00C4A7DC; pinned by address) run.
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
class DamageInfo;
struct Rva00485D11DataHead
{
	unsigned char m_pad00[0x4C];
};
struct Rva00485C19Data
{
	int m_00;
};
struct CreateObjectDieIfEldestKindofModuleData : public Rva00485D11DataHead, public Rva00485C19Data
{
};
struct StatusBitsEldestFrame
{
	Bool rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key);
private:
	int m_cachedFrame;
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};
class CreateObjectDie : public ModuleBase, public BehaviorModuleInterface, public DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
};
class CreateObjectDieIfEldestKindof : public CreateObjectDie
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
private:
	StatusBitsEldestFrame m_eldestFrame;	// +0x14
};
void CreateObjectDieIfEldestKindof::onDie(const DamageInfo *damageInfo)
{
	static NameKeyType TheCreateObjectDieIfEldestKindofKey =
		TheNameKeyGenerator->nameToKey("CreateObjectDieIfEldestKindof");
	const CreateObjectDieIfEldestKindofModuleData *data =
		(const CreateObjectDieIfEldestKindofModuleData *)m_moduleData;
	Object *obj = m_object;
	if (m_eldestFrame.rva00485C19(obj, data, &TheCreateObjectDieIfEldestKindofKey))
		CreateObjectDie::onDie(damageInfo);
}
