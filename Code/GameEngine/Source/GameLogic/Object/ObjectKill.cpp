// cl: /DNDEBUG /MD /GX-
// ?kill@Object@@QAEXW4DamageType@@W4DeathType@@@Z
// Target boundary 0x002984D4..0x00298515 (67B). Retail disassembly establishes
// the 0x7C-byte local; source ID zero; enum fields at +0x10/+0x1C; Object's
// body-module pointer at +0x254; max-health virtual call at slot +0x18; amount
// and kill fields at +0x20/+0x24; and a direct call to 0x0029848E.
// Donor: BFME1 Object.cpp:1954-1968 identifies Object::kill and its
// DamageInfo/max-health/attemptDamage flow. BFME2 zeroes the source field and
// omits the donor-only debug assertion. The attemptDamage pin is supported by
// this target call site and the donor's matching call with a DamageInfo pointer.

enum DamageType { DamageType_Unknown };
enum DeathType { DeathType_Unknown };
class DamageInfo;

class Rva00263653
{
public:
    Rva00263653() throw();
    char m_data[0x68];
};

class Rva00263895Member
{
public:
    Rva00263895Member() throw();
    virtual void rva00263895_dummy();

private:
    Rva00263653 m_mem;
    const void *m_ptr;
    float m_f70;
    float m_f74;
    unsigned char m_b78;
};

// Target-backed slot facade: getMaxHealth is called at vtable offset +0x18.
class BodyModuleInterface
{
public:
    virtual void vf00() = 0;
    virtual void vf04() = 0;
    virtual void vf08() = 0;
    virtual void vf0C() = 0;
    virtual void vf10() = 0;
    virtual void vf14() = 0;
    virtual float getMaxHealth() const = 0;
};

class Object
{
public:
    void kill(DamageType damageType, DeathType deathType);
    void attemptDamage(DamageInfo *damageInfo);

private:
    unsigned char pad_0000[0x254];
    BodyModuleInterface *m_body;
};

void Object::kill(DamageType damageType, DeathType deathType)
{
    Rva00263895Member damageInfo;
    *(int *)((char *)&damageInfo + 0x08) &= 0;
    *(int *)((char *)&damageInfo + 0x10) = damageType;
    *(int *)((char *)&damageInfo + 0x1C) = deathType;
    *(float *)((char *)&damageInfo + 0x20) = m_body->getMaxHealth();
    *(unsigned char *)((char *)&damageInfo + 0x24) = 1;
    attemptDamage((DamageInfo *)&damageInfo);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDoBGB@BfmeSubBGB@@QAEXHH@Z=?kill@Object@@QAEXW4DamageType@@W4DeathType@@@Z")
