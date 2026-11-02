// UpgradeTemplate and UpgradeCenter: canonical BFME2 declarations.
// Target facts (code addresses are RVAs; table addresses are VAs):
// UpgradeCenter constructor 0x0026F419 calls SubsystemInterface's 0x001B4E63 at 0x0026F41D and installs 0x00BFABB8 at 0x0026F435. Destructor 0x0026F445 restores the same table at 0x0026F457 and calls the parent's 0x001B4E74 at 0x0026F4E1. The parent's 0x00BD77A0 is the base construction/destruction table, not a competing derived table.
// Table 0x00BFABB8 has fourteen slots: 0=0x0026F597 (deleting destructor calling 0x0026F445), 1=0x0026FAFE (init), 2=0x001B5384 (loadIniFilesFromLegend), 3/8/10/12=0x000B3FD0 (ret), 4=0x0026F16D (attemptReload), 5=0x0026EF1E (attemptRefresh), 6=0x000D43D0 (zero), 7/13=0x0047A69C (ret 4), 9=0x0026FBBC (reset), 11=0x005CB9FF (false, ret 4). Slots 4 and 5 are inherited subsystem slots with ledger-proven override names.
// The parent occupies +0..+0xC. Constructor stores at 0x0026F424/27/2A clear the head +0xC, next mask index +0x10 and flag +0x14; 0x0026F432/3B constructs a twelve-byte vector at +0x18. Destructor 0x0026F487..0x0026F4D5 deletes the vector's template pointers and frees its storage. The allocation observed for this constructor is 0x24 bytes.
// UpgradeCenter lookup/link/unlink rows 0x0026EEA0/0x0026EEB8/0x0026EED0/0x0026EEF2 prove head +0xC and template key +0xC, mask index +0x38, next +0x64 and prev +0x68. newUpgrade 0x0026F952 allocates 0x9C bytes, calls the template constructor 0x0026F5B3 and assignment 0x0026F767, then sets name +8 and key +0xC. Those lifetime rows retain the ledger's Rva0026F684 spelling.
// UpgradeTemplate constructor 0x0026F5B3 and destructor 0x0026F684 store the same table 0x00BFABF0 at 0x0026F5C5/0x0026F695. Its sole slot is 0x0026F8BA, a deleting destructor calling 0x0026F684. There are no other retail virtual functions. Zero Hour supplies the MemoryPoolObject base; retail has one vptr and starts data at +4, with no additional base storage.
// Constructor 0x0026F5CB..0x0026F670 and assignment 0x0026F767..0x0026F8BA establish scalar widths and member boundaries through +0x98. Destructor 0x0026F6B4/CF/DB/E7 and 0x0026F713/1F/2B/55 releases strings at +0x8C/+0x7C/+0x74/+0x6C/+0x3C/+0x2C/+0x28/+8. Two twelve-byte vector members start at +0x10/+0x1C; 0x0026F8D6 resolves the former's strings into the latter's template pointers. Their storage remains opaque here.
// friend_makeVeterancyUpgrade 0x0026F1A5 writes type +4, name +8, key +0xC, display label +0x28, build time +0x30 and cost +0x34. calcCostToBuild 0x0026EF50 reads +0x79 and the build-template name +0x7C. cacheButtonImage 0x0026F216 resolves image names +0x6C/+0x8C to pointers +0x70/+0x90. Unknown member names remain fieldNN.
// Out-of-line center rows: findUpgrade 0x0026F26D, findVeterancyUpgrade 0x0026F3D0, getUpgradeNames 0x0026FBEF, parseUpgradeDefinition 0x0026FA05, rva0026F93C 0x0026F93C, rva0026F11A 0x0026F11A and rva001DB0A8 0x001DB0A8. Template rows: friend_makeVeterancyUpgrade 0x0026F1A5, cacheButtonImage 0x0026F216, friend_resolveSubUpgradeNames 0x0026F8D6, rva0026EE30 0x0026EE30 and calcCostToBuild 0x0026EF50. Lifetime and assignment calls remain out of line.
// Donor facts: Zero Hour Common/Upgrade.h supplies the class hierarchy, shared field names and inline name, type and list accessors. BFME2's extra fields and offsets come from the retail sites above.
#ifndef BFME2_UPGRADE_H
#define BFME2_UPGRADE_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#define vslot04 attemptReload
#define vslot05 attemptRefresh
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#undef vslot04
#undef vslot05
#include "MemoryPoolObject.h"

class Player;
class Object;
class Image;
class INI;
enum NameKeyType;
enum VeterancyLevel;
enum UpgradeType;
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector;
}

class UpgradeTemplate : public MemoryPoolObject {
public:
    UpgradeTemplate();
    virtual ~UpgradeTemplate();
    UpgradeTemplate &operator=(const UpgradeTemplate &that);

    unsigned int calcCostToBuild(Player *player, unsigned int requester) const;
    int rva0026EE30(void *player, void *requester);
    void friend_makeVeterancyUpgrade(VeterancyLevel level);
    void cacheButtonImage();
    void friend_resolveSubUpgradeNames();

    void setUpgradeName(const AsciiString &name) { m_name = name; }
    const AsciiString &getUpgradeName() const { return m_name; }
    void setUpgradeNameKey(NameKeyType key) { m_nameKey = key; }
    NameKeyType getUpgradeNameKey() const { return m_nameKey; }
    const AsciiString &getDisplayNameLabel() const { return m_displayNameLabel; }
    UpgradeType getUpgradeType() const { return static_cast<UpgradeType>(m_type); }
    const Image *getButtonImage() const { return m_buttonImage; }
    void friend_setNext(UpgradeTemplate *next) { m_next = next; }
    void friend_setPrev(UpgradeTemplate *prev) { m_prev = prev; }
    UpgradeTemplate *friend_getNext() { return m_next; }
    UpgradeTemplate *friend_getPrev() { return m_prev; }
    const UpgradeTemplate *friend_getNext() const { return m_next; }
    const UpgradeTemplate *friend_getPrev() const { return m_prev; }

    int m_type;
    AsciiString m_name;
    NameKeyType m_nameKey;
    unsigned int field10[3];
    unsigned int field1C[3];
    AsciiString m_displayNameLabel;
    AsciiString field2C;
    float m_buildTime;
    int m_cost;
    int field38;
    AsciiString field3C;
    void *field40;
    int field44;
    void *field48;
    int field4C;
    int field50;
    int field54;
    int field58;
    int field5C;
    int field60;
    UpgradeTemplate *m_next;
    UpgradeTemplate *m_prev;
    AsciiString m_buttonImageName;
    const Image *m_buttonImage;
    AsciiString field74;
    bool field78;
    bool field79;
    AsciiString field7C;
    unsigned int field80[3];
    AsciiString field8C;
    const Image *field90;
    bool field94;
    int field98;
};

class UpgradeCenter : public SubsystemInterface {
public:
    UpgradeCenter();
    virtual ~UpgradeCenter();
    virtual void init();
    virtual bool attemptReload(int reason);
    virtual bool attemptRefresh();
    virtual void reset();
    virtual void update() {}

    const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
    const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
    const UpgradeTemplate *findVeterancyUpgrade(VeterancyLevel level) const;
    UpgradeTemplate *newUpgrade(const AsciiString &name, bool assignMaskBit);
    void linkUpgrade(UpgradeTemplate *upgrade);
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > getUpgradeNames() const;
    static void parseUpgradeDefinition(INI *ini);
    const UpgradeTemplate *rva0026EEA0(int index) const;
    const UpgradeTemplate *rva001DB0A8() const;
    bool rva0026F11A(Player *player, const UpgradeTemplate *upgrade, Object *object, bool displayReason);
    void rva0026F93C();

    UpgradeTemplate *m_upgradeList;
    int m_nextTemplateMaskBit;
    bool m_buttonImagesCached;
    unsigned int field18[3];

protected:
    void unlinkUpgrade(UpgradeTemplate *upgrade);
};

extern UpgradeCenter *TheUpgradeCenter;

#endif
