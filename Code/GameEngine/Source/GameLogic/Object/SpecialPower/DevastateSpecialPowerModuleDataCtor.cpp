// cl: /MD /GX /DNDEBUG /Oy-
//
// ??0DevastateSpecialPowerModuleData@@QAE@XZ, retail 0x004C84BD, 94 bytes.
// SpecialPower-side ModuleData for the Devastate (earthquake) power. The
// table at 0x00C5E3D0 (Radius, FX, TreeValueMultiplier, TreeValueTotalCap,
// FireWeapon at +0x7C through +0x8C) sizes the class at 0x90 bytes over a
// 0x7C-byte base built by the out-of-line 0x004930A0 constructor (pinned as
// SpecialPowerModuleData, shared with DeliverPayload/AIUpdateInterface ctors).
// FireWeapon defaults to the empty string through the rowed StringBase
// const-char constructor at 0x37BA0. The base (declared-only dtor, no code)
// is the TU's sole unwindable, which arms retail's EH frame with its single
// state-0 store; the member has no declared dtor so the string call advances
// no state. The derived vtable store is compiler-emitted (virtual classes,
// TU-local, nothing defined so no vtable is emitted here; the store resolves
// through the ??_7 pin at the true vtable 0x00C5E518, whose slot0 is the
// scalar-deleting dtor right after this ctor at 0x4C851B), which is what
// places it mid-init between the hoisted string setup and the float stores:
// a source-written store can only land last. /Oy- forces the ebp frame with
// the __EH_prolog prologue; /arch:SSE keeps the float zeros as xorps plus
// movss. Supersedes the 0x4C84BD ctor pin (row proves the body).

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
};

template<class T> class StringBase {
	void *m_data;
	StringBase(const T *);
	friend class DevastateSpecialPowerModuleData;
};

class DevastateSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	DevastateSpecialPowerModuleData();
	virtual ~DevastateSpecialPowerModuleData();

private:
	float m_radius; // +0x7C
	void *m_fx; // +0x80
	float m_treeValueMultiplier; // +0x84
	float m_treeValueTotalCap; // +0x88
	StringBase<char> m_fireWeapon; // +0x8C
};

// ??0DevastateSpecialPowerModuleData@@QAE@XZ @0x4C84BD
DevastateSpecialPowerModuleData::DevastateSpecialPowerModuleData()
	: SpecialPowerModuleData()
	, m_fx(0)
	, m_radius(0.0f)
	, m_treeValueMultiplier(0.0f)
	, m_treeValueTotalCap(0.0f)
	, m_fireWeapon("")
{
}
