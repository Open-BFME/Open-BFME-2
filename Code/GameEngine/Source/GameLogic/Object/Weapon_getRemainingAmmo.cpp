// cl: /DNDEBUG /MD
// Ported from Open-BFME-1's Weapon_getRemainingAmmo.cpp (landed there against
// retail 0x001E5660). BFME2 keeps the shape with different offsets: the ammo
// descriptor sits at WeaponTemplate+0x120 (BFME1 +0x4E8) and the owner's ammo
// provider at Object+0x250 (BFME1 +0x1FC). Retail calls the provider's
// getRemainingAmmo through vtable slot 0x114, hence the placeholder virtuals.
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ObjectID
{
    INVALID_OBJECT_ID = 0
};

enum WeaponStatus
{
    READY_TO_FIRE,
    OUT_OF_AMMO,
    BETWEEN_FIRING_SHOTS,
    RELOADING_CLIP,
    PRE_ATTACK,
    // Sixth status gated on Weapon+0x20 with caching disabled like PRE_ATTACK;
    // design name unproven (see computeStatus attempt 0x002CC422).
    WEAPON_STATUS_5
};

class ObjectFilter
{
public:
    Bool isValid() const;
};

class WeaponTemplate
{
public:
    // computeStatus reads an int flag at +0x78; this body only needs the ammo
    // descriptor at +0x120.
    char m_pad00[0x120];
    ObjectFilter m_ammo;
};

class BfmeAmmoProvider
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
    virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
    virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
    virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
    virtual void slot68();
    virtual UnsignedInt getRemainingAmmo(const ObjectFilter *descriptor);
};

class Object
{
public:
    BfmeAmmoProvider *getAmmoProvider() const { return m_ammoProvider; }
    // Owner-side ammo-availability gate used by Weapon::isAmmoReady; true name
    // unproven (address proven by REL32, body reads Object+0x330).
    Bool rva0028AF65() const;

    char m_padding[0x250];
    BfmeAmmoProvider *m_ammoProvider;
};

class GameLogic
{
public:
    Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Weapon
{
public:
    virtual void unused();
    UnsignedInt getRemainingAmmo(Bool countReloadingAsEmpty) const;
    WeaponStatus computeStatus(Bool *changed) const;
    // Owner-has-usable-ammo gate for the empty-clip READY path; true name
    // unproven (BFME1 attempt: bfmeAmmoReady). Adjacent to computeStatus.
    Bool isAmmoReady() const;

private:
    WeaponTemplate *m_template;
    ObjectID m_ownerID;
    UnsignedInt m_weaponSlot;
    mutable WeaponStatus m_status;
    UnsignedInt m_ammoInClip;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

UnsignedInt Weapon::getRemainingAmmo(Bool countReloadingAsEmpty) const
{
    const WeaponTemplate *weaponTemplate = m_template;
    if (weaponTemplate->m_ammo.isValid())
    {
        Object *owner = TheGameLogic->findObjectByID(m_ownerID);
        BfmeAmmoProvider *provider = owner ? owner->getAmmoProvider() : 0;
        if (provider)
        {
            const WeaponTemplate *templateForAmmo = m_template;
            UnsignedInt remaining = provider->getRemainingAmmo(&templateForAmmo->m_ammo);
            _ReadWriteBarrier();
            return remaining;
        }
    }

    if (countReloadingAsEmpty && computeStatus(0) == RELOADING_CLIP)
        return 0;

    return m_ammoInClip;
}

Bool Weapon::isAmmoReady() const
{
    Object *owner = TheGameLogic->findObjectByID(m_ownerID);
    if (owner != 0)
    {
        if (owner->rva0028AF65())
            return true;
    }
    return false;
}
