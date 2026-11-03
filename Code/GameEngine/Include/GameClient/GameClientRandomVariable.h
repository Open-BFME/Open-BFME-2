/* Target facts: GameClientRandomVariable has no virtual functions or base subobject. Its constructor (RVA 0x000B4979) stores zero at +0, +4 and +8 with no vptr store or base call; +0 is the distribution enum (getDistributionType, 0x00421795), and +4/+8 are floats (getMinimumValue, 0x00452D82; getMaximumValue, 0x004F5F92). Assignment (0x0000353A) copies three dwords, and TerrainFireEmissionInfo's copy constructor (0x003A6E0E) copies adjacent 12-byte members at +8/+0x14/+0x20: sizeof is 0x0C. getValue (0x002341A1) tests distribution values 0 and 1; setRange (0x002341E7) stores its float bounds at +4/+8 and enum at +0. Equality (0x00005568) compares these three fields; inequality (0x0000559B) calls equality. The distribution-name table is at VA 0x00DBA3E8, used by INI::parseGameClientRandomVariable (RVA 0x00338A9D). No destructor or vftable belongs to this plain value class.
Donor facts: Zero Hour GeneralsMD ClientRandomValue.h names DistributionType, its six enumerators, m_type, m_low, m_high, DistributionTypeNames and the range/accessor methods. Retail's named rows establish the constructor, assignment and comparison declarations. Methods with rowed bodies remain declared out of line; copying and destruction otherwise use the implicit trivial operations.
*/
#pragma once

#ifndef __BFME2_GAMECLIENTRANDOMVARIABLE_H_
#define __BFME2_GAMECLIENTRANDOMVARIABLE_H_

class GameClientRandomVariable
{
public:
    enum DistributionType
    {
        CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
    };

    GameClientRandomVariable();
    GameClientRandomVariable &operator=(const GameClientRandomVariable &that);

    void setRange(float low, float high, DistributionType type = UNIFORM);
    float getValue() const;
    float getMinimumValue() const;
    float getMaximumValue() const;
    DistributionType getDistributionType() const;

    static const char *DistributionTypeNames[];

    DistributionType m_type;
    float m_low;
    float m_high;

    friend bool operator==(const GameClientRandomVariable &a, const GameClientRandomVariable &b);
};

bool operator==(const GameClientRandomVariable &a, const GameClientRandomVariable &b);
bool operator!=(const GameClientRandomVariable &a, const GameClientRandomVariable &b);

#endif
