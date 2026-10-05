// cl: /O1 /MD /DNDEBUG
// ??0UntamedAllegianceSpecialPowerModuleData@@QAE@XZ at retail 0x004C72D3.
// Default ctor over opaque intermediate base 0x004930A0 (pinned); vtable
// 0x00C5E7A8 only, no trailing members. Target identity: ModuleFactory
// registers the data factories 0x2524B2 (UntamedAllegianceSpecialPower),
// 0x2526DF (ManTheWalls/SplitHorde), 0x252768 (Repair) and 0x25287D
// (HordeDispatch); all four new 0x7C with this one folded ctor. Named after
// the lowest-address registration; the other three classes fold here.
class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

protected:
	unsigned char m_pad[0x7C - 4];
};

class UntamedAllegianceSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	UntamedAllegianceSpecialPowerModuleData();
	virtual ~UntamedAllegianceSpecialPowerModuleData();
};

UntamedAllegianceSpecialPowerModuleData::UntamedAllegianceSpecialPowerModuleData()
	: SpecialPowerModuleData()
{
}

// ??1UntamedAllegianceSpecialPowerModuleData@@UAE@XZ present-unmatched
UntamedAllegianceSpecialPowerModuleData::~UntamedAllegianceSpecialPowerModuleData()
{
}
