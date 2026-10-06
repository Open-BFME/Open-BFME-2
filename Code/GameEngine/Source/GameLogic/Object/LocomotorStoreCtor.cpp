// cl: /DNDEBUG /MD /EHsc
//
// ??0LocomotorStore@@QAE@XZ, retail 0x0022078E (55 bytes).
// LocomotorStore default ctor: nulls +0/+4, constructs the +0x08 member
// through the opaque 0x3623E5 pin (same member-pin as the landed
// AnimationSteeringUpdateModuleData ctor 0x4BD651, which shares the
// lea-ecx-[esi+8] + call shape), returns this. SEH B8+E8 head with two
// EH states (0 after the null stores, 1 across the member call).
// Unlike ZH's SubsystemInterface-based store, retail stores no vtable here:
// +0/+4 are plain zeroed scalars, so the class is modeled without a
// polymorphic base. Member identities past offsets are unproven (see notes).

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	char m_data[16];
};

// Inferred head at +0: two 4-byte subobjects, each with an inline zeroing
// ctor and an elsewhere-defined destructor. That pair is what forces the two
// EH states (state 0 lands between the zero stores, state 1 across the member
// call); a single 8-byte head emits only one state. Layout past offsets and
// member roles are unproven.
struct LocomotorStoreSlot00
{
	LocomotorStoreSlot00() { ptr = 0; }
	~LocomotorStoreSlot00();
	void *ptr;
};

struct LocomotorStoreSlot04
{
	LocomotorStoreSlot04() { val = 0; }
	~LocomotorStoreSlot04();
	int val;
};

class LocomotorStore
{
public:
	LocomotorStore();

private:
	LocomotorStoreSlot00 m_slot00;
	LocomotorStoreSlot04 m_slot04;
	Rva003623E5Member m_templates;
};

// ??0LocomotorStore@@QAE@XZ
LocomotorStore::LocomotorStore()
{
}
