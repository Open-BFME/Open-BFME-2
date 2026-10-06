// cl: /DNDEBUG /MD
//
// ?triggerAbilityEffect@ScaleWallSpecialAbilityUpdate@@UAEXXZ, retail 0x00494E26, 34 bytes.
// Slot 17 of the vftable 0x00C4EB40 whose slot-2 name getter returns
// "ScaleWallSpecialAbilityUpdate". Runs the base SpecialAbilityUpdate slot 17
// (pinned triggerAbilityEffect, whose address name it carries so cl 7.1 places it in
// slot 17), then hands 1.0f to slot 15 of the special-power module the rowed
// lookup 0x0044E633 finds for this ability (ZH's getMySPM shape: the owner's
// module for module data +0x38). Method identity not established.

class Rva0044E633
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	void *rva0044E633();
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void rva15(float value);
};

class SpecialAbilityUpdate : public Rva0044E633
{
public:
	virtual void triggerAbilityEffect();
};

class ScaleWallSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
};

// ?triggerAbilityEffect@ScaleWallSpecialAbilityUpdate@@UAEXXZ @0x00494E26
void ScaleWallSpecialAbilityUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	SpecialPowerModuleInterface *spm = (SpecialPowerModuleInterface *)rva0044E633();
	if (spm)
		spm->rva15(1.0f);
}
