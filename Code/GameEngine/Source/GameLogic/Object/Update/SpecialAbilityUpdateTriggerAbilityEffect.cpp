// ?triggerAbilityEffect@SpecialAbilityUpdate@@UAEXXZ
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /I. /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Retail 0x0045108D..0x00451B92: SpecialAbilityUpdate::triggerAbilityEffect.
// WB10E4270 establishes SpecialAbilityUpdate::triggerAbilityEffect and its
// branch structure. Release instructions establish every accessed offset,
// virtual slot, numeric kind/status/condition and helper argument below.
// ZH SpecialAbilityUpdate.cpp at BFME1 cee35b7d8 supplies shared trigger,
// experience, sound, laser attack and stealth semantics; BFME2 pickup/capture
// paths are reconstructed from release and WB, not copied from the ZH switch.
#include <math.h>
#include <string.h>
#include <stddef.h>
#include "Common/BfmeAudioEventPrefix136.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"

extern GameLogic *TheGameLogic;
class Player;
class Team;
class ThingTemplate;
class Module;
enum NameKeyType { NAMEKEY_INVALID = 0 };
// These status labels describe use in this body, not recovered enum names.
// Role labels below are not asserted original enumeration spellings.
enum ObjectStatusTypes { STATUS_CAPTURE_REFUND = 2, STATUS_NO_REFUND = 21, STATUS_NO_SCORE = 86 };
enum KindOfType { KINDOF_DISGUISER = 300 };
enum WeaponSlotType { SECONDARY_WEAPON = 1 };
enum WeaponLockType { LOCKED_TEMPORARILY = 1 };
enum CommandSourceType { CMD_FROM_AI = 2 };
enum DamageType { DAMAGE_CAPTURE = 8 };
enum DeathType { DEATH_NORMAL = 0 };
enum DisabledType { DISABLED_SPECIAL_ABILITY = 3 };
enum EvaEventID { EVA_CAPTURED = 17 };
struct GrabPosition : Coord3D {
    GrabPosition() {}
    GrabPosition(const Coord3D &pos) { x=pos.x; y=pos.y; z=pos.z; }
    ~GrabPosition() {}
};
// Vector3::Rotate_Z from the cited ZH reference. Keep the CRT float
// wrappers visible: replacing them with casts of sin/cos changes scheduling.
struct GrabRotation {
    float x,y,z;
    __forceinline GrabRotation(float a,float b,float c){x=a; y=b; z=c;}
    __forceinline void rotate(float sine,float cosine) {
        float oldX=x,oldY=y;
        x=cosine*oldX-sine*oldY;
        y=sine*oldX+cosine*oldY;
    }
    __forceinline void rotate(float angle) { rotate(sinf(angle),cosf(angle)); }
};
class Matrix3D {
  public:
    float Get_Z_Rotation() const;
    float values[12];
};
class Drawable {
  public:
    const Matrix3D *getTransformMatrix() const;
    void rva00274176(bool);
};
class Thing {
  public:
    Drawable *getDrawable() const;
};
class NameKeyGenerator {
  public:
    NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva00373EC6;
class StealthUpdate {
  public:
    void disguiseAsObject(const Object *);
    void markAsDetected(unsigned, int, Object *, bool);
};
class ExperienceTracker {
  public:
    void rva0039B315(float, bool, bool, bool, bool);
};
class Rva00380200 {
  public:
    bool rva003805BB(float, bool);
};
class Rva002A9EFB {
  public:
    void rva002A9EFB(int);
};
class Rva0039B7AD;
class Rva003B0D7C {
  public:
    void rva003B0D7C(int, Rva0039B7AD *, bool);
};
class ScoreKeeper {
  public:
    void addObjectBuilt(Object *, int);
};
// Accessed prefixes only. One-byte call-only member views below are padded
// to each next proven field; they do not assert those classes' full sizes.
// Accessed prefixes, not complete recovered class sizes.
class Player {
  public:
    char pad00[8];
    Rva00380200 skill;
    char pad09[0x90 - 9];
    Rva003B0D7C money;
    char pad91[0x2ec - 0x91];
    Team *defaultTeam;
    char pad2f0[0x3bc - 0x2f0];
    ScoreKeeper score;
};
class Rva2225E0Filter {
  public:
    bool accepts(Object *, Player *);
};
class ObjectFilter {
  public:
    bool isValid() const;
};
class Overridable {
  public:
    const Overridable *friend_getFinalOverride() const;
    char pad00[0x1c];
    int powerType;
    char pad20[0x30 - 0x20];
    int resourceCost;
    char pad34[0x60 - 0x34];
    Rva2225E0Filter targetFilter;
};
class FXList {
  public:
    static void doFXPos(const FXList *, const Coord3D *, const Matrix3D *, float, const Coord3D *);
};
// Eight-byte hidden-result view for BodyModuleInterface slot 0x7C; the
// original type name is unproven. WB also shows the temporary's empty cleanup.
struct GrabOffsetValue {
    float x, y;
    GrabOffsetValue() {}
    __forceinline GrabOffsetValue(const GrabOffsetValue &other) : x(other.x), y(other.y) {}
    ~GrabOffsetValue() {}
};
class SpecialPowerModuleInterface {
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual const Overridable *getSpecialPowerTemplate() const;
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void resetRecharge(float);
};
// Vtable slots are release facts; neutral slot names avoid importing ZH
// interface positions into BFME2. Named methods below describe observed roles.
class ContainModuleInterface {
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual bool rvaSlot10() const;
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void remove(Object *);
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void setTeam(Team *);
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual ContainModuleInterface *rvaSlot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual bool canContain(Object *, bool, int);
    virtual void contain(Object *);
    virtual void slotA0();
    virtual void release(Object *, bool);
    virtual void rvaSlotA8(bool);
};
// Getter roles: native ActiveBody interface C5B5B0 slots70/74/78/7C;
// FieldParse C5B2A8..C5B2E8 names GrabObject2C, GrabFX38, GrabDamage3C,
// GrabOffset40. Slot7C returns two float coordinates via an 8-byte hidden
// buffer (4BDC56); its original C++ return-type spelling is unproven.
class BodyModuleInterface {
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual AsciiString getGrabObject() const;
    virtual const FXList *getGrabFX() const;
    virtual float getGrabDamage() const;
    virtual GrabOffsetValue getGrabOffset() const;
};
class CaptureRefundInterface {
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void reset();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual float rvaSlot34() const;
};
class AICommandInterface {
  public:
    virtual void aiDoCommand(const void *);
    void rva0026C2D9(Object *, int, CommandSourceType);
    void rva0044FFD9(Object *, CommandSourceType);
};
class AIUpdateModuleView
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual bool rvaSlot168(); // +0x168
	char prefix[0x1c]; // +0x04
};
class AIUpdateInterface : public AIUpdateModuleView, public AICommandInterface {};
struct Rva00297612Entry;
class Rva00263895Member {
  public:
    Rva00263895Member();
    char pad00[8];
    int source;
    char pad0c[4];
    int damageType, deathType;
    char pad18[4];
    int mode;
    float amount;
    char pad24[0x7c - 0x24];
};
class Weapon;
class WeaponSet {
  public:
    Weapon *getWeaponInWeaponSlot(WeaponSlotType) const;
};
class ModelConditionFlags {
public:
    unsigned words[19];
    unsigned test(unsigned bit) const { return words[bit >> 5] & (1U << (bit & 31)); }
    void set(unsigned bit) { words[bit >> 5] |= 1U << (bit & 31); }
    void clear(unsigned bit) { words[bit >> 5] &= ~(1U << (bit & 31)); }
};
class Object : public Thing {
    friend class SpecialAbilityUpdate;

  public:
    const Matrix3D *getTransform() const { return &transform; }
    Team *getTeam() const { return team; }
    const Coord3D &getPosition() const { return position; }
    void *vtable;
    const ThingTemplate *tmplate;
    Matrix3D transform;
    Coord3D position;
    char pad44[0x74 - 0x44];
    ObjectID id;
    char pad78[8];
    int captor;
    char pad84[0x10c - 0x84];
    ModelConditionFlags modelConditions;
    char pad158[0x250 - 0x158];
    ContainModuleInterface *contain;
    BodyModuleInterface *body;
    AIUpdateInterface *ai;
    char pad25c[8];
    ExperienceTracker *experience;
    char pad268[0xc];
    Object *container;
    char pad278[0x304 - 0x278];
    Team *team;
    char pad308[0x330 - 0x308];
    WeaponSet weaponSet;
    Player *getControllingPlayer() const;
    bool isLocallyControlled() const;
    bool isKindOf(KindOfType) const;
    bool testStatus(ObjectStatusTypes) const;
    void setStatus(ObjectStatusTypes, bool);
    void setProducer(Object *);
    void rva002975AC(Rva00297612Entry *);
    void rva0028AE6D();
    void rva0028CFB2(const int *, const int *);
    void *rva0028BD17() const;
    void rva0028DA28();
    void defect(Team *, unsigned);
    void kill(DamageType, DeathType);
    bool setWeaponLock(WeaponSlotType, WeaponLockType);
    Rva00373EC6 *rva0028F4BC();
    void setDisabledUntil(DisabledType, unsigned);
    void setDisabledFor(DisabledType type, unsigned frames) {
        setDisabledUntil(type, TheGameLogic->getFrame()+frames);
    }
    bool addAttributeModifierToPool(const AsciiString &, int);
    __forceinline void setModelCondition(unsigned bit) {
        if (modelConditions.test(bit)) return;
        modelConditions.set(bit);
        rva0028AE6D();
    }
    __forceinline void clearModelCondition(unsigned bit) {
        if (!modelConditions.test(bit)) return;
        modelConditions.clear(bit);
        rva0028AE6D();
    }

  protected:
    Module *findModule(NameKeyType) const;
};
class ThingTemplate {
  public:
    char pad[0x108];
    unsigned kind[7];
    __forceinline bool isKind(unsigned bit) const {
        return (((const unsigned char *)kind)[bit >> 3] & (1 << (bit & 7))) != 0;
    }
};
class Rva0044E633 {
  public:
    void *rva0044E633();
};
class Rva002D9531 {
  public:
    void rva002D9531(int);
};
class Rva001E431E {
  public:
    void rva001E431E(const int *);
};
class Rva0028F59A {
  public:
    Rva0028F59A(int, int);
    unsigned words[19];
};
class Rva00045411BitSet {
  public:
    Rva00045411BitSet(int, int);
    unsigned words[7];
};
class BfmeFixedStorage0004543D {
  public:
    unsigned words[7];
};
template <int> class BitFlags {
  public:
    unsigned words[7];
};
extern BitFlags<116> KINDOFMASK_NONE;
class Rva000421C8 {
  public:
    virtual ~Rva000421C8() {}
    virtual bool allow(Object *) = 0;
    virtual int getPlayerMask();
    Rva000421C8 *next;
};
class Rva0004584D : public Rva000421C8 {
  public:
    Rva0004584D(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &);
    virtual bool allow(Object *);
    BfmeFixedStorage0004543D require, exclude;
};
class BfmeThingCME {
  public:
    int rva0027F108(void *, float, int, int);
};
class TerrainLogic {
  public:
    Object *rva00283D70(const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
extern PartitionManager *ThePartitionManager;
struct CreateMask {
    CreateMask() { memset(words, 0, sizeof(words)); }
    unsigned words[4];
};
enum ObjectID; class ThingFactory {
  public:
    const ThingTemplate *findTemplate(const AsciiString &);
    Object *newObject(const ThingTemplate *, Team *, const CreateMask *, ObjectID);
};
extern ThingFactory *TheThingFactory;
class Eva {
  public:
    bool reportEvaEvent(EvaEventID, const Coord3D *, const Coord3D *);
};
extern Eva *TheEva;
class Rva00439E0C {
  public:
    bool detected(Object *, Object *, int, int);
};
class AutoHealBehavior {
  public:
    void rva004523CC();
};
class SpecialDisguiseUpdate {
  public:
    void rva004B05F5(bool);
};
class Rva002A8F24 {
  public:
    void UnRegister(Object *);
    void rva002A9365(Object *);
};
// Descriptive bank-only declarations: existing address-named owners need a
// coherent rename before landing. Never bind a second global at their address.
extern Rva002A8F24 *TheSkirmishAIManager;
class Rva00421520;
extern Rva00421520 *TheLightPointSystem;
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
struct BfmeDelayedLuaEventList;
class BfmeObjectEventDispatch {
  public:
    void rva003360D2(int, void *, BfmeDelayedLuaEventList *);
};
struct EventParameterView {
    void *vtable;
    float real;
    bool boolean;
    int integer;
    void *string;
    int type;
};
class DelayedLuaEventList {
  public:
    DelayedLuaEventList();
    virtual ~DelayedLuaEventList();
    EventParameterView parameters[3];
};
class SpecialAbilityUpdateModuleData {
  public:
    char pad00[0x14];
    OpaqueRefElement4 triggerSound;
    char pad18[0x34 - 0x18];
    OpaqueRefElement4 triggerLoopSound;
    Overridable *specialPowerTemplate;
    char pad3c[0x48 - 0x3c];
    AsciiString attributeModifier;
    char pad4c[0x60 - 0x4c];
    float eventValue;
    int awardXPForTriggering, skillPointsForTriggering;
    int abilityCondition;
    char pad70[0x98 - 0x70];
    int attributeDuration;
    unsigned disableFrames;
    char pada0[0xb0 - 0xa0];
    bool loseStealth;
    char padb1;
    bool specialAttackAnim;
    char padb3[0xc0 - 0xb3];
    AsciiString rechargeTrigger;
};
class SpecialAbilityUpdate {
  public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void triggerAbilityEffect();
    const SpecialAbilityUpdateModuleData *getData() const { return data; }
    const AsciiString &getRechargeTrigger() const { return getData()->rechargeTrigger; }
    Object *getObject() const { return object; }
    SpecialAbilityUpdateModuleData *data;
    Object *object;
    char pad0c[0x24 - 0xc];
    int triggerCount;
    char pad28[0x38 - 0x28];
    unsigned loopSound;
    char pad3c[4];
    ObjectID targetID;
    Coord3D targetPosition;
    char pad50[0x7d - 0x50];
    bool completed;
    char pad7e[4];
    bool attackAnimStarted, attackIssued;
};
#define CHECK_FIELD(T, F, O) typedef char Check_##T##_##F[(offsetof(T, F) == O) ? 1 : -1]
CHECK_FIELD(Object, position, 0x38);
CHECK_FIELD(Object, contain, 0x250);
CHECK_FIELD(Object, experience, 0x264);
CHECK_FIELD(Object, team, 0x304);
CHECK_FIELD(Player, defaultTeam, 0x2ec);
CHECK_FIELD(Player, score, 0x3bc);
CHECK_FIELD(SpecialAbilityUpdate, targetPosition, 0x44);
CHECK_FIELD(SpecialAbilityUpdate, attackIssued, 0x83);
CHECK_FIELD(SpecialAbilityUpdateModuleData, rechargeTrigger, 0xc0);
typedef char CheckDamageSize[(sizeof(Rva00263895Member) == 0x7c) ? 1 : -1];
typedef char CheckEventsSize[(sizeof(DelayedLuaEventList) == 0x4c) ? 1 : -1];
class AudioManager {
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual unsigned addAudioEvent(const BfmeAudioEventPrefix136 *);
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual bool isCurrentlyPlaying(unsigned);
};
extern AudioManager *TheAudio;

void SpecialAbilityUpdate::triggerAbilityEffect() {
    const SpecialAbilityUpdateModuleData *moduleData = data;
    const Overridable *powerTemplate = moduleData->specialPowerTemplate;
    Object *owner = object;
    Object *target = TheGameLogic->findObjectByID(targetID);
    SpecialPowerModuleInterface *power =
        (SpecialPowerModuleInterface *)((Rva0044E633 *)this)->rva0044E633();
    if (power && ((const StringBase<char> *)&getRechargeTrigger())->isEmpty())
        power->resetRecharge(1.0f);
    ++triggerCount;
    if (moduleData->awardXPForTriggering) {
        ExperienceTracker *xp = owner->experience;
        if (xp)
            xp->rva0039B315((float)moduleData->awardXPForTriggering, true, true, true, false);
    }
    int skillPoints = moduleData->skillPointsForTriggering != -1
                          ? moduleData->skillPointsForTriggering
                          : moduleData->awardXPForTriggering;
    if (skillPoints > 0) {
        Player *player = owner->getControllingPlayer();
        if (player)
            player->skill.rva003805BB((float)skillPoints, false);
    }
    if (TheLightPointSystem) {
        Player *player = owner->getControllingPlayer();
        if (player)
            ((Rva002A9EFB *)player)
                ->rva002A9EFB(powerTemplate->friend_getFinalOverride()->resourceCost);
    }
    BfmeAudioEventPrefix136 sound(moduleData->triggerSound, 0);
    ((Rva002D9531 *)&sound)->rva002D9531(owner->id);
    TheAudio->addAudioEvent(&sound);
    if (moduleData->triggerLoopSound.referent && !TheAudio->isCurrentlyPlaying(loopSound)) {
        BfmeAudioEventPrefix136 loop(moduleData->triggerLoopSound, owner->id);
        loopSound = TheAudio->addAudioEvent(&loop);
    }
    switch (powerTemplate->friend_getFinalOverride()->powerType) {
    case 0x27:
    case 0x28:
        // BFME2 pickup/grab pair. The two target kinds select a replacement
        // and damage path, otherwise the owner's contain interface takes it.
        if (triggerCount == 1) {
            ContainModuleInterface *holder = owner->contain;
            if (!holder)
                break;
            if (!target) {
                if (!((BfmeThingCME *)TheTerrainLogic)->rva0027F108(&targetPosition, 5.0f, 1, 1))
                    break;
                target = TheTerrainLogic->rva00283D70(&targetPosition);
                if (!target)
                    break;
                targetID = target->id;
            }
            {
                const ThingTemplate *targetTemplate = target->tmplate;
                bool createGrabObject = false;
                if (targetTemplate->isKind(132) &&
                    powerTemplate->friend_getFinalOverride()->powerType == 0x28)
                    createGrabObject = true;
                if (targetTemplate->isKind(136) &&
                    powerTemplate->friend_getFinalOverride()->powerType == 0x27)
                    createGrabObject = true;
                if (createGrabObject) {
                    BodyModuleInterface *grabBody = target->body;
                    if (!grabBody)
                        return;
                    if (!((const StringBase<char> *)&grabBody->getGrabObject())->isEmpty()) {
                        const ThingTemplate *replacement =
                            TheThingFactory->findTemplate(target->body->getGrabObject());
                        Object *created = TheThingFactory->newObject(replacement, 0, &CreateMask(), (ObjectID)0);
                        if (created) {
                            created->setProducer(owner);
                            holder->contain(created);
                        }
                    }
                    Rva00263895Member damage;
                    damage.source = 0;
                    damage.damageType = 5;
                    damage.mode = 1;
                    damage.amount = target->body->getGrabDamage();
                    damage.deathType = 7;
                    target->rva002975AC((Rva00297612Entry *)&damage);
                    GrabPosition position(getObject()->getPosition());
                    GrabOffsetValue offset = target->body->getGrabOffset();
                    float angle = getObject()->getTransform()->Get_Z_Rotation();
                    GrabRotation rotated(offset.x, offset.y, 0.0f);
                    rotated.rotate(angle);
                    position.x += rotated.x;
                    position.y += rotated.y;
                    position.z += rotated.z;
                    BodyModuleInterface *harvestBody = target->body;
                    Object *actor = object;
                    FXList::doFXPos(harvestBody->getGrabFX(), &position,
                                    actor->getDrawable()->getTransformMatrix(), 100.0f, &position);
                } else if (holder->canContain(target, true, 0)) {
                    Object *container = target->container;
                    if (container) {
                        ContainModuleInterface *containerModule = container->contain;
                        if (containerModule) {
                            ContainModuleInterface *riders = containerModule->rvaSlot7C();
                            if (riders)
                                riders->remove(target);
                        }
                    }
                    holder->contain(target);
                    if (target->tmplate->isKind(99))
                        target->setModelCondition(95);
                }
            }
        } else if (triggerCount == 2 && target) {
            if (target->tmplate->isKind(6))
                target->setModelCondition(91);
            else if (target->tmplate->isKind(99)) {
                ContainModuleInterface *holder = owner->contain;
                if (holder)
                    holder->release(target, false);
                Object *actor = object;
                actor->clearModelCondition(95);
                target->clearModelCondition(95);
                if (moduleData->abilityCondition) {
                    switch (moduleData->abilityCondition) {
                    case 1:
                        actor->setModelCondition(97);
                        break;
                    case 2:
                        actor->setModelCondition(98);
                        break;
                    case 3:
                        actor->setModelCondition(99);
                        break;
                    case 4:
                        actor->setModelCondition(585);
                        break;
                    case 5:
                        actor->setModelCondition(586);
                        break;
                    case 6:
                        actor->setModelCondition(587);
                        break;
                    }
                }
                completed = true;
            }
        }
        break;
    case 0x15: {
        if (target) {
            const Weapon *weapon = owner->weaponSet.getWeaponInWeaponSlot(SECONDARY_WEAPON);
            if (weapon) {
                owner->setWeaponLock(SECONDARY_WEAPON, LOCKED_TEMPORARILY);
                AIUpdateInterface *ai = owner->ai;
                if (ai)
                    ai->rva0026C2D9(target, 0x7fffffff, CMD_FROM_AI);
            }
        }
        break;
    }
    case 0x2a: {
        AIUpdateInterface *ai = owner->ai;
        if (ai) {
            if (moduleData->specialAttackAnim && !attackAnimStarted) {
                attackAnimStarted = true;
                object->setModelCondition(132);
            }
            if (target) {
                ai->rva0044FFD9(target, CMD_FROM_AI);
                attackIssued = true;
            }
        }
    } break;
    case 0x80:
    case 0x8f: {
        static NameKeyType autoHealKey = TheNameKeyGenerator->nameToKey("AutoHealBehavior");
        AutoHealBehavior *heal = (AutoHealBehavior *)owner->findModule(autoHealKey);
        if (heal)
            heal->rva004523CC();
    } break;
    case 0x89: {
        DelayedLuaEventList parameters;
        parameters.parameters[0].integer = owner->id;
        parameters.parameters[0].type = 3;
        parameters.parameters[1].real = moduleData->eventValue;
        parameters.parameters[1].type = 1;
        ((BfmeObjectEventDispatch *)TheLuaScriptEngine)
            ->rva003360D2(8, owner, (BfmeDelayedLuaEventList *)&parameters);
    } break;
    case 0x85:
        if (owner->isKindOf(KINDOF_DISGUISER)) {
            static NameKeyType disguiseKey =
                TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
            SpecialDisguiseUpdate *disguise =
                (SpecialDisguiseUpdate *)owner->findModule(disguiseKey);
            if (disguise)
                disguise->rva004B05F5(false);
        }
        break;
    case 0x1a:
    case 0x1d: {
        if (!target || !power)
            return;
        Object *captured = target;
        Rva2225E0Filter *filter = (Rva2225E0Filter *)&power->getSpecialPowerTemplate()
                                      ->friend_getFinalOverride()
                                      ->targetFilter;
        if (((ObjectFilter *)filter)->isValid()) {
            if (!filter->accepts(target, 0))
                return;
        } else {
            captured = ThePartitionManager->getClosestObject(
                &target->position, 150.0f, 1,
                &Rva0004584D((const BfmeFixedStorage0004543D &)Rva00045411BitSet(0, 50),
                             (const BfmeFixedStorage0004543D &)KINDOFMASK_NONE));
            if (!captured)
                return;
        }
        if (target->getTeam() == owner->getTeam() && captured->getTeam() == owner->getTeam())
            return;
        Team *newTeam = owner->getControllingPlayer()->defaultTeam;
        ContainModuleInterface *holder = captured ? captured->contain : 0;
        if (!holder)
            holder = target->contain;
        if (holder && holder->rvaSlot10()) {
            holder->rvaSlotA8(true);
            holder->setTeam(newTeam);
        }
        if (target->isLocallyControlled())
            TheEva->reportEvaEvent(EVA_CAPTURED, &target->position, 0);
        if (target != captured) {
            if (captured->testStatus(STATUS_CAPTURE_REFUND)) {
                Player *oldPlayer = captured->getControllingPlayer();
                if (oldPlayer) {
                    CaptureRefundInterface *refund =
                        (CaptureRefundInterface *)captured->rva0028BD17();
                    if (refund) {
                        int amount = (int)refund->rvaSlot34();
                        if (amount && !captured->testStatus(STATUS_NO_REFUND))
                            oldPlayer->money.rva003B0D7C(amount, (Rva0039B7AD *)&oldPlayer->score,
                                                         true);
                        refund->reset();
                    }
                    captured->setStatus(STATUS_NO_SCORE, true);
                    captured->kill(DAMAGE_CAPTURE, DEATH_NORMAL);
                    captured->setStatus(STATUS_NO_SCORE, false);
                    oldPlayer->score.addObjectBuilt(captured, -1);
                }
            }
            target->rva0028CFB2((const int *)&Rva0028F59A(0, 110),
                                (const int *)&Rva0028F59A(0, 119));
            Drawable *draw = target->getDrawable();
            if (draw)
                draw->rva00274176(false);
            target->rva0028DA28();
            target->defect(newTeam, 1);
        }
        TheSkirmishAIManager->UnRegister(captured);
        captured->rva0028DA28();
        captured->defect(newTeam, 1);
        ((Rva001E431E *)captured)->rva001E431E((const int *)&Rva0028F59A(0, 119));
        target->captor = 0;
        TheSkirmishAIManager->rva002A9365(captured);
        if (powerTemplate->friend_getFinalOverride()->powerType == 0x1a)
            power->resetRecharge(1.0f);
    } break;
    case 0x20:
        if (target) {
            StealthUpdate *stealth = (StealthUpdate *)owner->rva0028F4BC();
            if (stealth)
                stealth->disguiseAsObject(target);
        }
        break;
    }
    if (moduleData->loseStealth) {
        StealthUpdate *stealth = (StealthUpdate *)owner->rva0028F4BC();
        if (stealth)
            stealth->markAsDetected(0, 1, 0, true);
        TheGameLogic->getManager178()->detected(owner, 0, 0, 1);
    }
    if (moduleData->disableFrames > 0)
        owner->setDisabledFor(DISABLED_SPECIAL_ABILITY,moduleData->disableFrames);
    if (!((const StringBase<char> *)&moduleData->attributeModifier)->isEmpty())
        owner->addAttributeModifierToPool(moduleData->attributeModifier,
                                          moduleData->attributeDuration);
}
