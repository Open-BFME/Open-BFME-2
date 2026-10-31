// cl: /I. /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/Libraries/Include /Ireference/shims/bfme2_ascii  /D_CRTIMP=
// stlport
// platformsdk
//
// ProductionUpdate queue members (BFME 2), from the Generals Zero Hour
// ProductionUpdate.cpp and ProductionUpdate.h.
//
// Target facts. The ProductionUpdateInterface vftable 0x00C51478 sits at
// +0x20 (after UpdateModule), so these members get `this` at +0x20: the
// object is at [this-0x18] and the module data at [this-0x1C]. Slots 0-22
// are rowed here, except:
// - slot 16 and slot 17 (getProductionCount);
// - slot 10 cancelUnitCreate (0x0049DC50) and slot 12 (0x0049CCF0);
// - slot 15 cancelAndRefundAllProduction (ProductionUpdate.cpp);
// - slot 21 firstProduction, folded into a shared getter.
// Slots without a ZH counterpart keep placeholder names.
// The queue head and tail are at +0x28/+0x2C, the unique id at +0x30 and the
// entry count at +0x34. +0x130 holds a vector of type names (slot 13) and
// +0x13C a flag that disables unit queueing (slot 0).
// addToProductionQueue and removeFromProductionQueue are the rowed 0x0049D526
// and 0x0049D57F, spelled through their Rva view here. The module data keeps
// MaxQueueEntries at +0x28.
// Each entry is a 0x54-byte Rva0049D1B1 (rowed ctor 0x0049D162) with:
// - type +4, object template +8, upgrade +0xC, production id +0x10;
// - percent complete +0x14, cost +0x28, a door/slot index +0x30 (-1 for
//   none), the upgrade's +0x70 copy at +0x38 and +0x3C (set by slot 14);
// - next/prev links at +0x48/+0x4C.
// The unit test (type 1 or 3) is the rowed out-of-line copy 0x00327C1B.
// BFME 2 differences from ZH:
// - queueUpgrade has no canProduceUpgrade check.
// - canAffordUpgrade and calcCostToBuild also take the object.
// - the withdrawal and refund are recorded against the player's +0x3BC
//   tracker, and the refund is the cost stored on the entry.
// - when the object's castle-member module (0x00395708) has its data flag
//   +0x18 set, the cost is also stored as a float at object +0x324.
// - addUpgrade and removeUpgrade take a trailing 0.
// - unit matches go through ThingTemplate::isEquivalentTo.
// - xfer is at version 7. Each entry also carries +0x18, +0x1C, quantities
//   +0x20/+0x24, the cost, the +0x34 flag and the slot; versions 4 and 5 add
//   a dummy Real, list<int> and Bool per entry. The tail keeps an unused
//   uint, the +0x118..+0x120 fields, the doors, both flag sets (0x000BB710)
//   and the version 2/3/6/7 fields.
// The STL containers come from STLport with the bfmelist/bfmealloc shims; a
// hand-written list view puts the dummy list's allocator temporary in a new
// frame slot, where retail reuses the dead parameter slot.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include "unicode_string.h"
#include "Lib/Coord3D.h"
#include <string.h>
// Preserve the local STLport max overload below.
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <bitset>
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
enum ModelConditionFlagType { MODEL_NONE=0 };
enum DisabledType { DISABLED_NONE=0 };
enum KindOfType { KINDOF_NONE=0 };
enum CellShroudStatus { SHROUD_NONE=0 };
class Drawable; class Team; struct CreateMask; class Rva0049CD4FArg;

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;


class Thing;
class ModuleData;
class Object;
class Player;
class Upgrade;


// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>

// The Drawable list uses the native 12-byte node pool, not the generic
// allocator. Keep these definitions visible: declaration-only trials enlarge
// update's stack frame, while these provider definitions preserve its bytes.
// Same providers as stlport_list_drawable_base_ctor.cpp and
// AIUpdateInterface_voiceResponses_Rva0026B25A.cpp (0x00239BB0/0x00239BD8).
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &a)
    : _M_node(a, (_List_node<Drawable *> *)0)
{
    _List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
    node->_M_next = node;
    node->_M_prev = node;
    _M_node._M_data = node;
}
template <> __declspec(noinline)
_List_node<Drawable *> *list<Drawable *, allocator<Drawable *> >::_M_create_node(Drawable *const &value)
{
    _List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
    if (&node->_M_data != 0) node->_M_data = value;
    return node;
}
}

// Keep the inlined node comparison local, as in GameClientXfer.cpp, so
// this unit does not emit an incompatible STLport base-iterator COMDAT.
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _List_iterator<T, L> &a,
                              const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include <vector>

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

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

Xfer *Rva00460216XferList(Xfer *xfer, _STL::list<int> *list);
Xfer *xferAsciiStringVector(Xfer *xfer, _STL::vector<AsciiString> *vec);

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
	virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74();
	virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84();
	virtual void v85(); virtual void v86(); virtual void v87();
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle) = 0; // slot 88
};

extern AudioManager *TheAudio;

// ModelConditionFlags-sized bit set (0x4C bytes) with the rowed member xfer.
template<int NUMBITS> class BitFlags
{
public:
	void xfer(Xfer *xfer);
 unsigned int test(unsigned bit) const { return m_words[bit>>5] & (1u << (bit&31)); }
 void clear() { memset(m_words,0,sizeof(m_words)); }
 void set(unsigned bit,bool value=true) { if(value) m_words[bit>>5] |= 1u << (bit&31); else m_words[bit>>5] &= ~(1u << (bit&31)); }
private:
	unsigned int m_words[(NUMBITS+31)/32];
};

enum CanMakeType
{
	CANMAKE_OK = 0,
	CANMAKE_NO_PREREQ,
	CANMAKE_NO_MONEY,
	CANMAKE_FACTORY_IS_DISABLED,
	CANMAKE_QUEUE_FULL
};

enum ProductionID
{
	PRODUCTIONID_INVALID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_3E = 0x3E
};

struct Rva0049D0DEMask
{
	UnsignedInt m_bits[1];
};

class Image;
#include "../../../../Include/Common/ThingTemplate.h"

enum ObjectID; class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *,Team *,const CreateMask *,ObjectID);
	const ThingTemplate *findTemplate(const AsciiString &key); // findTemplate
};

extern ThingFactory *TheThingFactory;

enum UpgradeType
{
	UPGRADE_TYPE_PLAYER = 0,
	UPGRADE_TYPE_OBJECT = 1
};

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID = 0,
	UPGRADE_STATUS_IN_PRODUCTION = 1
};

enum ProductionType
{
	PRODUCTION_INVALID = 0,
	PRODUCTION_UNIT,
	PRODUCTION_UPGRADE,
	PRODUCTION_HORDE_UNIT
};

class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType() const { return m_type; }
	UnsignedInt calcCostToBuild(Player *player, UnsignedInt requester) const;

	const AsciiString &getUpgradeName() const { return m_name; }

	char m_unknown00[4];
	UpgradeType m_type; // +4
	AsciiString m_name; // +8
	char m_unknown0C[0x28-0xC];
	AsciiString m_displayName;
	char m_unknown2C[0x40-0x2C];
	void *m_researchSound;
	int m_evaEvent;
	void *m_unitSound;
	char m_unknown4C[0x70-0x4C];
	Int m_bfme70; // +0x70
};

class UpgradeCenter
{
public:
	Bool rva0026F11A(Player *player, const UpgradeTemplate *upgrade, Object *obj, Bool displayReason); // canAffordUpgrade
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class Rva0039B795
{
	char m_unknown00[4];
};

class Rva0039B7AD;

// Money.
class Rva003B0D7C
{
public:
	UnsignedInt countMoney() const { return *reinterpret_cast<const UnsignedInt *>(m_unknown00+4); }
	UnsignedInt withdraw(UnsignedInt amount, Rva0039B795 *tracker, bool flag); // withdraw
	void rva003B0D7C(Int amount, Rva0039B7AD *tracker, bool flag); // deposit

private:
	char m_unknown00[0xC];
};

// The lookup's existing address-derived owner is retained: neither WB helper
// carries an original name. Native GetEntryToProcess passes Player+0x738 to
// both this RET12 lookup and the RET8, float-returning progress query.
class Rva0037EE4C
{
public:
	Int rva0037EE4C(const ThingTemplate *, Int, Int);
	char m_unknown00[0x14];
};

class Rva002A7461;
class Player
{
public:
 Rva002A7461 *revivalGate() { return reinterpret_cast<Rva002A7461 *>(reinterpret_cast<char *>(this)+0x60); }
	Bool allowedToBuild(const ThingTemplate *) const;
	void onUnitCreated(Object *,Object *);
	Rva003B0D7C *getMoney() { return &m_money; }
	Bool rva002AB87D(const UpgradeTemplate *upgrade) const; // hasUpgradeComplete
	Bool rva002AA8EF(const UpgradeTemplate *upgrade) const; // hasUpgradeInProduction
	Upgrade *addUpgrade(const UpgradeTemplate *upgrade, UpgradeStatusType status, Int flag); // addUpgrade
	void removeUpgrade(const UpgradeTemplate *upgrade, Int flag); // removeUpgrade

	char m_unknown00[0x54];
	Int m_playerIndex;
	char m_unknown58[0x90-0x58];
	Rva003B0D7C m_money; // +0x90
	char m_unknown9C[0x2ec-0x9c];
	Team *m_defaultTeam;
	char m_unknown2F0[0x3bc-0x2f0];
	Rva0039B795 m_tracker; // +0x3BC
	char m_unknown3C0[0x738 - 0x3C0];
	Rva0037EE4C m_revivalTracker; // +0x738 (WB uses +0x740)
};

enum ObjectID
{
	INVALID_ID = 0
};

enum ExitDoorType
{
	DOOR_1 = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

#define _GAME_TYPE_H_
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Module;

// ZH ExitInterface slots 0..10 (BFME 1 UpdateModule.h); BFME 2 adds slot 11.
class ExitInterface
{
public:
	virtual Bool isExitBusy() const = 0;
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject) = 0;
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;
	virtual void exitObjectByBudding(Object *newObj, Object *budHost) = 0;
	virtual void unreserveDoorForExit(ExitDoorType exitDoor) = 0;
	virtual void exitObjectInAHurry(Object *newObj) = 0;
	virtual void setRallyPoint(const void *pos) = 0;
	virtual const void *getRallyPoint() const = 0;
	virtual Bool useSpawnRallyPoint() const = 0;
	virtual Bool getNaturalRallyPoint(void *rallyPoint, Bool offset) const = 0;
	virtual Bool getExitPosition(void *exitPosition, float *orientation) const = 0;
	virtual void exitSlot11() = 0;
};

class BehaviorModule;
class ProductionUpdateInterface;

class ProductionContainView; class ProductionAIUpdateView;
class Object
{
public:
 const ThingTemplate *getTemplate() const { return m_template; }
	Player *getControllingPlayer() const;
 void rva0028AE6D();
 __forceinline void setProductionCondition() { if(m_modelConditionFlags.test(332)) return; m_modelConditionFlags.set(332); rva0028AE6D(); }
 __forceinline void clearProductionCondition() { if(!m_modelConditionFlags.test(332)) return; m_modelConditionFlags.set(332,false); rva0028AE6D(); } void rva0028CFB2(const int *,const int *);
 void setProducer(Object *); CellShroudStatus getShroudStatusForPlayer(int) const;
 void setSpecialModelConditionState(ModelConditionFlagType,unsigned int);
 void teleportTo(const Coord3D *,bool); void setStatus(ObjectStatusTypes,bool);
 void updateUpgradeModules(); void setDisabledUntil(DisabledType,unsigned int);
 bool clearDisabled(DisabledType); bool isKindOf(KindOfType) const;
 bool isLocallyControlled() const; void rva00293077(const void *);
 void rva002900FA(int);
	ExitInterface *getObjectExitInterface() const;
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool hasUpgrade(const UpgradeTemplate *upgrade) const; // hasUpgrade
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const; // affectedByUpgrade
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }

	char m_unknown00[4]; const ThingTemplate *m_template;
 char m_unknown08[0x38-8]; Coord3D m_position;
 char m_unknown44[0x74-0x44]; ObjectID m_id; ObjectID m_containerID;
 char m_unknown7C[0x88-0x7c]; AsciiString m_name;
 char m_unknown8C[0x10c-0x8c]; BitFlags<591> m_modelConditionFlags;
 char m_unknown158[0x244-0x158];
 BehaviorModule **m_behaviors; // +0x244, null-terminated
	char m_unknown248[8]; ProductionContainView *m_contain;
 char m_unknown254[4]; ProductionAIUpdateView *m_ai;
 char m_unknown25C[8]; void *m_experience;
 char m_unknown268[0x324-0x268];
	Real m_bfme324; // +0x324
 char m_unknown328[0x438-0x328]; unsigned char m_flag438;
 char m_unknown439[0x45c-0x439]; int m_handle45C;

protected:
	Module *findModule(NameKeyType key) const;
};

struct Rva00395708Data
{
	char m_unknown00[0x18];
	Bool m_flag; // +0x18
};

#include "../../../../Include/Common/Module.h"

// Partial access view; native queueUpgrade reads ModuleData+0x18.
class Rva00395708ModuleView : public Module
{
public:
    using Module::m_moduleData;
};

class CastleBehavior
{
public:
	static Module *rva000395708(Object *obj);
};

class ProductionEntry
{
public:
	Bool getProductionObject() const;
};

// ProductionEntry.
class Rva0049D1B1
{
public:
	Rva0049D1B1() throw();
	virtual ~Rva0049D1B1();

	// type 1 or 3, the rowed out-of-line copy 0x00327C1B
	Bool isUnit() const { return ((const ProductionEntry *)this)->getProductionObject(); }
	ProductionType getProductionType() const { return m_type; }
 Int getProductionID() const { return m_productionID; }
	const ThingTemplate *getProductionObject() const { return m_objectToProduce; }
	const UpgradeTemplate *getProductionUpgrade() const { return m_upgradeToResearch; }

	ProductionType m_type; // +4
	const ThingTemplate *m_objectToProduce; // +8
	const UpgradeTemplate *m_upgradeToResearch; // +0xC
	Int m_productionID; // +0x10
	Real m_percentComplete; // +0x14
	Real m_bfme18; // +0x18
	Int m_bfme1C; // +0x1C
	Int m_productionQuantityTotal; // +0x20
	Int m_productionQuantityProduced; // +0x24
	Int m_cost; // +0x28
	ExitDoorType m_exitDoor; // +0x2C
	Int m_bfme30; // +0x30
	Bool m_bfme34; // +0x34
	union { Int m_bfme38; const Image *m_buttonImage; }; // +0x38
	Int m_bfme3C; // +0x3C
	AsciiString m_name; // +40
	Bool m_slave; // +44
	char m_unknown45[3];
	Rva0049D1B1 *m_next; // +0x48
	Rva0049D1B1 *m_prev; // +0x4C
	char m_unknown50[0x54 - 0x50];
};

struct QuantityModifier { AsciiString m_templateName; Int m_quantity; };
class ProductionUpdateModuleData
{
public:
	char m_unknown00[8];
	Int m_numDoorAnimations;
	char m_unknown0C[0x18-0xc];
	UnsignedInt m_constructionCompleteDuration;
	_STL::vector<QuantityModifier> m_quantityModifiers; // +0x1C
	UnsignedInt m_maxQueueEntries; // +0x28
	char m_unknown2C[4]; bool m_noExperience; char m_unknown31[3];
	unsigned m_specialDuration; unsigned m_completeDuration; char m_unknown3C[4];
	bool m_inheritVeterancy; bool m_economyCondition; char m_unknown42[2];
	AsciiString m_economyKey; void *m_economySound;
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

// BehaviorModuleInterface: the per-module interface queries; retail reads
// getProductionUpdateInterface from slot 28 (+0x70).
class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
	virtual void bmi01();
	virtual void bmi02();
	virtual void bmi03();
	virtual void bmi04();
	virtual void bmi05();
	virtual void bmi06();
	virtual void bmi07();
	virtual void bmi08();
	virtual void bmi09();
	virtual void bmi10();
	virtual void bmi11();
	virtual void bmi12();
	virtual void bmi13();
	virtual void bmi14();
	virtual void bmi15();
	virtual void bmi16();
	virtual void bmi17();
	virtual void bmi18();
	virtual void bmi19();
	virtual void bmi20();
	virtual void bmi21();
	virtual void bmi22();
	virtual void bmi23();
	virtual void bmi24();
	virtual void bmi25();
	virtual void bmi26();
	virtual void bmi27();
	virtual ProductionUpdateInterface *getProductionUpdateInterface();	// +0x70
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	void xfer(Xfer *xfer);

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

// BuildAssistant: the observed canMakeUnit slot (+0x60, slot 24) over the real global.
class BuildAssistant;
extern BuildAssistant *TheBuildAssistant;
class BuildAssistantView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual CanMakeType canMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex) const;
};

struct Rva0039BAD2Input;
class Rva0039BAD2 { public: void rva0039BAD2(Rva0039BAD2Input *,Int); };
class ProductionUpdateInterface
{
public:
	virtual CanMakeType rva0049CFCD() const;
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade) const;
	virtual ProductionID requestUniqueUnitID();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);
	virtual void rva0049CC9D(const ThingTemplate *unitType, Bool five);
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *unitType) const;
	virtual Bool queueCreateUnit(const ThingTemplate *,Int,ProductionID,Int,Bool,const AsciiString &,Bool);
	virtual Bool rva0049CC36(ProductionID productionID) const;
	virtual void cancelUnitCreate(ProductionID productionID);
	virtual void rva0049CC61(const ThingTemplate *unitType);
	virtual void i12();
	virtual void rva0049F8A9(const ThingTemplate *unitType, Bool cancel);
	virtual void rva0049CC15(ProductionID productionID, Int value);
	virtual void cancelAndRefundAllProduction();
	virtual void rva0049DEC8();
	virtual void i17();
	virtual UnsignedInt rva0049CEAE(const ThingTemplate *unitType) const;
	virtual UnsignedInt rva0049CEE1(Int value) const;
	virtual UnsignedInt rva0049D0DE(const Rva0049D0DEMask *mask) const;
	virtual const Rva0049D1B1 *firstProduction() const;
	virtual const Rva0049D1B1 *nextProduction(const Rva0049D1B1 *p) const;
};

class DieModuleInterface
{
public:
	virtual void onDie();
};

class Rva0049D526
{
public:
	void rva0049D526(void *entry); // addToProductionQueue
	void rva0049D57F(void *entry); // removeFromProductionQueue
};

enum
{
	DOOR_COUNT_MAX = 4
};

struct DoorInfo
{
	UnsignedInt m_doorOpenedFrame;
	UnsignedInt m_doorWaitOpenFrame;
	UnsignedInt m_doorClosedFrame;
	Bool m_holdOpen;
};

// Native-only supplemental views for the update bank. No inferred full class ABI.
#include "Code/GameEngine/Include/Common/BfmeAudioEventPrefix136.h"
// bfme link decl-only begin
namespace _STL { template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base(); }
// bfme link decl-only end
class Rva002D9531 { public: void rva002D9531(int); };
class Rva0033F15DDwordSlot { public: void set(int); };
class Rva002AE98B { public: float rva002AE98B(const AsciiString *); };
struct Rva002A7557In;
class Rva002A7461 { public: bool rva002A7557(Rva002A7557In *,int); };
class Rva0037E6E8 { public: int rva0037E649(int,Object *); float rva0037E815(int,Object *); };
class Rva0037E421 { public: void *rva0037E7A5(int); void *rva0037E451(int); void *rva0037E421(int); };
struct ProductionRevivalCount { char m_pad[0x98]; int m_98; };
class UnitRevivalTracker { public: bool productionSystemQueueCreateUnit(int,int,const Image **); Object *productionSystemNewObject(unsigned int,const Coord3D *); };
class Rva0039ADF3 { public: bool rva0039AE04() const; };
class ExperienceTracker { public: void rva0039B315(float,bool,bool,bool,bool); };
struct ProductionExperienceView { char pad[0x24]; int level; int next; };
class Rva003BD306Target { public: void rva0039B2C7(int,bool); };
class Rva004DC8E7AsciiField { public: AsciiString get() const; };
#include "../../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;
class Rva00358752Opaque { public: Object *lookupUnitByValue(AsciiString); };
#include "../../../Common/Thing/thing.h"
class Rva002390CB { public: int opaque00; OpaqueRefElement4 ref; ~Rva002390CB() { if(ref.referent) ref.referent->Release_Ref(); } };
class Drawable { public:
 void setFullyObscuredByShroud(bool); void rva002723C0(int); void rva00274176(bool);
 void setDrawableHidden(bool); void fadeIn(unsigned int);
 Rva002390CB rva0049D114();
 // Native shared empty RET hook; owner/identity still needs fold proof.
 void rva000B3FD0();
};
class Rva002707FA { public: void rva002707FA(unsigned char); };
class Rva0028CBFD { public: void rva0028CBFD(); };
class SlaveWatcherBehavior { public: void rva00484869(int); };
struct CreateMask { unsigned int bits[4]; CreateMask() { memset(bits,0,sizeof(bits)); } };
struct ProductionPlayerListView { char pad[0x10]; Player *localPlayer; };
class PlayerList; extern PlayerList *ThePlayerList;
struct ProductionAIDataView { char pad[0xbb]; bool createdFlag; };
class Pathfinder { public: int MoveAlliesAwayFromDestination(Object *,const Coord3D *,const Coord3D *); };
struct ProductionAIView { char pad[0x10]; Pathfinder *pathfinder; Pathfinder *getPathfinder() const { return pathfinder; } char pad14[4]; ProductionAIDataView *data; };
class AI; extern AI *TheAI;
// Shared writable timing owners and door-state tables are reconciled across
// their existing consumers; the globals keep one definition at each address.
extern int BfmeLogicFramesPerSecond;
extern int BfmeClientFramesPerSecond;
extern unsigned int ProductionDoorOpeningFlags[4];
extern unsigned int ProductionDoorClosingFlags[4];
extern unsigned int ProductionDoorWaitingOpenFlags[4];
enum EvaEventID { EVA_NONE=0 };
class Eva { public: bool reportEvaEvent(EvaEventID,const Coord3D *,const Coord3D *); };
extern Eva *TheEva;
enum RadarEventType { RADAR_NONE=0 };
class Radar { public: void createEvent(const Coord3D *,RadarEventType,float); };
extern Radar *TheRadar;
class FXList { public: static void doFXObj(const FXList *,const Object *,const Object *); };
class FXListStore { public: const FXList *findFXList(const char *) const; };
extern FXListStore *TheFXListStore;
class GameTextInterface { public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0c();
 virtual void s10();virtual void s14();virtual void s18();virtual void s1c();
 virtual void s20();virtual void s24();virtual void s28();virtual void s2c();
 virtual void s30();virtual void s34();virtual void s38();
 virtual UnicodeString fetch(const char *,bool * =0);
};
extern GameTextInterface *TheGameText;
class InGameUI; extern InGameUI *TheInGameUI;
class ControlBar; extern ControlBar *TheControlBar;
struct ProductionControlBarView { char pad[0x28]; bool dirty; };
struct ProductionDrawableView { char pad[0xfc]; Object *object; };
class TerrainLogic; extern TerrainLogic *TheTerrainLogic;
class RespawnUpdate { public: void triggerRevival(Object *); };
struct Rva0028F633 { Rva0028F633(int,int); unsigned int bits[32]; };
namespace _STL {
}
class DrawableList: public _STL::list<Drawable *> {public: ~DrawableList() throw();};
class PickAndPlayInfo;
class PickAndPlayInfo { public: PickAndPlayInfo(); char pad[8]; Drawable *drawTarget; char tail[24]; };
class GameMessage { public: enum Type { MSG_NONE=0 }; };
bool pickAndPlayUnitVoiceResponse(const DrawableList *,GameMessage::Type,PickAndPlayInfo *);
// WB1207EF0 and native caller prove this member ABI; provider corrected and byte-verified.
struct Rva0049DF81Input;

class ProductionAudioView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual unsigned int addEvent(const BfmeAudioEventPrefix136 *);
virtual void s68();
virtual void stopEvent(unsigned int);
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual bool isPlaying(unsigned int);
};

class ProductionInGameUIView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void message(UnicodeString,...);
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10c();
virtual void s110();
virtual void s114();
virtual void s118();
virtual void s11c();
virtual void s120();
virtual void s124();
virtual void s128();
virtual Drawable *getSelectedDrawable();
};

class ProductionAIUpdateView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10c();
virtual void s110();
virtual void s114();
virtual void s118();
virtual void s11c();
virtual void s120();
virtual void s124();
virtual void s128();
virtual void s12c();
virtual void s130();
virtual void s134();
virtual void s138();
virtual void s13c();
virtual void s140();
virtual void s144();
virtual void s148();
virtual void s14c();
virtual void s150();
virtual void s154();
virtual void s158();
virtual void s15c();
virtual void s160();
virtual void s164();
virtual bool s168();
virtual void s16c();
virtual void s170();
virtual void s174();
virtual void s178();
virtual void s17c();
virtual void s180();
virtual void s184();
virtual void s188();
virtual void s18c();
virtual void s190();
virtual void s194();
virtual void s198();
virtual void s19c();
virtual void s1a0();
virtual void s1a4();
virtual void s1a8();
virtual void s1ac();
virtual void s1b0();
virtual void s1b4();
virtual void s1b8();
virtual void s1bc();
virtual void s1c0();
virtual void s1c4();
virtual void s1c8();
virtual void s1cc();
virtual void s1d0();
virtual void s1d4();
virtual void s1d8();
virtual void s1dc();
virtual void s1e0();
virtual void s1e4();
virtual void s1e8();
virtual void s1ec();
virtual void s1f0();
virtual void s1f4();
virtual void s1f8();
virtual void s1fc();
virtual void s200();
virtual void s204();
virtual void s208();
virtual void s20c();
virtual void s210();
virtual void s214();
virtual void s218();
virtual void s21c();
virtual void s220();
virtual void s224();
virtual void s228();
virtual void s22c();
virtual void s230();
virtual void s234(Object *);
};

class ProductionSlaveInterface { public:
virtual void s00();
virtual void setMaster(Object *);
};

class ProductionBehaviorView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual ProductionSlaveInterface *getSlave();
};

class ProductionHordeInterface { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual AsciiString getTemplateName();
virtual int getExtraCount();
};

class ProductionContainView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual ProductionAIUpdateView *getAI();
virtual ProductionHordeInterface *getHorde();
};

class ProductionTerrainView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void terrainHeight(float,float,float *,int,int);
};

class ProductionUpdate : public UpdateModule, public ProductionUpdateInterface, public DieModuleInterface
{
public:
 virtual UpdateSleepTime update();
 void rva0049D3BC(); void rva0049CD24(Object *);
 virtual Bool queueCreateUnit(const ThingTemplate *,Int,ProductionID,Int,Bool,const AsciiString &,Bool);
 void rva0049E368(); void rva0049CF25();
 void rva0049DF81(Rva0049DF81Input *,Object *);
 Int calcTotalProductionFrames(Rva0049CD4FArg *);

	virtual CanMakeType rva0049CFCD() const;
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade) const;
	virtual ProductionID requestUniqueUnitID();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);
	virtual void rva0049CC9D(const ThingTemplate *unitType, Bool five);
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *unitType) const;
	virtual Bool rva0049CC36(ProductionID productionID) const;
	virtual void rva0049CC61(const ThingTemplate *unitType);
	virtual void rva0049F8A9(const ThingTemplate *unitType, Bool cancel);
	virtual void rva0049CC15(ProductionID productionID, Int value);
	virtual void cancelAndRefundAllProduction();
	virtual void rva0049DEC8();
	virtual UnsignedInt rva0049CEAE(const ThingTemplate *unitType) const;
	virtual UnsignedInt rva0049CEE1(Int value) const;
	virtual UnsignedInt rva0049D0DE(const Rva0049D0DEMask *mask) const;
	virtual const Rva0049D1B1 *nextProduction(const Rva0049D1B1 *p) const;

	static ProductionUpdateInterface *getProductionUpdateInterfaceFromObject(Object *obj);
	const Rva0049D1B1 *GetEntryToProcess();

protected:
	virtual void xfer(Xfer *xfer);

	const ProductionUpdateModuleData *getProductionUpdateModuleData() const
	{
		return (const ProductionUpdateModuleData *)m_moduleData;
	}
	void addToProductionQueue(Rva0049D1B1 *production)
	{
		((Rva0049D526 *)this)->rva0049D526(production);
	}
	void removeFromProductionQueue(Rva0049D1B1 *production)
	{
		((Rva0049D526 *)this)->rva0049D57F(production);
	}

	Rva0049D1B1 *m_productionQueue; // +0x28
	Rva0049D1B1 *m_productionQueueTail; // +0x2C
	ProductionID m_uniqueID; // +0x30
	UnsignedInt m_productionCount; // +0x34
	UnsignedInt m_constructionCompleteFrame; // +0x38
	DoorInfo m_doors[DOOR_COUNT_MAX]; // +0x3C
	BitFlags<591> m_clearFlags; // +0x7C
	BitFlags<591> m_setFlags; // +0xC8
	Bool m_flagsDirty; // +0x114
	UnsignedInt m_bfme118; // +0x118
	Bool m_bfme11C; // +0x11C
	ObjectID m_bfme120; // +0x120
	_STL::list<ObjectID> m_createdAuxiliary; // +124
	UnsignedInt m_bfme128; // +0x128
	AudioHandle m_bfme12C; // +0x12C
	_STL::vector<AsciiString> m_bfme130; // +0x130
	Bool m_bfme13C; // +0x13C
};

// WB 0x1203E30 names this routine. Native 49CFEB..49D07A first prefers
// unit entries with KindOfType bit14, then horde entries whose revival
// progress is at least one, otherwise the head. Both walks use the native
// interface's slot22 (+0x58); WB's corresponding slot is +0x54.
const Rva0049D1B1 *ProductionUpdate::GetEntryToProcess()
{
	const Rva0049D1B1 *entry;
	for (entry = m_productionQueue; entry; entry = nextProduction(entry))
	{
		if (entry->isUnit() && (entry->getProductionObject()->m_kindof[0] & (1 << 14)))
			return entry;
	}
	for (entry = m_productionQueue; entry; entry = nextProduction(entry))
	{
		if (entry->getProductionType() == PRODUCTION_HORDE_UNIT)
		{
			Rva0037EE4C *tracker = &getObject()->getControllingPlayer()->m_revivalTracker;
			Int productionID = entry->m_productionID;
			Int index = tracker->rva0037EE4C(entry->getProductionObject(), productionID, 0);
			if (reinterpret_cast<Rva0037E6E8 *>(tracker)->rva0037E815(index, getObject()) >= 1.0f)
				return entry;
		}
	}
	return m_productionQueue;
}

// ?queueUpgrade@ProductionUpdate@@UAE_NPBVUpgradeTemplate@@@Z @0x0049D867 315B
Bool ProductionUpdate::queueUpgrade( const UpgradeTemplate *upgrade )
{

	// sanity
	if( upgrade == NULL )
		return FALSE;

	// get the player
	Player *player = getObject()->getControllingPlayer();

	// sanity check to make sure we can build this upgrade
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
			TheUpgradeCenter->rva0026F11A( player, upgrade, getObject(), FALSE ) == FALSE )
		return FALSE;
	else if( upgrade->getUpgradeType() == UPGRADE_TYPE_OBJECT &&
					 (getObject()->hasUpgrade( upgrade ) == TRUE ||
					  getObject()->affectedByUpgrade( upgrade ) == FALSE) )
		return FALSE;

	// you cannot queue the production of an upgrade twice in this queue
	if( isUpgradeInQueue( upgrade ) == TRUE )
		return FALSE;

	//
	// you cannot queue a player upgrade production if you are producing one already somewhere else
	// (or that somewhere else could even possibly be here)
	//
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
      (player->rva002AB87D( upgrade ) || player->rva002AA8EF( upgrade )) )
		return FALSE;

	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return FALSE;

	// allocate a new production entry
	Rva0049D1B1 *production = new Rva0049D1B1;

	// assing production entry data
	production->m_productionID = 0;
	production->m_type = PRODUCTION_UPGRADE;
	production->m_upgradeToResearch = upgrade;
	production->m_bfme38 = upgrade->m_bfme70;

	// take the cost for the build away from the player
	production->m_cost = upgrade->calcCostToBuild( player, reinterpret_cast<UnsignedInt>(getObject()) );
	player->getMoney()->withdraw( production->m_cost, &player->m_tracker, true );

	Object *obj = getObject();
	Module *castle = CastleBehavior::rva000395708( obj );
	if( castle && ((const Rva00395708Data *)((Rva00395708ModuleView *)castle)->m_moduleData)->m_flag )
		obj->m_bfme324 = (Real)production->m_cost;

	// tie to the end of the production queue
	addToProductionQueue( production );

	// add this upgrade as in progress in the player
	player->addUpgrade( upgrade, UPGRADE_STATUS_IN_PRODUCTION, 0 );

	return TRUE;  // queued

}  // end queueUpgrade

// ?cancelUpgrade@ProductionUpdate@@UAEXPBVUpgradeTemplate@@@Z @0x0049D9A2 146B
void ProductionUpdate::cancelUpgrade( const UpgradeTemplate *upgrade )
{

	// sanity
	if( upgrade == NULL )
		return;

	// get the player
	Player *player = getObject()->getControllingPlayer();

	// sanity, you can't cancel it if the player isn't actually building one
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER && player->rva002AA8EF( upgrade ) == FALSE )
		return;

	//
	// find the production entry for this upgrade in the queue here, there can only be one
	// of this type in the queue
	//
	Rva0049D1B1 *production;
	for( production = m_productionQueue; production; production = production->m_next )
	{

		if( production->m_type == PRODUCTION_UPGRADE &&
				production->m_upgradeToResearch == upgrade )
			break;

	}  // end for

	// sanity, entry not found
	if( production == NULL )
		return;

	// refund the cost paid back to the player
	player->getMoney()->rva003B0D7C( production->m_cost, (Rva0039B7AD *)&player->m_tracker, true );

	// remove this production from the queue
	removeFromProductionQueue( production );

	// delete production instance
	::delete production;

	//
	// remove the IN_PRODUCTION status of this upgrade from the player, object upgrades don't
	// have any other IN_PRODUCTION status other than their existence in the build queue
	//
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER )
		player->removeUpgrade( upgrade, 0 );

}  // end cancelUpgrade

// ?rva0049CFCD@ProductionUpdate@@UBE?AW4CanMakeType@@XZ @0x0049CFCD 30B
// Slot 0, where ZH has canQueueCreateUnit; BFME 2's takes no argument and
// refuses while the +0x13C flag is set.
CanMakeType ProductionUpdate::rva0049CFCD() const
{
	if( m_bfme13C )
		return CANMAKE_FACTORY_IS_DISABLED;

	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return CANMAKE_QUEUE_FULL;

	return CANMAKE_OK;
}

// ?canQueueUpgrade@ProductionUpdate@@UBE?AW4CanMakeType@@PBVUpgradeTemplate@@@Z @0x0049CFA9 36B
CanMakeType ProductionUpdate::canQueueUpgrade( const UpgradeTemplate *upgrade ) const
{
	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return CANMAKE_QUEUE_FULL;

	return getObject()->testStatus( OBJECT_STATUS_BFME_3E ) ? CANMAKE_FACTORY_IS_DISABLED : CANMAKE_OK;
}

// ?requestUniqueUnitID@ProductionUpdate@@UAE?AW4ProductionID@@XZ @0x0049E142 10B
ProductionID ProductionUpdate::requestUniqueUnitID( void )
{
	ProductionID tmp = m_uniqueID;
	m_uniqueID = (ProductionID)(m_uniqueID+1);
	return tmp;
}

// ?rva0049CC9D@ProductionUpdate@@UAEXPBVThingTemplate@@_N@Z @0x0049CC9D 83B
// Cancels the last one (or five) queued units of the type, newest first.
void ProductionUpdate::rva0049CC9D( const ThingTemplate *unitType, Bool five )
{
	Int count = five ? 5 : 1;
	Rva0049D1B1 *production = m_productionQueueTail;
	while( count )
	{
		if( production == NULL )
			break;
		if( production->isUnit() && unitType->isEquivalentTo( production->m_objectToProduce ) )
		{
			cancelUnitCreate( (ProductionID)production->m_productionID );
			--count;
			production = m_productionQueueTail;
		}
		else
			production = production->m_prev;
	}
}

// ?isUpgradeInQueue@ProductionUpdate@@UBE_NPBVUpgradeTemplate@@@Z @0x0049CDF9 47B
Bool ProductionUpdate::isUpgradeInQueue( const UpgradeTemplate *upgrade ) const
{
	const Rva0049D1B1 *production;

	for( production = firstProduction(); production; production = nextProduction( production ) )
		if( production->getProductionType() == PRODUCTION_UPGRADE &&
				production->getProductionUpgrade() == upgrade )
			return TRUE;

	return FALSE;  // not in queue

}  // end isUpgradeInQueue

// ?countUnitTypeInQueue@ProductionUpdate@@UBEIPBVThingTemplate@@@Z @0x0049CE28 59B
UnsignedInt ProductionUpdate::countUnitTypeInQueue( const ThingTemplate *unitType ) const
{
	UnsignedInt count = 0;
	const Rva0049D1B1 *production;

	for( production = firstProduction(); production; production = nextProduction( production ) )
		if( production->getProductionType() == PRODUCTION_UNIT &&
				unitType->isEquivalentTo( production->getProductionObject() ) )
			count++;

	return count;

}  // end countUnitTypeInQueue

// ?rva0049CC36@ProductionUpdate@@UBE_NW4ProductionID@@@Z @0x0049CC36 43B
// Is a unit with this production id in the queue.
Bool ProductionUpdate::rva0049CC36( ProductionID productionID ) const
{
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
		if( production->isUnit() && production->m_productionID == productionID )
			return TRUE;

	return FALSE;
}

// ?rva0049CC61@ProductionUpdate@@UAEXPBVThingTemplate@@@Z @0x0049CC61 60B
// Cancels the oldest queued unit of the type.
void ProductionUpdate::rva0049CC61( const ThingTemplate *unitType )
{
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
	{
		if( production->isUnit() && unitType->isEquivalentTo( production->m_objectToProduce ) )
		{
			cancelUnitCreate( (ProductionID)production->m_productionID );
			return;
		}
	}
}

// ?rva0049F8A9@ProductionUpdate@@UAEXPBVThingTemplate@@_N@Z @0x0049F8A9 113B
// Without the flag, records the type's name in the +0x130 list; with it,
// cancels every unfinished queued unit of the type.
void ProductionUpdate::rva0049F8A9( const ThingTemplate *unitType, Bool cancel )
{
	if( !cancel )
	{
		m_bfme130.push_back( unitType->getName() );
		return;
	}

	Rva0049D1B1 *production = m_productionQueue;
	while( production )
	{
		ProductionType type = production->m_type;
		if( production->m_percentComplete < 100.0f &&
				(type == PRODUCTION_UNIT || type == PRODUCTION_HORDE_UNIT) &&
				unitType->isEquivalentTo( production->m_objectToProduce ) )
		{
			Rva0049D1B1 *next = production->m_next;
			cancelUnitCreate( (ProductionID)production->m_productionID );
			production = next;
		}
		else
			production = production->m_next;
	}
}

// ?rva0049CC15@ProductionUpdate@@UAEXW4ProductionID@@H@Z @0x0049CC15 33B
// Sets the +0x3C field of the entry with this production id.
void ProductionUpdate::rva0049CC15( ProductionID productionID, Int value )
{
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
	{
		if( production->m_productionID == productionID )
		{
			production->m_bfme3C = value;
			return;
		}
	}
}

// ?rva0049CEAE@ProductionUpdate@@UBEIPBVThingTemplate@@@Z @0x0049CEAE 51B
// Counts the queued units (and hordes) of the type.
UnsignedInt ProductionUpdate::rva0049CEAE( const ThingTemplate *unitType ) const
{
	UnsignedInt count = 0;
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
		if( production->isUnit() && unitType->isEquivalentTo( production->m_objectToProduce ) )
			count++;
	return count;
}

// ?rva0049CEE1@ProductionUpdate@@UBEIH@Z @0x0049CEE1 27B
// Counts the entries whose +0x30 field equals the value.
UnsignedInt ProductionUpdate::rva0049CEE1( Int value ) const
{
	UnsignedInt count = 0;
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
		if( value == production->m_bfme30 )
			count++;
	return count;
}

// ?getProductionUpdateInterfaceFromObject@ProductionUpdate@@SAPAVProductionUpdateInterface@@PAVObject@@@Z @0x0049CEFC 41B
// ZH's static lookup: the first behavior module that answers
// getProductionUpdateInterface.
ProductionUpdateInterface *ProductionUpdate::getProductionUpdateInterfaceFromObject( Object *obj )
{
	if( obj == NULL )
		return NULL;

	for( BehaviorModule **behaviorModule = obj->getBehaviorModules(); *behaviorModule; ++behaviorModule )
	{
		ProductionUpdateInterface *pui = (*behaviorModule)->getProductionUpdateInterface();
		if( pui )
			return pui;
	}

	return NULL;
}

// ?rva0049D0DE@ProductionUpdate@@UBEIPBURva0049D0DEMask@@@Z @0x0049D0DE 54B
// Counts the entries whose +0x30 index (-1 for none) is set in the mask.
UnsignedInt ProductionUpdate::rva0049D0DE( const Rva0049D0DEMask *mask ) const
{
	UnsignedInt count = 0;
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
	{
		UnsignedInt index = production->m_bfme30;
		if( index != (UnsignedInt)-1 && (mask->m_bits[index >> 5] & (1 << (index & 31))) )
			count++;
	}
	return count;
}

// ?nextProduction@ProductionUpdate@@UBEPBVRva0049D1B1@@PBV2@@Z @0x0049E14C 18B
const Rva0049D1B1 *ProductionUpdate::nextProduction( const Rva0049D1B1 *p ) const
{
	return p ? p->m_next : NULL;
}

// ?rva0049DEC8@ProductionUpdate@@UAEXXZ @0x0049DEC8 154B
// Slot 16: cancels and refunds the queue, then sends the object held at
// +0x120 out through door 1 unless it has a RespawnUpdate, and finally
// calls the exit interface's slot 11.
void ProductionUpdate::rva0049DEC8()
{
	cancelAndRefundAllProduction();
	ExitInterface *exitInterface = getObject()->getObjectExitInterface();
	ObjectID id = m_bfme120;
	if( id != INVALID_ID )
	{
		Object *obj = TheGameLogic->findObjectByID( id );
		if( obj )
		{
			static NameKeyType key_RespawnUpdate = NAMEKEY( "RespawnUpdate" );
			if( obj->findUpdateModule( key_RespawnUpdate ) == NULL )
				exitInterface->exitObjectViaDoor( obj, DOOR_1 );
		}
	}
	if( exitInterface )
		exitInterface->exitSlot11();
}

// ?xfer@ProductionUpdate@@MAEXPAVXfer@@@Z @0x0049F91A 1192B
// The ZH xfer at version 7. Over ZH it adds the entry's +0x18/+0x1C, cost,
// +0x34 flag and slot, the object's +0x118/+0x11C/+0x120 and four gated
// tails; version 4 and 5 entries carry a dead float, int list and flag.
void ProductionUpdate::xfer( Xfer *xfer )
{
	// extend base class
	UpdateModule::xfer( xfer );
	if( xfer->IsLightCRC() )
		return;

	// version
	Xfer::Version version( 1, 7 );
	*xfer == version;

	// production queue count
	Rva0049D1B1 *production;
	unsigned short productionCount = 0;
	for( production = m_productionQueue; production; production = production->m_next )
		productionCount++;
	*xfer == productionCount;

	// production queue data
	if( xfer->IsStoring() )
	{
		AsciiString name;

		// write all queue data
		for( production = m_productionQueue; production; production = production->m_next )
		{

			// type
			xfer->XferRawBytes( &production->m_type, sizeof( ProductionType ) );

			// thing/upgrade template name
			switch( production->m_type )
			{
				case PRODUCTION_UNIT:
				case PRODUCTION_HORDE_UNIT:
					name = production->m_objectToProduce->getName();
					break;
				case PRODUCTION_UPGRADE:
					name = production->m_upgradeToResearch->getUpgradeName();
					break;
				default:
					XferException error;
					bfmeFormatText( &error, 5, 0 );
					_CxxThrowException( &error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo ); __assume(0);
			}
			*xfer == name;

			xfer->XferRawBytes( &production->m_productionID, sizeof( ProductionID ) );
			*xfer == production->m_percentComplete;
			*xfer == production->m_bfme18;
			*xfer == production->m_bfme1C;
			*xfer == production->m_productionQuantityTotal;
			*xfer == production->m_productionQuantityProduced;
			*xfer == production->m_cost;
			*xfer == production->m_bfme34;
			xfer->XferRawBytes( &production->m_exitDoor, sizeof( ExitDoorType ) );
			Int slot = production->m_bfme30;
			*xfer == slot;
			if( version.m_minimum >= 4 )
			{
				Real unusedReal = 0.0f;
				*xfer == unusedReal;
				_STL::list<Int> unusedList;
				Rva00460216XferList( xfer, &unusedList );
			}
			if( version.m_minimum >= 5 )
			{
				Bool unusedBool = FALSE;
				*xfer == unusedBool;
			}

		}  // end for

	}  // end if, save
	else
	{
		AsciiString name;

		// the queue should be emtpy now
		if( m_productionQueue != NULL )
		{
			XferException error;
			bfmeFormatText( &error, 5, 0 );
			_CxxThrowException( &error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo ); __assume(0);
		}

		// read each element
		for( unsigned short i = 0; i < productionCount; ++i )
		{

			// allocate new production entry
			production = new Rva0049D1B1;

			// tie to list at end
			if( m_productionQueue == NULL )
				m_productionQueue = production;

			// make any existing tail pointer now point to us, and we point back to them
			if( m_productionQueueTail )
			{
				m_productionQueueTail->m_next = production;
				production->m_prev = m_productionQueueTail;
			}

			// this production entry is now the new tail at the end of the list
			m_productionQueueTail = production;

			// type
			xfer->XferRawBytes( &production->m_type, sizeof( ProductionType ) );

			// thing/upgrade template name
			*xfer == name;
			switch( production->m_type )
			{
				case PRODUCTION_UNIT:
				case PRODUCTION_HORDE_UNIT:
					production->m_objectToProduce = TheThingFactory->findTemplate(name);
					production->m_objectToProduce = production->m_objectToProduce ?
						(const ThingTemplate *)production->m_objectToProduce->getFinalOverride() : NULL;
					break;
				case PRODUCTION_UPGRADE:
					production->m_upgradeToResearch = TheUpgradeCenter->findUpgrade( name );
					break;
			}

			xfer->XferRawBytes( &production->m_productionID, sizeof( ProductionID ) );
			*xfer == production->m_percentComplete;
			*xfer == production->m_bfme18;
			*xfer == production->m_bfme1C;
			*xfer == production->m_productionQuantityTotal;
			*xfer == production->m_productionQuantityProduced;
			*xfer == production->m_cost;
			*xfer == production->m_bfme34;
			xfer->XferRawBytes( &production->m_exitDoor, sizeof( ExitDoorType ) );
			Int slot;
			*xfer == slot;
			production->m_bfme30 = slot;
			if( version.m_minimum >= 4 )
			{
				Real unusedReal = 0.0f;
				*xfer == unusedReal;
				_STL::list<Int> unusedList;
				Rva00460216XferList( xfer, &unusedList );
			}
			if( version.m_minimum >= 5 )
			{
				Bool unusedBool = FALSE;
				*xfer == unusedBool;
			}

		}  // end for, i

	}  // end else, load

	// unique id
	xfer->XferRawBytes( &m_uniqueID, sizeof( ProductionID ) );

	// production count
	*xfer == m_productionCount;

	// construction complete frame
	*xfer == m_constructionCompleteFrame;

	UnsignedInt unused = 0;
	*xfer == unused;
	XferObjectID( xfer, &m_bfme120 );
	*xfer == m_bfme118;
	*xfer == m_bfme11C;

	// door info
	for( Int i = 0; i < DOOR_COUNT_MAX; ++i )
	{
		*xfer == m_doors[ i ].m_doorOpenedFrame;
		*xfer == m_doors[ i ].m_doorWaitOpenFrame;
		*xfer == m_doors[ i ].m_doorClosedFrame;
		*xfer == m_doors[ i ].m_holdOpen;
	}

	// clear flags
	m_clearFlags.xfer( xfer );

	// set flags
	m_setFlags.xfer( xfer );

	// flags dirty
	*xfer == m_flagsDirty;

	if( version.m_minimum >= 2 )
		*xfer == m_bfme128;
	if( version.m_minimum >= 3 && TheAudio )
		TheAudio->xferAudioHandle( xfer, &m_bfme12C );
	if( version.m_minimum >= 6 )
		xferAsciiStringVector( xfer, &m_bfme130 );
	if( version.m_minimum >= 7 )
		*xfer == m_bfme13C;

}  // end xfer


void ProductionUpdate::rva0049CF25()
{
 for (const Rva0049D1B1 *entry=m_productionQueue;entry;entry=(m_productionQueue ? nextProduction(entry) : nextProduction(entry))) {
  if (entry->m_type!=PRODUCTION_HORDE_UNIT) continue;
  Object *obj=getObject();
  if (!obj) continue;
  Player *player=obj->getControllingPlayer();
  if (!player) continue;
  if (player->revivalGate()->rva002A7557(reinterpret_cast<Rva002A7557In *>(const_cast<ThingTemplate *>(entry->getProductionObject())),1)) continue;
  Rva0037EE4C *tracker=&player->m_revivalTracker;
  if (!tracker) continue;
  int index=tracker->rva0037EE4C(entry->getProductionObject(),entry->getProductionID(),0);
  ProductionRevivalCount *item=reinterpret_cast<ProductionRevivalCount *>(reinterpret_cast<Rva0037E421 *>(tracker)->rva0037E421(index));
  if (item) ++item->m_98;
 }
}

// ZH update supplies the queue/door/unit/upgrade structure; BFME2/WB1204250
// supplies every added revival/companion/condition branch and observed offset.
UpdateSleepTime ProductionUpdate::update()
{
 static NameKeyType respawnKey=NAMEKEY("RespawnUpdate");
 const ProductionUpdateModuleData *productionUpdateModuleData=getProductionUpdateModuleData();
 unsigned int now=TheGameLogic->getFrame();
 Object *us=getObject();
 void *experience=us->m_experience;
 rva0049E368();
 rva0049CF25();
 Rva0049D1B1 *production=const_cast<Rva0049D1B1 *>(GetEntryToProcess());
 if(us->getControllingPlayer()) {
  if(productionUpdateModuleData->m_economyCondition) {
   if(((Rva002AE98B *)us->getControllingPlayer())->rva002AE98B(&productionUpdateModuleData->m_economyKey)<0.0f) {
    us->setProductionCondition();
   } else us->clearProductionCondition();
  }
  if(productionUpdateModuleData->m_economySound) {
   if(((Rva002AE98B *)us->getControllingPlayer())->rva002AE98B(&productionUpdateModuleData->m_economyKey)<0.0f && !(us->m_flag438&1) && !us->testStatus((ObjectStatusTypes)2)) {
    if(!((ProductionAudioView *)TheAudio)->isPlaying(m_bfme12C)) {
     BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4 *)&productionUpdateModuleData->m_economySound,us->m_id);
     ((Rva0033F15DDwordSlot *)&sound)->set(us->getControllingPlayer()->m_playerIndex);
     m_bfme12C=((ProductionAudioView *)TheAudio)->addEvent(&sound);
    }
   } else { ((ProductionAudioView *)TheAudio)->stopEvent(m_bfme12C); m_bfme12C=1; }
  }
 }
 if(productionUpdateModuleData->m_numDoorAnimations>0) rva0049D3BC();
 if(m_bfme128>0) --m_bfme128;
 if(m_constructionCompleteFrame && now-m_constructionCompleteFrame>productionUpdateModuleData->m_constructionCompleteDuration) {
  m_constructionCompleteFrame=0;
  m_clearFlags.set(74,true); m_setFlags.set(74,false); m_flagsDirty=true;
 }
 if(m_flagsDirty==true) { us->rva0028CFB2((const int *)&m_clearFlags,(const int *)&m_setFlags); m_clearFlags.clear(); m_setFlags.clear(); m_flagsDirty=false; }
 if(!production || us->testStatus((ObjectStatusTypes)19)) return UPDATE_SLEEP_NONE;
 Player *player=us->getControllingPlayer();
 if(!player) { removeFromProductionQueue(production); ::delete production; return UPDATE_SLEEP_NONE; }
 if((production->m_type==PRODUCTION_UNIT || production->m_type==PRODUCTION_HORDE_UNIT) && m_bfme120==0 && m_bfme118<=0) {
  bool allowed=player->allowedToBuild(production->getProductionObject());
  bool available=((Rva002A7461 *)((char *)player+0x60))->rva002A7557((Rva002A7557In *)production->getProductionObject(),1);
  if((!allowed || !available) && !production->m_bfme34) {
   if(!available && player==((ProductionPlayerListView *)ThePlayerList)->localPlayer) TheEva->reportEvaEvent((EvaEventID)11,&us->m_position,0);
   return UPDATE_SLEEP_NONE;
  }
 }
 if(production->m_type==PRODUCTION_UPGRADE) {
  const UpgradeTemplate *upgrade=production->m_upgradeToResearch;
  if(upgrade && upgrade->getUpgradeType()==UPGRADE_TYPE_OBJECT && !getObject()->affectedByUpgrade(upgrade)) { cancelUpgrade(upgrade); return UPDATE_SLEEP_NONE; }
 }
 ++production->m_bfme1C;
 int total=calcTotalProductionFrames((Rva0049CD4FArg *)production);
 production->m_percentComplete=(float)production->m_bfme1C/(float)total*100.0f;
 production->m_bfme18=100.0f/(float)total;
 bool ready=false;
 if(production->m_type==PRODUCTION_HORDE_UNIT && &player->m_revivalTracker) {
  int index=player->m_revivalTracker.rva0037EE4C(production->getProductionObject(),production->getProductionID(),0);
  float progress=((Rva0037E6E8 *)&player->m_revivalTracker)->rva0037E815(index,us);
  if(progress>=1.0f && m_bfme128==0) ready=true;
 } else if(production->m_percentComplete>=100.0f) ready=true;
 if(!ready) return UPDATE_SLEEP_NONE;
 switch(production->m_type) {
 case PRODUCTION_UNIT:
 case PRODUCTION_HORDE_UNIT: {
  bool revival=production->m_type==PRODUCTION_HORDE_UNIT;
  ExitInterface *exitInterface=us->getObjectExitInterface();
  if(exitInterface) {
  int numberToTry=production->m_productionQuantityTotal-production->m_productionQuantityProduced;
  for(int i=0;i<numberToTry;++i) {
   ExitDoorType exitDoor=production->m_exitDoor;
   if(production->m_objectToProduce && (production->m_objectToProduce->m_kindof[6]&0x8000)) exitDoor=(ExitDoorType)-2;
   if(exitDoor==(ExitDoorType)-1) { exitDoor=exitInterface->reserveDoorForExit(production->m_objectToProduce,0); production->m_exitDoor=exitDoor; }
   if(exitDoor==(ExitDoorType)-1) continue;
   DoorInfo *door=(exitDoor>=0 && exitDoor<4)? &m_doors[exitDoor] : 0;
   if(productionUpdateModuleData->m_numDoorAnimations>0 && door) {
    if(door->m_doorOpenedFrame==0 && door->m_doorWaitOpenFrame==0 && door->m_doorClosedFrame==0) {
     door->m_doorOpenedFrame=now; m_setFlags.set(ProductionDoorOpeningFlags[exitDoor]); m_flagsDirty=true;
    } else if(door->m_doorWaitOpenFrame!=0) door->m_doorWaitOpenFrame=now;
    else if(door->m_doorClosedFrame!=0) {
     door->m_doorWaitOpenFrame=now;
     m_clearFlags.set(ProductionDoorOpeningFlags[exitDoor],true); m_clearFlags.set(ProductionDoorClosingFlags[exitDoor],true);
     m_setFlags.set(ProductionDoorOpeningFlags[exitDoor],false); m_setFlags.set(ProductionDoorClosingFlags[exitDoor],false);
     m_setFlags.set(ProductionDoorWaitingOpenFlags[exitDoor]); m_flagsDirty=true;
    }
   }
   if(m_constructionCompleteFrame==0) { m_constructionCompleteFrame=now; m_setFlags.set(74); m_flagsDirty=true; }
   if(productionUpdateModuleData->m_numDoorAnimations!=0 && door && door->m_doorWaitOpenFrame==0) continue;
   Object *newObj;
   if(m_bfme120==0) {
    Coord3D pos; pos.z=pos.y=pos.x=0.0f; float angle=0.0f;
    bool havePosition=exitInterface->getExitPosition(&pos,&angle);
    int revivalExperience=0;
    CreateMask mask;
    if(revival) {
     Player *controller=us->getControllingPlayer();
     UnitRevivalTracker *tracker=(UnitRevivalTracker *)&controller->m_revivalTracker;
     void *record=((Rva0037E421 *)tracker)->rva0037E451(production->m_productionID);
     if(record) revivalExperience=*(int *)((char *)record+0xc8);
     newObj=tracker->productionSystemNewObject(production->m_productionID,&pos);
     if(!newObj) { removeFromProductionQueue(production); ::delete production; return UPDATE_SLEEP_NONE; }
     if(newObj->m_handle45C) TheGameLogic->rva0023D0C2(newObj,newObj->m_handle45C);
     else TheGameLogic->rva0023D0C2(newObj,us->m_handle45C);
     if(production->m_name!=AsciiString::TheEmptyString) {
      newObj->m_name=production->m_name;
      if(!((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(production->m_name) && !TheScriptEngine->didUnitExist(production->m_name)) TheScriptEngine->addObjectToCache(newObj,AsciiString(""));
      else TheScriptEngine->rva00357960(production->m_name,newObj);
     }
    } else {
     if(((ProductionAIView *)TheAI)->data->createdFlag) mask.bits[1]|=0x00800000;
     Team *team=us->getControllingPlayer()->m_defaultTeam;
     newObj=TheThingFactory->newObject(production->m_objectToProduce,team,&mask,(ObjectID)0);
     if(!newObj) { removeFromProductionQueue(production); ::delete production; return UPDATE_SLEEP_NONE; }
     if(production->m_name!=AsciiString::TheEmptyString) {
      newObj->m_name=production->m_name;
      if(!((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(production->m_name) && !TheScriptEngine->didUnitExist(production->m_name)) TheScriptEngine->addObjectToCache(newObj,AsciiString(""));
      else TheScriptEngine->rva00357960(production->m_name,newObj);
     }
     if(production->m_slave) {
      static NameKeyType slaveKey=NAMEKEY("SlaveWatcherBehavior");
      Module *watcher=getObject()->findUpdateModule(slaveKey);
      if(watcher) ((SlaveWatcherBehavior *)watcher)->rva00484869(newObj->m_id);
      for(BehaviorModule **behaviorModule=newObj->getBehaviorModules();*behaviorModule;++behaviorModule) {
       ProductionSlaveInterface *slave=((ProductionBehaviorView *)((char *)*behaviorModule+0xc))->getSlave();
       if(slave && getObject()) slave->setMaster(getObject());
      }
     }
     rva0049CD24(newObj);
     if(productionUpdateModuleData->m_specialDuration>0) newObj->setSpecialModelConditionState((ModelConditionFlagType)0x14a,productionUpdateModuleData->m_specialDuration);
     newObj->m_bfme324=(float)production->m_cost;
     TheGameLogic->rva0023D0C2(newObj,us->m_handle45C);
    }
    m_bfme120=newObj->m_id; newObj->setProducer(us);
    if(((Thing *)newObj)->getDrawable() && us->getShroudStatusForPlayer(((ProductionPlayerListView *)ThePlayerList)->localPlayer->m_playerIndex)>=3) ((Thing *)newObj)->getDrawable()->setFullyObscuredByShroud(true);
    void *newExperience=newObj->m_experience;
    if(productionUpdateModuleData->m_inheritVeterancy && newExperience && ((ProductionExperienceView *)experience)->level>=3) ((Rva003BD306Target *)newExperience)->rva0039B2C7(1,0);
    if(experience && !productionUpdateModuleData->m_noExperience && ((Rva0039ADF3 *)experience)->rva0039AE04()) {
     int cost=production->m_objectToProduce->rva0033A69A(0,0,-1);
     if(cost>0) ((ExperienceTracker *)experience)->rva0039B315((float)cost,true,true,true,false);
    }
    if(havePosition) {
     ProductionAIUpdateView *ai=newObj->m_ai;
     if(ai && ai->s168()) {
      pos.z+=250.0f; newObj->teleportTo(&pos,true); ((Thing *)newObj)->setOrientation(angle);
     } else { ((Thing *)newObj)->setOrientation(angle); ((ProductionTerrainView *)TheTerrainLogic)->terrainHeight(pos.x,pos.y,&pos.z,0,0); newObj->teleportTo(&pos,true); }
    }
    const ThingTemplate *thingTemplate=newObj->m_template;
    newObj->setStatus((ObjectStatusTypes)0x5a,true);
    if(thingTemplate->m_buildFadeInOnCreateTime>0.0f) {
     Coord3D rally; if(exitInterface->getNaturalRallyPoint(&rally,true)) ((ProductionAIView *)TheAI)->getPathfinder()->MoveAlliesAwayFromDestination(newObj,&us->m_position,&rally);
    }
    if(production->m_bfme30!=-1) {
     ((_STL::_Base_bitset<32> *)((char *)newObj+0x284))->_M_do_or((const _STL::_Base_bitset<32> &)Rva0028F633(0,production->m_bfme30));
    }
    newObj->updateUpgradeModules();
    Drawable *drawable=((Thing *)newObj)->getDrawable();
    drawable->rva000B3FD0(); ((Rva002707FA *)drawable)->rva002707FA(1);
    BfmeAudioEventPrefix136 voiceCreated(drawable->rva0049D114().ref,0);
    ((Rva002D9531 *)&voiceCreated)->rva002D9531(m_bfme120);
    ((Rva0033F15DDwordSlot *)&voiceCreated)->set(us->getControllingPlayer()->m_playerIndex);
    ((ProductionAudioView *)TheAudio)->addEvent(&voiceCreated);
    us->getControllingPlayer()->onUnitCreated(us,newObj);
    ((Rva0028CBFD *)newObj)->rva0028CBFD();
    if(production->m_productionQuantityTotal==production->m_productionQuantityTotal-production->m_productionQuantityProduced) {
     DrawableList list; list.push_back(drawable); PickAndPlayInfo info; info.drawTarget=((Thing *)us)->getDrawable();
     pickAndPlayUnitVoiceResponse(&list,(GameMessage::Type)0x7da,(PickAndPlayInfo *)&info);
    }
    rva0049DF81((Rva0049DF81Input *)production,newObj);
    float buildDuration=thingTemplate->m_buildFadeInOnCreateTime;
    m_bfme118=(unsigned int)(buildDuration*(float)BfmeLogicFramesPerSecond);
    newObj->setSpecialModelConditionState((ModelConditionFlagType)0xda,m_bfme118);
    newObj->setSpecialModelConditionState((ModelConditionFlagType)0x14d,5);
    newObj->setDisabledUntil((DisabledType)3,TheGameLogic->getFrame()+m_bfme118);
    if(!revival) { Drawable *draw=((Thing *)newObj)->getDrawable(); if(draw) { drawable->rva002723C0(m_bfme118); draw->rva00274176(true); } }
    const _STL::vector<AsciiString> &names=*(const _STL::vector<AsciiString> *)thingTemplate->m_buildFadeInOnCreateList;
    if(!names.empty()) {
     for(_STL::vector<AsciiString>::const_iterator it=names.begin();it!=names.end();++it) {
      const ThingTemplate *extraTemplate=TheThingFactory->findTemplate(*it); if(!extraTemplate) continue;
      Team *team=us->getControllingPlayer()->m_defaultTeam;
      Object *extra=TheThingFactory->newObject(extraTemplate,team,&mask,(ObjectID)0);
      rva0049CD24(extra);
      if(exitInterface->getExitPosition(&pos,&angle)) { ((Thing *)extra)->setPosition(&pos); ((Thing *)extra)->setOrientation(angle); }
      ((Thing *)extra)->getDrawable()->setDrawableHidden(true);
      if(!extra->m_modelConditionFlags.test(218)) { extra->m_modelConditionFlags.set(218); extra->rva0028AE6D(); }
      newObj->setSpecialModelConditionState((ModelConditionFlagType)0x14d,5);
      ObjectID id=extra->m_id; m_createdAuxiliary.push_back(id);
     }
     m_bfme11C=false;
    }
    Module *respawn=newObj->findUpdateModule(respawnKey);
    if(revival && respawn) { ((RespawnUpdate *)respawn)->triggerRevival(us); if(newObj->m_experience) ((ProductionExperienceView *)newObj->m_experience)->next=revivalExperience;
     m_bfme128=4*BfmeLogicFramesPerSecond; newObj->rva002900FA(TheGameLogic->getFrame()+4*BfmeLogicFramesPerSecond); }
   } else { newObj=TheGameLogic->findObjectByID(m_bfme120); if(!newObj) { removeFromProductionQueue(production); ::delete production; return UPDATE_SLEEP_NONE; } }
   ProductionContainView *contain=newObj->m_contain;
   ProductionHordeInterface *horde=contain ? contain->getHorde() : 0;
   if(horde) { const ThingTemplate *thingTemplate=TheThingFactory->findTemplate(horde->getTemplateName()); int extraCount=horde->getExtraCount();
    if(thingTemplate) { ++extraCount; production->m_cost=0; production->m_objectToProduce=thingTemplate; production->m_productionQuantityTotal=extraCount; production->m_bfme34=true; } }
   if(!m_bfme11C) {
    float duration=getObject()->m_template->m_buildFadeInOnCreateTime;
    if(!m_createdAuxiliary.empty()) for(_STL::list<ObjectID>::iterator it=m_createdAuxiliary.begin();it!=m_createdAuxiliary.end();++it) {
     Object *extra=TheGameLogic->findObjectByID(*it); if(!extra) continue;
     ((Thing *)extra)->getDrawable()->setDrawableHidden(false); ((Thing *)extra)->getDrawable()->rva000B3FD0();
     ((Thing *)extra)->getDrawable()->fadeIn((unsigned int)(BfmeClientFramesPerSecond*duration));
    }
    m_bfme11C=true;
   }
   if(m_bfme118) { --m_bfme118; return UPDATE_SLEEP_NONE; }
   if(newObj->m_modelConditionFlags.test(218)) { newObj->m_modelConditionFlags.set(218,false); newObj->rva0028AE6D(); }
   if(productionUpdateModuleData->m_completeDuration>0) newObj->setSpecialModelConditionState((ModelConditionFlagType)0x5f,productionUpdateModuleData->m_completeDuration);
   if(newObj->isKindOf((KindOfType)0xda)) newObj->clearDisabled((DisabledType)3);
   m_bfme120=(ObjectID)0;
   if(!newObj->findUpdateModule(respawnKey)) exitInterface->exitObjectViaDoor(newObj,exitDoor);
   ++production->m_productionQuantityProduced; production->m_exitDoor=(ExitDoorType)-1;
   if(production->m_productionQuantityTotal-production->m_productionQuantityProduced==0) {
    Object *container=TheGameLogic->findObjectByID(newObj->m_containerID);
    if(container) { ProductionContainView *containerInterface=container->m_contain;
    if(containerInterface) {
     ProductionAIUpdateView *hordeAI=containerInterface->getAI();
     if(hordeAI) { DrawableList list; Drawable *draw=((Thing *)container)->getDrawable(); list.push_back(draw);
      PickAndPlayInfo info; info.drawTarget=((Thing *)us)->getDrawable(); pickAndPlayUnitVoiceResponse(&list,(GameMessage::Type)0x7e2,(PickAndPlayInfo *)&info);
      hordeAI->s234(us); }
    } }
   }
  }
  if(production->m_productionQuantityTotal-production->m_productionQuantityProduced==0) { removeFromProductionQueue(production); ::delete production; exitInterface->exitSlot11(); }
  } else { removeFromProductionQueue(production); ::delete production; }
  break;
 }
 case PRODUCTION_UPGRADE: {
  const UpgradeTemplate *upgrade=production->m_upgradeToResearch;
  if(experience && !productionUpdateModuleData->m_noExperience && ((Rva0039ADF3 *)experience)->rva0039AE04()) { int cost=upgrade->calcCostToBuild(0,0); if(cost>0) ((ExperienceTracker *)experience)->rva0039B315((float)cost,true,true,true,false); }
  ObjectID producerID=us->m_id;
  int producerPlayer=us->getControllingPlayer()->m_playerIndex;
  TheScriptEngine->rva00357F11(producerPlayer,upgrade->getUpgradeName(),producerID);
  if(us->isLocallyControlled()) {
   UnicodeString message; UnicodeString format=TheGameText->fetch("UPGRADE:UpgradeComplete"); UnicodeString name=TheGameText->fetch(upgrade->m_displayName.str());
   message.format(format.str(),name.str()); ((ProductionInGameUIView *)TheInGameUI)->message(message);
   TheRadar->createEvent(&us->m_position,(RadarEventType)2,4.0f);
   bool sounded=false;
   if(upgrade->m_evaEvent!=-1) { TheEva->reportEvaEvent((EvaEventID)upgrade->m_evaEvent,&us->m_position,0); sounded=true; }
   if(upgrade->m_researchSound) { BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4 *)&upgrade->m_researchSound,0); ((Rva002D9531 *)&sound)->rva002D9531(us->m_id); ((ProductionAudioView *)TheAudio)->addEvent(&sound); sounded=true; }
   if(!sounded) TheEva->reportEvaEvent((EvaEventID)4,&us->m_position,0);
   BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4 *)&upgrade->m_unitSound,0); ((Rva002D9531 *)&sound)->rva002D9531(us->m_id); ((ProductionAudioView *)TheAudio)->addEvent(&sound);
  }
  if(!((Rva004DC8E7AsciiField *)upgrade)->get().isEmpty()) {
   const FXList *fx=TheFXListStore->findFXList(((Rva004DC8E7AsciiField *)upgrade)->get().str()); if(fx) FXList::doFXObj(fx,us,0);
  }
  if(upgrade->getUpgradeType()==UPGRADE_TYPE_PLAYER) player->addUpgrade(upgrade,(UpgradeStatusType)2,0); else us->rva00293077(upgrade);
  Drawable *draw=((ProductionInGameUIView *)TheInGameUI)->getSelectedDrawable(); Object *selected=draw ? ((ProductionDrawableView *)draw)->object : 0;
  if(selected) { const ThingTemplate *selectedTemplate=selected->getTemplate(); for(int i=0;i<5;++i) if(TheUpgradeCenter->findUpgrade(selectedTemplate->m_upgradeCameoUpgradeNames[i])==upgrade) { ((ProductionControlBarView *)TheControlBar)->dirty=true; break; } }
  removeFromProductionQueue(production); ::delete production; m_bfme120=(ObjectID)0;
  break;
 }
 }
 return UPDATE_SLEEP_NONE;
}

// Native 0x0049DA34..0x0049DC50 (RET28); WB 0x01202B70 identifies queueCreateUnit.
// ZH provides the queue/quantity structure; BFME2 bytes and WB establish the
// revival path, five-entry loop, tracker calls, and cached Money pointer.
// Native 0x0049DAA9 tests template +0x11B bit 5 (KindOf index 157), leaving
// cost zero when set. The older bank omitted that branch entirely.
// Donor context: open-bfme-1 64d369b90170b7e9ec917d646f020b11f13eb0d5,
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD ProductionUpdate.cpp.
Bool ProductionUpdate::queueCreateUnit( const ThingTemplate *unitType, Int revivalIndex, ProductionID productionID,
		Int slot, Bool five, const AsciiString &name, Bool flag )
{
	const ProductionUpdateModuleData *data = getProductionUpdateModuleData();
	Bool revival = revivalIndex != -1;
	if( revival )
		unitType = NULL;

	// if we can't create the unit do nothing
	if( ((BuildAssistantView *)TheBuildAssistant)->canMakeUnit( getObject(), unitType, revivalIndex ) != CANMAKE_OK )
		return FALSE;

	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return FALSE;

	UnsignedInt cost = 0;
	Player *player = getObject()->getControllingPlayer();
	Bool isRevival = revival;
	if( isRevival )
		cost = reinterpret_cast<Rva0037E6E8 *>(&player->m_revivalTracker)->rva0037E649( revivalIndex, getObject() );
	else if (!(unitType->m_kindof[4] & 0x20000000))
		cost = unitType->rva0033A69A( player, reinterpret_cast<Int>(getObject()), -1 );

	Rva003B0D7C *money = player->getMoney();
	Int count = five ? 5 : 1;
	Bool first = TRUE;
	while (count)
	{
		if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
			break;

		// take the cost for the build away from the player
		money->withdraw( cost, &player->m_tracker, true );
		((Rva0039BAD2 *)&player->m_tracker)->rva0039BAD2( (Rva0039BAD2Input *)unitType, cost );

		// allocate a new production entry
		Rva0049D1B1 *production = new Rva0049D1B1;

		ProductionID id;
		if( first )
		{
			id = productionID;
			first = FALSE;
		}
		else
			id = requestUniqueUnitID();

		production->m_productionQuantityProduced = 0;
		production->m_productionID = id;
		production->m_productionQuantityTotal = 1;
		if( !revival )
		{
			for( _STL::vector<QuantityModifier>::const_iterator it = data->m_quantityModifiers.begin(); it != data->m_quantityModifiers.end(); ++it )
			{
				const ThingTemplate* productionTemplate = TheThingFactory->findTemplate( it->m_templateName );
				if( productionTemplate && productionTemplate->isEquivalentTo( unitType ) )
				{
					production->m_productionQuantityTotal = it->m_quantity;
					break;
				}
			}
			production->m_type = PRODUCTION_UNIT;
			production->m_objectToProduce = unitType;
			production->m_buttonImage = ((ThingTemplate *)unitType)->getButtonImage();
		}
		else
		{
			// Preserve retail's reload of the stored ID before the revival call.
			_ReadWriteBarrier();
			production->m_type = PRODUCTION_HORDE_UNIT;
			if( !reinterpret_cast<UnitRevivalTracker *>(&player->m_revivalTracker)->productionSystemQueueCreateUnit( revivalIndex, production->m_productionID, &production->m_buttonImage ) )
			{
				::delete production;
				return FALSE;
			}
			production->m_objectToProduce = (const ThingTemplate *)((Rva0037E421 *)&player->m_revivalTracker)->rva0037E7A5( revivalIndex );
		}

		production->m_exitDoor = (ExitDoorType)-1;
		production->m_bfme30 = slot;
		production->m_cost = cost;
		production->m_name = name;
		production->m_slave = flag;

		// tie to the end of the production queue
		addToProductionQueue( production );

		--count;
		if( money->countMoney() < cost )
			break;
	}

	return TRUE;  // unit queued

}  // end queueCreateUnit

