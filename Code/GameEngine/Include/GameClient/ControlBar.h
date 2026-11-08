// ControlBar: canonical BFME2 interface. Code addresses are RVAs; table addresses are VAs.
// Target facts: constructor 0x0031E94C calls SubsystemInterface's 0x001B4E63 at 0x0031E961, then installs 0x00C0CC88 at +0 at 0x0031E96E. Destructor 0x0031DCF0 restores the same table at 0x0031DD05 and calls the parent destructor 0x001B4E74 at 0x0031DF75. The parent's 0x00BD77A0 table is installed during base construction/destruction, not the derived lifetime. The destructor and deleting wrapper retain the ledger's Rva0031DCF0 identity; the header declares the destructor without emitting another body.
// Target facts: allocation 0x0029E5B9 pushes 0x2B4, calls scalar new at 0x0029E5BE, then calls the constructor at 0x0029E5D0. A second allocation writes 0x2B4 at 0x0029F873 and calls the constructor at 0x0029F890. The parent occupies +0..+0xC: its constructor stores the vptr, clears byte +4 and dword +8. ControlBar has one primary vptr and no additional base construction.
// Target facts: 0x00C0CC88 has fourteen slots: 0=0x0031EB7A (deleting wrapper calling destructor 0x0031DCF0), 1=0x0031C83D (rowed init), 2=0x0031B53D (INI-loading override), 3/8/12=0x000B3FD0 (ret), 4=0x0031E7F0 (reload notice, one argument), 5=0x0047A699 (false), 6=0x000D43D0 (zero), 7/13=0x0047A69C (ret 4), 9=0x0031E09E (rowed reset), 10=0x0031E25E (rowed update), 11=0x005CB9FF (false, ret 4). At 0x00C0CCC0 a UTF-16 string begins; its first word pair 0x00490052 is not a fifteenth function pointer. The registered parent supplies slots 2-8 and 11-13; only its overridden slots 1/2/4/9/10 are redeclared here. The parent's integer slot-4 parameter preserves the existing ABI for retail's pointer argument.
// Target facts: constructor 0x0031EA46 clears byte +0x28, 0x0031E9C9 clears pointer +0x210, and 0x0031E983 clears byte +0x214. Other storage stays opaque; its extent follows the two allocations. Field names are neutral because these stores do not establish original member spellings.
// Target facts: W3DCommandBarBackgroundDraw reads the manager pointer +0x44 at 0x0009FA95, W3DCommandBarGridDraw reads the border-color dword +0x22C at 0x0009DE6C, and ControlBarArrowTransition::init reads the image pointer +0x26C at 0x0035D87A, each through TheControlBar (VA 0x00E01CFC). Player's 0x002ADC77 writes byte +0x28 = 1 through that global.
// Target facts: the constructor clears +0x10 at 0x0031EAC8, nine dwords +0x48..+0x6B with one rep stosd at 0x0031EA4C, +0x6C at 0x0031EA9D, +0x70 at 0x0031EAA0, +0x7C at 0x0031EAAB and +0x29C at 0x0031EB26. HideControlBar reads +0x10 at 0x00402A1C and calls AnimateWindowManager::reverseAnimateWindow (0x0053B417) on it; ShowControlBar tests +0x29C at 0x00402A99. processCommandTransitionUI 0x00539997 reads the context dword +0x70 and the drawable +0x6C whose object it tests at +0xFC; populateOCLTimer reads window +0x64 at 0x0053E360; updateContextOCLTimer compares +0x7C at 0x0053E326 and updateOCLTimerTextDisplay stores it at 0x0053E29D. The constructor also clears dword +0x80 at 0x0031EABF and 32 dwords +0xDC..+0x15B with one rep stosd at 0x0031EA55, and stores the clock color 0x64000000 at +0x208 at 0x0031EA1B. It clears 32 dwords +0x15C..+0x1DB (ecx 0x20 from 0x0031E9B8, rep stosd at 0x0031EA13), which updateContextMultiSelect walks from 0x0053E11F. populateMultiSelect loads +0x2A0 at 0x0053DEFA and calls ?rva0053EF2E@Rva0053ED1A@@QAEXXZ (0x0053EF2E) on it; init passes the same pointer at 0x0031CA2C. Zero Hour declares the same positions as AnimateWindowManager*, GameWindow* parents, Drawable*, the context, the unsigned OCL-timer seconds, an inventory count, the 32 GameWindow* command windows, the 32 const CommandButton* common commands and the clock Color; names stay neutral.
// Donor facts: Zero Hour ControlBar.h declares markUIDirty, setObserverLookAtPlayer, getObserverLookAtPlayer, getControlBarSchemeManager, getBorderColor and getArrowImage. Their operations use the fields established by retail. All other methods below are declarations for ledger rows or existing retail-call bindings; no lifetime or rowed method is defined inline.
// Ledger declarations (RVA, exact decorated identity):
// 0x000D43D0 ?calculateVeterancyOverlayForObject@ControlBar@@KAPBVImage@@PBVObject@@@Z
// 0x001DAF81 ?parseCommandButtonDefinition@ControlBar@@SAXPAVINI@@@Z
// 0x0031AA86 ?rva0031AA86@ControlBar@@QAEHXZ
// 0x0031AB77 ?rva0031AB77SetFlag@ControlBar@@QAEXXZ
// 0x0031ABCF ?processContextSensitiveButtonClick@ControlBar@@QAE?AW4CBCommandStatus@@PAVGameWindow@@W4GadgetGameMessage@@@Z
// 0x0031ABD4 ?processContextSensitiveButtonTransition@ControlBar@@QAE?AW4CBCommandStatus@@PAVGameWindow@@W4GadgetGameMessage@@@Z
// 0x0031ABD9 ?setCommandBarBorder@ControlBar@@QAEXPAVGameWindow@@W4CommandButtonMappedBorderType@@@Z
// 0x0031AC39 ?postProcessCommands@ControlBar@@QAEXXZ
// 0x0031AC4F ?setPortraitByImage@ControlBar@@QAEXPBVImage@@@Z
// 0x0031ACF5 ?updateRightHUDImage@ControlBar@@QAEXPBVImage@@@Z
// 0x0031AD14 ?rva0031AD14@ControlBar@@QAEXHHHHH@Z
// 0x0031AD48 ?rva0031AD48@ControlBar@@QAEX_N@Z
// 0x0031AD5A ?showPurchaseScience@ControlBar@@QAEXXZ
// 0x0031AD8F ?hidePurchaseScience@ControlBar@@QAEXXZ
// 0x0031AD94 ?rva0031AD94@ControlBar@@QAEXXZ
// 0x0031ADAE ?rva0031ADAE@ControlBar@@QAEXXZ
// 0x0031AE01 ?setHiddenControlBar@ControlBar@@IAEXXZ
// 0x0031AE13 ?rva0031AE13@ControlBar@@QAEXXZ
// 0x0031AE93 ?rva0031AE93@ControlBar@@QAEXPAH0@Z
// 0x0031AEAE ?rva0031AEAE@ControlBar@@QAEXPAH0@Z
// 0x0031AEC9 ?rva0031AEC9@ControlBar@@QAEXXZ
// 0x0031AFCC ?hideSpecialPowerShortcut@ControlBar@@QAEXXZ
// 0x0031B05B ?rva0031B05B@ControlBar@@QAEPAVCommandSet@@PAV2@@Z
// 0x0031B0CE ?setDefaultControlBarConfig@ControlBar@@IAEXXZ
// 0x0031B134 ?setLowControlBarConfig@ControlBar@@IAEXXZ
// 0x0031B1BC ?rva0031B1BC@ControlBar@@QAEXPBVImage@@0000000@Z
// 0x0031B210 ?rva0031B210@ControlBar@@QAEXXZ
// 0x0031B5A3 ?rva0031B5A3@ControlBar@@QAEXPBVPlayer@@@Z
// 0x0031B641 ?setControlCommand@ControlBar@@QAEXPAVGameWindow@@PBVCommandButton@@@Z
// 0x0031B892 ?showRallyPoint@ControlBar@@QAEXPBUCoord3D@@@Z
// 0x0031B99A ?switchControlBarStage@ControlBar@@QAEXW4ControlBarStages@@@Z
// 0x0031BA47 ?setControlCommand@ControlBar@@QAEXABVAsciiString@@PAVGameWindow@@PBVCommandButton@@@Z
// 0x0031BA80 ?setControlBarScheme@ControlBar@@QAEXABVAsciiString@@@Z
// 0x0031BAB1 ?rva0031BAB1@ControlBar@@QAEXXZ
// 0x0031BAC3 ?rva0031BAC3@ControlBar@@QAEXPAVPlayer@@@Z
// 0x0031BE3C ?findCommandButton@ControlBar@@QAEPBVCommandButton@@ABVAsciiString@@@Z
// 0x0031BF64 ?switchToContext@ControlBar@@QAEXHPAX@Z
// 0x0031C40E ?setControlBarSchemeByPlayer@ControlBar@@QAEXPAVPlayer@@@Z
// 0x0031C5C8 ?setControlBarSchemeByPlayerTemplate@ControlBar@@QAEXPBVPlayerTemplate@@@Z
// 0x0031C83D ?init@ControlBar@@UAEXXZ
// 0x0031D230 ?rva0031D230@ControlBar@@QAEXXZ
// 0x0031D61E ?rva0031D61E@ControlBar@@QAEXPBVAsciiString@@@Z
// 0x0031D64F ?rva0031D64F@ControlBar@@QAEXXZ
// 0x0031D85D ?populateSpecialPowerShortcut@ControlBar@@IAEXPAVPlayer@@@Z
// 0x0031DAF8 ?showSpecialPowerShortcut@ControlBar@@QAEXXZ
// 0x0031DFD1 ?GetPurchaseScienceStatus@ControlBar@@QAEXPAVPlayer@@HPAPBVCommandButton@@PA_N22@Z
// 0x0031E068 ?rva0031E068@ControlBar@@QAE_NPAVPlayer@@H@Z
// 0x0031E09E ?reset@ControlBar@@UAEXXZ
// 0x0031E25E ?update@ControlBar@@UAEXXZ
// 0x0031E879 ?forgetStaleCommandSet@ControlBar@@QAEXABVAsciiString@@@Z
// 0x0031E8D5 ?rva0031E8D5@ControlBar@@QAEPAVCommandSet@@ABVAsciiString@@H@Z
// 0x0031EC03 ?parseCommandSetDefinition@ControlBar@@SAXPAVINI@@@Z
// 0x00405D77 ?rva00405D77@ControlBar@@QAEXXZ
// 0x00405DBC ?rva004C1B60@ControlBar@@QAEXPAVGameWindow@@PAX@Z
// 0x00406D95 ?rva00406D95@ControlBar@@QAEPAVCommandSet@@ABVAsciiString@@@Z
// 0x0047A69C ?setPortraitByObject@ControlBar@@QAEXPAVObject@@@Z
// 0x0050DBE6 ?populateBeacon@ControlBar@@QAEXPAVObject@@@Z
// 0x0050DE39 ?initObserverControls@ControlBar@@QAEXXZ
// 0x0050E08E ?populateObserverList@ControlBar@@QAEXXZ
// 0x0050E3E5 ?populateObserverInfoWindow@ControlBar@@QAEXXZ
// 0x00539997 ?processCommandTransitionUI@ControlBar@@IAE?AW4CBCommandStatus@@PAVGameWindow@@W4GadgetGameMessage@@@Z
// 0x005399D0 ?rva005399D0Check@ControlBar@@QAEHPAVObject@@@Z
// 0x00539A65 ?processCommandUI@ControlBar@@QAE?AW4CBCommandStatus@@PBVCommandButton@@_N1@Z
// 0x0053B1CF ?rva0053B1CF@ControlBar@@QAE?AW4CBCommandStatus@@PAVGameWindow@@I@Z
// 0x0053B98C ?populateInvDataCallback@ControlBar@@KAXPAVObject@@PAX@Z
// 0x0053BA87 ?rva0053BA87@ControlBar@@QBEHPBVCommandButton@@PAVObject@@@Z
// 0x0053BB16 ?doTransportInventoryUI@ControlBar@@QAEXPAVObject@@PAVCommandSet@@@Z
// 0x0053BD66 ?getCommandAvailability@ControlBar@@QBE?AW4CommandAvailability@@PBVCommandButton@@PAVGameWindow@@PAVObject@@PAM_N@Z
// 0x0053CF65 ?updateContextCommand@ControlBar@@IAEXXZ
// 0x0053D355 ?populateCommand@ControlBar@@QAEXPAVObject@@_N@Z
// 0x0053DB2D ?addCommonCommands@ControlBar@@IAEXPAVDrawable@@_N@Z
// 0x0053DD53 ?populateMultiSelect@ControlBar@@IAEXXZ
// 0x0053DF0A ?updateContextMultiSelect@ControlBar@@IAEXXZ
// 0x0053E17E ?updateOCLTimerTextDisplay@ControlBar@@IAEXIM@Z
// 0x0053E2B6 ?updateContextOCLTimer@ControlBar@@IAEXXZ
// 0x0053E34A ?populateOCLTimer@ControlBar@@QAEXPAVObject@@@Z
// 0x0053E3E6 ?updateConstructionTextDisplay@ControlBar@@QAEXPAVObject@@@Z
// 0x0053E4B1 ?rva0053E4B1@ControlBar@@QAEXXZ
// 0x0053E4F1 ?populateUnderConstruction@ControlBar@@IAEXPAVObject@@@Z
// 0x0053E6E1 ?rva0053E6E1@ControlBar@@QAEXXZ
// 0x0053E6E6 ?populateButtonProc@ControlBar@@KAXPAVObject@@PAX@Z
// 0x0053E754 ?rva0053E754@ControlBar@@QAEPAVObject@@PAVGameWindow@@@Z
// 0x0053E783 ?populateStructureInventory@ControlBar@@IAEXPAVObject@@_N@Z
// 0x0053EAEC ?updateContextStructureInventory@ControlBar@@IAEXXZ
// 0x0053EB81 ?updateContextContestedStructureInventory@ControlBar@@QAEXXZ
// Existing retail-call bindings: findCommandSet(const AsciiString &) -> 0x0031D5F8 (call 0x00495444); findNonConstCommandButton(const AsciiString &) -> 0x0031BE07 (called by rowed findCommandButton 0x0031BE3C); bfmeShowDN(BfmeMsgDN *) -> 0x00405C04 (called by rowed 0x00405DBC). These preserve existing binding spellings, not additional recovered identities.
#ifndef BFME2_CONTROLBAR_H
#define BFME2_CONTROLBAR_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include ControlBar.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class AnimateWindowManager;
class CommandButton;
class CommandSet;
class ControlBarSchemeManager;
class Drawable;
class GameWindow;
class Image;
class INI;
class Object;
class Player;
class PlayerTemplate;
class Rva0053ED1A;
struct BfmeMsgDN;
struct Coord3D;
enum CBCommandStatus;
enum CommandAvailability;
enum CommandButtonMappedBorderType;
enum ControlBarStages;
enum GadgetGameMessage;

class ControlBar : public SubsystemInterface {
public:
    ControlBar();
    virtual ~ControlBar();
    virtual void init();
    virtual bool loadIniFilesFromLegend();
    virtual bool vslot04(int);
    virtual void reset();
    virtual void update();

    const CommandButton *findCommandButton(const AsciiString &name);
    const CommandSet *findCommandSet(const AsciiString &name);
    void hideSpecialPowerShortcut();
    void showSpecialPowerShortcut();
    void hidePurchaseScience();
    void showPurchaseScience();
    void postProcessCommands();
    void updateRightHUDImage(const Image *image);
    void updateConstructionTextDisplay(Object *object);
    void switchControlBarStage(ControlBarStages stage);
    void switchToContext(int context, void *object);
    void setControlBarScheme(const AsciiString &name);
    void setControlBarSchemeByPlayer(Player *player);
    void setControlBarSchemeByPlayerTemplate(const PlayerTemplate *playerTemplate);
    void setCommandBarBorder(GameWindow *window, CommandButtonMappedBorderType type);
    void setControlCommand(GameWindow *window, const CommandButton *command);
    void setControlCommand(const AsciiString &name, GameWindow *parent, const CommandButton *command);
    void setPortraitByImage(const Image *image);
    void setPortraitByObject(Object *object);
    void showRallyPoint(const Coord3D *position);
    void GetPurchaseScienceStatus(Player *, int, const CommandButton **, bool *, bool *, bool *);
    void forgetStaleCommandSet(const AsciiString &name);
    void initObserverControls();
    void populateCommand(Object *, bool);
    void populateBeacon(Object *);
    void populateOCLTimer(Object *);
    void populateObserverInfoWindow();
    void populateObserverList();
    void doTransportInventoryUI(Object *, CommandSet *);
    void updateContextContestedStructureInventory();
    CommandAvailability getCommandAvailability(const CommandButton *, GameWindow *, Object *, float *, bool) const;
    CBCommandStatus processCommandUI(const CommandButton *, bool, bool);
    CBCommandStatus processContextSensitiveButtonClick(GameWindow *, GadgetGameMessage);
    CBCommandStatus processContextSensitiveButtonTransition(GameWindow *, GadgetGameMessage);
    CBCommandStatus rva0053B1CF(GameWindow *, unsigned int);
    static void parseCommandButtonDefinition(INI *);
    static void parseCommandSetDefinition(INI *);

    int rva0031AA86();
    void rva0031AB77SetFlag();
    void rva0031AD14(int, int, int, int, int);
    void rva0031AD48(bool);
    void rva0031AD94();
    void rva0031ADAE();
    void rva0031AE13();
    void rva0031AE93(int *, int *);
    void rva0031AEAE(int *, int *);
    void rva0031AEC9();
    CommandSet *rva0031B05B(CommandSet *);
    void rva0031B1BC(const Image *, const Image *, const Image *, const Image *, const Image *, const Image *, const Image *, const Image *);
    void rva0031B210();
    void rva0031B5A3(const Player *);
    void rva0031BAB1();
    void rva0031BAC3(Player *);
    void rva0031D230();
    void rva0031D61E(const AsciiString *);
    void rva0031D64F();
    bool rva0031E068(Player *, int);
    CommandSet *rva0031E8D5(const AsciiString &, int);
    void rva00405D77();
    CommandSet *rva00406D95(const AsciiString &);
    void rva004C1B60(GameWindow *, void *);
    int rva005399D0Check(Object *);
    int rva0053BA87(const CommandButton *, Object *) const;
    void rva0053E4B1();
    void rva0053E6E1();
    Object *rva0053E754(GameWindow *);
    void bfmeShowDN(BfmeMsgDN *);

    void markUIDirty() { field28 = true; }
    void setObserverLookAtPlayer(Player *player) { field210 = player; }
    Player *getObserverLookAtPlayer() { return field210; }
    ControlBarSchemeManager *getControlBarSchemeManager() { return field44; }
    int getBorderColor() { return field22C; }
    const Image *getArrowImage() { return field26C; }

    unsigned char field0C[0x4];
    AnimateWindowManager *field10;
    unsigned char field14[0x14];
    bool field28;
    unsigned char field29[0x1B];
    ControlBarSchemeManager *field44;
    GameWindow *field48[9];
    Drawable *field6C;
    int field70;
    unsigned char field74[0x8];
    unsigned int field7C;
    int field80;
    unsigned char field84[0x58];
    GameWindow *fieldDC[32];
    const CommandButton *field15C[32];
    unsigned char field1DC[0x2C];
    int field208;
    unsigned char field20C[0x4];
    Player *field210;
    unsigned char field214[0x18];
    int field22C;
    unsigned char field230[0x3C];
    const Image *field26C;
    unsigned char field270[0x2C];
    int field29C;
    Rva0053ED1A *field2A0;
    unsigned char field2A4[0x10];

protected:
    CommandButton *findNonConstCommandButton(const AsciiString &name);
    void setHiddenControlBar();
    void setLowControlBarConfig();
    void setDefaultControlBarConfig();
    void addCommonCommands(Drawable *, bool);
    void populateMultiSelect();
    void populateSpecialPowerShortcut(Player *);
    void populateStructureInventory(Object *, bool);
    void populateUnderConstruction(Object *);
    void updateContextCommand();
    void updateContextMultiSelect();
    void updateContextOCLTimer();
    void updateContextStructureInventory();
    void updateOCLTimerTextDisplay(unsigned int, float);
    CBCommandStatus processCommandTransitionUI(GameWindow *, GadgetGameMessage);
    static void populateButtonProc(Object *, void *);
    static void populateInvDataCallback(Object *, void *);
    static const Image *calculateVeterancyOverlayForObject(const Object *);
};

extern ControlBar *TheControlBar;

#endif
