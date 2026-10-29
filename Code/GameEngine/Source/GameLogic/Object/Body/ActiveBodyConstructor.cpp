// cl: /GX /MD /D_CRTIMP= /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// BFME1 ActiveBody_Constructor.cpp and Zero Hour ActiveBody.cpp guide the
// health, damage-info, armor-validation, and damage-state sequence. BFME2
// target evidence expands the DamageInfo member to 0x7C (0x263895), places
// the damage-creation vector at +0xE0, and copies it from module data +0x58.
// The factory at 0x2513AD and the ModuleFactory "ActiveBody" registration
// establish the ctor identity; the retail body is 423B at 0x4BF6A1.

#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorIface
{
public:
	virtual void behaviorIfaceAnchor() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorIface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class BodyModuleInterface
{
public:
	virtual void bodyAnchor() = 0;
};

class __declspec(novtable) BodyModule : public BehaviorModule, public BodyModuleInterface
{
public:
	BodyModule(Thing *thing, const ModuleData *moduleData);
	virtual ~BodyModule();

private:
	float m_damageScalar;
};

class Rva00263653
{
public:
	Rva00263653() throw();
	char m_data[0x68];
};

class Rva00263895Member
{
public:
	Rva00263895Member() throw();
	virtual void rva00263895_dummy();

private:
	Rva00263653 m_mem;
	const void *m_ptr;
	float m_f70;
	float m_f74;
	unsigned char m_b78;
};

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmeE16, BfmeE16>(BfmeE16 *, BfmeE16 const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PBUBfmeE16@@PAU1@@_STL@@YAPAUBfmeE16@@PBU1@0PAU1@ABU__false_type@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE16;
namespace _STL { template <> BfmeE16 * __uninitialized_copy<BfmeE16 const *,BfmeE16 *>(BfmeE16 const *,BfmeE16 const *,BfmeE16 *,__false_type const &); }
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// Retail's copy for this member (call at 0x004BF6A1) is 0x004BF4CE, rowed as
// vector<BfmeE12>::operator= (stlport_vector_e12_assign.cpp): it steps 0xC per
// element. Forward the assignment to that row; the empty base ctor stays the
// BfmeE16 row 0x00211E58 that retail calls.
struct BfmeE12;
namespace _STL { template <> vector<BfmeE12, allocator<BfmeE12> > &vector<BfmeE12, allocator<BfmeE12> >::operator=(const vector<BfmeE12, allocator<BfmeE12> > &); }
namespace _STL { template <> __declspec(dllimport) __forceinline vector<BfmeE16, allocator<BfmeE16> > &vector<BfmeE16, allocator<BfmeE16> >::operator=(const vector<BfmeE16, allocator<BfmeE16> > &x) { return (vector<BfmeE16, allocator<BfmeE16> > &)((vector<BfmeE12, allocator<BfmeE12> > *)this)->operator=((const vector<BfmeE12, allocator<BfmeE12> > &)x); } }

struct ActiveBodyModuleDataFields
{
	unsigned char m_pad00[8];
	float m_maxHealth;
	float m_initialHealth;
	float m_maxHealthDamaged;
	float m_maxHealthReallyDamaged;
	unsigned char m_pad18[0x10];
	unsigned char m_useDefault;
	unsigned char m_pad29[0x2f];
	_STL::vector<BfmeE16> m_damageCreation;
};

class GlobalData
{
public:
	unsigned char m_pad00[0xb4];
	float m_unitDamagedThresh;
	float m_unitReallyDamagedThresh;
};

extern class GlobalData *TheWritableGlobalData;

template<int N>
class BitFlags
{
public:
	BitFlags();
	unsigned int m_bits;
};

class ActiveBody : public BodyModule
{
public:
	ActiveBody(Thing *thing, const ModuleData *moduleData);
	virtual ~ActiveBody();
	void validateArmorAndDamageFX() const;
	void setCorrectDamageState(Bool update);

private:
	float m_currentHealth;
	float m_prevHealth;
	float m_maxHealth;
	float m_damagedThreshold;
	float m_reallyDamagedThreshold;
	float m_initialHealth;
	int m_curDamageState;
	int m_field34;
	int m_nextDamageFXTime;
	int m_lastDamageFXDone;
	Rva00263895Member m_lastDamageInfo;
	UnsignedInt m_lastDamageTimestamp;
	UnsignedInt m_lastHealingTimestamp;
	Bool m_frontCrushed;
	Bool m_backCrushed;
	Bool m_lastDamageCleared;
	Bool m_indestructible;
	void *m_particleSystems;
	float m_damageStateValues[4];
	Bool m_damageStateFlags[4];
	_STL::vector<BfmeE16> m_damageCreation;
	UnsignedInt m_fieldEC;
	BitFlags<11> m_curArmorSetFlags;
	const void *m_curArmorSet;
	AsciiString m_armorSetName;
	const void *m_curDamageFX;
};

ActiveBody::ActiveBody(Thing *thing, const ModuleData *moduleData)
	: BodyModule(thing, moduleData),
	  m_curDamageState(0),
	  m_field34(0),
	  m_nextDamageFXTime(0),
	  m_lastDamageFXDone(29),
	  m_lastDamageInfo(),
	  m_lastDamageTimestamp(0xffffffff),
	  m_lastHealingTimestamp(0xffffffff),
	  m_frontCrushed(false),
	  m_backCrushed(false),
	  m_lastDamageCleared(false),
	  m_indestructible(false),
	  m_particleSystems(0),
	  m_damageCreation(),
	  m_fieldEC(0),
	  m_curArmorSetFlags(),
	  m_curArmorSet(0),
	  m_armorSetName(AsciiString::TheEmptyString),
	  m_curDamageFX(0)
{
	const ActiveBodyModuleDataFields *data =
		reinterpret_cast<const ActiveBodyModuleDataFields *>(m_moduleData);
	m_prevHealth = data->m_initialHealth;
	m_maxHealth = data->m_maxHealth;
	m_damageCreation = data->m_damageCreation;
	float reciprocal = 1.0f / m_maxHealth;
	m_damagedThreshold = reciprocal * data->m_maxHealthDamaged;
	m_reallyDamagedThreshold = reciprocal * data->m_maxHealthReallyDamaged;
	m_initialHealth = m_currentHealth = data->m_initialHealth != -1.0f
		? data->m_initialHealth : data->m_maxHealth;
	if (data->m_useDefault)
	{
		if (m_damagedThreshold == 0.0f)
			m_damagedThreshold = TheWritableGlobalData->m_unitDamagedThresh;
		if (m_reallyDamagedThreshold == 0.0f)
			m_reallyDamagedThreshold = TheWritableGlobalData->m_unitReallyDamagedThresh;
	}
	for (int i = 0; i < 4; ++i)
	{
		m_damageStateValues[i] = 0.0f;
		m_damageStateFlags[i] = false;
	}
	validateArmorAndDamageFX();
	setCorrectDamageState(false);
}

// ?g_Va00DE0878@@3IA: the global at this VA is ?TheEmptyString@AsciiString@@2V1@B; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00DE0878@@3IA=?TheEmptyString@AsciiString@@2V1@B")
#pragma comment(linker, "/alternatename:?g_str009E0878@@3V?$StringBase@D@@A=?TheEmptyString@AsciiString@@2V1@B")
// ?g_Va00DE0878@@3IA: the global at VA 0xde0878 is ?TheEmptyString@AsciiString@@2V1@B.
#pragma comment(linker, "/alternatename:?g_Va00DE0878@@3IA=?TheEmptyString@AsciiString@@2V1@B")
