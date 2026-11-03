// Target facts (retail RVAs): 0x003608C9 constructs 0x78 DFX records at this+0 through 0x00001423 with stride 0x10 and constructor 0x003608B4; 0x00360858/0x00360896/0x00360917 copy 0x1E0 dwords after the map key, and 0x00360939 allocates a 0x788-byte node (next, key, 0x780-byte DamageFX). DamageFX has no base, vptr, virtual functions or nontrivial destructor; the constructor initializes its entire storage as DFX records and the copies preserve that storage without a vtable store.
// Target facts: DFX constructor 0x003608B4 and clear 0x0036059C zero float +0 and dwords +4/+8/+0xC; clear loop 0x003605AF iterates 30 damage types and four veterancy levels. Parsers 0x00360689/0x00360702/0x00360774/0x003607E6 store the threshold, major FX, minor FX and throttle at those offsets with strides 0x10/0x40; selector 0x003605E3 reads +0/+4/+8, throttle reader 0x003605D5 reads +0xC, wrapper 0x003608DF calls the selector, and 0x00360911 returns field table VA 0x00C168F8.
// Names: Zero Hour Common/DamageFX.h supplies DFX, m_dfx and its four member names; retail field table VA 0x00C168F8 binds AmountForMajorFX/MajorFX/MinorFX/ThrottleTime to the four parser rows. Placeholder method spellings follow the ledger; 0x003608C9/0x003605AF/0x003605D5 remain owned by their address-named classes. DFX construction and clear are declared out of line, and DamageFX copying remains implicit as the three retail block-copy bodies prove.

#pragma once

#ifndef BFME2_DAMAGEFXCLASS_H
#define BFME2_DAMAGEFXCLASS_H

class FXList;
class INI;
class Object;
struct FieldParse;

class DamageFX
{
public:
    class DFX
    {
    public:
        DFX();
        void clear();

        float m_amountForMajorFX;
        const FXList *m_majorDamageFXList;
        const FXList *m_minorDamageFXList;
        unsigned int m_damageFXThrottleTime;
    };

    static void parseAmount(INI *ini, void *instance, void *store, const void *userData);
    static void parseMajorFXList(INI *ini, void *instance, void *store, const void *userData);
    static void parseMinorFXList(INI *ini, void *instance, void *store, const void *userData);
    static void parseTime(INI *ini, void *instance, void *store, const void *userData);
    void *rva003605E3(int damageType, float amount, const Object *source);
    bool rva003608DF(int damageType, float amount, const Object *source, const Object *victim);
    const FieldParse *getFieldParse() const;

    DFX m_dfx[30][4];
};

#endif
