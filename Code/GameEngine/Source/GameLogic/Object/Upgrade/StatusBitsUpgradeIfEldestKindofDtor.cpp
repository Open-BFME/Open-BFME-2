// cl: /DNDEBUG /MD
//
// ??1StatusBitsUpgradeIfEldestKindof@@UAE@XZ, retail 0x004B4AFA, 5 bytes.
// StatusBitsUpgradeIfEldestKindof behavior dtor: trivial tail-jmp to the
// StatusBitsUpgrade base dtor (twin pin ??1StatusBitsUpgrade@@UAE@XZ at
// 0x004B48D3, rowed as ??1Rva004B48D3@@UAE@XZ there).
// No vptr stores: novtable suppresses the derived store retail lacks.
// Identity is vtable 0x00C57ADC of the rowed ctor 0x004B4A32 plus sole caller
// ??_G 0x004B4ADE slot 0 plus pool key 0x004B4A99 with the class string.
// Base cluster proves the twin: dtor 0x004B48D3 plus name 0x004B48F3
// returning StatusBitsUpgrade plus pool key 0x004B48F9 plus ctor 0x004B4960.
// Shape follows ReplaceSelfUpgradeDtor (novtable trivial jmp, public UAE).

class Thing;
class ModuleData;

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

class Object;
struct Rva00485C19Data;

enum NameKeyType
{
	NK_UNKNOWN = 0
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

StatusBitsUpgradeIfEldestKindof::~StatusBitsUpgradeIfEldestKindof()
{
}
