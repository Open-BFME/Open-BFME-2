// cl: /DNDEBUG /MD
//
// Two overrides in the special-power interface vtable WeaponChangeSpecialPowerModule's
// ctor 0x004C3FF8 installs at +0x10 (0x00C5D150), both forwarding to slot 10
// (0x004C40BA) with their last argument, the other arguments unread:
//   ?rva004C405D@WeaponChangeSpecialPowerModule@@UAEXPAXH@Z  retail 0x004C405D, 12 bytes:
//     slots 11 and 12 (two two-argument slots folded onto one body; also
//     PlayerUpgradeSpecialPower's slots 11/12, vtable 0x00C5E120);
//   ?rva004C4069@WeaponChangeSpecialPowerModule@@UAEXPAXMH@Z retail 0x004C4069, 12 bytes:
//     slot 13 (three arguments).
// Zero Hour's SpecialPowerModuleInterface has the same at-object / at-location
// forwarders shape over doSpecialPower(commandOptions); the slot order here
// differs, so the names stay by address. Compiled with the +0x10 subobject
// this.
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
private:
	unsigned char m_pad04[0x10 - 4];
};

class SpecialPowerModuleInterface
{
public:
	virtual void slot0() = 0; virtual void slot1() = 0; virtual void slot2() = 0; virtual void slot3() = 0;
	virtual void slot4() = 0; virtual void slot5() = 0; virtual void slot6() = 0; virtual void slot7() = 0;
	virtual void slot8() = 0; virtual void slot9() = 0;
	virtual void rva004C40BA(int commandOptions) = 0;
	virtual void rva004C405D(void *target, int commandOptions) = 0;
	virtual void rva004C4069(void *target, float angle, int commandOptions) = 0;
};

class WeaponChangeSpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	virtual void rva004C40BA(int commandOptions);
	virtual void rva004C405D(void *target, int commandOptions);
	virtual void rva004C4069(void *target, float angle, int commandOptions);
};

void WeaponChangeSpecialPowerModule::rva004C405D(void *target, int commandOptions)
{
	rva004C40BA(commandOptions);
}

void WeaponChangeSpecialPowerModule::rva004C4069(void *target, float angle, int commandOptions)
{
	rva004C40BA(commandOptions);
}
