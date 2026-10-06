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

class StatusBitsUpgrade
{
public:
	virtual ~StatusBitsUpgrade();
};

class __declspec(novtable) StatusBitsUpgradeIfEldestKindof : public StatusBitsUpgrade
{
public:
	virtual ~StatusBitsUpgradeIfEldestKindof();
};

StatusBitsUpgradeIfEldestKindof::~StatusBitsUpgradeIfEldestKindof()
{
}
