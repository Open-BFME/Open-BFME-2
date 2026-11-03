// Target facts: ActiveBody constructor RVA 0x004BF6A1 calls BodyModule constructor 0x004BD7FD, then installs VAs 0x00C5B038 at +0, 0x00C5AD78 at +0x0C and 0x00C5B5B0 at +0x10. Destructor 0x004BF951 restores those same tables, releases the string at +0xF8 through 0x00036410, frees the pointer at +0xE0 through 0x00030830, and calls BodyModule destructor 0x004BD763. Factory 0x002513AD allocates 0x100 bytes and calls 0x004BF6A1 at 0x002513D7. ActiveBody is polymorphic; its primary table has 23 entries, followed by non-code at VA 0x00C5B094.
// Target facts: primary VA 0x00C5B038 slots 1/2 implement Snapshot's loadPostProcess/GetSnapshotName at 0x004BF40F/0x004BF88D. Slots 13/18/19/22 point to the rowed rva004BE69C/doDamageFX/createParticleSystems/rva004BF9ED; slot 17 points to the nonvirtual-spelled validateArmorAndDamageFX row 0x004BE1AE and slot 21 to the nonvirtual-spelled setCorrectDamageState row 0x004BE8BD. Separate neutral slot declarations preserve those existing out-of-line call spellings. Slots 15/16 are 0x004BF8DF/0x004BF8ED (conditional attacker ID at +0x48 and clearing byte +0xC6); slot 14 is 0x004BF8AC (armor at +0xF8). Body-interface VA 0x00C5B5B0 has the registered parent's 43 slots; its slots 0/1/2/9/11/12/13/14/18/20/21/22/31/32/33 name the corresponding rowed ActiveBody overrides.
// Target facts: constructor 0x004BF6A1 initializes health floats +0x18/+0x1C/+0x20/+0x24/+0x28/+0x2C, dwords +0x30/+0x34/+0x38/+0x3C, the DamageInfo record at +0x40 through constructor 0x00263895, timestamps +0xBC/+0xC0, flags +0xC4..+0xC7, particle pointer +0xC8, four floats +0xCC and four bytes +0xDC, vector storage +0xE0 through 0x00211E58 and assignment 0x004BF4CE, dword +0xEC, flags +0xF0 through 0x003B31AD, cached pointer +0xF4, string +0xF8 through 0x000365F0, and cached FX +0xFC. Readers 0x004F5F92/0x00314046/0x0023CAD2/0x005BE1A7 independently prove complete-object +0x18/+0x40/+0xBC/+0xC0 from secondary this. validateArmorAndDamageFX 0x004BE1AE proves the flags/cache/string/FX at +0xF0/+0xF4/+0xF8/+0xFC; setMaxHealth 0x004BDB85 proves health accesses at secondary-this +8/+0x10/+0x1C and slot-32 dispatch with a DamageInfo pointer.
// Donor names: Zero Hour GeneralsMD ActiveBody.h and BodyModule.h supply BodyModule, the health/damage/timestamp/flag/particle names, getClearableLastAttacker, clearLastAttacker and deleteAllParticleSystems. BFME2's different slots, additional fields and 0x7C-byte DamageInfo come from the target facts above; unresolved identities retain offset or slot names. Constructors, destructor and rowed nonvirtual accessors are declared out of line.

#pragma once

#ifndef BFME2_GAMELOGIC_MODULE_ACTIVEBODY_H
#define BFME2_GAMELOGIC_MODULE_ACTIVEBODY_H

#include "BehaviorModule.h"
#include "BodyModuleClass.h"
#include "../Damage.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class ActiveBodyModuleData;
class BodyParticleSystem;
class ParticleSystemTemplate;
class DamageFX;
class ArmorTemplateSet;

class ActiveBody : public BodyModule
{
public:
    ActiveBody(Thing *thing, const ModuleData *moduleData);
    virtual ~ActiveBody();
    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    const char *name() const;
    virtual NameKeyType getModuleNameKey() const;
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void onDelete();

    virtual void rva004BE69C(); // primary slot 13
    virtual int vslot14();
    virtual ObjectID getClearableLastAttacker() const;
    virtual void clearLastAttacker();
    virtual void vslot17() const;
protected:
    virtual void doDamageFX(const DamageInfo *damageInfo);
    virtual void createParticleSystems(const AsciiString &boneBaseName, const ParticleSystemTemplate *systemTemplate, int maxSystems);
public:
    virtual void deleteAllParticleSystems();
    virtual void vslot21(bool update);
    virtual void rva004BF9ED();

    virtual void attemptDamage(DamageInfo *damageInfo);
    virtual void attemptHealing(DamageInfo *damageInfo);
    virtual float estimateDamage(DamageInfoInput &damageInfo) const;
    virtual void rva004BDB25();
    virtual float getHealth() const;
    virtual float getHealthRatio() const;
    virtual float getMaxHealth() const;
    virtual float rva00094A94() const;
    virtual BodyDamageType getDamageState() const;
    virtual void setDamageState(BodyDamageType newState);
    virtual void updateBodyParticleSystems();
    virtual void onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel);
    virtual void setArmorSetFlag(ArmorSetType armorSet);
    virtual void clearArmorSetFlag(ArmorSetType armorSet);
    virtual BitFlags<21> rva004BF8F5();
    virtual const DamageInfo *getLastDamageInfo() const;
    virtual unsigned int getLastDamageTimestamp() const;
    virtual unsigned int getLastHealingTimestamp() const;
    virtual ObjectID rva004BF897();
    virtual unsigned char rva0052BAAB() const;
    virtual bool getBackCrushed() const;
    virtual void setInitialHealth(float initialPercent, bool directional);
    virtual void setMaxHealth(float maxHealth, MaxHealthChangeType healthChangeType);
    virtual void rva004BDB37();
    virtual void rva004BF8BE(unsigned char value);
    virtual void rva004BF8CB(unsigned char value);
    virtual void applyDamageScalar(float scalar);
    virtual float getDamageScalar() const;
    virtual AsciiString Rva004BE67E() const;
    virtual int rva004BDC48() const;
    virtual float rva004BDC4F() const;
    virtual BfmeBodyDataPair8 rva004BDC56();
    virtual void internalChangeHealth(float delta, DamageInfo *damageInfo);
    virtual void setIndestructible(bool indestructible);
    virtual unsigned char rva004BF8D8() const;
    virtual float rva004BDC41() const;
    virtual void rvaSlot36();
    virtual void rva004C15F7(unsigned char value);
    virtual bool rva004C2127(Object *object);
    virtual void rvaSlot39(BodyDamageType state);
    virtual void rvaSlot40(float value, bool flag);
    virtual BodyModule *getIface();
    virtual void rva00101CBE(float value);

    void validateArmorAndDamageFX() const;
    void setCorrectDamageState(bool update);
    void rva004BFB1C(float amount, const Coord3D *position);
    void rva004BFCD4(float amount, DamageInfo *damageInfo);

protected:
    virtual void xfer(Xfer *xfer);
    static bool shouldRetaliate(Object *object);
    const ActiveBodyModuleData *getActiveBodyModuleData() const { return (const ActiveBodyModuleData *)m_moduleData; }
    Object *getObject() const { return m_object; }

public:
    float m_currentHealth; // +0x18
    float m_prevHealth; // +0x1C
    float m_maxHealth; // +0x20
    float field24;
    float field28;
    float m_initialHealth; // +0x2C
    BodyDamageType m_curDamageState; // +0x30
    int field34;
    unsigned int m_nextDamageFXTime; // +0x38
    int m_lastDamageFXDone; // +0x3C
    DamageInfo m_lastDamageInfo; // +0x40
    unsigned int m_lastDamageTimestamp; // +0xBC
    unsigned int m_lastHealingTimestamp; // +0xC0
    bool m_frontCrushed; // +0xC4
    bool m_backCrushed; // +0xC5
    bool m_lastDamageCleared; // +0xC6
    bool m_indestructible; // +0xC7
    BodyParticleSystem *m_particleSystems; // +0xC8
    float fieldCC[4];
    bool fieldDC[4];
    void *fieldE0;
    void *fieldE4;
    void *fieldE8;
    unsigned int fieldEC;
    unsigned int fieldF0;
    mutable const ArmorTemplateSet *m_curArmorSet; // +0xF4
    mutable AsciiString fieldF8;
    mutable const DamageFX *m_curDamageFX; // +0xFC
};

typedef char ActiveBodySizeCheck[sizeof(ActiveBody) == 0x100 ? 1 : -1];

#endif
