// cl: /O1 /G7 /arch:SSE
// Object::getSpecialPowerModule, retail RVA 0x0028BB9E, 67 bytes.
// Reference: Open-BFME-1 968ca36c32, inputs/reference/CnC_Generals_Zero_Hour/
// GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Object.cpp. That donor
// checks a non-null template, queries each behavior for its special-power
// interface, and returns the first interface whose isModuleForPower accepts it.
// Target evidence: the Object callers pass the same complete this and template;
// WorldBuilder's ActionManager::canDoSpecialPower follows this same call chain.
// Native accesses place the behavior list at +0x244, its interface at +0x0C,
// the getSpecialPower query at slot 0x20, and isModuleForPower at slot 0.
// Preserve the target offsets; these views do not claim the full class layouts.

class SpecialPowerTemplate;

class SpecialPowerModuleInterface
{
public:
    virtual bool isModuleForPower(const SpecialPowerTemplate *power) const;
};

class Bfme2BehaviorPowerQuery
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual SpecialPowerModuleInterface *getSpecialPower();
};

struct Bfme2BehaviorPowerView
{
    unsigned char m_pad[0x0C];
    Bfme2BehaviorPowerQuery m_interface;
};

class Object
{
public:
    SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
private:
    unsigned char m_pad[0x244];
    Bfme2BehaviorPowerView **m_behaviors;
};

SpecialPowerModuleInterface *Object::getSpecialPowerModule(const SpecialPowerTemplate *power) const
{
    if (power == 0)
        return 0;
    Bfme2BehaviorPowerView **cursor = m_behaviors;
    Bfme2BehaviorPowerView *candidate = *cursor;
    while (candidate != 0) {
        SpecialPowerModuleInterface *found = candidate->m_interface.getSpecialPower();
        if (found != 0) {
            if (found->isModuleForPower(power))
                return found;
        }
        candidate = *++cursor;
    }
    return 0;
}
