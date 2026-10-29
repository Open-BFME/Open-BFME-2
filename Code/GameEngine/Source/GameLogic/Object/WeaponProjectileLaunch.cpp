// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// ?calcProjectileLaunchPosition@Weapon@@SAXPBVObject@@W4WeaponSlotType@@HAAVMatrix3D@@AAUCoord3D@@@Z
// retail 0x002C9E48, 2315 bytes (Ghidra FUN_006c9e48).
//
// Target evidence: the byte-verified Weapon::positionProjectileForLaunch
// (0x002CA753) calls it cdecl with launcher, slot, barrel, an identity
// Matrix3D and a Coord3D. The body reads the launcher's AI at +0x258
// (getWhichTurretForWeaponSlot 0x0026278A), its drawable through the
// out-of-line getDrawable (0x005508E2) and that drawable's launch offset
// (0x00275376), the slot weapon (WeaponSet at +0x330, 0x002C7469) whose
// template byte +0x16C gates the turret math, and ends in
// Thing::convertBonePosToWorldPos (0x0030A528).
//
// BFME 2 addition (target evidence): a launcher with status 0x3A rides the
// object it is contained by (+0x274; one more step up when that host's
// template has KindOf bit 0x6D, byte +0x115 & 0x20); when the host's contain
// module (+0x250) reports bit 61 of the vtable +0xB0 mask for the launcher,
// the host's AI, drawable and bone transform stand in for the launcher's.
//
// Donor: Zero Hour / BFME 1 Weapon.cpp Weapon::calcProjectileLaunchPosition
// (BFME 1 matched it at 0x001E2D60 with the slot weapon template gate);
// the turret math is the donor's verbatim.
// Crack evidence: the WB BBA980 body keeps separate host/outer-host branches,
// a shared AI pointer, and separately scoped contain pointers. Preserve those
// scopes: flattening the branches changes the angle/coordinate stack homes.
// The final scalar-constructed coordinate is bound to a const reference; its
// lifetime restores native pitch math and postMul scheduling. All emitted
// Matrix3D, Vector4 and Coord3D helper copies also match their existing owners.

#include "matrix3d.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

#include "Code/Libraries/Include/Lib/Coord3D.h"
inline void Coord3D::zero()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

// Scalar construction view over the canonical three-float coordinate.
struct LaunchCoord : Coord3D
{
    LaunchCoord(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }
    ~LaunchCoord() {}
};
enum WeaponSlotType
{
    PRIMARY_WEAPON
};

enum WhichTurretType
{
    TURRET_INVALID = -1
};

enum ObjectStatusTypes
{
    OBJECT_STATUS_RIDER = 0x3A
};

class Object;

class AIUpdateInterface
{
  public:
    WhichTurretType getWhichTurretForWeaponSlot(WeaponSlotType slot, Real *turretAngle,
                                                Real *turretPitch) const;
};

class Drawable
{
  public:
    bool getProjectileLaunchOffset(WeaponSlotType, Int, Matrix3D *, WhichTurretType, Coord3D *,
                                   Coord3D *) const;
};

struct Flags128
{
    bool test(int i) const { return ((m_bits[i >> 5] >> (i & 31)) & 1) != 0; }
    unsigned int m_bits[4];
};

class ContainModuleInterface
{
  public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual Flags128 getRiderFlags(const Object *rider);
};

class WeaponTemplate
{
  public:
    Bool isTurretAimed() const { return m_turretAimed; }

  private:
    char m_pad000[0x16C];
    Bool m_turretAimed; // +0x16C
};

#include "../../../Include/GameLogic/Weapon.h"

class WeaponSet
{
  public:
    Weapon *getWeaponInWeaponSlot(WeaponSlotType wslot) const;
};

class ThingTemplate
{
  public:
    Bool isKindOf6D() const { return (((const unsigned char *)m_kindOf)[13] & 0x20) != 0; }

  private:
    char m_pad000[0x108];
    unsigned int m_kindOf[5]; // +0x108
};

class Thing
{
  public:
    const ThingTemplate *getTemplate() const { return m_template; }
    void convertBonePosToWorldPos(const Coord3D *bonePos, const Matrix3D *boneTransform,
                                  Coord3D *worldPos, Matrix3D *worldTransform) const;
    Drawable *getDrawable() const;

  private:
    void *m_vtbl;
    const ThingTemplate *m_template; // +4
};

class Object : public Thing
{
  public:
    Bool testStatus(ObjectStatusTypes bit) const;
    ContainModuleInterface *getContain() const { return m_contain; }
    AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
    Object *getContainedBy() const { return m_containedBy; }
    const WeaponSet *getWeaponSet() const { return &m_weaponSet; }

  private:
    char m_pad008[0x250 - 0x08];
    ContainModuleInterface *m_contain; // +0x250
    void *m_pad254;
    AIUpdateInterface *m_ai; // +0x258
    char m_pad25C[0x274 - 0x25C];
    Object *m_containedBy; // +0x274
    char m_pad278[0x330 - 0x278];
    WeaponSet m_weaponSet; // +0x330
};

//-------------------------------------------------------------------------------------------------
/*static*/ void Weapon::calcProjectileLaunchPosition(const Object *launcher, WeaponSlotType wslot,
                                                     Int specificBarrelToUse,
                                                     Matrix3D &worldTransform, Coord3D &worldPos)
{
    Real turretAngle = 0.0f;
    Real turretPitch = 0.0f;
    Matrix3D attachTransform(true);
    Coord3D turretRotPos = {0.0f, 0.0f, 0.0f};
    Coord3D turretPitchPos = {0.0f, 0.0f, 0.0f};
    const AIUpdateInterface *ai = 0;
    const Drawable *draw = 0;
    const Object *host = 0;
    Bool useHost = false;
    WhichTurretType tur;

    if (launcher->testStatus(OBJECT_STATUS_RIDER) && (host = launcher->getContainedBy()) != 0)
    {
        if (host->getTemplate()->isKindOf6D())
        {
            if (host->getContainedBy() != 0)
            {
                host = host->getContainedBy();
                if (host)
                {
                    ContainModuleInterface *contain = host->getContain();
                    if (contain && contain->getRiderFlags(launcher).test(61))
                    {
                        ai = host->getAIUpdateInterface();
                        tur =
                            ai ? ai->getWhichTurretForWeaponSlot(wslot, &turretAngle, &turretPitch)
                               : TURRET_INVALID;
                        draw = host->getDrawable();
                        useHost = true;
                    }
                }
            }
        }
        else
        {
            if (host)
            {
                ContainModuleInterface *contain = host->getContain();
                if (contain && contain->getRiderFlags(launcher).test(61))
                {
                    ai = host->getAIUpdateInterface();
                    tur = ai ? ai->getWhichTurretForWeaponSlot(wslot, &turretAngle, &turretPitch)
                             : TURRET_INVALID;
                    draw = host->getDrawable();
                    useHost = true;
                }
            }
        }
    }
    if (!useHost)
    {
        ai = launcher->getAIUpdateInterface();
        tur = ai ? ai->getWhichTurretForWeaponSlot(wslot, &turretAngle, &turretPitch)
                 : TURRET_INVALID;
        draw = launcher->getDrawable();
    }

    if (!draw || !draw->getProjectileLaunchOffset(wslot, specificBarrelToUse, &attachTransform, tur,
                                                  &turretRotPos, &turretPitchPos))
    {
        attachTransform.Make_Identity();
        turretRotPos.zero();
        turretPitchPos.zero();
    }

    const Weapon *slotWeapon = launcher->getWeaponSet()->getWeaponInWeaponSlot(wslot);
    if (slotWeapon && slotWeapon->getTemplate()->isTurretAimed() && tur != TURRET_INVALID)
    {
        // The attach transform is the pristine front and center position of the fire point
        // We can't read from the client, so we need to reproduce the actual point that
        // takes turn and pitch into account.
        Matrix3D turnAdjustment(1);
        Matrix3D pitchAdjustment(1);

        // To rotate about a point, move that point to 0,0, rotate, then move it back.
        // Pre rotate will keep the first twist from screwing the angle of the second pitch
        pitchAdjustment.Translate(turretPitchPos.x, turretPitchPos.y, turretPitchPos.z);
        pitchAdjustment.In_Place_Pre_Rotate_Y(-turretPitch);
        pitchAdjustment.Translate(-turretPitchPos.x, -turretPitchPos.y, -turretPitchPos.z);

        turnAdjustment.Translate(turretRotPos.x, turretRotPos.y, turretRotPos.z);
        turnAdjustment.In_Place_Pre_Rotate_Z(turretAngle);
        turnAdjustment.Translate(-turretRotPos.x, -turretRotPos.y, -turretRotPos.z);

        Matrix3D tmp = attachTransform;
        attachTransform.mul(turnAdjustment, pitchAdjustment);
        attachTransform.postMul(tmp);
    }

    if (useHost)
    {
        if (host)
            host->convertBonePosToWorldPos(0, &attachTransform, 0, &worldTransform);
    }
    else
    {
        launcher->convertBonePosToWorldPos(0, &attachTransform, 0, &worldTransform);
    }

    const Matrix3D &wt = worldTransform;
    const LaunchCoord &pos = LaunchCoord(wt[0][3], wt[1][3], wt[2][3]);
    worldPos = pos;
}
