// cl: /DNDEBUG /MD /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ow
// Split from Rva0008EF3FProductCtor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// ??0Rva0008EF3FProduct@@QAE@XZ retail 0x0008EF3F 66B.
//
// The 0xAC0-byte product of game client vtable 0x00BC4738 factory 0x0004C492
// (W3DGameClientFactories.cpp). Target facts: it calls the rowed
// ??0InGameUI@@QAE@XZ 0x002A61A9, stores its own vptrs 0x00BC7A88/+0x0C
// 0x00BC7A78/+0x10 0x00BC7A64 over InGameUI's three bases, clears two
// 25-pointer arrays at +0x9F0/+0xA54 in one loop and then +0xAB8/+0xABC; the
// object ends at 0xAC0, the factory's allocation size.
//
// Donor inference (Zero Hour W3DInGameUI.cpp, not asserted as the target
// name): this is W3DInGameUI::W3DInGameUI -- MAX_MOVE_HINTS is 25 and the
// fields are m_moveHintRenderObj/m_moveHintAnim then the building placement
// anchor and arrow. The class keeps the ledger's address-derived name.
//
// The tables below are retail's, each slot the ledger row at the native address.
// Several slots still sit under placeholder names in the Common getter units, so
// the class is novtable and the constructor stores the tables itself: the compiler's
// own table would name InGameUI members nothing defines yet.

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class View;
class Drawable;
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class RenderObjClass;
class HAnimClass;

// The five-slot interface at +0x10 (InGameUICtor.cpp).
#include "../../../../GameEngine/Include/GameClient/InGameUI.h"


extern "C" {
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("??_ERva008F00D@@WM@AEPAXI@Z")();
void __identifier("??_GRva008F00D@@UAEPAXI@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?Rva0008EFCCGet@@YAHXZ")();
void __identifier("?addFloatingText@InGameUI@@UAEXABVUnicodeString@@PBUCoord3D@@H@Z")();
void __identifier("?addIdleWorker@InGameUI@@UAEXPAVObject@@@Z")();
void __identifier("?addSuperweapon@InGameUI@@UAEXHABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z")();
void __identifier("?areTooltipsDisabled@InGameUI@@UBE_NXZ")();
void __identifier("?beginAreaSelectHint@InGameUI@@UAEXPBVGameMessage@@@Z")();
void __identifier("?bfmeGoBLD@@YGXPAX@Z")();
void __identifier("?clearRva0029B060@InGameUI@@UAEXXZ")();
void __identifier("?createCommandHint@InGameUI@@UAEXPBVGameMessage@@@Z")();
void __identifier("?createGarrisonHint@InGameUI@@UAEXPBVGameMessage@@@Z")();
void __identifier("?createMouseoverHint@InGameUI@@UAEXPBVGameMessage@@@Z")();
void __identifier("?deselectAllDrawables@InGameUI@@UAEXXZ")();
void __identifier("?deselectDrawable@InGameUI@@UAEXPAVDrawable@@@Z")();
void __identifier("?disable@Rva0029AB03ByteZeroSetter@@QAEXXZ")();
void __identifier("?displayCantBuildMessage@InGameUI@@UAEXW4LegalBuildCode@@@Z")();
void __identifier("?drawMilitarySubtitle@InGameUI@@UAEXXZ")();
void __identifier("?drawMoveHints@Rva0008EF3FProduct@@UAEXPAVView@@@Z")();
void __identifier("?drawPlaceAngle@Rva0008EF3FProduct@@UAEXPAVView@@@Z")();
void __identifier("?drawSelectionRegion@Rva0008EF3FProduct@@UAEXXZ")();
void __identifier("?findIdleWorker@InGameUI@@EAEPAVObject@@PAV2@@Z")();
void __identifier("?get@Rva0008EF95ByteField@@QBEEXZ")();
void __identifier("?get@Rva0008EF9CByteField@@QBEEXZ")();
void __identifier("?get@Rva0008EFA3ByteField@@QBEEXZ")();
void __identifier("?get@Rva0008EFB7DwordField@@QBEHXZ")();
void __identifier("?get@Rva0008EFBEDwordField@@QBEHXZ")();
void __identifier("?get@Rva0008EFC5ByteField@@QBEEXZ")();
void __identifier("?get@Rva0028A94BDwordField@@QBEHXZ")();
void __identifier("?get@Rva0029A7EADwordField@@QBEHXZ")();
void __identifier("?get@Rva0029A9BBDwordField@@QBEHXZ")();
void __identifier("?get@Rva0036739CDwordField@@QBEHXZ")();
void __identifier("?get@Rva0043812FDwordField@@QBEHXZ")();
void __identifier("?get@Rva0045310DByteField@@QBEEXZ")();
void __identifier("?get@Rva004F5F8EByteField@@QBEEXZ")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
void __identifier("?get@Rva0054902CDwordField@@QBEHXZ")();
void __identifier("?getAllSelectedLocalDrawables@InGameUI@@UAEPBV?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@XZ")();
void __identifier("?getIdleWorkerCount@InGameUI@@EAEHXZ")();
void __identifier("?getPlacementAngle@InGameUI@@UAEMXZ")();
void __identifier("?getPlacementPoints@InGameUI@@UAEXPAUICoord2D@@0@Z")();
void __identifier("?hideIdleWorkerLayout@InGameUI@@EAEXXZ")();
void __identifier("?hideObjectSuperweaponDisplayByScript@InGameUI@@UAEXPBVObject@@@Z")();
void __identifier("?init@Rva0008EF3FProduct@@UAEXXZ")();
void __identifier("?isAllSelectedKindOf@InGameUI@@UBE_NW4KindOfType@@@Z")();
void __identifier("?isAnySelectedKindOf@InGameUI@@UBE_NW4KindOfType@@@Z")();
void __identifier("?isPlacementAnchored@InGameUI@@UAE_NXZ")();
void __identifier("?isScrolling@InGameUI@@UAE_NXZ")();
void __identifier("?isSelecting@InGameUI@@UAE_NXZ")();
void __identifier("?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ")();
void __identifier("?loadPostProcess@InGameUI@@MAEXXZ")();
void __identifier("?mergeRva0029AF3F@InGameUI@@UAEXPBH0PAH@Z")();
void __identifier("?message@InGameUI@@UAAXVAsciiString@@ZZ")();
void __identifier("?message@InGameUI@@UAAXVUnicodeString@@ZZ")();
void __identifier("?messageColor@InGameUI@@UAAXPBURGBColor@@VUnicodeString@@ZZ")();
void __identifier("?militarySubtitle@InGameUI@@UAEXABVAsciiString@@H@Z")();
void __identifier("?militarySubtitle@InGameUI@@UAEXVUnicodeString@@H@Z")();
void __identifier("?name@Rva0008EFD2Named@@QBEPBDXZ")();
void __identifier("?objectChangedTeam@InGameUI@@UAEXPBVObject@@HH@Z")();
void __identifier("?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z")();
void __identifier("?playCameoMovie@InGameUI@@UAEXABVAsciiString@@@Z")();
void __identifier("?postDraw@InGameUI@@UAEXXZ")();
void __identifier("?preDraw@InGameUI@@UAEXXZ")();
void __identifier("?recreateControlBar@InGameUI@@UAEXXZ")();
void __identifier("?removeIdleWorker@InGameUI@@UAEXPAVObject@@H@Z")();
void __identifier("?removeMilitarySubtitle@InGameUI@@UAEXXZ")();
void __identifier("?removeSuperweapon@InGameUI@@UAE_NHABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z")();
void __identifier("?reset@Rva0008EF3FProduct@@UAEXXZ")();
void __identifier("?resetIdleWorker@InGameUI@@UAEXXZ")();
void __identifier("?rva0008EF81@Rva0008EF81@@QAEXXZ")();
void __identifier("?rva0008EFD8@Rva0008EF3FProduct@@QAEPAXXZ")();
void __identifier("?rva0008F0CA@Rva0008F0CA@@QAEXXZ")();
void __identifier("?rva0008F32C@@YAXXZ")();
void __identifier("?rva0029A60C@Rva0029A60C@@QAEX_N@Z")();
void __identifier("?rva0029A872@Rva0029A872@@QAE?AURva00SlotFloat2Copy@@XZ")();
void __identifier("?rva0029A9B4@Rva0029A9B4@@QAEHXZ")();
void __identifier("?rva0029AA62@Rva0029AA3F@@QAEXPBUCoord3D@@@Z")();
void __identifier("?rva0029AAC8@Rva0029AA3F@@QAEXPBUCoord3D@@@Z")();
void __identifier("?rva0029AC03@InGameUI@@UAEX_N@Z")();
void __identifier("?rva0029AC98@Rva0029AC98Forwarder@@QAEXXZ")();
void __identifier("?rva0029ACFB@Rva0029ACFB@@UAEHXZ")();
void __identifier("?rva0029B558@Rva0029B558@@UAEXXZ")();
void __identifier("?rva0029B563@Rva0029B558@@UAEXXZ")();
void __identifier("?rva0029B56E@InGameUI@@UAEXABVUnicodeString@@ABVRva002217EA@@H@Z")();
void __identifier("?rva0029B5CD@Rva0029B5CD@@QAE_NPAVAnimateWindow@@@Z")();
void __identifier("?rva0029B5D8@Rva0029B558@@UAEHXZ")();
void __identifier("?rva0029BE05@InGameUI@@UAEX_NPAVPlayer@@@Z")();
void __identifier("?rva0029C096@Rva0029C096@@QAEHXZ")();
void __identifier("?rva0029C0A9@Rva0029C0A9@@QAE_NH@Z")();
void __identifier("?rva0029DB61@InGameUI@@UAE_NXZ")();
void __identifier("?rva0029E656@InGameUI@@UAAXVAsciiString@@ZZ")();
void __identifier("?rva0029E846@InGameUI@@UAAXVUnicodeString@@ZZ")();
void __identifier("?rva0029E99F@InGameUI@@UAAXPBURGBColor@@VUnicodeString@@ZZ")();
void __identifier("?rva0029EAFA@Rva0029EAFA@@QAEXPBVGameMessage@@@Z")();
void __identifier("?rva0029FD1B@InGameUI@@UAEXHPAVMaterialPassClass@@PAVOverridable@@H@Z")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?rva005F688B@QueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEXPAX@Z")();
void __identifier("?selectDrawable@InGameUI@@UAEXPAVDrawable@@@Z")();
void __identifier("?selectMatchingAcrossMap@InGameUI@@UAEHXZ")();
void __identifier("?selectMatchingAcrossRegion@InGameUI@@UAEHPAUIRegion2D@@@Z")();
void __identifier("?selectMatchingAcrossScreen@InGameUI@@UAEHXZ")();
void __identifier("?selectNextIdleWorker@InGameUI@@UAEXXZ")();
void __identifier("?selectUnitsMatchingCurrentSelection@InGameUI@@UAEHXZ")();
void __identifier("?set@Rva0008EFAAByteSlot@@QAEXE@Z")();
void __identifier("?set@Rva004AD9A6ByteSlot@@QAEXE@Z")();
void __identifier("?setGUICommand@InGameUI@@UAEXPBVCommandButton@@@Z")();
void __identifier("?setInputEnabled@InGameUI@@UAEX_NPA_N@Z")();
void __identifier("?setPlacementEnd@InGameUI@@UAEXPBUICoord2D@@@Z")();
void __identifier("?setPlacementStart@InGameUI@@UAEXPBUICoord2D@@@Z")();
void __identifier("?setRadiusCursorNone@InGameUI@@UAEXXZ")();
void __identifier("?setRva0029B04D@InGameUI@@UAEXH@Z")();
void __identifier("?setScrollAmount@InGameUI@@UAEXVCoord2D@@@Z")();
void __identifier("?setScrolling@InGameUI@@UAEX_N@Z")();
void __identifier("?setSelecting@InGameUI@@UAEX_N@Z")();
void __identifier("?showIdleWorkerLayout@InGameUI@@EAEXXZ")();
void __identifier("?showObjectSuperweaponDisplayByScript@InGameUI@@UAEXPBVObject@@@Z")();
void __identifier("?stopCameoMovie@InGameUI@@UAEXXZ")();
void __identifier("?stopMovie@InGameUI@@UAEXXZ")();
void __identifier("?update@Rva0008EF3FProduct@@UAEXXZ")();
void __identifier("?updateFormationPreview@InGameUI@@UAEXXZ")();
void __identifier("?updateIdleWorker@InGameUI@@EAEXXZ")();
void __identifier("?xfer@InGameUI@@MAEXPAVXfer@@@Z")();
}

// Retail table at VA 0x00BC7A88.
extern "C" const void *const __identifier("g_productPrimaryTable")[125] = {
	(const void *)&__identifier("??_GRva008F00D@@UAEPAXI@Z"), // slot 0, RVA 0x0008F379
	(const void *)&__identifier("?init@Rva0008EF3FProduct@@UAEXXZ"), // slot 1, RVA 0x0008F0BB
	(const void *)&__identifier("?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ"), // slot 2, RVA 0x001B5384
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 3, RVA 0x000B3FD0
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 4, RVA 0x005CB9FF
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 5, RVA 0x0047A699
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 6, RVA 0x000D43D0
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 7, RVA 0x0047A69C
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 8, RVA 0x000B3FD0
	(const void *)&__identifier("?reset@Rva0008EF3FProduct@@UAEXXZ"), // slot 9, RVA 0x0008F0C5
	(const void *)&__identifier("?update@Rva0008EF3FProduct@@UAEXXZ"), // slot 10, RVA 0x0008F0C0
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 11, RVA 0x005CB9FF
	(const void *)&__identifier("?rva0008F0CA@Rva0008F0CA@@QAEXXZ"), // slot 12, RVA 0x0008F0CA
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 13, RVA 0x0047A69C
	(const void *)&__identifier("?rva0029E99F@InGameUI@@UAAXPBURGBColor@@VUnicodeString@@ZZ"), // slot 14, RVA 0x0029E99F
	(const void *)&__identifier("?rva0029E656@InGameUI@@UAAXVAsciiString@@ZZ"), // slot 15, RVA 0x0029E656
	(const void *)&__identifier("?rva0029E846@InGameUI@@UAAXVUnicodeString@@ZZ"), // slot 16, RVA 0x0029E846
	(const void *)&__identifier("?messageColor@InGameUI@@UAAXPBURGBColor@@VUnicodeString@@ZZ"), // slot 17, RVA 0x0029EA54
	(const void *)&__identifier("?message@InGameUI@@UAAXVAsciiString@@ZZ"), // slot 18, RVA 0x0029E757
	(const void *)&__identifier("?message@InGameUI@@UAAXVUnicodeString@@ZZ"), // slot 19, RVA 0x0029E8FA
	(const void *)&__identifier("?rva0008EF81@Rva0008EF81@@QAEXXZ"), // slot 20, RVA 0x0008EF81
	(const void *)&__identifier("?get@Rva0008EF95ByteField@@QBEEXZ"), // slot 21, RVA 0x0008EF95
	(const void *)&__identifier("?militarySubtitle@InGameUI@@UAEXVUnicodeString@@H@Z"), // slot 22, RVA 0x0029F530
	(const void *)&__identifier("?militarySubtitle@InGameUI@@UAEXABVAsciiString@@H@Z"), // slot 23, RVA 0x0029C2F6
	(const void *)&__identifier("?removeMilitarySubtitle@InGameUI@@UAEXXZ"), // slot 24, RVA 0x002A0C87
	(const void *)&__identifier("?displayCantBuildMessage@InGameUI@@UAEXW4LegalBuildCode@@@Z"), // slot 25, RVA 0x0029C291
	(const void *)&__identifier("?beginAreaSelectHint@InGameUI@@UAEXPBVGameMessage@@@Z"), // slot 26, RVA 0x0029A79F
	(const void *)&__identifier("?rva005F688B@QueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEXPAX@Z"), // slot 27, RVA 0x005F688B
	(const void *)&__identifier("?rva0029EAFA@Rva0029EAFA@@QAEXPBVGameMessage@@@Z"), // slot 28, RVA 0x0029EAFA
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 29, RVA 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 30, RVA 0x0047A69C
	(const void *)&__identifier("?createMouseoverHint@InGameUI@@UAEXPBVGameMessage@@@Z"), // slot 31, RVA 0x0029EBE2
	(const void *)&__identifier("?createCommandHint@InGameUI@@UAEXPBVGameMessage@@@Z"), // slot 32, RVA 0x002A3273
	(const void *)&__identifier("?createGarrisonHint@InGameUI@@UAEXPBVGameMessage@@@Z"), // slot 33, RVA 0x0029A7C4
	(const void *)&__identifier("?addSuperweapon@InGameUI@@UAEXHABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z"), // slot 34, RVA 0x002A70AE
	(const void *)&__identifier("?removeSuperweapon@InGameUI@@UAE_NHABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z"), // slot 35, RVA 0x002A4975
	(const void *)&__identifier("?objectChangedTeam@InGameUI@@UAEXPBVObject@@HH@Z"), // slot 36, RVA 0x002A43A0
	(const void *)&__identifier("?rva0029A60C@Rva0029A60C@@QAEX_N@Z"), // slot 37, RVA 0x0029A60C
	(const void *)&__identifier("?get@Rva004F5F8EByteField@@QBEEXZ"), // slot 38, RVA 0x004F5F8E
	(const void *)&__identifier("?hideObjectSuperweaponDisplayByScript@InGameUI@@UAEXPBVObject@@@Z"), // slot 39, RVA 0x0029E20B
	(const void *)&__identifier("?showObjectSuperweaponDisplayByScript@InGameUI@@UAEXPBVObject@@@Z"), // slot 40, RVA 0x0029E25A
	(const void *)&__identifier("?setScrolling@InGameUI@@UAEX_N@Z"), // slot 41, RVA 0x0029A7F1
	(const void *)&__identifier("?isScrolling@InGameUI@@UAE_NXZ"), // slot 42, RVA 0x0029A83A
	(const void *)&__identifier("?setSelecting@InGameUI@@UAEX_N@Z"), // slot 43, RVA 0x0029A841
	(const void *)&__identifier("?isSelecting@InGameUI@@UAE_NXZ"), // slot 44, RVA 0x0029A854
	(const void *)&__identifier("?setScrollAmount@InGameUI@@UAEXVCoord2D@@@Z"), // slot 45, RVA 0x0029A85B
	(const void *)&__identifier("?rva0029A872@Rva0029A872@@QAE?AURva00SlotFloat2Copy@@XZ"), // slot 46, RVA 0x0029A872
	(const void *)&__identifier("?setGUICommand@InGameUI@@UAEXPBVCommandButton@@@Z"), // slot 47, RVA 0x0029A889
	(const void *)&__identifier("?get@Rva0036739CDwordField@@QBEHXZ"), // slot 48, RVA 0x0036739C
	(const void *)&__identifier("?rva0029AA62@Rva0029AA3F@@QAEXPBUCoord3D@@@Z"), // slot 49, RVA 0x0029AA62
	(const void *)&__identifier("?rva0029AAC8@Rva0029AA3F@@QAEXPBUCoord3D@@@Z"), // slot 50, RVA 0x0029AAC8
	(const void *)&__identifier("?get@Rva0008EF9CByteField@@QBEEXZ"), // slot 51, RVA 0x0008EF9C
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 52, RVA 0x000D43D0
	(const void *)&__identifier("?updateFormationPreview@InGameUI@@UAEXXZ"), // slot 53, RVA 0x002A4E1F
	(const void *)&__identifier("?rva0029DB61@InGameUI@@UAE_NXZ"), // slot 54, RVA 0x0029DB61
	(const void *)&__identifier("?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z"), // slot 55, RVA 0x0029BB8B
	(const void *)&__identifier("?rva0029A9B4@Rva0029A9B4@@QAEHXZ"), // slot 56, RVA 0x0029A9B4
	(const void *)&__identifier("?get@Rva0029A9BBDwordField@@QBEHXZ"), // slot 57, RVA 0x0029A9BB
	(const void *)&__identifier("?setPlacementStart@InGameUI@@UAEXPBUICoord2D@@@Z"), // slot 58, RVA 0x0029A9C2
	(const void *)&__identifier("?setPlacementEnd@InGameUI@@UAEXPBUICoord2D@@@Z"), // slot 59, RVA 0x0029AAE0
	(const void *)&__identifier("?isPlacementAnchored@InGameUI@@UAE_NXZ"), // slot 60, RVA 0x0029AAFC
	(const void *)&__identifier("?getPlacementPoints@InGameUI@@UAEXPAUICoord2D@@0@Z"), // slot 61, RVA 0x0029B45C
	(const void *)&__identifier("?getPlacementAngle@InGameUI@@UAEMXZ"), // slot 62, RVA 0x0029AB0B
	(const void *)&__identifier("?get@Rva0008EFA3ByteField@@QBEEXZ"), // slot 63, RVA 0x0008EFA3
	(const void *)&__identifier("?set@Rva0008EFAAByteSlot@@QAEXE@Z"), // slot 64, RVA 0x0008EFAA
	(const void *)&__identifier("?disable@Rva0029AB03ByteZeroSetter@@QAEXXZ"), // slot 65, RVA 0x0029AB03
	(const void *)&__identifier("?selectDrawable@InGameUI@@UAEXPAVDrawable@@@Z"), // slot 66, RVA 0x002A3805
	(const void *)&__identifier("?deselectDrawable@InGameUI@@UAEXPAVDrawable@@@Z"), // slot 67, RVA 0x0029F34F
	(const void *)&__identifier("?deselectAllDrawables@InGameUI@@UAEXXZ"), // slot 68, RVA 0x0029BDBC
	(const void *)&__identifier("?rva0029BE05@InGameUI@@UAEX_NPAVPlayer@@@Z"), // slot 69, RVA 0x0029BE05
	(const void *)&__identifier("?get@Rva0054902CDwordField@@QBEHXZ"), // slot 70, RVA 0x0054902C
	(const void *)&__identifier("?get@Rva0008EFB7DwordField@@QBEHXZ"), // slot 71, RVA 0x0008EFB7
	(const void *)&__identifier("?get@Rva0028A94BDwordField@@QBEHXZ"), // slot 72, RVA 0x0028A94B
	(const void *)&__identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ"), // slot 73, RVA 0x004F5FA3
	(const void *)&__identifier("?getAllSelectedLocalDrawables@InGameUI@@UAEPBV?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@XZ"), // slot 74, RVA 0x002A3908
	(const void *)&__identifier("?rva0029C096@Rva0029C096@@QAEHXZ"), // slot 75, RVA 0x0029C096
	(const void *)&__identifier("?get@Rva0008EFBEDwordField@@QBEHXZ"), // slot 76, RVA 0x0008EFBE
	(const void *)&__identifier("?rva0029C0A9@Rva0029C0A9@@QAE_NH@Z"), // slot 77, RVA 0x0029C0A9
	(const void *)&__identifier("?isAnySelectedKindOf@InGameUI@@UBE_NW4KindOfType@@@Z"), // slot 78, RVA 0x0029C0D6
	(const void *)&__identifier("?isAllSelectedKindOf@InGameUI@@UBE_NW4KindOfType@@@Z"), // slot 79, RVA 0x0029C107
	(const void *)&__identifier("?rva0029FD1B@InGameUI@@UAEXHPAVMaterialPassClass@@PAVOverridable@@H@Z"), // slot 80, RVA 0x0029FD1B
	(const void *)&__identifier("?setRadiusCursorNone@InGameUI@@UAEXXZ"), // slot 81, RVA 0x0029A64A
	(const void *)&__identifier("?setInputEnabled@InGameUI@@UAEX_NPA_N@Z"), // slot 82, RVA 0x0029AB48
	(const void *)&__identifier("?rva0029AC98@Rva0029AC98Forwarder@@QAEXXZ"), // slot 83, RVA 0x0029AC98
	(const void *)&__identifier("?preDraw@InGameUI@@UAEXXZ"), // slot 84, RVA 0x002A3255
	(const void *)&__identifier("?postDraw@InGameUI@@UAEXXZ"), // slot 85, RVA 0x002A0161
	(const void *)&__identifier("?drawMilitarySubtitle@InGameUI@@UAEXXZ"), // slot 86, RVA 0x0029AD12
	(const void *)&__identifier("?bfmeGoBLD@@YGXPAX@Z"), // slot 87, RVA 0x0029ACE3
	(const void *)&__identifier("?stopMovie@InGameUI@@UAEXXZ"), // slot 88, RVA 0x0029B4C4
	(const void *)&__identifier("?rva0029ACFB@Rva0029ACFB@@UAEHXZ"), // slot 89, RVA 0x0029ACFB
	(const void *)&__identifier("?playCameoMovie@InGameUI@@UAEXABVAsciiString@@@Z"), // slot 90, RVA 0x0029F3D7
	(const void *)&__identifier("?stopCameoMovie@InGameUI@@UAEXXZ"), // slot 91, RVA 0x0029F4AB
	(const void *)&__identifier("?get@Rva0043812FDwordField@@QBEHXZ"), // slot 92, RVA 0x0043812F
	(const void *)&__identifier("?get@Rva0029A7EADwordField@@QBEHXZ"), // slot 93, RVA 0x0029A7EA
	(const void *)&__identifier("?rva0029AC03@InGameUI@@UAEX_N@Z"), // slot 94, RVA 0x0029AC03
	(const void *)&__identifier("?get@Rva0008EFC5ByteField@@QBEEXZ"), // slot 95, RVA 0x0008EFC5
	(const void *)&__identifier("?Rva0008EFCCGet@@YAHXZ"), // slot 96, RVA 0x0008EFCC
	(const void *)&__identifier("?selectUnitsMatchingCurrentSelection@InGameUI@@UAEHXZ"), // slot 97, RVA 0x0029AF1C
	(const void *)&__identifier("?selectMatchingAcrossScreen@InGameUI@@UAEHXZ"), // slot 98, RVA 0x0029CEB1
	(const void *)&__identifier("?selectMatchingAcrossMap@InGameUI@@UAEHXZ"), // slot 99, RVA 0x0029CFC8
	(const void *)&__identifier("?selectMatchingAcrossRegion@InGameUI@@UAEHPAUIRegion2D@@@Z"), // slot 100, RVA 0x002A3AFA
	(const void *)&__identifier("?mergeRva0029AF3F@InGameUI@@UAEXPBH0PAH@Z"), // slot 101, RVA 0x0029AF3F
	(const void *)&__identifier("?get@Rva0045310DByteField@@QBEEXZ"), // slot 102, RVA 0x0045310D
	(const void *)&__identifier("?set@Rva004AD9A6ByteSlot@@QAEXE@Z"), // slot 103, RVA 0x004AD9A6
	(const void *)&__identifier("?addFloatingText@InGameUI@@UAEXABVUnicodeString@@PBUCoord3D@@H@Z"), // slot 104, RVA 0x002A0D19
	(const void *)&__identifier("?addIdleWorker@InGameUI@@UAEXPAVObject@@@Z"), // slot 105, RVA 0x002A3D98
	(const void *)&__identifier("?removeIdleWorker@InGameUI@@UAEXPAVObject@@H@Z"), // slot 106, RVA 0x0029F77E
	(const void *)&__identifier("?selectNextIdleWorker@InGameUI@@UAEXXZ"), // slot 107, RVA 0x0029D64F
	(const void *)&__identifier("?recreateControlBar@InGameUI@@UAEXXZ"), // slot 108, RVA 0x0029F7EA
	(const void *)&__identifier("?setRva0029B04D@InGameUI@@UAEXH@Z"), // slot 109, RVA 0x0029B04D
	(const void *)&__identifier("?clearRva0029B060@InGameUI@@UAEXXZ"), // slot 110, RVA 0x0029B060
	(const void *)&__identifier("?areTooltipsDisabled@InGameUI@@UBE_NXZ"), // slot 111, RVA 0x0029B068
	(const void *)&__identifier("?getIdleWorkerCount@InGameUI@@EAEHXZ"), // slot 112, RVA 0x0029F7C8
	(const void *)&__identifier("?findIdleWorker@InGameUI@@EAEPAVObject@@PAV2@@Z"), // slot 113, RVA 0x0029D612
	(const void *)&__identifier("?showIdleWorkerLayout@InGameUI@@EAEXXZ"), // slot 114, RVA 0x0029AFA6
	(const void *)&__identifier("?hideIdleWorkerLayout@InGameUI@@EAEXXZ"), // slot 115, RVA 0x0029D735
	(const void *)&__identifier("?updateIdleWorker@InGameUI@@EAEXXZ"), // slot 116, RVA 0x0029AFFC
	(const void *)&__identifier("?resetIdleWorker@InGameUI@@UAEXXZ"), // slot 117, RVA 0x0029D777
	(const void *)&__identifier("?rva0008EFD8@Rva0008EF3FProduct@@QAEPAXXZ"), // slot 118, RVA 0x0008EFD8
	(const void *)&__identifier("?rva0008F32C@@YAXXZ"), // slot 119, RVA 0x0008F32C
	(const void *)&__identifier("?drawSelectionRegion@Rva0008EF3FProduct@@UAEXXZ"), // slot 120, RVA 0x0008F395
	(const void *)&__identifier("?drawMoveHints@Rva0008EF3FProduct@@UAEXPAVView@@@Z"), // slot 121, RVA 0x0008F48E
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 122, RVA 0x0047A69C
	(const void *)&__identifier("?drawPlaceAngle@Rva0008EF3FProduct@@UAEXPAVView@@@Z"), // slot 123, RVA 0x0008F179
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 124, RVA 0x0047A69C
};

// Retail table at VA 0x00BC7A78.
extern "C" const void *const __identifier("g_productSnapshotTable")[4] = {
	(const void *)&__identifier("??_ERva008F00D@@WM@AEPAXI@Z"), // slot 0, RVA 0x0008F371
	(const void *)&__identifier("?loadPostProcess@InGameUI@@MAEXXZ"), // slot 1, RVA 0x002A2184
	(const void *)&__identifier("?name@Rva0008EFD2Named@@QBEPBDXZ"), // slot 2, RVA 0x0008EFD2
	(const void *)&__identifier("?xfer@InGameUI@@MAEXPAVXfer@@@Z"), // slot 3, RVA 0x002A6AC2
};

// Retail table at VA 0x00BC7A64.
extern "C" const void *const __identifier("g_productInterface10Table")[5] = {
	(const void *)&__identifier("?rva0029B558@Rva0029B558@@UAEXXZ"), // slot 0, RVA 0x0029B558
	(const void *)&__identifier("?rva0029B563@Rva0029B558@@UAEXXZ"), // slot 1, RVA 0x0029B563
	(const void *)&__identifier("?rva0029B56E@InGameUI@@UAEXABVUnicodeString@@ABVRva002217EA@@H@Z"), // slot 2, RVA 0x0029B56E
	(const void *)&__identifier("?rva0029B5CD@Rva0029B5CD@@QAE_NPAVAnimateWindow@@@Z"), // slot 3, RVA 0x0029B5CD
	(const void *)&__identifier("?rva0029B5D8@Rva0029B558@@UAEHXZ"), // slot 4, RVA 0x0029B5D8
};

class __declspec(novtable) Rva0008EF3FProduct : public InGameUI
{
public:
	Rva0008EF3FProduct();
	virtual ~Rva0008EF3FProduct();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void drawSelectionRegion(void);
	virtual void drawMoveHints(View *view);
	virtual void drawPlaceAngle(View *view);

private:
	enum { MAX_MOVE_HINTS = 25 };

	RenderObjClass *m_moveHintRenderObj[MAX_MOVE_HINTS];	// +0x9F0
	HAnimClass *m_moveHintAnim[MAX_MOVE_HINTS];		// +0xA54
	class RenderObjClass *m_buildingPlacementAnchor;	// +0xAB8
	class RenderObjClass *m_buildingPlacementArrow;		// +0xABC
};

Rva0008EF3FProduct::Rva0008EF3FProduct()
{
	int i;

	*(const void *const **)this = g_productPrimaryTable;
	*(const void *const **)((char *)this + 0x0C) = g_productSnapshotTable;
	*(const void *const **)((char *)this + 0x10) = g_productInterface10Table;

	for (i = 0; i < MAX_MOVE_HINTS; i++)
	{
		m_moveHintRenderObj[i] = 0;
		m_moveHintAnim[i] = 0;
	}

	m_buildingPlacementAnchor = 0;
	m_buildingPlacementArrow = 0;
}
