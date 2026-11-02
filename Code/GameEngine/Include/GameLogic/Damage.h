// Target facts: default constructor RVA 0x00263895 and copy constructor RVA 0x0028F68F install VA 0x00BF9200 at +0, construct the 0x68-byte input at +4 (RVAs 0x00263653/0x0028C62B), and construct the 0x10-byte output at +0x6C (copy RVA 0x0028C6D6). The complete record is 0x7C bytes; RVA 0x0043B196 copies that record before its separate +0x7C/+0x80/+0x84 fields.
// Target facts: VA 0x00BF9200 has one slot, RVA 0x004D6F86, which transfers the two embedded records through their slot 0. Input VA 0x00BF91FC has one slot, RVA 0x004D6FC4; output VA 0x00BF91AC has one slot, RVA 0x004D70D5. None has a virtual destructor or a Snapshot base. RVA 0x00263653 initializes input dwords +4..+0x1C, bytes +0x20/+0x21, dwords +0x24..+0x48, byte +0x4C and dwords +0x50..+0x64; RVA 0x004D6FC4 transfers their types, including ObjectID at input +4/+0x2C and the vector at input +0x30. RVA 0x00509F3A writes the second vector at complete-object +0x5C. RVA 0x00263895 initializes complete-object floats +0x70/+0x74 and byte +0x78.
// Names: Zero Hour Damage.h supplies xfer, m_sourceID, m_sourcePlayerMask, m_damageType, m_deathType, m_amount, m_kill, m_shockWaveVector and the output names; retail RVA 0x004D6FC4 confirms the corresponding transfer types, and RVAs 0x0028FEA7/0x004BFE07 confirm their complete-object offsets. The embedded records are exposed as fields of this class; unnamed target fields retain offset placeholders. The default constructor has the existing DamageInfo symbol pin at RVA 0x00263895; the copy constructor is called out of line at RVA 0x0043B19F.

#pragma once

#ifndef BFME2_GAMELOGIC_DAMAGE_H
#define BFME2_GAMELOGIC_DAMAGE_H

class Xfer;
struct Coord3D;
enum ObjectID;
#include "../../../Libraries/Include/Lib/Coord3D.h"

class DamageInfo
{
public:
    DamageInfo();
    DamageInfo(const DamageInfo &other);
    virtual void xfer(Xfer *xfer);

    const void *field04;
    ObjectID m_sourceID;
    unsigned int m_sourcePlayerMask;
    int m_damageType;
    int field14;
    int field18;
    int m_deathType;
    float m_amount;
    bool m_kill;
    bool field25;
    float m_x28;
    int field2C;
    unsigned int field30;
    Coord3D m_shockWaveVector;
    float field40;
    float field44;
    float field48;
    float field4C;
    bool field50;
    float field54;
    float field58;
    Coord3D field5C;
    float field68;
    const void *field6C;
    float m_actualDamageDealt;
    float m_actualDamageClipped;
    bool m_noEffect;
};

#endif
