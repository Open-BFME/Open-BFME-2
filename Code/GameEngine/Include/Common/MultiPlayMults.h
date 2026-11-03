// Target facts (BFME2 retail RVAs unless marked VA):
// Constructor 0x002358A2 writes six twenty-float arrays at +0, +0x50, +0xA0, +0xF0, +0x140 and +0x190 with 1.0f (VA 0x00BBB8D8). It has no calls or vptr stores. This plain class has no virtual functions or base, and no rowed destructor.
// GlobalData calls that constructor at 0x00237234 with this+0xEC4, then initializes separate storage at +0x10A4 at 0x0023769C: the multiplier subobject occupies 0x1E0 bytes, aligned to four bytes.
// Getter/setter pairs prove the first five array roles and signed slot-1 bounds [0,20): money 0x00235971/0x002358E2, unit XP 0x0023598B/0x002358FC, building XP 0x002359A6/0x00235917, unit speed 0x002359C4/0x00235935, building speed 0x002359E2/0x00235953. Getters return 1.0f outside the bounds. The sixth array's role is unknown.

#pragma once

#ifndef __BFME2_MULTIPLAYMULTS_H_
#define __BFME2_MULTIPLAYMULTS_H_

class MultiPlayMults
{
public:
    MultiPlayMults();

    float getMoneyMult(int slot) const;
    float getUnitXPMult(int slot) const;
    float getBuildingXPMult(int slot) const;
    float getUnitSpeedMult(int slot) const;
    float getBuildingSpeedMult(int slot) const;

    void setMoneyMult(int slot, float value);
    void setUnitXPMult(int slot, float value);
    void setBuildingXPMult(int slot, float value);
    void setUnitSpeedMult(int slot, float value);
    void setBuildingSpeedMult(int slot, float value);

    float m_money[20];
    float m_unitXP[20];
    float m_buildingXP[20];
    float m_unitSpeed[20];
    float m_buildingSpeed[20];
    float m_190[20];
};

#endif
