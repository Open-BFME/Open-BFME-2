// ?rva004C21A9@PorcupineFormationBodyModule@@QAEXPAVDamageInfo@@@Z
// partial score=0.95 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// PorcupineFormationBodyModule's +0x10 body-interface overrides (table
// 0x00C5C318) and the formation test they share, all names but
// attemptDamage by address.
// rva004C2095, retail 0x004C2095 (37 bytes), on the primary this: asks the
// container module (+0x250) of the Object our Object is contained by (+0x274)
// its slot 31 when all three exist, and answers false either way.
// attemptDamage, retail 0x004C2230 (45 bytes), slot 0: with the formation
// test holding, the class's 0x004C21A9 (pinned by address) sees the damage
// first; ActiveBody::attemptDamage 0x004BFE07 always follows.
// rva004C2127, retail 0x004C2127 (130 bytes), slot 38: true while the
// formation test fails, without our Object or module data, without the data's
// +0x6C level, or when that level is below the other Object's (Object
// 0x00294815, pinned by address); otherwise false, after the data's +0x68
// weapon (when set) is fired from our Object at the other through
// TheWeaponStore (the rowed rva002CE964) if the two positions are within the
// weapon's range (its +0x14 float; the getter folds with the rowed
// TerrainRoadType::getRoadWidth, used here only as a call view) by the rowed
// 0x004C20D5 distance test (reached as a member; pinned for this class).
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
// Inlined here; imported, this unit emits no non-retail out-of-line copies (STLport
// bodies verbatim).
namespace _STL {
template <> __declspec(dllimport) __forceinline vector<void *, allocator<void *> >::const_iterator vector<void *, allocator<void *> >::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline vector<void *, allocator<void *> >::size_type vector<void *, allocator<void *> >::size() const { return size_type(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t __n) const { return *(begin() + __n); }
}
// Call view for the existing folded fld [ecx+0x14]; ret provider at 0x0049CB57.
class TerrainRoadType
{
public:
	float getRoadWidth();
};

class WeaponTemplate;
class Object;
namespace {
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHashVF;
}
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;
	ObjectPtrHashVF &objectPtrHashVF = *(ObjectPtrHashVF *)((char *)this + 0xB4);
	ObjectPtrHashVF::iterator it = objectPtrHashVF.find(id);
	if (it == objectPtrHashVF.end())
		return 0;
	return (*it).second;
}

extern GameLogic *TheGameLogic;
class ThingTemplate
{
public:
	bool testKindOf10BBit1() const { return (m_kindOf[0x10B - 0x108] & 0x02) != 0; }
private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x0C];	// +0x108
};
#include "../../../../Include/GameLogic/WeaponStore.h"
extern WeaponStore *TheWeaponStore;
template <int N> class Rva004C2095Slots : public Rva004C2095Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C2095Slots<0>
{
};
class Rva004C2095Contain : public Rva004C2095Slots<31>
{
public:
	virtual void *rvaSlot31() = 0;
};
class Object
{
public:
	char rva00294815();
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	bool test438Bit0() const { return (m_438 & 1) != 0; }
	Object *getContainedBy() const { return m_containedBy; }
	Rva004C2095Contain *getContain() const { return m_contain; }
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position;		// +0x38
	unsigned char m_pad044[0x250 - 0x44];
	Rva004C2095Contain *m_contain;	// +0x250
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_containedBy;		// +0x274
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_438;		// +0x438
};
#include "../../../../Include/GameLogic/Damage.h"
struct PorcupineFormationBodyModuleData
{
	unsigned char m_pad00[0x64];
	const WeaponTemplate *m_reactionWeapon;	// +0x64
	const WeaponTemplate *m_weapon;	// +0x68
	char m_level;			// +0x6C
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/BodyModule.h"
#include "../../../../Include/GameLogic/Module/ActiveBody.h"
class PorcupineFormationBodyModule : public ActiveBody
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual bool rva004C2127(Object *other);
	bool rva004C2095();
	void rva004C21A9(DamageInfo *damageInfo);
	bool Rva004C20D5IsWithin(float range, const Coord3D *a, const Coord3D *b);
};

// PorcupineFormationBodyModule::rva004C2095 is rowed in its home unit; this copy was a duplicate definition.

void PorcupineFormationBodyModule::rva004C21A9(DamageInfo *damageInfo)
{
	Object *source = m_object;
	if (source != 0) {
		const PorcupineFormationBodyModuleData *data = (const PorcupineFormationBodyModuleData *)m_moduleData;
		if (data != 0) {
			const WeaponTemplate *weapon = data->m_reactionWeapon;
			if (weapon != 0) {
				Object *target = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
				if (target != 0 && !target->test438Bit0() &&
					!target->getTemplate()->testKindOf10BBit1() &&
					this->Rva004C20D5IsWithin(((TerrainRoadType *)weapon)->getRoadWidth(), source->getPosition(), target->getPosition())) {
					TheWeaponStore->rva002CE964(data->m_reactionWeapon, source, target);
				}
			}
		}
	}
}

// PorcupineFormationBodyModule::attemptDamage is rowed in its home unit; this copy was a duplicate definition.

// PorcupineFormationBodyModule::rva004C2127 is rowed in its home unit; this copy was a duplicate definition.
