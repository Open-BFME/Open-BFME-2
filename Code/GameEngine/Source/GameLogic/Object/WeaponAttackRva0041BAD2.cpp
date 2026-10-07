// cl: /MD /Oy-
// Native Ghidra 0041BAD2..0041BB26 RET16. Source/target null checks,
// WeaponSet at Object+330, attack results 3 or 2, then the measured
// 244-byte Weapon helper 002CCED3 with source and target. The original
// wrapper and the helper's precise purpose remain address-derived.
enum WeaponSlotType { Rva0041BAD2SlotZero };
enum AbleToAttackType { Rva0041BAD2AttackZero };
enum CommandSourceType { Rva0041BAD2CommandZero };
enum CanAttackResult { Rva0041BAD2Impossible, Rva0041BAD2Invalid,
                       Rva0041BAD2AfterMoving, Rva0041BAD2Possible };
class Object;
class Weapon
{
public:
    bool rva002CCED3(const Object *source, const Object *target);
};
class WeaponSet
{
public:
    Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;
};
class Object
{
public:
    CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attack,
                                                const Object *target,
                                                CommandSourceType command) const;
};

bool __stdcall Rva0041BAD2(const Object *source, const Object *target,
                           CommandSourceType command, WeaponSlotType slot)
{
    if (source && target)
    {
        const WeaponSet *weapons = reinterpret_cast<const WeaponSet *>(
            reinterpret_cast<const char *>(source) + 0x330);
        Weapon *weapon = weapons->getWeaponInWeaponSlot(slot);
        if (weapon)
        {
            CanAttackResult result = source->getAbleToAttackSpecificObject(
                Rva0041BAD2AttackZero, target, command);
            if (result == Rva0041BAD2Possible || result == Rva0041BAD2AfterMoving)
                return weapon->rva002CCED3(source, target);
        }
    }
    return false;
}
