// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// ??0StopSpecialPowerModuleData@@QAE@XZ, retail 0x004C68AB (22 bytes).
// Frameless trivial ctor over the pinned SpecialPower base (0x4930A0):
// zeroes the StopPowerTemplate word at +0x7C, then overwrites the base
// vptr slot with the explicit vtable 0x00C5E7A8 (Defector precedent:
// pointer-cast write, no virtuals declared anywhere so no vtable is
// emitted here; the 0x00C5E7A8 fold is shared with Defector/Bounty, and
// the address is DIR32-masked in comparison). Flat classes throughout
// (no declared dtors anywhere) keep the body frameless. Field identity
// is the rowed base-call buildFieldParse table 0x00C5DDE4 holding
// exactly StopPowerTemplate at +0x7C; the StopSpecialPower pool key at
// 0x4C6805 sits in the same cluster (ElvenWood precedent). The owning
// factory at 0x002522B5 pushes this ctor's address (sole raw caller).

class Rva004930A0
{
public:
	Rva004930A0();

private:
	unsigned char m_pad[0x7C];
};

class StopSpecialPowerModuleData : public Rva004930A0
{
public:
	StopSpecialPowerModuleData();

private:
	int m_stopPowerTemplate;	// +0x7C
};

// ??0StopSpecialPowerModuleData@@QAE@XZ @0x4C68AB
StopSpecialPowerModuleData::StopSpecialPowerModuleData()
	: Rva004930A0()
{
	m_stopPowerTemplate = 0;
	*(unsigned int *)this = 0x00C5E7A8;
}
