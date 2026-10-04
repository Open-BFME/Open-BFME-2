// cl: /O1 /DNDEBUG /MD
//
// ToggleDeploySpecialAbilityUpdate slot 8 of its +0x20 interface table
// 0x00C55348, retail 0x004AE583 (53 bytes), so `this` is that subobject (the
// Object at -0x18): false for an Object of kind 0x5E or 0x60, otherwise the
// SpecialAbilityUpdate +0x20 slot-8 base 0x0044EDA6 (the slot-8 entry of the
// special-ability +0x20 tables; pinned by address). Named by the base's
// address.
typedef bool Bool;
enum KindOfType
{
	KINDOF_BFME_5E = 0x5e,
	KINDOF_BFME_60 = 0x60
};
class Object
{
public:
	Bool isKindOf(KindOfType kind) const;
};
class ModuleData;
class UpdateModule
{
public:
	virtual ~UpdateModule();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};
class SpecialPowerUpdateInterface
{
public:
	virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3();
	virtual void u4(); virtual void u5(); virtual void u6(); virtual void u7();
	virtual Bool rva0044EDA6(int value);
};
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual Bool rva0044EDA6(int value);
};
class ToggleDeploySpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual Bool rva0044EDA6(int value);
};
Bool ToggleDeploySpecialAbilityUpdate::rva0044EDA6(int value)
{
	Object *obj = m_object;
	if (obj->isKindOf(KINDOF_BFME_5E) || obj->isKindOf(KINDOF_BFME_60))
		return false;
	return SpecialAbilityUpdate::rva0044EDA6(value);
}
