// cl: /O1 /MD /DNDEBUG
// ??0UntamedAllegianceSpecialPowerModuleData@@QAE@XZ at retail 0x004C72D3.
// Default ctor over opaque intermediate base 0x004930A0 (pinned); vtable
// 0x00C5E7A8 only, no trailing members. Target identity: ModuleFactory
// registers the data factories 0x2524B2 (UntamedAllegianceSpecialPower),
// 0x2526DF (ManTheWalls/SplitHorde), 0x252768 (Repair) and 0x25287D
// (HordeDispatch); all four new 0x7C with this one folded ctor. Named after
// the lowest-address registration; the other three classes fold here.
class Rva004930A0
{
public:
	Rva004930A0();
	virtual ~Rva004930A0();

protected:
	unsigned char m_pad[0x7C - 4];
};

// ??1Rva004930A0@@UAE@XZ present-unmatched
Rva004930A0::~Rva004930A0()
{
}

class UntamedAllegianceSpecialPowerModuleData : public Rva004930A0
{
public:
	UntamedAllegianceSpecialPowerModuleData();
	virtual ~UntamedAllegianceSpecialPowerModuleData();
};

UntamedAllegianceSpecialPowerModuleData::UntamedAllegianceSpecialPowerModuleData()
	: Rva004930A0()
{
}

// ??1UntamedAllegianceSpecialPowerModuleData@@UAE@XZ present-unmatched
UntamedAllegianceSpecialPowerModuleData::~UntamedAllegianceSpecialPowerModuleData()
{
}
