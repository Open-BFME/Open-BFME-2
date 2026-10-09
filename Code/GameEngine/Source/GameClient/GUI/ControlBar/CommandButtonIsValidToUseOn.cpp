// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Reference: ZH ControlBar.cpp CommandButton::isValidToUseOn, BFME1 874e38488.
// Native35B2C3..35B3E7 verifies RET16, offsets14/1C/24/44/80, production
// entry tag2 at4 plus upgrade pointerC, and all ActionManager call destinations.
// BFME2 passes the supplied location directly and adds weapon/no-target and
// command-type23 readiness branches. Old neutral pins remain usable by their
// callers; this row uses the canonical struct Coord3D declaration, correcting
// the old class-tag spelling without changing ABI. Semantic identity supported
// independently by reference/callgraph.
class UpgradeTemplate;
class SpecialPowerTemplate;
struct Coord3D;
enum CommandSourceType { COMMANDSOURCE_AI=0, COMMANDSOURCE_PLAYER=1, COMMANDSOURCE_SCRIPT=2 };
enum WeaponSlotType { PRIMARY_WEAPON=0, SECONDARY_WEAPON=1, TERTIARY_WEAPON=2 };
struct ProductionEntry {
    int pad00;
    int type;
    int pad08;
    const UpgradeTemplate *upgrade;
};
class ProductionUpdateInterface {
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
    virtual const ProductionEntry *firstProduction();
    virtual const ProductionEntry *nextProduction(const ProductionEntry *entry);
};
class Object {
public:
    void *rva0028BC58(int which);
    bool rva002940B9(const UpgradeTemplate *upgrade);
    bool rva00290D2B(const UpgradeTemplate *upgrade) const;
};
class ActionManager {
public:
    bool canDoSpecialPowerAtObject(const Object *, const Object *, CommandSourceType,
        const SpecialPowerTemplate *, unsigned, bool);
    bool rva0041BAD2(const Object *, const Object *, CommandSourceType, WeaponSlotType);
    bool canDoSpecialPowerAtLocation(const Object *, const Coord3D *, CommandSourceType,
        const SpecialPowerTemplate *, const Object *, unsigned, bool);
    bool canDoSpecialPower(const Object *, const SpecialPowerTemplate *, CommandSourceType, unsigned, bool);
};
extern ActionManager *TheActionManager;
class CommandButton {
public:
    bool isReady(const Object *source) const;
};
class Rva0035B2C3 {
public:
    bool rva0035B2C3(void *source, int target, const Coord3D *location, int commandSource);
    char pad00[0x14];
    int command;
    int pad18;
    unsigned options;
    int pad20;
    const UpgradeTemplate *upgrade;
    char pad28[0x44-0x28];
    const SpecialPowerTemplate *power;
    char pad48[0x80-0x48];
    WeaponSlotType weapon;
};
bool Rva0035B2C3::rva0035B2C3(void *source, int target, const Coord3D *location, int commandSource)
{
    Object *sourceObj = (Object *)source;
    const Object *targetObj = (const Object *)target;
    CommandSourceType commandSourceType = (CommandSourceType)commandSource;
    if (upgrade && command != 0x17) {
        ProductionUpdateInterface *pui = (ProductionUpdateInterface *)sourceObj->rva0028BC58(0);
        if (pui) {
            const ProductionEntry *pe = pui->firstProduction();
            while (pe) {
                if (pe->type == 2 && pe->upgrade) return false;
                pe = pui->nextProduction(pe);
            }
            return sourceObj->rva002940B9(upgrade) && !sourceObj->rva00290D2B(upgrade);
        }
        return false;
    }
    if ((options & 7) && !targetObj) return false;
    if ((options & 0x20) && !location) return false;
    if (options & 7) {
        if (power)
            return TheActionManager->canDoSpecialPowerAtObject(sourceObj, targetObj, commandSourceType, power, options, false);
        return TheActionManager->rva0041BAD2(sourceObj, targetObj, commandSourceType, weapon);
    }
    if (options & 0x20)
        {
        const SpecialPowerTemplate *sp = power;
        return TheActionManager->canDoSpecialPowerAtLocation(sourceObj, location, commandSourceType, sp, 0, options, false);
    }
    if (command == 0x17)
        return ((const CommandButton *)this)->isReady(sourceObj);
    const SpecialPowerTemplate *sp = power;
    return TheActionManager->canDoSpecialPower(sourceObj, sp, commandSourceType, options, false);
}
