// cl: /DBFME_ASCII_DTOR_DECL /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Source/Common
// stlport
// The protected destructor is the separately verified body at 0x004BA47C.
//
// ??0TransitionDamageFX@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004BA3EA,
// 71 bytes. TransitionDamageFX ctor over the rowed DamageModule base
// (0x4B9704, thing plus data). The TU-local DamageModule models the donor
// multiple inheritance (primary 0x0C plus two pure interface words, 0x14
// total) so the derived vtable group lands at ([esi], +0x0C, +0x10) ahead of
// the implicit vector member init; the vector member at +0xD4 builds through
// the folded Vector_base at 0x211E58. The particle ids at +0x14 drain through the
// for-loop-over-ints idiom (rep stosd with lea-before-xor setup,
// DynamicPortalBehaviour precedent).
//
// The rowed instance factory 0x250D4F (sole caller, ModuleFactory
// registration literal) proves the class. Row supersedes the ctor pin.

#include "ascii_string.h"
#include <vector>

#include "../../../../Include/Common/ObjectModule.h"
class Dict;
class BehaviorModuleinterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0;
	virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0;
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
class Xfer;
class Rva004BA1C8Triple {
public:
	unsigned int a;
	unsigned int b;
	unsigned int c;
};
class Rva004BA1C8 {
public:
	~Rva004BA1C8();
	Rva004BA1C8 &operator=(const Rva004BA1C8 &other);
private:
	int m_00;
	_STL::vector<AsciiString> m_04;
	unsigned int m_10;
	Rva004BA1C8Triple m_14;
	Rva004BA1C8Triple m_20;
};
class Rva004BA1D0;
class TransitionDamageFXModuleDataView;
enum ParticleSystemID
{
    INVALID_PARTICLE_SYSTEM_ID = 0
};
// The neighbour-record vector at +0xD4 of the module. Its constructor is the folded
// Vector_base 0x00211E58 and its destructor the row 0x004BA35A.
class TensileFormationUpdateMember : public _STL::vector<Rva004BA1C8>
{
public:
	__forceinline TensileFormationUpdateMember() {}
	~TensileFormationUpdateMember();
};
class DamageModule : public ObjectModule,
    public BehaviorModuleinterface,
    public DamageModuleinterface
{
public:
    DamageModule(Thing *thing, const ModuleData *moduleData);
    virtual ~DamageModule();
};
// Layout from constructor 0x00252F50: interfaces at +0x0C and +0x10, 0x30
// zeroed words from +0x14, and the vector at +0xD4 (allocation 0xE0).
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
    const TransitionDamageFXModuleDataView *getTransitionDamageFXModuleData() const
    {
        return (const TransitionDamageFXModuleDataView *)m_moduleData;
    }

private:
    ParticleSystemID m_particleSystemID[4][12]; // +0x14
    TensileFormationUpdateMember resolvedNeighbors; // +0xD4
};

namespace _STL
{
// Retail arms no state before this call, so the base is nothrow.
template <>
_Vector_base<Rva004BA1C8, allocator<Rva004BA1C8> >::_Vector_base(
	const allocator<Rva004BA1C8> &storage) throw();
}

// ??0TransitionDamageFX@@QAE@PAVThing@@PBVModuleData@@@Z @0x4BA3EA
TransitionDamageFX::TransitionDamageFX(Thing *thing, const ModuleData *moduleData)
	: DamageModule(thing, moduleData)
{
	for (int i = 0; i < 0x30; ++i)
		((int *)m_particleSystemID)[i] = 0;
}
