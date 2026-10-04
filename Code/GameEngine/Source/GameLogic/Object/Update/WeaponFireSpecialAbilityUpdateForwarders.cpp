// cl: /O1 /DNDEBUG /MD
//
// Two WeaponFireSpecialAbilityUpdate primary-vtable (0x00C4E090) slots that
// defer to the SpecialAbilityUpdate base entries of 0x00C3FBA8, named by the
// bases' addresses like the slot-8 override:
// - slot 16, retail 0x004927D0 (26 bytes): false while the module data's
//   +0xD0 flag is set and the +0x24 state is 2, else the base 0x0044FC52;
// - slot 21, retail 0x004925DB (10 bytes): ignores its flag and runs the
//   base 0x00450635 with true.
typedef bool Bool;
struct WeaponFireSpecialAbilityUpdateModuleData
{
	unsigned char m_pad00[0xD0];
	Bool m_D0; // +0xD0
};
class Object;
class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
	virtual Bool rva0044FC52();
	virtual void rva00450635(Bool flag);
protected:
	const WeaponFireSpecialAbilityUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	int m_24; // +0x24
};
class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual Bool rva0044FC52();
	virtual void rva00450635(Bool flag);
};
Bool WeaponFireSpecialAbilityUpdate::rva0044FC52()
{
	if (m_moduleData->m_D0 && m_24 == 2)
		return false;
	return SpecialAbilityUpdate::rva0044FC52();
}
void WeaponFireSpecialAbilityUpdate::rva00450635(Bool)
{
	SpecialAbilityUpdate::rva00450635(true);
}
