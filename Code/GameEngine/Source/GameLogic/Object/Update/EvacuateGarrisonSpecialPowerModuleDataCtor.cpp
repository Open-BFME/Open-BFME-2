// cl: /O1 /MD /DNDEBUG
// ??0EvacuateGarrisonSpecialPowerModuleData@@QAE@XZ at retail 0x004CDFD9.
// Default ctor over the second intermediate base 0x0044EB54 (pinned opaque
// as SpecialAbilityUpdateModuleData, 0xC8 bytes). No trailing members (factory size 0xC8).
// Target identity: ModuleFactory registers the data factories 0x2531B0
// (EvacuateGarrisonSpecialPower) and 0x25327A (UnleashSpecialPower); both new
// 0xC8 with this one folded ctor (vtable 0x00C5F778). Named after the
// lower-address registration. Do NOT declare an explicit vptr member.
class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();
	virtual ~SpecialAbilityUpdateModuleData();

protected:
	unsigned char m_pad[0xC8 - 4];
};

class EvacuateGarrisonSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
	EvacuateGarrisonSpecialPowerModuleData();
	virtual ~EvacuateGarrisonSpecialPowerModuleData();
};

EvacuateGarrisonSpecialPowerModuleData::EvacuateGarrisonSpecialPowerModuleData()
	: SpecialAbilityUpdateModuleData()
{
}

// ??1EvacuateGarrisonSpecialPowerModuleData@@UAE@XZ present-unmatched
EvacuateGarrisonSpecialPowerModuleData::~EvacuateGarrisonSpecialPowerModuleData()
{
}
