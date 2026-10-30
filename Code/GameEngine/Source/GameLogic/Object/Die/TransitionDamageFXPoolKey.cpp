// cl: /DBFME_ASCII_DTOR_DECL /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/Libraries/Include /ICode/GameEngine/Source
#include <vector>
// stlport
// ?getModuleNameKey@TransitionDamageFX@@UBE?AW4NameKeyType@@XZ @0x4BA437
// (69B): cached pool-name key for TransitionDamageFX. The class
// identity comes from the pool-name string the body pushes
// ("TransitionDamageFX"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;


// ?getModuleNameKey@TransitionDamageFX@@UBE?AW4NameKeyType@@XZ
#include "../../../../Include/Common/ObjectModule.h"

class Dict;

class BehaviorModuleinterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void mapLoadPostProcess(const Dict *) = 0;
};

// The three-slot table the constructor installs at +0x10 (0x010B2588).
class DamageInfo;
enum BodyDamageType;

class DamageModuleinterface
{
public:
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType) = 0;
};

class DamageInfo;
class Dict;
class Xfer;
class Rva004BA1D0;
class TDFXObject;
class TransitionDamageFXModuleDataView;
enum BodyDamageType;
enum ParticleSystemID
{
    INVALID_PARTICLE_SYSTEM_ID = 0
};

class DamageModule : public ObjectModule,
    public BehaviorModuleinterface,
    public DamageModuleinterface
{
public:
    DamageModule(Thing *thing, const ModuleData *moduleData);
    virtual ~DamageModule();
};

class TransitionDamageFX : public DamageModule
{
public:
    TransitionDamageFX(Thing *thing, const ModuleData *moduleData);
    void bfmeGoFDE();
    void bfmeUseFDE(void *r);
    void rva004B9DA9(bool applyTransition);
    virtual NameKeyType getModuleNameKey() const;
    virtual void mapLoadPostProcess(const Dict *);
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType);

protected:
    virtual ~TransitionDamageFX();
    virtual void xfer(Xfer *xfer);
    TDFXObject *getObject() const { return (TDFXObject *)m_object; }
    const TransitionDamageFXModuleDataView *getTransitionDamageFXModuleData() const
    {
        return (const TransitionDamageFXModuleDataView *)m_moduleData;
    }

private:
    ParticleSystemID m_particleSystemID[4][12]; // +0x14
    _STL::vector<Rva004BA1D0> resolvedNeighbors;
};

NameKeyType TransitionDamageFX::getModuleNameKey() const
{
	static NameKeyType TheTransitionDamageFXPoolKey =
		TheNameKeyGenerator->nameToKey("TransitionDamageFX");
	return TheTransitionDamageFXPoolKey;
}
