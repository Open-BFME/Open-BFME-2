// ??0ThingTemplate@@QAE@XZ
// Retail RVA 0033E1B8, complete 1875-byte constructor and 45 unwind states.
// stlport
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// Native calls, cleanup graph, globals and vtable are reconciled to their owners.
// Native 0033E1B8..0033E90B and WB BC7500; allocation at2D1AB4 proves0x640.
// Matched assignment2D1101 supplies member extents. ZH ThingTemplate supplies
// the default-initialization purpose, not BFME2 offsets or unknown field names.
// INI-configurable names are key-backed: retail FieldParse table RVA009BECD8,
// joined to ZH names where available; otherwise lower-cased native INI key.
// Numeric names retain unresolved offsets. Floating/byte widths and every
// default below are native facts; do not import WB-only debug poison at620.
// Non-INI names: copyFrom33EBEB proves name+64; existing assignment/provider
// views and the locomotor parser33E17D supply the container relationships.
// Container declarations preserve existing assignment/provider spellings.
// They are ABI views, not recovered semantic names for the unknown containers.
// ICF helper rows add no unique coverage; their whole bodies and relocations agree.
#include <stddef.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/Overridable.h"
struct TemplateStringRange { AsciiString name; float first,second; TemplateStringRange() : first(50.0f),second(50.0f) {} };
struct Rva0033B352Record { ~Rva0033B352Record(); AsciiString name; UnicodeString text; __forceinline void clear() { name.clear(); text.clear(); } };
enum GeometryType { GEOMETRY_SPHERE,GEOMETRY_CYLINDER,GEOMETRY_BOX };
class GeometryInfo {
public:
    GeometryInfo(GeometryType,bool,float,float,float);
    virtual ~GeometryInfo();
private: unsigned char remaining[0x58];
};
class Rva0024C7B3Member { public: Rva0024C7B3Member(); unsigned int words[7]; };
template<int N> class BitFlags : public Rva0024C7B3Member { public: __declspec(dllimport) __forceinline BitFlags() {} };
typedef BitFlags<116> KindOfMaskType;
extern KindOfMaskType KINDOFMASK_NONE;
class OpaqueRefCounted;
class Rva002390CB { void *unknown00; OpaqueRefCounted *owner04; public: Rva002390CB(); ~Rva002390CB(); };
class Rva00254FE4Member { public: Rva00254FE4Member(); private: Rva002390CB slots[56]; };

#include <vector>
#include <map>
struct Rva002D0EDCElement; struct BfmeStringRecord002CF4C6;
class ProductionPrerequisite; struct BfmeObject872;
struct BfmeContainerRecord002CF46E; struct Rva0021C21BElement;
struct BfmeFixedObject260 { unsigned int fixedStorage[65]; };
struct BfmeObject872 { unsigned int fixedStorage[218]; };
struct Rva0021C21BElement { unsigned int fixedStorage; };
struct NoCaseTreeValue4 { char data[4]; };
struct BfmeStringNoCaseLess {}; struct Rva002D07F4Element { short words[1]; };
class LocomotorTemplate; enum LocomotorSetType { LOCOMOTORSET_NORMAL=0 };
typedef _STL::vector<Rva002D0EDCElement,_STL::allocator<Rva002D0EDCElement> > VRva002D0EDCElement;
struct BfmeStringRecord002CF4C6;
typedef _STL::vector<BfmeStringRecord002CF4C6,_STL::allocator<BfmeStringRecord002CF4C6> > VBfmeStringRecord002CF4C6;
class ProductionPrerequisite;
typedef _STL::vector<ProductionPrerequisite,_STL::allocator<ProductionPrerequisite> > VProductionPrerequisite;
struct BfmeObject872;
typedef _STL::vector<BfmeObject872,_STL::allocator<BfmeObject872> > VBfmeObject872;
struct BfmeContainerRecord002CF46E;
typedef _STL::vector<BfmeContainerRecord002CF46E,_STL::allocator<BfmeContainerRecord002CF46E> > VBfmeContainerRecord002CF46E;
template _STL::_Vector_base<BfmeContainerRecord002CF46E,_STL::allocator<BfmeContainerRecord002CF46E> >::_Vector_base(
    const _STL::allocator<BfmeContainerRecord002CF46E> &);
struct Rva0021C21BElement;
typedef _STL::vector<Rva0021C21BElement,_STL::allocator<Rva0021C21BElement> > VRva0021C21BElement;
struct BfmeFixedObject260;
typedef _STL::vector<BfmeFixedObject260,_STL::allocator<BfmeFixedObject260> > VBfmeFixedObject260;
typedef _STL::vector<AsciiString,_STL::allocator<AsciiString> > VAsciiString;
class OpaqueRefCounted;

struct BfmeStringRecord002CF550 { AsciiString text; Rva002390CB ref; ~BfmeStringRecord002CF550(); };
typedef _STL::_Rb_tree<BfmeStringRecord002CF550,BfmeStringRecord002CF550,_STL::_Identity<BfmeStringRecord002CF550>,_STL::less<BfmeStringRecord002CF550>,_STL::allocator<BfmeStringRecord002CF550> > SoundRecordTree;
typedef _STL::_Rb_tree<AsciiString,_STL::pair<const AsciiString,NoCaseTreeValue4> ,_STL::_Select1st<_STL::pair<const AsciiString,NoCaseTreeValue4> >,BfmeStringNoCaseLess,_STL::allocator<_STL::pair<const AsciiString,NoCaseTreeValue4> > > NoCaseTree;
typedef _STL::_Rb_tree<LocomotorSetType,_STL::pair<const LocomotorSetType,_STL::vector<const LocomotorTemplate*,_STL::allocator<const LocomotorTemplate*> > > ,_STL::_Select1st<_STL::pair<const LocomotorSetType,_STL::vector<const LocomotorTemplate*,_STL::allocator<const LocomotorTemplate*> > > >,_STL::less<LocomotorSetType>,_STL::allocator<_STL::pair<const LocomotorSetType,_STL::vector<const LocomotorTemplate*,_STL::allocator<const LocomotorTemplate*> > > > > LocomotorTree;
namespace _STL {
// The owned FX tree destructor uses its verified EHs provider.
// Keep that cleanup out of this EHsc constructor unit.
template<> LocomotorTree::~_Rb_tree();
template<> NoCaseTree::~_Rb_tree();
template<> SoundRecordTree::~_Rb_tree();
template<> vector<Rva002D0EDCElement,allocator<Rva002D0EDCElement> >::~vector();
template<> _Vector_base<Rva002D0EDCElement,allocator<Rva002D0EDCElement> >::~_Vector_base();
template<> vector<BfmeStringRecord002CF4C6,allocator<BfmeStringRecord002CF4C6> >::~vector();
template<> _Vector_base<BfmeStringRecord002CF4C6,allocator<BfmeStringRecord002CF4C6> >::~_Vector_base();
template<> vector<ProductionPrerequisite,allocator<ProductionPrerequisite> >::~vector();
template<> _Vector_base<ProductionPrerequisite,allocator<ProductionPrerequisite> >::~_Vector_base();


template<> vector<BfmeContainerRecord002CF46E,allocator<BfmeContainerRecord002CF46E> >::~vector();
template<> _Vector_base<BfmeContainerRecord002CF46E,allocator<BfmeContainerRecord002CF46E> >::~_Vector_base();




template<> vector<AsciiString,allocator<AsciiString> >::~vector();
template<> _Vector_base<AsciiString,allocator<AsciiString> >::~_Vector_base();
}
struct LocomotorMapView { ~LocomotorMapView(); LocomotorTree tree; LocomotorMapView() : tree(_STL::less<LocomotorSetType>(), LocomotorTree::allocator_type()) {} };

// ZH ModuleInfo semantics; native INI keys prove the four 12-byte groups
// Behavior/Draw/ClientUpdate/ClientBehavior at2E4/2F0/2FC/308.
struct ModuleInfo { VBfmeStringRecord002CF4C6 records; ModuleInfo() {} ~ModuleInfo(); };

// Native constructors and cleanup graph establish these 12-byte tree owners.
// Native clone2CFA30 copies 16-byte key plus one pointer; key bit semantics remain unresolved.
struct BfmeObject872Header { unsigned int words[4]; };
struct ArmorSetKeyLess { bool operator()(const BfmeObject872Header &,const BfmeObject872Header &) const; };
typedef _STL::pair<const BfmeObject872Header,const BfmeObject872*> ArmorSetValue;
typedef _STL::_Rb_tree<BfmeObject872Header,ArmorSetValue,_STL::_Select1st<ArmorSetValue>,ArmorSetKeyLess,_STL::allocator<ArmorSetValue> > ArmorSetTree;
struct ArmorSetFinderView { ArmorSetTree tree; ArmorSetFinderView() : tree(ArmorSetKeyLess(), ArmorSetTree::allocator_type()) {} ~ArmorSetFinderView(); };
// Native clone2CFA4E copies an eight-byte value; scalar key plus pointer.
struct WeaponSetKeyView { unsigned int bits; };
struct WeaponSetKeyLess { bool operator()(const WeaponSetKeyView &,const WeaponSetKeyView &) const; };
typedef _STL::pair<const WeaponSetKeyView,const BfmeContainerRecord002CF46E*> WeaponSetValue;
typedef _STL::_Rb_tree<WeaponSetKeyView,WeaponSetValue,_STL::_Select1st<WeaponSetValue>,WeaponSetKeyLess,_STL::allocator<WeaponSetValue> > WeaponSetTree;
struct WeaponSetFinderView { WeaponSetTree tree; WeaponSetFinderView() : tree(WeaponSetKeyLess(), WeaponSetTree::allocator_type()) {} ~WeaponSetFinderView(); };
// Native third finder clone has an eight-byte payload. Original key/value semantics unresolved.
struct Rva002CF156Key { unsigned int word; };
struct Rva002CF156Value { unsigned int word; };
struct Rva002CF156Less { bool operator()(const Rva002CF156Key &,const Rva002CF156Key &) const; };
typedef _STL::pair<const Rva002CF156Key,Rva002CF156Value> TemplateNameValue;
typedef _STL::_Rb_tree<Rva002CF156Key,TemplateNameValue,_STL::_Select1st<TemplateNameValue>,Rva002CF156Less,_STL::allocator<TemplateNameValue> > TemplateNameTree;
struct TemplateNameMapView { TemplateNameTree tree; TemplateNameMapView() : tree(Rva002CF156Less(), TemplateNameTree::allocator_type()) {} ~TemplateNameMapView(); };
struct Words16 { unsigned int words[4]; Words16(){words[0]=0;words[1]=0;words[2]=0;words[3]=0;} };
class AssetList { public: AssetList(); ~AssetList(); private: unsigned char layout[0x14]; };
class Rva001EAE6FHelper { public: Rva001EAE6FHelper *clear80(); };
struct TemplateMask128 { unsigned int words[32]; TemplateMask128(){((Rva001EAE6FHelper *)this)->clear80();} };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
// Existing data-ledger owner at RVA009BA4E4 (initializer 5).
extern int BfmeLogicFramesPerSecond;
struct TemplateGlobalDataView {
    unsigned char prefix[0xCC]; unsigned int occlusionDelay;
    unsigned char middle[0xC34-0xD0]; unsigned int valueC34;
    float valueC38; unsigned int valueC3C;
};
// WB BC51A0 initializes the native four-byte ThreatBreakdown member to all bits.
struct TemplateThreatBreakdown { unsigned int bits; TemplateThreatBreakdown() : bits(~0U) {} };
struct NoCaseMapView { ~NoCaseMapView(); NoCaseTree tree; NoCaseMapView() : tree(BfmeStringNoCaseLess(), NoCaseTree::allocator_type()) {} };
struct Rva0025753F { SoundRecordTree tree; Rva0025753F() : tree(_STL::less<BfmeStringRecord002CF550>(), SoundRecordTree::allocator_type()) {} ~Rva0025753F(); };
struct Rva0033C3F3 : VRva002D0EDCElement { __forceinline Rva0033C3F3() {} ~Rva0033C3F3(); };
class Rva002DFC30 { public: ~Rva002DFC30(); unsigned char m_data[0xC]; };
namespace _STL { template<> vector<Rva002DFC30>::~vector(); }
typedef _STL::vector<Rva002DFC30> WeaponTemplateSetVector;
class ThingTemplate : public Overridable {
public:
    ThingTemplate(); virtual ~ThingTemplate();
    float m_camouflageDetectionMultiplier;
    TemplateStringRange m_formationPreviewDecal;
    TemplateStringRange m_formationPreviewItemDecal;
    Rva0033B352Record m_displayName;
    Rva0033B352Record m_description;
    Rva0033B352Record m_descriptionStrategic;
    Rva0033B352Record m_reviveText;
    Rva0033B352Record m_recruitText;
    Rva0033B352Record m_displayNameStrategic;
    AsciiString m_displayNameInvisibleForEnemy;
    AsciiString m_hotkey;
    AsciiString m_name;
    AsciiString m_editorName;
    AsciiString m_defaultOwningSide;
    AsciiString m_commandSetString;
    AsciiString m_selectedPortraitImageName;
    AsciiString m_buttonImageName;
    AsciiString m_upgradeCameoUpgradeNames[5];
    AsciiString m_shadowTextureName;
    AsciiString m094;
    AsciiString m098;
    AsciiString m_experienceScalarTable;
    GeometryInfo m_geometryInfo;
    Rva0033C3F3 m_geometryOther;
    KindOfMaskType m_kindof;
    Rva00254FE4Member m124;
    ModuleInfo m_behaviorModuleInfo;
    ModuleInfo m_drawModuleInfo;
    ModuleInfo m_clientUpdateModuleInfo;
    ModuleInfo m_clientBehaviorModuleInfo;
    Words16 m_flammability;
    VProductionPrerequisite m_prereqInfo;
    VAsciiString m_buildVariations;
    VAsciiString m_equivalentTo;
    VAsciiString m_buildFadeInOnCreateList;
    float m_buildFadeInOnCreateTime;
    VBfmeObject872 m_armorTemplateSets;
    ArmorSetFinderView m_armorTemplateSetFinder;
    WeaponTemplateSetVector m_weaponTemplateSets;
    WeaponSetFinderView m_weaponTemplateSetFinder;
    Rva0025753F m_perUnitSounds;
    NoCaseMapView m_perUnitFX;
    TemplateNameMapView m3A0;
    LocomotorMapView m_locomotorSets;
    VRva0021C21BElement m_browser;
    AssetList m3C4[2];
    VBfmeFixedObject260 m_autoResolveArmor;
    VBfmeFixedObject260 m_autoResolveWeapon;
    TemplateMask128 m_worldMapArmoryUpgradesAllowed;
    unsigned int m484;
    unsigned int m488;
    unsigned int m48C;
    unsigned int m_autoResolveBody;
    unsigned int m_autoResolveLeadership;
    unsigned int m_autoResolveCombatChain;
    unsigned int m_crowdResponseKey;
    float m_fenceWidth;
    float m_fenceXOffset;
    float m_removeTerrainRadius;
    float m_visionRange;
    float m_shroudClearingRange;
    float m_visionSide;
    float m_visionRear;
    float m_visionBonusPercentPerFoot;
    float m_maxVisionBonusPercent;
    float m_minVisionBonusPercent;
    float m_visionBonusTestRadius;
    float m_emotionRange;
    float m_placementViewAngle;
    float m_factoryExitWidth;
    float m_factoryExtraBibWidth;
    float m_buildTime;
    float m_assetScale;
    float m_instanceScaleFuzziness;
    float m_shadowSizeX;
    float m_shadowSizeY;
    float m_shadowOffsetX;
    float m_shadowOffsetY;
    float m_shadowOpacityFadeInTime;
    float m_shadowOpacityFadeOutTime;
    float m_shadowSunAngle;
    float m_shadowMaxHeight;
    float m_maxDistanceForEngaged;
    float m_minCrushVelocityPercent;
    float m_crushDecelerationPercent;
    float m_crushKnockback;
    float m_crushZFactor;
    float m_threatLevel;
    TemplateThreatBreakdown m_threatBreakdown;
    float m_minZIncreaseForVoiceMoveToHigherGround;
    float m_geometryFrontAngle;
    float m_pathfindDiameter;
    float m_threatRadius;
    float m_healthBoxScale;
    float m_healthBoxHeightOffset;
    float m_firingArc;
    float m_campnessValueRadius;
    unsigned int m_visionBonusTestSegments;
    unsigned int m_energyProduction;
    unsigned int m_energyBonus;
    unsigned int m_displayColor;
    unsigned int m_occlusionDelay;
    unsigned int m_voiceAttackChargeTimeout;
    unsigned int m_engagedStateTimeout;
    unsigned int m_voicePriority;
    unsigned int m_formationDepth;
    unsigned int m_formationWidth;
    unsigned int m_slopeLimitIndex;
    unsigned int m_bountyValue;
    unsigned int m_evaEventDieOwner;
    unsigned int m_evaEventDieAlly;
    unsigned int m_evaEventDieEnemy;
    unsigned int m_evaEventDamagedOwner;
    unsigned int m_evaEventDamagedFromShroudedSourceOwner;
    unsigned int m_evaEventDamagedByFireOwner;
    unsigned int m_evaEventSecondDamageFarFromFirstOwner;
    float m_evaEventSecondDamageFarFromFirstScanRange;
    unsigned int m_evaEventSecondDamageFarFromFirstTimeoutMS;
    unsigned int m_evaEventAmbushed;
    unsigned int m_evaEnemyObjectSightedEvent;
    unsigned int m_evaEnemyObjectSightedAfterRespawnEvent;
    unsigned int m_evaOnFirstSightingEventEnemy;
    unsigned int m_evaOnFirstSightingEventNonEnemy;
    unsigned int m_shadowOpacityStart;
    unsigned int m_shadowOpacityPeak;
    unsigned int m_shadowOpacityEnd;
    unsigned int m_supplyOverride;
    unsigned int m_displayMeleeDamage;
    unsigned int m_displayRangedDamage;
    unsigned int m_autoResolveUnitType;
    unsigned int m_evaEventDetectedEnemy;
    unsigned int m_evaEventDetectedAlly;
    unsigned int m_evaEventDetectedOwner;
    unsigned int m_campnessValue;
    unsigned short m5D8;
    unsigned short m_buildCost;
    unsigned short m_refundValue;
    unsigned short m_threatValue;
    unsigned short m_maxSimultaneousOfType;
    unsigned short m_shadowType;
    unsigned char m_isPrerequisite;
    unsigned char m_isBridge;
    unsigned char m5E6;
    unsigned char m_isTrainable;
    unsigned char m_isForbidden;
    unsigned char m5E9;
    unsigned char m5EA;
    unsigned char m_isGrabbable;
    unsigned char m_isHarvestable;
    unsigned char m_shadowOverrideLODVisibility;
    unsigned char m_shadowUseHouseColor;
    unsigned char m_shadowIsRotatingWithObject;
    unsigned char m_radarPriority;
    unsigned char m_transportSlotCount;
    unsigned char m_buildable;
    unsigned char m_buildCompletion;
    unsigned char m_editorSorting;
    unsigned char m_deadCollideSize;
    unsigned char m_thingClass;
    unsigned char m_structureRubbleHeight;
    unsigned char m5F8;
    unsigned char m_crusherLevel;
    unsigned char m_crushableLevel;
    unsigned char m_mountedCrusherLevel;
    unsigned char m_mountedCrushableLevel;
    unsigned char m_useCrushAttack;
    unsigned char m_crushOnlyWhileCharging;
    unsigned int m_crushWeapon;
    unsigned int m_crushRevengeWeapon;
    float m_ramPower;
    float m_ramZMult;
    float m_shockwaveResistance;
    unsigned char m_crushAllies;
    unsigned int m_commandPoints;
    unsigned int m_commandPointBonus;
    Coord3D m_liveCameraOffset; // Native leaves x uninitialized; WB debug poison is not retail behavior.
    float m_liveCameraPitch;
    unsigned char m_forceLuaRegistration;
    unsigned char m_showHealthInSelectionDecal;
    unsigned char m_keepSelectableWhenDead;
    unsigned char m_isAutoBuilt;
    unsigned char m_canPathThroughGates;
    unsigned char m_shouldClearShotsOnIdle;
    unsigned int m_heroSortOrder;
    unsigned int m_selectionPriority;
};
typedef char TemplateExtentCheck[sizeof(ThingTemplate)==0x640 ? 1 : -1];
typedef char TemplateOffset014[offsetof(ThingTemplate,m_formationPreviewDecal)==0x14 ? 1 : -1];
typedef char TemplateOffset0A0[offsetof(ThingTemplate,m_geometryInfo)==0xA0 ? 1 : -1];
typedef char TemplateOffset0FC[offsetof(ThingTemplate,m_geometryOther)==0xFC ? 1 : -1];
typedef char TemplateOffset108[offsetof(ThingTemplate,m_kindof)==0x108 ? 1 : -1];
typedef char TemplateOffset124[offsetof(ThingTemplate,m124)==0x124 ? 1 : -1];
typedef char TemplateOffset2E4[offsetof(ThingTemplate,m_behaviorModuleInfo)==0x2E4 ? 1 : -1];
typedef char TemplateOffset354[offsetof(ThingTemplate,m_buildFadeInOnCreateTime)==0x354 ? 1 : -1];
typedef char TemplateOffset364[offsetof(ThingTemplate,m_armorTemplateSetFinder)==0x364 ? 1 : -1];
typedef char TemplateOffset388[offsetof(ThingTemplate,m_perUnitSounds)==0x388 ? 1 : -1];
typedef char TemplateOffset3AC[offsetof(ThingTemplate,m_locomotorSets)==0x3AC ? 1 : -1];
typedef char TemplateOffset3C4[offsetof(ThingTemplate,m3C4)==0x3C4 ? 1 : -1];
typedef char TemplateOffset404[offsetof(ThingTemplate,m_worldMapArmoryUpgradesAllowed)==0x404 ? 1 : -1];
typedef char TemplateOffset484[offsetof(ThingTemplate,m484)==0x484 ? 1 : -1];
typedef char TemplateOffset620[offsetof(ThingTemplate,m_liveCameraOffset)==0x620 ? 1 : -1];
typedef char TemplateOffset638[offsetof(ThingTemplate,m_heroSortOrder)==0x638 ? 1 : -1];
ThingTemplate::ThingTemplate()
    : m_camouflageDetectionMultiplier(1.0f),m_experienceScalarTable(""),m_geometryInfo(GEOMETRY_SPHERE,false,1.0f,1.0f,1.0f),m_buildFadeInOnCreateTime(0.0f),
      m_autoResolveBody(0),
      m_autoResolveLeadership(0),
      m_autoResolveCombatChain(0),
      m_crowdResponseKey(0),
      m_minCrushVelocityPercent(0.01f),
      m_crushDecelerationPercent(0.0f),
      m_crushKnockback(0.0f),
      m_crushZFactor(1.0f),
      m_threatLevel(1.0f),
      m_minZIncreaseForVoiceMoveToHigherGround(-1.0f),
      m_geometryFrontAngle(0.0f),
      m_pathfindDiameter(-1.0f),
      m_healthBoxScale(1.5f),
      m_healthBoxHeightOffset(10.0f),
      m_firingArc(360.0f),
      m_campnessValueRadius(1000.0f),
      m_slopeLimitIndex(0),
      m_evaEventDieOwner(-1),
      m_evaEventDieAlly(-1),
      m_evaEventDieEnemy(-1),
      m_evaEventDamagedOwner(-1),
      m_evaEventDamagedFromShroudedSourceOwner(-1),
      m_evaEventDamagedByFireOwner(-1),
      m_evaEventSecondDamageFarFromFirstOwner(-1),
      m_evaEventSecondDamageFarFromFirstScanRange(200.0f),
      m_evaEventSecondDamageFarFromFirstTimeoutMS(BfmeLogicFramesPerSecond * 30),
      m_evaEventAmbushed(-1),
      m_evaEnemyObjectSightedEvent(-1),
      m_evaEnemyObjectSightedAfterRespawnEvent(-1),
      m_evaOnFirstSightingEventEnemy(-1),
      m_evaOnFirstSightingEventNonEnemy(-1),
      m_displayMeleeDamage(-1),
      m_displayRangedDamage(-1),
      m_autoResolveUnitType(7),
      m_evaEventDetectedEnemy(-1),
      m_evaEventDetectedAlly(-1),
      m_evaEventDetectedOwner(-1),
      m_campnessValue(2),
      m_editorSorting(0x0),
      m_deadCollideSize(0x0),
      m_thingClass(0x0),
      m_showHealthInSelectionDecal(0x0),
      m_canPathThroughGates(0x1),
      m_shouldClearShotsOnIdle(0x0),
      m_heroSortOrder(0x7fffffff),
      m_selectionPriority(0x7fffffff)
{
    m5F8 = 0x0;
    m_radarPriority = 0x0;
    m484 = 0;
    m_transportSlotCount = 0x0;
    m_buildable = 0x0;
    m_fenceWidth = 0.0f;
    m_fenceXOffset = 0.0f;
    m_visionRange = 0.0f;
    m_removeTerrainRadius = 0.0f;
    m_shroudClearingRange = -1.0f;
    m_visionSide = 1.0f;
    m_visionRear = 1.0f;
    m_visionBonusPercentPerFoot = 0.0f;
    m_maxVisionBonusPercent = 0.5f;
    m_minVisionBonusPercent = -0.5f;
    m_visionBonusTestRadius = 100.0f;
    m_visionBonusTestSegments = 8;
    m_buildCost = 0;
    m_bountyValue = 0;
    m_buildTime = 1.0f;
    m_refundValue = 0;
    m_energyProduction = 0;
    m_energyBonus = 0;
    m_displayColor = -1;
    m_buildCompletion = 0x1;
    m_formationWidth = 1;
    m_formationDepth = 1;
    m_isTrainable = 0x1;
    m_isForbidden = 0x0;
    m5D8 = 0;
    m_kindof = KINDOFMASK_NONE;
    m_assetScale = 1.0f;
    m_isBridge = 0x0;
    m5E6 = 0x0;
    m_isPrerequisite = 0x0;
    m_placementViewAngle = 0.0f;
    m_factoryExitWidth = 0.0f;
    m_factoryExtraBibWidth = 0.0f;
    m5E9 = 0x0;
    m5EA = 0x0;
    m_isGrabbable = 0x0;
    m_isHarvestable = 0x0;
    m488 = 0;
    m48C = 0;
    m_liveCameraOffset.y = 0.0f;
    m_liveCameraOffset.z = 0.0f;
    m_liveCameraPitch = 0.0f;
    m_shadowType = 0;
    m_shadowSizeX = 0.0f;
    m_shadowSizeY = 0.0f;
    m_shadowOffsetX = 0.0f;
    m_shadowOffsetY = 0.0f;
    m_shadowOpacityStart = 0;
    m_shadowOpacityFadeInTime = 0.0f;
    m_shadowOpacityPeak = 0xff;
    m_shadowOpacityFadeOutTime = 0.0f;
    m_shadowOpacityEnd = 0;
    m_shadowSunAngle = 0.0f;
    m_shadowMaxHeight = 20.0f;
    m_shadowOverrideLODVisibility = 0x0;
    m_shadowUseHouseColor = 0x0;
    m_shadowIsRotatingWithObject = 0x1;
    m_occlusionDelay = ((const TemplateGlobalDataView *)TheWritableGlobalData)->occlusionDelay;
    m_structureRubbleHeight = 0x0;
    m_instanceScaleFuzziness = 0.0f;
    m_threatValue = 0;
    m_threatRadius = -1.0f;
    m_maxSimultaneousOfType = 0;
    m_crusherLevel = 0x0;
    m_crushableLevel = 0x7f;
    m_mountedCrusherLevel = 0xff;
    m_mountedCrushableLevel = 0xff;
    m_useCrushAttack = 0x1;
    m_crushOnlyWhileCharging = 0x0;
    m_crushWeapon = 0;
    m_crushRevengeWeapon = 0;
    m_supplyOverride = 0;
    m_ramPower = 0.0f;
    m_ramZMult = 1.0f;
    m_shockwaveResistance = 0.0f;
    m_crushAllies = 0x0;
    m_commandPoints = 0;
    m_commandPointBonus = 0;
    m_emotionRange = 0.0f;
    m_isAutoBuilt = 0x0;
    m_forceLuaRegistration = 0x0;
    m_keepSelectableWhenDead = 0x0;
    if (TheWritableGlobalData) {
        m_voiceAttackChargeTimeout = ((const TemplateGlobalDataView *)TheWritableGlobalData)->valueC34;
        m_maxDistanceForEngaged = ((const TemplateGlobalDataView *)TheWritableGlobalData)->valueC38;
        m_engagedStateTimeout = ((const TemplateGlobalDataView *)TheWritableGlobalData)->valueC3C;
    } else {
        m_voiceAttackChargeTimeout = BfmeLogicFramesPerSecond * 10;
        m_maxDistanceForEngaged = 50.0f;
        m_engagedStateTimeout = BfmeLogicFramesPerSecond * 2;
    }
    m_voicePriority = 5;
    m_reviveText.clear();
    m_recruitText.clear();
    m_hotkey.clear();
}
