// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@StatusBitsUpgradeIfEldestKindof@@UBE?AW4NameKeyType@@XZ @0x4B4A99
// (69B): cached pool-name key for StatusBitsUpgradeIfEldestKindof. The class
// identity comes from the pool-name string the body pushes
// ("StatusBitsUpgradeIfEldestKindof"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

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

class Thing;
class ModuleData;
class Object;
struct Rva00485C19Data;

class Xfer;

class __declspec(novtable) StatusBitsUpgrade
{
public:
	StatusBitsUpgrade(Thing *thing, const ModuleData *moduleData);
	virtual ~StatusBitsUpgrade();

protected:
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);

	unsigned char m_pad04[0x08];
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x04];
	const void *m_slot18;
};

struct StatusBitsEldestFrame
{
public:
	StatusBitsEldestFrame *cacheGameLogicFrame(void);
	bool rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key);
private:
	int m_cachedFrame; // +0x00
};

class __declspec(novtable) StatusBitsUpgradeIfEldestKindof : public StatusBitsUpgrade
{
public:
	StatusBitsUpgradeIfEldestKindof(Thing *thing, const ModuleData *moduleData);

	virtual ~StatusBitsUpgradeIfEldestKindof();
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void xfer(Xfer *xfer);

private:
	StatusBitsEldestFrame m_eldestFrame;
};

// ?getModuleNameKey@StatusBitsUpgradeIfEldestKindof@@UBE?AW4NameKeyType@@XZ
NameKeyType StatusBitsUpgradeIfEldestKindof::getModuleNameKey() const
{
	static NameKeyType TheStatusBitsUpgradeIfEldestKindofPoolKey =
		TheNameKeyGenerator->nameToKey("StatusBitsUpgradeIfEldestKindof");
	return TheStatusBitsUpgradeIfEldestKindofPoolKey;
}
