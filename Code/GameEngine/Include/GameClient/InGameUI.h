/* Target facts (code addresses are RVAs; table addresses are VAs):
Constructor 0x002A61A9 calls SubsystemInterface's constructor 0x001B4E63 at 0x002A61BE. The parent stores 0x00BD77A0, clears byte +4 and the AsciiString at +8. InGameUI stores Snapshot's 0x00BBB554 at +0xC (0x002A61C8) and a five-purecall interface table 0x00C078DC at +0x10 (0x002A61CF), then installs its own tables 0x00BFD410, 0x00BFD400 and 0x00BC7A64 at 0x002A61E1/0x002A61E7/0x002A61EE.
Destructor 0x002A5B30 restores those same three derived tables at 0x002A5B42/0x002A5B48/0x002A5B4F. Its final stores at 0x002A5EBB/0x002A5EC4 restore the secondary bases before the call to SubsystemInterface's destructor at 0x002A5ECB. The different final constructor/destructor stores belong to different lifetime phases, not competing InGameUI layouts. The deleting destructor 0x002A6A11 calls 0x002A5B30. Both lifetime methods are declared out of line.
The primary table 0x00BFD410 contains 120 slots. Slots 0/1/9/10 are the deleting destructor/init/reset/update; slots 2-8/11/13 match the fourteen-slot parent table. Slot 12 is purecall, overriding the parent's empty slot. Slots 118/119 are purecall; the derived table 0x00BC7A88 supplies the pointer-returning factory 0x0008EFD8 and the void initializer 0x0008F32C there. Named rowed slots follow the ledger's names at their table targets; other named slots have donor or call-site evidence below. Unnamed slots retain neutral names. Message overloads occupy 18/19 and subtitle overloads 22/23 in reverse declaration order under VC7.1.
The +0xC table has four slots: 0=0x002A5EDE (subtract 0xC, jump to the deleting destructor), 1=loadPostProcess 0x002A2184, 2=0x0008EFD2 (return name literal VA 0x00BC7C7C), 3=xfer 0x002A6AC2. The +0x10 table has five slots, 0x0029B558/0x0029B563/0x0029B56E/0x0029B5CD/0x0029B5D8, with no destructor slot. Their +0x9BC accesses address the complete object's +0x9CC notification owner.
The constructor writes its last float at +0x9EC at 0x002A645B. Its only direct constructor caller, 0x0008EF3F, calls it at 0x0008EF42 and initializes the derived arrays starting at +0x9F0 (0x0008EF5D..0x0008EF6F); the base extent is 0x9F0 with four-byte alignment.
The constructor builds lists at +0x18/+0x20/+0x24 (0x002A61F5/0x002A620A/0x002A621A), initializes the movie string at +0x1C (0x002A61FD), builds 25 twenty-byte hints at +0x40 (0x002A6229..0x002A6235), and initializes selection/input flags and counters in 0x002A6463..0x002A64FD. Retail input forwards 0x0029AB22/0x0029AB35 pass +0x15/+0x16 to primary slot 82. Other storage remains opaque unless a retail access below identifies it.
Exposed scalar storage is proved by constructor stores: byte +0x14 at 0x002A67C6, +0x15/+0x16 at 0x002A6463/0x002A6467, +0x28 at 0x002A646B, +0x3C at 0x002A6936, +0x811 at 0x002A6738; dwords +0x238 at 0x002A662E, +0x53C/+0x540 at 0x002A66A6/0x002A66AC, +0x568/+0x56C/+0x570 at 0x002A6474/0x002A644E/0x002A647A, and the allocated notification pointer +0x9CC at 0x002A6415. Rva00524FA7 reads dword +0x988 at 0x00524FAD and converts it as unsigned through the sign test and x87 correction at 0x00524FC1/0x00524FC3.
Nonvirtual declarations retain rowed out-of-line bodies: resetCamera 0x0029B4F9, areSelectedObjectsControllable 0x0029C752, expireHint/expireAllHints 0x0029ACA0/0x0029ACC7, evaluateSoloNexus 0x0029B967, addMessageText 0x0029BA58, createControlBar/createReplayControl 0x0029C23E/0x0029C269, updateMilitarySubtitle 0x0029C404, updateFloatingText/drawFloatingText 0x0029D0E5/0x0029D200, updateAndDrawWorldAnimations 0x0029D44E, handleRadiusCursor 0x0029A661, handleBuildPlacements 0x002A21E1, updateLocalPhantomStructureDisplay 0x002A1158, updateOrderDisplayMode 0x0029A72C, addNamedTimer 0x002A5A50, addWorldAnimation 0x002A0E16, rva002A4A68 0x002A4A68, rva0029D9F9 0x0029D9F9, clearFormationPreviewDrawables 0x002A3DD3, rva002A3E24 0x002A3E24. No inline lifetime, copy or assignment body is supplied.
The monotonic setter 0x0029B04D and clearer 0x0029B060 access an unsigned dword at +0x7EC. The constructor builds four-byte STLport lists at +0x18/+0x20/+0x24/+0x8A0/+0x8CC (0x002A61F5/0x002A620A/0x002A621A/0x002A6356/0x002A6369) and twenty four-byte lists at +0x928 through its vector constructor call 0x002A63BC (count 0x14, size 4); Zero Hour declares m_windowLayouts, m_selectedDrawables, m_selectedLocalDrawables, m_floatingTextList, m_worldAnimationList and m_idleWorkers[MAX_PLAYER_COUNT] in this order with these element types. They are typed where the includer loaded STLport's list header first and stay opaque elsewhere; the selection return types retain the ledger's STLport list identity without requiring a container implementation in callers. canSelectedObjectsDoAction 0x0029C823, canSelectedObjectsEffectivelyUseWeapon 0x0029CDD2, canSelectedObjectsNonAttackInteractWithObject 0x0029F72F, canSelectedObjectsDoSpecialPower 0x002A395C, canSelectedObjectsOverrideSpecialPowerDestination 0x0029CBA6 and getCanSelectedObjectsAttack 0x0029C779 prove the nested ActionType/SelectionRules method signatures. Zero Hour names SelectionRules values ANY=0 and ALL=1; no ActionType values are asserted.
Additional rowed declarations: rva0029CC19 0x0029CC19, rva0029FCD9 0x0029FCD9, rva0029B3C1 0x0029B3C1, rva002A123F/1261/1283 at their named RVAs, notifyHeroEarnedAward 0x0029DCA9, notifyOfHeroSpawnEvent 0x0029F954, findSWInfo 0x002A435D, parseNamedRadiusDecalTemplate 0x002A4523, rva002A3E5A 0x002A3E5A, rva002A470F 0x002A470F, rva002A4A0C 0x002A4A0C and rva002A4BFC 0x002A4BFC. Their declarations use the ledger's existing types and names.
HintSpyTranslator::translateGameMessage 0x00428C43 dispatches slots 26-33 with one GameMessage pointer; its retail call sites and Zero Hour name slots 27-30 endAreaSelectHint/createMoveHint/createAttackHint/createForceAttackHint. Getter 0x0029A7EA (slot 93) reads the drawable ID dword at +0x804. The constructor clears the bytes at +0x8B0/+0x8B8/+0x8B9 at 0x002A6946/0x002A694C/0x002A6952; issueMoveToLocationCommand 0x004292F6 reads those same three bytes. Slot 83 (0x0029AC98) tail-dispatches deselectDrawable, preserving its one Drawable pointer argument; Zero Hour names this disregardDrawable. The row at 0x0029E159 proves the nested FormationPreviewDecal constructor's scope. The pinned method rva000CF155 at 0x000CF155 returns the null-preserving +0x10 interface conversion, called by HideControlBar 0x00402A72 and ShowControlBar 0x00402AE4.
Donor facts: Zero Hour's InGameUI declaration supplies the names of message toggles, selection getters and placement getters. Their BFME2 table targets access the corresponding retail fields: +0x811, +0x238, +0x53C/+0x540, +0x568/+0x56C/+0x570, +0x20/+0x24 and +0x3C. The interface at +0x10 has only a structural name; its original class name is not established.
The INI field-parse table at VA 0x00BFC338 gives each key's offset and parser: parseAsciiString 0x0002F11E, parseInt 0x0002EF56, parseBool 0x0002E850, parseColorInt 0x0002F3FE, parseReal 0x0002EFC0, parseDurationReal 0x00338B0A and parseVelocityReal 0x00338BBD type the superweapon (+0x728..+0x748), named-timer (+0x76C..+0x798), drawable-caption (+0x79C..+0x7A4), message (+0x814..+0x838), military-caption (+0x858..+0x86C), floating-text (+0x8A4..+0x8AC) and RMB-anchor (+0x8C3/+0x8C4) members; Zero Hour's table maps the same keys to these names. BFME2-only keys keep neutral names: UnitHelpTextDelay +0x984 (integral store by 0x0002F0F7) and the four Hero*NotificationMessage/Timeout pairs +0x9D0..+0x9EC (AsciiString, Real).
Rowed accesses: setScrolling/isScrolling 0x0029A7F1/0x0029A83A use byte +0x7F8, setSelecting/isSelecting 0x0029A841/0x0029A854 byte +0x7F9, isPlacementAnchored 0x0029AAFC reads byte +0x554, updateOrderDisplayMode 0x0029A72C stores 0/1/2 to dword +0x8B4, evaluateSoloNexus 0x0029B967 stores the drawable ID at +0x980 (0x0029B9C3), placeBuildAvailable 0x0029BB8B stores 1/2 to dword +0x9C8 (0x0029BCF6/0x0029BD2D), and playCameoMovie 0x0029F3D7 passes the pointer at +0x5C8 to the window's video-buffer setter (0x0029F48D). stopMovie 0x0029B4C4 calls slot 7 of the pointer at +0x5C4 and clears it (0x0029B4D6/0x0029B4D9), then empties the movie string at +0x1C, and the constructor clears it at 0x002A66D0; Zero Hour's stopMovie releases and clears m_videoStream before it empties m_currentlyPlayingMovie.
Pointee types: the constructor stores the result of InGameNotificationBoxMovieClip's constructor 0x004E6C34 (called at 0x002A640C) at +0x9CC (0x002A6415). playCameoMovie stores at +0x5CC (0x0029F40D) what TheVideoPlayer's slot 17 returns (call 0x0029F408); slot 17 of its table VA 0x00BC7EA8 is 0x0009151D, whose row returns VideoStreamInterface *. drawConstructPercent 0x002779CE reads TheInGameUI's +0x7A4 byte and +0x7A0 dword inline (0x00277A53/0x00277A59), the Zero Hour inline caption accessors.
Inline slots: W3DInGameUI's object (constructor 0x0008EF3F) emits InGameUI's inline virtuals right after its constructor, in table order, and both tables 0x00BFD410 and 0x00BC7A88 point at those copies: toggleMessages 0x0008EF81 (slot 20, byte +0x811 = 1 - itself), isMessagesOn 0x0008EF95 (21), slot51 0x0008EF9C (byte +0x98C), slot63/slot64 0x0008EFA3/0x0008EFAA (byte +0x8C6), getMaxSelectCount 0x0008EFB7 (+0x56C), slot76 0x0008EFBE (+0x980), slot95 0x0008EFC5 (byte +0x810) and the Snapshot name getter 0x0008EFD2 (+0xC table slot 2, the "InGameUI" literal at VA 0x00BC7C7C). Slots 52, 70, 72, 102 and 103 point at identical bodies folded elsewhere: 0x000D43D0 (xor eax,eax), 0x0054902C (+0x568), 0x0028A94B (+0x570), 0x0045310D and 0x004AD9A6 (byte +0x3C). Donor facts: Zero Hour declares toggleMessages, isMessagesOn, getSelectCount, getMaxSelectCount, getFrameSelectionChanged and getDisplayedMaxWarning inline with these bodies, and its snapshot methods protected; the loadPostProcess 0x002A2184 and xfer 0x002A6AC2 rows are protected virtuals.
*/
#ifndef BFME2_INGAMEUI_H
#define BFME2_INGAMEUI_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

namespace _STL {
template<class T> class allocator;
template<class T, class Allocator> class list;
}

class UnicodeString;
class Coord2D;
struct Coord3D;
struct ICoord2D;
struct IRegion2D;
struct RGBColor;
class Drawable;
class Object;
class Player;
class CommandButton;
class ThingTemplate;
class SpecialPowerTemplate;
class GameMessage;
class GameWindow;
class VideoBuffer;
class VideoStreamInterface;
class InGameNotificationBoxMovieClip;
class WindowLayout;
class FloatingTextData;
class WorldAnimationData;
class MaterialPassClass;
class Overridable;
class Anim2DTemplate;
class SuperweaponInfo;
class INI;
class Rva002217EA;
class AnimateWindow;
class Rva005CB260;
struct Rva0029AEF9Item;
struct Rva002A1B1DChunk;
enum ObjectID;
enum LegalBuildCode;
enum KindOfType;
enum CanAttackResult;
enum SpecialPowerType;
enum WorldAnimationOptions;

class InGameUIInterface10 {
public:
    virtual void slot10_00() = 0;
    virtual void slot10_01() = 0;
    virtual void rva0029B56E(const UnicodeString &, const Rva002217EA &, int) = 0;
    virtual bool slot10_03(class AnimateWindow *) = 0;
    virtual int slot10_04() = 0;
};

class InGameUI : public SubsystemInterface, public Snapshot, public InGameUIInterface10 {
public:
    enum SelectionRules { SELECTION_ANY = 0, SELECTION_ALL = 1 };
    enum ActionType;
    class FormationPreviewPoolObject;
    class FormationPreviewDecal;
    InGameUI();
    virtual ~InGameUI();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void vslot12() = 0;

    virtual void __cdecl rva0029E99F(const RGBColor *, UnicodeString, ...);
    virtual void __cdecl rva0029E656(AsciiString, ...);
    virtual void __cdecl rva0029E846(UnicodeString, ...);
    virtual void __cdecl messageColor(const RGBColor *, UnicodeString, ...);
    virtual void __cdecl message(UnicodeString, ...);
    virtual void __cdecl message(AsciiString, ...);
    virtual void toggleMessages() { field811 = 1 - field811; }
    virtual bool isMessagesOn() { return field811; }
    virtual void militarySubtitle(const AsciiString &, int);
    virtual void militarySubtitle(UnicodeString, int);
    virtual void removeMilitarySubtitle();
    virtual void displayCantBuildMessage(LegalBuildCode);
    virtual void beginAreaSelectHint(const GameMessage *);
    virtual void endAreaSelectHint(const GameMessage *);
    virtual void createMoveHint(const GameMessage *);
    virtual void createAttackHint(const GameMessage *);
    virtual void createForceAttackHint(const GameMessage *);
    virtual void createMouseoverHint(const GameMessage *);
    virtual void createCommandHint(const GameMessage *);
    virtual void createGarrisonHint(const GameMessage *);
    virtual void addSuperweapon(int, const AsciiString &, ObjectID, const SpecialPowerTemplate *);
    virtual bool removeSuperweapon(int, const AsciiString &, ObjectID, const SpecialPowerTemplate *);
    virtual void objectChangedTeam(const Object *, int, int);
    virtual void setSuperweaponDisplayEnabledByScript(bool);
    virtual bool getSuperweaponDisplayEnabledByScript() const;
    virtual void hideObjectSuperweaponDisplayByScript(const Object *);
    virtual void showObjectSuperweaponDisplayByScript(const Object *);
    virtual void setScrolling(bool);
    virtual bool isScrolling();
    virtual void setSelecting(bool);
    virtual bool isSelecting();
    virtual void setScrollAmount(Coord2D);
    virtual Coord2D getScrollAmount();
    virtual void setGUICommand(const CommandButton *);
    virtual const CommandButton *getGUICommand() const;
    virtual void slot49(const Coord3D *);
    virtual void slot50(const Coord3D *);
    virtual bool slot51() { return field98C; }
    virtual int slot52() { return 0; }
    virtual void updateFormationPreview();
    virtual bool rva0029DB61();
    virtual void placeBuildAvailable(const ThingTemplate *, Drawable *);
    virtual const ThingTemplate *getPendingPlaceType();
    virtual ObjectID getPendingPlaceSourceObjectID();
    virtual void setPlacementStart(const ICoord2D *);
    virtual void setPlacementEnd(const ICoord2D *);
    virtual bool isPlacementAnchored();
    virtual void getPlacementPoints(ICoord2D *, ICoord2D *);
    virtual float getPlacementAngle();
    virtual bool slot63() { return field8C6; }
    virtual void slot64(bool value) { field8C6 = value; }
    virtual void slot65();
    virtual void selectDrawable(Drawable *);
    virtual void deselectDrawable(Drawable *);
    virtual void deselectAllDrawables();
    virtual void rva0029BE05(bool, Player *);
    virtual int getSelectCount() { return field568; }
    virtual int getMaxSelectCount() { return field56C; }
    virtual unsigned int getFrameSelectionChanged() { return field570; }
    virtual const _STL::list<Drawable *, _STL::allocator<Drawable *> > *getAllSelectedDrawables() const;
    virtual const _STL::list<Drawable *, _STL::allocator<Drawable *> > *getAllSelectedLocalDrawables();
    virtual Drawable *getFirstSelectedDrawable();
    virtual int slot76() { return m_soloNexusSelectedDrawableID; }
    virtual bool slot77(int) const;
    virtual bool isAnySelectedKindOf(KindOfType) const;
    virtual bool isAllSelectedKindOf(KindOfType) const;
    virtual void rva0029FD1B(int, MaterialPassClass *, Overridable *, int);
    virtual void setRadiusCursorNone();
    virtual void setInputEnabled(bool, bool *);
    virtual void disregardDrawable(Drawable *);
    virtual void preDraw();
    virtual void postDraw();
    virtual void drawMilitarySubtitle();
    virtual void slot87(const AsciiString &);
    virtual void stopMovie();
    virtual int slot89();
    virtual void playCameoMovie(const AsciiString &);
    virtual void stopCameoMovie();
    virtual int slot92();
    virtual int getMousedOverDrawableID() const;
    virtual void rva0029AC03(bool);
    virtual bool slot95() const { return field810; }
    virtual const void *slot96() const;
    virtual int selectUnitsMatchingCurrentSelection();
    virtual int selectMatchingAcrossScreen();
    virtual int selectMatchingAcrossMap();
    virtual int selectMatchingAcrossRegion(IRegion2D *);
    virtual void mergeRva0029AF3F(const int *, const int *, int *);
    virtual bool getDisplayedMaxWarning() { return field03C; }
    virtual void setDisplayedMaxWarning(bool value) { field03C = value; }
    virtual void addFloatingText(const UnicodeString &, const Coord3D *, int);
    virtual void addIdleWorker(Object *);
    virtual void removeIdleWorker(Object *, int);
    virtual void selectNextIdleWorker();
    virtual void recreateControlBar();
    virtual void setRva0029B04D(int);
    virtual void clearRva0029B060();
    virtual bool areTooltipsDisabled() const;
private:
    virtual int getIdleWorkerCount();
    virtual Object *findIdleWorker(Object *);
    virtual void showIdleWorkerLayout();
    virtual void hideIdleWorkerLayout();
    virtual void updateIdleWorker();
public:
    virtual void resetIdleWorker();
    virtual void *slot118() = 0;
    virtual void slot119() = 0;

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const { return "InGameUI"; }
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *);
public:
    virtual void slot10_00();
    virtual void slot10_01();
    virtual void rva0029B56E(const UnicodeString &, const Rva002217EA &, int);
    virtual bool slot10_03(class AnimateWindow *);
    virtual int slot10_04();

    bool getInputEnabled() { return field015 && field016; }
    bool isInWaypointMode() const { return field8B0; }
    bool isInForceAttackMode() const { return field8B8; }
    int getDrawableCaptionPointSize() { return m_drawableCaptionPointSize; }
    bool isDrawableCaptionBold() { return m_drawableCaptionBold; }
    void setEngineInputEnabled(bool);
    void setInputEnabled(bool);
    void resetCamera();
    bool areSelectedObjectsControllable() const;
    bool rva0029AEF9(Rva0029AEF9Item *, int, int, int, int, int) const;
    void expireHint(int, unsigned int);
    void expireAllHints(int);
protected:
    void evaluateSoloNexus(Drawable * = 0);
    void addMessageText(const UnicodeString &, const RGBColor * = 0);
    void createControlBar();
    void createReplayControl();
    void updateMilitarySubtitle();
    void updateFloatingText();
    void drawFloatingText();
    void updateAndDrawWorldAnimations();
    void handleRadiusCursor();
    void handleBuildPlacements();
public:
    void updateLocalPhantomStructureDisplay();
    void updateOrderDisplayMode();
    void addNamedTimer(const AsciiString &, const UnicodeString &, bool);
    void addWorldAnimation(Anim2DTemplate *, const Coord3D *, WorldAnimationOptions, float, float);
    void rva002A4A68();
    Coord2D rva0029D9F9();
    void clearFormationPreviewDrawables();
    void rva002A3E24();
    bool rva0029CC19(const Object *);
    Rva005CB260 *rva000CF155();
    bool rva0029FCD9(const char *);
    float rva0029B3C1(const Object *) const;
    bool canSelectedObjectsDoAction(ActionType, const Object *, SelectionRules, bool) const;
    bool canSelectedObjectsEffectivelyUseWeapon(const CommandButton *, const Object *, const Coord3D *, SelectionRules) const;
    bool canSelectedObjectsNonAttackInteractWithObject(const Object *, SelectionRules) const;
    bool canSelectedObjectsDoSpecialPower(const CommandButton *, const Object *, const Coord3D *, SelectionRules, unsigned int, Object *) const;
    bool canSelectedObjectsOverrideSpecialPowerDestination(const Coord3D *, SelectionRules, SpecialPowerType) const;
    CanAttackResult getCanSelectedObjectsAttack(ActionType, const Object *, SelectionRules, bool) const;
    void rva002A123F(Object *);
    void rva002A1261(Object *);
    void rva002A1283(Object *);
    void notifyHeroEarnedAward(class CreateAHeroHero *, int);
    void notifyOfHeroSpawnEvent(Object *, const char *, const int *, float);
    FormationPreviewPoolObject *rva002A3E5A(ThingTemplate *);
    void rva002A470F(ThingTemplate *, const ICoord2D *, RGBColor);
    void rva002A4BFC(Object *, ThingTemplate *, const ICoord2D *, RGBColor);
    void rva002A4A0C(AsciiString, unsigned int, const Rva002A1B1DChunk *, const Rva002A1B1DChunk *, const Rva002A1B1DChunk *, const Rva002A1B1DChunk *);
    static void parseNamedRadiusDecalTemplate(INI *, void *, void *, const void *);
protected:
    SuperweaponInfo *findSWInfo(int, const AsciiString &, ObjectID, const SpecialPowerTemplate *);
public:

    bool field014;
    bool field015;
    bool field016;
#ifdef _STLP_INTERNAL_LIST_H
    _STL::list<WindowLayout *> m_windowLayouts;
#else
    void *field018;
#endif
    AsciiString field01C;
#ifdef _STLP_INTERNAL_LIST_H
    _STL::list<Drawable *> m_selectedDrawables;
    _STL::list<Drawable *> m_selectedLocalDrawables;
#else
    void *field020;
    void *field024;
#endif
    bool field028;
    char opaque029[0x3C - 0x29];
    bool field03C;
    char opaque040[0x238 - 0x40];
    const CommandButton *field238;
    char opaque23C[0x53C - 0x23C];
    const ThingTemplate *field53C;
    ObjectID field540;
    char opaque544[0x554 - 0x544];
    bool m_placeAnchorInProgress;
    char opaque555[0x568 - 0x555];
    int field568;
    int field56C;
    unsigned int field570;
    char opaque574[0x5C4 - 0x574];
    VideoStreamInterface *m_videoStream;
    VideoBuffer *m_cameoVideoBuffer;
    VideoStreamInterface *m_5CC;
    char opaque5D0[0x728 - 0x5D0];
    float m_superweaponFlashDuration;
    AsciiString m_superweaponNormalFont;
    int m_superweaponNormalPointSize;
    bool m_superweaponNormalBold;
    AsciiString m_superweaponReadyFont;
    int m_superweaponReadyPointSize;
    bool m_superweaponReadyBold;
    char opaque741[0x748 - 0x741];
    int m_superweaponFlashColor;
    char opaque74C[0x76C - 0x74C];
    float m_namedTimerFlashDuration;
    char opaque770[0x774 - 0x770];
    int m_namedTimerFlashColor;
    char opaque778[0x77C - 0x778];
    AsciiString m_namedTimerNormalFont;
    int m_namedTimerNormalPointSize;
    bool m_namedTimerNormalBold;
    int m_namedTimerNormalColor;
    AsciiString m_namedTimerReadyFont;
    int m_namedTimerReadyPointSize;
    bool m_namedTimerReadyBold;
    int m_namedTimerReadyColor;
    AsciiString m_drawableCaptionFont;
    int m_drawableCaptionPointSize;
    bool m_drawableCaptionBold;
    int m_drawableCaptionColor;
    char opaque7AC[0x7EC - 0x7AC];
    unsigned int field7EC;
    char opaque7F0[0x7F8 - 0x7F0];
    bool m_isScrolling;
    bool m_isSelecting;
    int m_7FC;
    int m_800;
    unsigned int m_804;
    char opaque808[0x810 - 0x808];
    bool field810;
    bool field811;
    int m_messageColor1;
    int m_messageColor2;
    char opaque81C[0x82C - 0x81C];
    AsciiString m_messageFont;
    int m_messagePointSize;
    bool m_messageBold;
    int m_messageDelayMS;
    char opaque83C[0x858 - 0x83C];
    AsciiString m_militaryCaptionTitleFont;
    int m_militaryCaptionTitlePointSize;
    bool m_militaryCaptionTitleBold;
    AsciiString m_militaryCaptionFont;
    int m_militaryCaptionPointSize;
    bool m_militaryCaptionBold;
    char opaque86D[0x8A0 - 0x86D];
#ifdef _STLP_INTERNAL_LIST_H
    _STL::list<FloatingTextData *> m_floatingTextList;
#else
    char opaque8A0[0x8A4 - 0x8A0];
#endif
    float m_floatingTextTimeOut;
    float m_floatingTextMoveUpSpeed;
    float m_floatingTextMoveVanishRate;
    bool field8B0;
    int m_8B4;
    bool field8B8;
    bool field8B9;
    char opaque8BA[0x8C3 - 0x8BA];
    bool m_drawRMBScrollAnchor;
    bool m_moveRMBScrollAnchor;
    unsigned char m_8C5;
    bool field8C6;
    char opaque8C7[0x8CC - 0x8C7];
#ifdef _STLP_INTERNAL_LIST_H
    _STL::list<WorldAnimationData *> m_worldAnimationList;
#else
    char opaque8CC[0x8D0 - 0x8CC];
#endif
    char opaque8D0[0x928 - 0x8D0];
#ifdef _STLP_INTERNAL_LIST_H
    _STL::list<Object *> m_idleWorkers[20];
#else
    char opaque928[0x978 - 0x928];
#endif
    GameWindow *m_idleWorkerWin;
    int m_97C;
    unsigned int m_soloNexusSelectedDrawableID;
    unsigned int m_984;
    unsigned int field988;
    bool field98C;
    char opaque98D[0x9B4 - 0x98D];
    unsigned char m_9B4;
    char opaque9B5[0x9C8 - 0x9B5];
    int m_9C8;
    InGameNotificationBoxMovieClip *field9CC;
    AsciiString m_9D0;
    float m_9D4;
    AsciiString m_9D8;
    float m_9DC;
    AsciiString m_9E0;
    float m_9E4;
    AsciiString m_9E8;
    float m_9EC;
};

extern InGameUI *TheInGameUI;

#endif
