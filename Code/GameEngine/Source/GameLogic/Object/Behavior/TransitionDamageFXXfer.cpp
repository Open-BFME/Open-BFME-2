// cl: /DBFME_ASCII_DTOR_DECL /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/Libraries/Include /ICode/GameEngine/Source
#include <vector>
// stlport
//
// ?xfer@TransitionDamageFX@@MAEXPAVXfer@@@Z, retail 0x004B98C6, 74 bytes: slot 3
// of TransitionDamageFX's vtable 0x00859AEC (dtor and ctor rowed in
// TransitionDamageFXDtor.cpp / TransitionDamageFXCtor.cpp). Zero Hour's
// TransitionDamageFX::xfer shape: version 1, the DamageModule base transfer
// (rowed Rva004CE56D::xfer 0x004CE56D), then, unless the transfer is a CRC,
// the 4 x 12 particle system ids at +0x14 through XferParticleSystemID.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva004CE56D
{
public:
	void xfer(Xfer *xfer);
};

void XferParticleSystemID(Xfer *xfer, int *id);





enum
{
	BODYDAMAGETYPE_COUNT = 4,
	DAMAGE_MODULE_MAX_FX = 12
};


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

void TransitionDamageFX::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004CE56D *)this)->xfer(xfer);
	if (!xfer->IsCRC())
	{
		for (int i = 0; i < BODYDAMAGETYPE_COUNT; ++i)
			for (int j = 0; j < DAMAGE_MODULE_MAX_FX; ++j)
				XferParticleSystemID(xfer, (int *)&m_particleSystemID[i][j]);
	}
}
