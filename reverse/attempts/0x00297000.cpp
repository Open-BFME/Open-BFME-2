// ?rva00297000@Object@@QAEXPBVCommandButton@@PAV1@HH@Z
// partial score=0.9 date=2026-10-10
// cl: /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Reference: Object::doSpecialPower and doSpecialPowerAtObject in ZH
// Object.cpp at pinned donor575ba2b04. Names are carried from that source;
// target Object identity and template dispatch are independently supported
// by getSpecialPowerModule/canUseSpecialPower and the named location sibling.
// Native28DF48..28E01F215B and28E01F..28E0F9218B add options bit29:
// look up AutoAbilityBehavior and permit a disabled object when the virtual
// mask at module+10 slot04 overlaps its one-word disabled storage at1C8.
// BitFlags<11> is the existing one-word ABI carrier, not a claim of the
// original BFME2 flag domain. The virtual-mask method's original name is
// unknown. The final Object helper28C4B6 precedes slots28/2C respectively.
// Separate function-local keys/guards are observed at DFED24/28 and2C/30;
// these are ordinary C++ statics, following the verified pool-key source.
// The inline helper keeps the virtual SRET call before the overlap argument
// push. Both bodies independently match, with no newpins or address globals.
class Object;class Module;class SpecialPowerTemplate;
enum NameKeyType {NK_UNKNOWN=0};
class NameKeyGenerator{public:NameKeyType nameToKey(const char*);};extern NameKeyGenerator*TheNameKeyGenerator;
template<int N>class BitFlags {public:BitFlags():bits(0){}bool any()const;bool test(const void*)const;unsigned bits;};
typedef BitFlags<11>DisabledMaskType;
class AutoAbilityMaskView{public:virtual void slot00();virtual DisabledMaskType slot04()const;};
class AutoAbilitySlot01View{public:virtual void *slot00();virtual DisabledMaskType slot01();};
class SpecialPowerStore{public:bool canUseSpecialPower(Object*,const SpecialPowerTemplate*);};extern SpecialPowerStore*TheSpecialPowerStore;
class SpecialPowerModuleInterface{public:virtual void v00();virtual void v01();virtual void v02();virtual void v03();virtual void v04();virtual void v05();virtual void v06();virtual void v07();virtual void v08();virtual void v09();virtual void doSpecialPower(unsigned);virtual void doSpecialPowerAtObject(Object*,unsigned);};
static __forceinline bool testAllowed(const DisabledMaskType&mask,const void*objMask){return mask.test(objMask);}
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum WeaponLockType { LOCKED_TEMPORARILY = 1 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };
class AICommandInterface
{
public:
	void rva0026C347(Object *target, CommandSourceType cmdSource);
	void rva0026C2D9(Object *victim, int maxShotsToFire, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
};
class AIUpdateInterface
{
public:
	AICommandInterface *getCommandInterface() { return &m_commandInterface; }
private:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commandInterface;
};
class CommandButton
{
public:
	int getCommandType() const { return m_command; }
	unsigned int getOptions() const { return m_options; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	WeaponSlotType getWeaponSlot() const { return m_weaponSlot; }
private:
	char m_unknown00[0x14];
	int m_command;
	char m_unknown18[0x1C - 0x18];
	unsigned int m_options;
	char m_unknown20[0x44 - 0x20];
	const SpecialPowerTemplate *m_specialPower;
	char m_unknown48[0x80 - 0x48];
	WeaponSlotType m_weaponSlot;
};
class Object{public:void doSpecialPower(const SpecialPowerTemplate*,unsigned,bool);void doSpecialPowerAtObject(const SpecialPowerTemplate*,Object*,unsigned,bool);protected:Module*findModule(NameKeyType)const;public:SpecialPowerModuleInterface*getSpecialPowerModule(const SpecialPowerTemplate*)const;void rva0028C4B6();__declspec(noinline) void rva0028C24C();bool setWeaponLock(WeaponSlotType,WeaponLockType);void rva00297000(const CommandButton*,Object*,int,int);char pad[0x1c8];DisabledMaskType disabled;char pad1CC[0x258-0x1CC];AIUpdateInterface*m_ai;};
void Object::doSpecialPower(const SpecialPowerTemplate*t,unsigned options,bool forced){
 if(options&0x20000000){static NameKeyType autoKey=TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");Module*m=findModule(autoKey);if(disabled.any()&&!testAllowed(((AutoAbilityMaskView*)((char*)m+0x10))->slot04(),&disabled))return;}
 else if(disabled.any())return;
 if(!forced&&!TheSpecialPowerStore->canUseSpecialPower(this,t))return;
 SpecialPowerModuleInterface*m=getSpecialPowerModule(t);if(m){rva0028C4B6();m->doSpecialPower(options);}
}

void Object::doSpecialPowerAtObject(const SpecialPowerTemplate*t,Object*target,unsigned options,bool forced){
 if(options&0x20000000){static NameKeyType autoKey=TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");Module*m=findModule(autoKey);if(disabled.any()&&!testAllowed(((AutoAbilityMaskView*)((char*)m+0x10))->slot04(),&disabled))return;}
 else if(disabled.any())return;
 if(!forced&&!TheSpecialPowerStore->canUseSpecialPower(this,t))return;
 SpecialPowerModuleInterface*m=getSpecialPowerModule(t);if(m){rva0028C4B6();m->doSpecialPowerAtObject(target,options);}
}

// ?rva00297000@Object@@QAEXPBVCommandButton@@PAV1@HH@Z retail 0x00297000 326B.
// Object command-button dispatch at an object: ZH Object::doCommandButtonAtObject
// donor with BFME2 changes (fourth bfmeArg gates the AutoAbilityBehavior module
// dance above with the slot01 mask query; subtractive command-type dispatch
// 0xE/0x17/0x18/0x1D/0x26 with shared special-power handling for 0x18/0x26).
// Evidence: pin from Rva003C5825Do 0x003C5825; AIGroupDoCommandButton declares
// (cmdSource, bfmeArg); InGameUIInputModes CommandButton layout
// (+0x14/+0x1C/+0x44/+0x80); FellBeast AIUpdateInterface +0x20 command
// interface; rowed callees (findModule, doSpecialPowerAtObject, setWeaponLock,
// rva0026C347/rva0026C2D9/aiIdle, nameToKey, BitFlags any/test).
void Object::rva00297000(const CommandButton *commandButton, Object *obj, int cmdSource, int bfmeArg)
{
	if ((bool)bfmeArg)
	{
		static NameKeyType autoKey = TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
		Module *m = findModule(autoKey);
		if (disabled.any())
		{
			AutoAbilitySlot01View *query = (AutoAbilitySlot01View *)((char *)m + 0x10);
			if (!query->slot01().test(&disabled))
				return;
		}
	}
	else
	{
		if (disabled.any())
			return;
	}
	if (!commandButton)
		return;
	AIUpdateInterface *ai = m_ai;
	if (!ai)
		return;
	switch (commandButton->getCommandType())
	{
	case 0x18:
	case 0x26:
	{
		const SpecialPowerTemplate *t = commandButton->getSpecialPowerTemplate();
		if (!t)
			return;
		unsigned options = commandButton->getOptions() | 0x40000;
		if ((bool)bfmeArg)
			options |= 0x20000000;
		doSpecialPowerAtObject(t, obj, options, cmdSource == 1);
		return;
	}
	case 0x1D:
		if (ai)
			ai->getCommandInterface()->rva0026C347(obj, (CommandSourceType)cmdSource);
		return;
	case 0x17:
		rva0028C24C();
		setWeaponLock(commandButton->getWeaponSlot(), LOCKED_TEMPORARILY);
		ai->getCommandInterface()->rva0026C2D9(obj, 1, (CommandSourceType)cmdSource);
		return;
	case 0x0E:
		if (ai)
			ai->getCommandInterface()->aiIdle((CommandSourceType)cmdSource);
		return;
	}
}
