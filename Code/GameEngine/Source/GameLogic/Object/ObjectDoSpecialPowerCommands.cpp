// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
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
class SpecialPowerStore{public:bool canUseSpecialPower(Object*,const SpecialPowerTemplate*);};extern SpecialPowerStore*TheSpecialPowerStore;
class SpecialPowerModuleInterface{public:virtual void v00();virtual void v01();virtual void v02();virtual void v03();virtual void v04();virtual void v05();virtual void v06();virtual void v07();virtual void v08();virtual void v09();virtual void doSpecialPower(unsigned);virtual void doSpecialPowerAtObject(Object*,unsigned);};
static __forceinline bool testAllowed(const DisabledMaskType&mask,const void*objMask){return mask.test(objMask);}
class Object{public:void doSpecialPower(const SpecialPowerTemplate*,unsigned,bool);void doSpecialPowerAtObject(const SpecialPowerTemplate*,Object*,unsigned,bool);protected:Module*findModule(NameKeyType)const;public:SpecialPowerModuleInterface*getSpecialPowerModule(const SpecialPowerTemplate*)const;void rva0028C4B6();char pad[0x1c8];DisabledMaskType disabled;};
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
