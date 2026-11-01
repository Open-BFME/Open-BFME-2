// Target facts (code addresses are RVAs, tables are VAs): INI parser 0x001DAF81 calls factory 0x0031AB1E, which allocates 0x2CC at 0x0031AB2B, calls constructor 0x0035B8AA at 0x0031AB46, assigns the name at +0x10 and links +0x18. The constructor initializes Overridable's +4/+8/+0xC at 0x0035B8BA..0x0035B8C7 and installs 0x00C16204 at 0x0035B8CA. Destructor 0x0035BB4B installs the same table at 0x0035BB5C and calls ~Overridable (0x001E3624) at 0x0035BCA9. That base restores its own 0x00BDDC48 table. CommandButton has exactly one virtual slot: 0x00C16204 contains deleting destructor 0x0035BCBB, which calls 0x0035BB4B at 0x0035BCBE; 0x00C16208 starts Shell's separately installed table. The lifetime rows retain their existing Rva0035BB4B names; these declarations emit no replacement bodies.
// Target fields: the 54-entry FieldParse table at VA 0x00C15468 supplies the named parser fields and offsets below. Constructor 0x0035B8AA establishes their widths, the 12-byte ranges at +0x28/+0x38/+0x58/+0x64/+0xA4/+0xB4/+0xC8/+0xD4/+0xE0/+0xEC/+0x188/+0x234, and the final +0x24C member. Factory 0x0031AB54 establishes name +0x10. Row 0x0035B069 reads command +0x14, upgrade +0x24 and special power +0x44; 0x0035B140 tests options +0x1C; 0x0035B19E/0x0035B1E9/0x0035B26F select images/text/descriptions through index +0xFC, with string override +0x7C; 0x0035B77D traverses image names +0xB4 and appends images +0xEC; 0x0035B6B8 indexes the pointer at +0x234. Zero Hour GameClient/ControlBar.h supplies the matching accessor names and getFlashCount/setFlashCount, whose BFME2 +0xF8 access is present in ScriptActions::doCameoFlash (0x003BB556). Storage without such naming evidence keeps offset names; ranges expose storage without defining another STL container.
// Ledger method declarations (RVA): parseCommand 0x0035AF62; isValidObjectTarget(Object,Object) 0x0035B03E; isReady 0x0035B069; getSpecialPowerPercentReady 0x0035B0F0; isValidObjectTarget(Drawable,Drawable) 0x0035B112; isContextCommand 0x0035B140; rva0035B19E 0x0035B19E; rva0035B1E9 0x0035B1E9; rva0035B26F 0x0035B26F; rva0035B570 0x0035B570; rva0035B5C2 0x0035B5C2; getStance 0x0035B6B8; rva0035B6FA 0x0035B6FA; cacheButtonImage 0x0035B77D. Every rowed method stays out of line.
#ifndef BFME2_COMMANDBUTTON_H
#define BFME2_COMMANDBUTTON_H

#include "../Common/Overridable.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class INI;
class Object;
class Drawable;
class Image;
class ThingTemplate;
class UpgradeTemplate;
class SpecialPowerTemplate;
enum ObjectID;
enum GUICommandType;
enum RadiusCursorType;
enum WeaponSlotType;
enum CommandButtonMappedBorderType;
enum ScienceType;
namespace _STL {
template <class T> class allocator;
template <class T, class Allocator> class vector;
}

class CommandButton : public Overridable
{
public:
    CommandButton();
    virtual ~CommandButton();

    static void parseCommand(INI *, void *, void *, const void *);
    bool isValidObjectTarget(const Object *, const Object *) const;
    bool isValidObjectTarget(const Drawable *, const Drawable *) const;
    bool isReady(const Object *) const;
    float getSpecialPowerPercentReady(const Object *) const;
    bool isContextCommand() const;
    const Image *rva0035B19E() const;
    const AsciiString &rva0035B1E9() const;
    const AsciiString &rva0035B26F() const;
    const ThingTemplate *rva0035B570() const;
    void rva0035B5C2(Object *, bool);
    int getStance(int);
    void rva0035B6FA(ObjectID, bool);
    void cacheButtonImage();

    const AsciiString &getName() const { return m_name; }
    GUICommandType getCommandType() const { return (GUICommandType)m_command; }
    unsigned int getOptions() const { return m_options; }
    const UpgradeTemplate *getUpgradeTemplate() const { return m_upgradeTemplate; }
    const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
    RadiusCursorType getRadiusCursorType() const { return (RadiusCursorType)m_radiusCursor; }
    WeaponSlotType getWeaponSlot() const { return (WeaponSlotType)m_weaponSlot; }
    int getMaxShotsToFire() const { return m_maxShotsToFire; }
    CommandButtonMappedBorderType getCommandButtonMappedBorderType() const { return (CommandButtonMappedBorderType)m_commandButtonBorder; }
    const AsciiString &getCursorName() const { return m_cursorName; }
    const AsciiString &getInvalidCursorName() const { return m_invalidCursorName; }
    const AsciiString &getPurchasedLabel() const { return m_purchasedLabel; }
    const AsciiString &getConflictingLabel() const { return m_conflictingLabel; }
    const CommandButton *getNext() const { return m_next; }
    CommandButton *friend_getNext() { return m_next; }
    void friend_addToList(CommandButton **list) { m_next = *list; *list = this; }
    int getFlashCount() const { return m_flashCount; }
    void setFlashCount(int value) const { m_flashCount = value; }
    const _STL::vector<ScienceType, _STL::allocator<ScienceType> > &getScienceVec() const
    {
        return *reinterpret_cast<const _STL::vector<ScienceType, _STL::allocator<ScienceType> > *>(&m_sciencesBegin);
    }

    AsciiString m_name;                                      // +0x10
    int m_command;                                           // +0x14
    CommandButton *m_next;                                    // +0x18
    unsigned int m_options;                                   // +0x1C
    const ThingTemplate *field20;                             // +0x20
    const UpgradeTemplate *m_upgradeTemplate;                 // +0x24
    const UpgradeTemplate **m_neededBegin;                    // +0x28
    const UpgradeTemplate **m_neededEnd;                      // +0x2C
    const UpgradeTemplate **m_neededCapacity;                 // +0x30
    bool m_neededUpgradeAny;                                  // +0x34
    unsigned char pad35[3];
    AsciiString *m_buildUpgradesBegin;                        // +0x38
    AsciiString *m_buildUpgradesEnd;                          // +0x3C
    AsciiString *m_buildUpgradesCapacity;                     // +0x40
    const SpecialPowerTemplate *m_specialPower;               // +0x44
    AsciiString m_toggleButtonName;                          // +0x48
    int m_radiusCursor;                                      // +0x4C
    AsciiString m_cursorName;                                // +0x50
    AsciiString m_invalidCursorName;                         // +0x54
    AsciiString *m_textLabelBegin;                           // +0x58
    AsciiString *m_textLabelEnd;                             // +0x5C
    AsciiString *m_textLabelCapacity;                        // +0x60
    AsciiString *m_descriptionBegin;                         // +0x64
    AsciiString *m_descriptionEnd;                           // +0x68
    AsciiString *m_descriptionCapacity;                      // +0x6C
    AsciiString m_purchasedLabel;                            // +0x70
    AsciiString m_conflictingLabel;                          // +0x74
    AsciiString m_lacksPrerequisiteLabel;                    // +0x78
    AsciiString field7C;                                     // +0x7C
    int m_weaponSlot;                                        // +0x80
    int m_weaponSlotToggle1;                                 // +0x84
    int m_weaponSlotToggle2;                                 // +0x88
    int m_weaponSlotToggle3;                                 // +0x8C
    unsigned char m_flagsUsedForToggle[16];                  // +0x90
    int m_maxShotsToFire;                                    // +0xA0
    ScienceType *m_sciencesBegin;                            // +0xA4
    ScienceType *m_sciencesEnd;                              // +0xA8
    ScienceType *m_sciencesCapacity;                         // +0xAC
    int m_commandButtonBorder;                               // +0xB0
    AsciiString *m_imageNamesBegin;                          // +0xB4
    AsciiString *m_imageNamesEnd;                            // +0xB8
    AsciiString *m_imageNamesCapacity;                       // +0xBC
    int fieldC0;                                             // +0xC0
    unsigned int fieldC4;                                    // +0xC4
    unsigned char fieldC8[0x24];                             // +0xC8
    const Image **m_imagesBegin;                             // +0xEC
    const Image **m_imagesEnd;                               // +0xF0
    const Image **m_imagesCapacity;                          // +0xF4
    mutable int m_flashCount;                                // +0xF8
    int fieldFC;                                             // +0xFC
    bool m_doubleClick;                                      // +0x100
    bool m_radial;                                           // +0x101
    bool m_inPalantir;                                       // +0x102
    bool field103;                                           // +0x103
    bool m_showProductionCount;                              // +0x104
    bool m_isClickable;                                      // +0x105
    bool m_showButton;                                       // +0x106
    bool m_requiresValidContainer;                           // +0x107
    int m_requireLevel;                                      // +0x108
    bool m_autoAbility;                                      // +0x10C
    unsigned char pad10D[3];
    unsigned char m_affectsKindOf[28];                       // +0x110
    bool m_triggerWhenReady;                                 // +0x12C
    unsigned char pad12D[3];
    float m_presetRange;                                     // +0x130
    float m_autoDelay;                                       // +0x134
    bool m_needDamagedTarget;                                // +0x138
    unsigned char pad139[3];
    unsigned char m_autoAbilityDisallowedOnModelCondition[76]; // +0x13C
    AsciiString *m_commandTriggerBegin;                      // +0x188
    AsciiString *m_commandTriggerEnd;                        // +0x18C
    AsciiString *m_commandTriggerCapacity;                   // +0x190
    unsigned char m_enableOnModelCondition[76];              // +0x194
    unsigned char m_disableOnModelCondition[76];             // +0x1E0
    int m_commandRangeStart;                                 // +0x22C
    int m_commandRangeCount;                                 // +0x230
    int *m_stancesBegin;                                     // +0x234
    int *m_stancesEnd;                                       // +0x238
    int *m_stancesCapacity;                                  // +0x23C
    AsciiString m_createAHeroUIPrerequisiteButtonName;        // +0x240
    int m_createAHeroUIMinimumLevel;                          // +0x244
    AsciiString m_createAHeroUIIconImageName;                 // +0x248
    unsigned char m_createAHeroUIAllowableUpgrades[128];      // +0x24C
};

typedef char CommandButtonSizeCheck[sizeof(CommandButton) == 0x2CC ? 1 : -1];

#endif
