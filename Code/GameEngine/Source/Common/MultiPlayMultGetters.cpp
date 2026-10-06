// cl: /DNDEBUG /MD /EHsc
// Getter siblings of the BFME1-derived MultiPlayMults facade.
// Array roles come from PC FieldParse callbacks and their matched setters.
// PC callers add GlobalData+0xEC4 before the XP/speed accessors; no Xbox ABI reused.
// Invalid signed slot-1 returns the independently checked float literal 1.0.
typedef int Int;
typedef float Real;
class MultiPlayMults
{
public:
	Real getMoneyMult( Int slot ) const;

	Real getUnitXPMult( Int slot ) const;

	Real getBuildingXPMult( Int slot ) const;

	Real getUnitSpeedMult( Int slot ) const;

	Real getBuildingSpeedMult( Int slot ) const;

	// Five twenty-slot arrays in the PC GlobalData subobject at +0xEC4.
	Real m_money[ 20 ];
	Real m_unitXP[ 20 ];
	Real m_buildingXP[ 20 ];
	Real m_unitSpeed[ 20 ];
	Real m_buildingSpeed[ 20 ];
};


Real MultiPlayMults::getMoneyMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_money[index];
    return 1.0f;
}

Real MultiPlayMults::getUnitXPMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_unitXP[index];
    return 1.0f;
}

Real MultiPlayMults::getBuildingXPMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_buildingXP[index];
    return 1.0f;
}

Real MultiPlayMults::getUnitSpeedMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_unitSpeed[index];
    return 1.0f;
}

Real MultiPlayMults::getBuildingSpeedMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_buildingSpeed[index];
    return 1.0f;
}
