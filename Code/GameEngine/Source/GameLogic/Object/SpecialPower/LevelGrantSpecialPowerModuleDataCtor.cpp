// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??0LevelGrantSpecialPowerModuleData@@QAE@XZ, retail 0x004C2AA0, 83 bytes.
// SpecialPower-side ModuleData for the level-grant power. The rowed chained
// proc's table at 0x00C5C8D0 (Experience at +0xC8, RadiusEffect at +0xCC,
// AcceptanceFilter at +0xD0, LevelFX at +0xD4) sizes the members over the
// pinned Rva0044EB54 base (0x44EB54, 0xC8 bytes); the AcceptanceFilter word
// constructs through the pinned 0x3623E5 member ctor and the LevelGrant
// pool key at 0x4C2BC1 sits in the same cluster. Devastate V5 recipe: the
// base (declared-only virtual dtor, no code) is the TU's sole unwindable,
// which arms retail's EH frame with its single state-0 store; the member
// has no declared dtor so its call advances no state. The derived vtable
// store is compiler-emitted (virtual classes, TU-local, nothing defined so
// no vtable is emitted here; the store resolves through the ??_7 pin at the
// true vtable 0x00C5C828, whose slot0 is the scalar-deleting dtor at
// 0x4C2C06), which places it mid-init between the hoisted member setup and
// the float store. /Oy- forces the ebp frame with the __EH_prolog prologue;
// /arch:SSE keeps the float zero as xorps plus movss. The ModuleData
// factory at 0x251A72 (news 0xD8) is the only raw caller.

class Rva0044EB54
{
public:
	Rva0044EB54();
	virtual ~Rva0044EB54();

private:
	unsigned char m_pad[0xC8 - 4];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();

private:
	unsigned char m_data[4];
};

class LevelGrantSpecialPowerModuleData : public Rva0044EB54
{
public:
	LevelGrantSpecialPowerModuleData();
	virtual ~LevelGrantSpecialPowerModuleData();

private:
	int m_experience; // +0xC8
	float m_radiusEffect; // +0xCC
	Rva003623E5Member m_acceptanceFilter; // +0xD0
	int m_levelFX; // +0xD4
};

// ??0LevelGrantSpecialPowerModuleData@@QAE@XZ @0x4C2AA0
LevelGrantSpecialPowerModuleData::LevelGrantSpecialPowerModuleData()
	: Rva0044EB54()
	, m_experience(0)
	, m_acceptanceFilter()
	, m_radiusEffect(0.0f)
	, m_levelFX(0)
{
}
