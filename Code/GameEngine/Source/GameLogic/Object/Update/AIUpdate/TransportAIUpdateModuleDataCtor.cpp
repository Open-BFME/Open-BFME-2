// cl: /Ireference/shims/bfme2_ascii /EHs /DNDEBUG /MD /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0TransportAIUpdateModuleData@@QAE@XZ, retail 0x0026E5D7, 166 bytes.
// Transport base ctor over the Turret-led combat table 0x00BF9378 (Turret at
// +0x14 plus MoodAttackCheckRate at +0x18 plus AutoAcquire at +0x1C plus
// StopChaseDistance at +0x20 plus StandGround at +0x24 plus
// CanAttackWhileContained at +0x25 plus HoldGroundCloseRange at +0x28 plus
// AttackPriority at +0x44) plus Transport tail (map at +8, inline name at
// +0x2C, ints at +0x30/34/38/40, PBD AttackPriority at +0x44, int at +0x48,
// angle 80.0f at +0x4C, int at +0x50, flag at +0x54, vector at +0x58).
// Donor is BFME1 TransportAIUpdateModuleData_ctor_Thunk (delay 10 via 5*2,
// distance 500.0f, angle 80.0f, DefaultAttackPriority, flag false).
// MoodAttackCheckRate is 2*global5 (0x00DBA4E4); StopChase/range/angle are
// float literals (movss via /arch:SSE, gate DIR32-fills to 0xBC7A54/0xBCF238).
// Map ctor is the rowed 0x00413727 (ModuleFactory.cpp); StringBase PBD is the
// rowed 0x0037BA0; Vector_base is the rowed 0x00211E58 (BfmeE16 fold).
// Empty UpdateModuleData base with declared-only dtor arms EH (Production
// precedent); inline AsciiString at +0x2C plus PBD at +0x44 plus map/vector
// give the 0->2 state shape.

extern "C" const void *const __identifier("??_7TransportAIUpdateModuleData@@6B@")[];  // vftable 0x00BFA288

#include <map>
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	kNameKeyInvalid = 0
};

#include "../../../../../Include/Common/ModuleFactoryClass.h"

#include "ascii_string.h"

#include "../../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

namespace _STL
{

template <>
_Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(
	const allocator<BfmeE16> &storage) throw();

template <>
map<NameKeyType, ModuleFactory::ModuleTemplate, less<NameKeyType>,
	allocator<pair<const NameKeyType, ModuleFactory::ModuleTemplate> > >::map() throw();

}

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData();
};

class TransportAIUpdateModuleData : public UpdateModuleData
{
public:
	TransportAIUpdateModuleData();

private:
	const void *m_vtable; // +0, retail 0x00BFA288
	int m_unused04; // +4, untouched padding
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate> m_map; // +8
	int m_turret; // +0x14
	int m_moodAttackCheckRate; // +0x18
	int m_autoAcquire; // +0x1C
	float m_stopChaseDistance; // +0x20
	bool m_standGround; // +0x24
	bool m_canAttackWhileContained; // +0x25
	float m_holdGroundRange; // +0x28
	AsciiString m_name; // +0x2C, inline zero
	int m_maxCowerTime; // +0x30
	int m_minCowerTime; // +0x34
	int m_rampageTime; // +0x38
	bool m_rampageRequiresAflame; // +0x3C (byte)
	int m_burningDeathTime; // +0x40
	AsciiString m_attackPriority; // +0x44, PBD DefaultAttackPriority
	int m_timeToEjectPassengersOnRampage; // +0x48
	float m_angle; // +0x4C, 80.0f
	int m_comboLocomotorSet; // +0x50
	bool m_fadeOnPortals; // +0x54
	_STL::vector<BfmeE16> m_vec; // +0x58
};

extern int BfmeLogicFramesPerSecond;

TransportAIUpdateModuleData::TransportAIUpdateModuleData()
	: UpdateModuleData()
	, m_vtable(reinterpret_cast<const void *>(((unsigned int)__identifier("??_7TransportAIUpdateModuleData@@6B@"))))
	, m_moodAttackCheckRate(BfmeLogicFramesPerSecond + BfmeLogicFramesPerSecond)
	, m_autoAcquire(0)
	, m_stopChaseDistance(500.0f)
	, m_standGround(false)
	, m_canAttackWhileContained(false)
	, m_holdGroundRange(0.0f)
	, m_name()
	, m_maxCowerTime(0)
	, m_minCowerTime(0)
	, m_rampageTime(0)
	, m_rampageRequiresAflame(false)
	, m_burningDeathTime(0)
	, m_attackPriority("DefaultAttackPriority")
	, m_timeToEjectPassengersOnRampage(0)
	, m_angle(80.0f)
	, m_comboLocomotorSet(0)
	, m_fadeOnPortals(false)
{
	m_turret = 0;
}
