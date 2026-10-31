#pragma once
// BFME2 interface: VA C5AB68 has 43 __purecall entries, no bases or data.
// Slots follow target tables C5B390/C5B5B0, not the different ZH ordering.
// Structural rva/slot names retain unknown original identities; see
// reverse/attempt_support/bodymoduleinterface-qc12-20261031/README.md.
class DamageInfo;
class DamageInfoInput;
class AsciiString;
class Object;
class BodyModule;
struct BfmeBodyDataPair8;
template <int N> class BitFlags;
enum BodyDamageType;
enum ObjectID;
enum VeterancyLevel;
enum ArmorSetType;
enum MaxHealthChangeType;
class BodyModuleInterface
{
public:
 virtual void attemptDamage(DamageInfo *) = 0; // 0
 virtual void attemptHealing(DamageInfo *) = 0; // 1
 virtual float estimateDamage(DamageInfoInput &) const = 0; // 2
 virtual void rva004BDB25() = 0; // 3
 virtual float getHealth() const = 0; // 4
 virtual float getHealthRatio() const = 0; // 5
 virtual float getMaxHealth() const = 0; // 6
 virtual float rva00094A94() const = 0; // 7
 virtual BodyDamageType getDamageState() const = 0; // 8
 virtual void setDamageState(BodyDamageType) = 0; // 9
 virtual void updateBodyParticleSystems() = 0; // 10
 virtual void onVeterancyLevelChanged(VeterancyLevel, VeterancyLevel) = 0; // 11
 virtual void setArmorSetFlag(ArmorSetType) = 0; // 12
 virtual void clearArmorSetFlag(ArmorSetType) = 0; // 13
 virtual BitFlags<21> rva004BF8F5() = 0; // 14
 virtual const DamageInfo *getLastDamageInfo() const = 0; // 15
 virtual unsigned int getLastDamageTimestamp() const = 0; // 16
 virtual unsigned int getLastHealingTimestamp() const = 0; // 17
 virtual ObjectID rva004BF897() = 0; // 18
 virtual unsigned char rva0052BAAB() const = 0; // 19
 virtual bool getBackCrushed() const = 0; // 20
 virtual void setInitialHealth(float, bool) = 0; // 21
 virtual void setMaxHealth(float, MaxHealthChangeType) = 0; // 22
 virtual void rva004BDB37() = 0; // 23
 virtual void rva004BF8BE(unsigned char) = 0; // 24
 virtual void rva004BF8CB(unsigned char) = 0; // 25
 virtual void applyDamageScalar(float) = 0; // 26
 virtual float getDamageScalar() const = 0; // 27
 virtual AsciiString Rva004BE67E() const = 0; // 28
 virtual int rva004BDC48() const = 0; // 29
 virtual float rva004BDC4F() const = 0; // 30
 virtual BfmeBodyDataPair8 rva004BDC56() = 0; // 31
 virtual void internalChangeHealth(float, DamageInfo *) = 0; // 32
 virtual void setIndestructible(bool) = 0; // 33
 virtual unsigned char rva004BF8D8() const = 0; // 34
 virtual float rva004BDC41() const = 0; // 35
 virtual void rvaSlot36() = 0; // 36
 virtual void rva004C15F7(unsigned char) = 0; // 37
 virtual bool rva004C2127(Object *) = 0; // 38
 virtual void rvaSlot39(BodyDamageType) = 0; // 39
 virtual void rvaSlot40(float, bool) = 0; // 40
 virtual BodyModule *getIface() = 0; // 41
 virtual void rva00101CBE(float) = 0; // 42
};
