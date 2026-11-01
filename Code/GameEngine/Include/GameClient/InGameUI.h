/* Target facts (code addresses are RVAs; table addresses are VAs):
Constructor 0x002A61A9 calls SubsystemInterface's constructor 0x001B4E63 at 0x002A61BE. The parent stores 0x00BD77A0, clears byte +4 and the AsciiString at +8. InGameUI stores Snapshot's 0x00BBB554 at +0xC (0x002A61C8) and a five-purecall interface table 0x00C078DC at +0x10 (0x002A61CF), then installs its own tables 0x00BFD410, 0x00BFD400 and 0x00BC7A64 at 0x002A61E1/0x002A61E7/0x002A61EE.
Destructor 0x002A5B30 restores those same three derived tables at 0x002A5B42/0x002A5B48/0x002A5B4F. Its final stores at 0x002A5EBB/0x002A5EC4 restore the secondary bases before the call to SubsystemInterface's destructor at 0x002A5ECB. The different final constructor/destructor stores belong to different lifetime phases, not competing InGameUI layouts. The deleting destructor 0x002A6A11 calls 0x002A5B30. Both lifetime methods are declared out of line.
The primary table 0x00BFD410 contains 120 slots. Slots 0/1/9/10 are the deleting destructor/init/reset/update; slots 2-8/11/13 match the fourteen-slot parent table. Slot 12 is purecall, overriding the parent's empty slot. Slots 118/119 are purecall; the derived table 0x00BC7A88 supplies the pointer-returning factory 0x0008EFD8 and the void initializer 0x0008F32C there. Named rowed slots follow the ledger's names at their table targets; other named slots have donor or call-site evidence below. Unnamed slots retain neutral names. Message overloads occupy 18/19 and subtitle overloads 22/23 in reverse declaration order under VC7.1.
The +0xC table has four slots: 0=0x002A5EDE (subtract 0xC, jump to the deleting destructor), 1=loadPostProcess 0x002A2184, 2=0x0008EFD2 (return name literal VA 0x00BC7C7C), 3=xfer 0x002A6AC2. The +0x10 table has five slots, 0x0029B558/0x0029B563/0x0029B56E/0x0029B5CD/0x0029B5D8, with no destructor slot. Their +0x9BC accesses address the complete object's +0x9CC notification owner.
The constructor writes its last float at +0x9EC at 0x002A645B. Its only direct constructor caller, 0x0008EF3F, calls it at 0x0008EF42 and initializes the derived arrays starting at +0x9F0 (0x0008EF5D..0x0008EF6F); the base extent is 0x9F0 with four-byte alignment.
The constructor builds lists at +0x18/+0x20/+0x24 (0x002A61F5/0x002A620A/0x002A621A), initializes the movie string at +0x1C (0x002A61FD), builds 25 twenty-byte hints at +0x40 (0x002A6229..0x002A6235), and initializes selection/input flags and counters in 0x002A6463..0x002A64FD. Retail input forwards 0x0029AB22/0x0029AB35 pass +0x15/+0x16 to primary slot 82. Other storage remains opaque unless a retail access below identifies it.
Exposed scalar storage is proved by constructor stores: byte +0x14 at 0x002A67C6, +0x15/+0x16 at 0x002A6463/0x002A6467, +0x28 at 0x002A646B, +0x3C at 0x002A6936, +0x811 at 0x002A6738; dwords +0x238 at 0x002A662E, +0x53C/+0x540 at 0x002A66A6/0x002A66AC, +0x568/+0x56C/+0x570 at 0x002A6474/0x002A644E/0x002A647A, and the allocated notification pointer +0x9CC at 0x002A6415. Rva00524FA7 reads dword +0x988 at 0x00524FAD and converts it as unsigned through the sign test and x87 correction at 0x00524FC1/0x00524FC3.
Nonvirtual declarations retain rowed out-of-line bodies: resetCamera 0x0029B4F9, areSelectedObjectsControllable 0x0029C752, expireHint/expireAllHints 0x0029ACA0/0x0029ACC7, evaluateSoloNexus 0x0029B967, addMessageText 0x0029BA58, createControlBar/createReplayControl 0x0029C23E/0x0029C269, updateMilitarySubtitle 0x0029C404, updateFloatingText/drawFloatingText 0x0029D0E5/0x0029D200, updateAndDrawWorldAnimations 0x0029D44E, handleRadiusCursor 0x0029A661, handleBuildPlacements 0x002A21E1, updateLocalPhantomStructureDisplay 0x002A1158, updateOrderDisplayMode 0x0029A72C, addNamedTimer 0x002A5A50, addWorldAnimation 0x002A0E16, rva002A4A68 0x002A4A68, rva0029D9F9 0x0029D9F9, clearFormationPreviewDrawables 0x002A3DD3, rva002A3E24 0x002A3E24. No inline lifetime, copy or assignment body is supplied.
The monotonic setter 0x0029B04D and clearer 0x0029B060 access an unsigned dword at +0x7EC. The list members' four-byte storage at +0x18/+0x20/+0x24 is opaque here; the selection return types retain the ledger's STLport list identity without requiring a container implementation in callers. canSelectedObjectsDoAction 0x0029C823, canSelectedObjectsEffectivelyUseWeapon 0x0029CDD2, canSelectedObjectsNonAttackInteractWithObject 0x0029F72F, canSelectedObjectsDoSpecialPower 0x002A395C, canSelectedObjectsOverrideSpecialPowerDestination 0x0029CBA6 and getCanSelectedObjectsAttack 0x0029C779 prove the nested ActionType/SelectionRules method signatures. Zero Hour names SelectionRules values ANY=0 and ALL=1; no ActionType values are asserted.
Additional rowed declarations: rva0029CC19 0x0029CC19, rva0029FCD9 0x0029FCD9, rva0029B3C1 0x0029B3C1, rva002A123F/1261/1283 at their named RVAs, notifyHeroEarnedAward 0x0029DCA9, notifyOfHeroSpawnEvent 0x0029F954, findSWInfo 0x002A435D, parseNamedRadiusDecalTemplate 0x002A4523, rva002A3E5A 0x002A3E5A, rva002A470F 0x002A470F, rva002A4A0C 0x002A4A0C and rva002A4BFC 0x002A4BFC. Their declarations use the ledger's existing types and names.
HintSpyTranslator::translateGameMessage 0x00428C43 dispatches slots 26-33 with one GameMessage pointer; its retail call sites and Zero Hour name slots 27-30 endAreaSelectHint/createMoveHint/createAttackHint/createForceAttackHint. Getter 0x0029A7EA (slot 93) reads the drawable ID dword at +0x804. The constructor clears the bytes at +0x8B0/+0x8B8/+0x8B9 at 0x002A6946/0x002A694C/0x002A6952; issueMoveToLocationCommand 0x004292F6 reads those same three bytes. Slot 83 (0x0029AC98) tail-dispatches deselectDrawable, preserving its one Drawable pointer argument; Zero Hour names this disregardDrawable. The row at 0x0029E159 proves the nested FormationPreviewDecal constructor's scope. The pinned method rva000CF155 at 0x000CF155 returns the null-preserving +0x10 interface conversion, called by HideControlBar 0x00402A72 and ShowControlBar 0x00402AE4.
Donor facts: Zero Hour's InGameUI declaration supplies the names of message toggles, selection getters and placement getters. Their BFME2 table targets access the corresponding retail fields: +0x811, +0x238, +0x53C/+0x540, +0x568/+0x56C/+0x570, +0x20/+0x24 and +0x3C. The interface at +0x10 has only a structural name; its original class name is not established.
*/
#ifndef BFME2_INGAMEUI_H
#define BFME2_INGAMEUI_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include InGameUI.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#error Include InGameUI.h before the legacy Snapshot slot spelling.
#endif
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

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
class WindowLayout;
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
    virtual void toggleMessages();
    virtual bool isMessagesOn();
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
    virtual bool slot51();
    virtual int slot52();
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
    virtual bool slot63();
    virtual void slot64(bool);
    virtual void slot65();
    virtual void selectDrawable(Drawable *);
    virtual void deselectDrawable(Drawable *);
    virtual void deselectAllDrawables();
    virtual void rva0029BE05(bool, Player *);
    virtual int getSelectCount();
    virtual int getMaxSelectCount();
    virtual unsigned int getFrameSelectionChanged();
    virtual const _STL::list<Drawable *, _STL::allocator<Drawable *> > *getAllSelectedDrawables() const;
    virtual const _STL::list<Drawable *, _STL::allocator<Drawable *> > *getAllSelectedLocalDrawables();
    virtual Drawable *getFirstSelectedDrawable();
    virtual int slot76();
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
    virtual bool slot95() const;
    virtual const void *slot96() const;
    virtual int selectUnitsMatchingCurrentSelection();
    virtual int selectMatchingAcrossScreen();
    virtual int selectMatchingAcrossMap();
    virtual int selectMatchingAcrossRegion(IRegion2D *);
    virtual void mergeRva0029AF3F(const int *, const int *, int *);
    virtual bool getDisplayedMaxWarning();
    virtual void setDisplayedMaxWarning(bool);
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

    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
    virtual void slot10_00();
    virtual void slot10_01();
    virtual void rva0029B56E(const UnicodeString &, const Rva002217EA &, int);
    virtual bool slot10_03(class AnimateWindow *);
    virtual int slot10_04();

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
    void *field018;
    AsciiString field01C;
    void *field020;
    void *field024;
    bool field028;
    char opaque029[0x3C - 0x29];
    bool field03C;
    char opaque040[0x238 - 0x40];
    const CommandButton *field238;
    char opaque23C[0x53C - 0x23C];
    const ThingTemplate *field53C;
    ObjectID field540;
    char opaque544[0x568 - 0x544];
    int field568;
    int field56C;
    unsigned int field570;
    char opaque574[0x7EC - 0x574];
    unsigned int field7EC;
    char opaque7F0[0x811 - 0x7F0];
    bool field811;
    char opaque812[0x8B0 - 0x812];
    bool field8B0;
    char opaque8B1[0x8B8 - 0x8B1];
    bool field8B8;
    bool field8B9;
    char opaque8BA[0x988 - 0x8BA];
    unsigned int field988;
    char opaque98C[0x9CC - 0x98C];
    void *field9CC;
    char opaque9D0[0x9F0 - 0x9D0];
};

extern InGameUI *TheInGameUI;

#endif
