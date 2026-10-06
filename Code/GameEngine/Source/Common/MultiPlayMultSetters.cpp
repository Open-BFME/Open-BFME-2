// cl: /DNDEBUG /MD /EHsc
// BFME1 MultiPlayMultParseCallbacks.cpp donor, reconciled to PC retail.
// Descriptive donor type name; PC callbacks establish each array's semantics.
// All setters test signed slot-1 in [0,20); arrays are 0x50 bytes apart.
typedef int Int;
typedef float Real;
class MultiPlayMults
{
public:
	void setMoneyMult( Int slot, Real value );

	void setUnitXPMult( Int slot, Real value );

	void setBuildingXPMult( Int slot, Real value );

	void setUnitSpeedMult( Int slot, Real value );

	void setBuildingSpeedMult( Int slot, Real value );

	// Five twenty-slot arrays in the PC GlobalData subobject at +0xEC4.
	Real m_money[ 20 ];
	Real m_unitXP[ 20 ];
	Real m_buildingXP[ 20 ];
	Real m_unitSpeed[ 20 ];
	Real m_buildingSpeed[ 20 ];
};


// PC RVA 0x2358FC, 27 bytes; called by the named MultiPlayUnitXPMult parser.
void MultiPlayMults::setUnitXPMult(Int slot, Real value)
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        m_unitXP[index] = value;
}

// PC RVA 0x235917, 30 bytes; named MultiPlayBuildingXPMult callback supplies the identity.
void MultiPlayMults::setBuildingXPMult(Int slot, Real value)
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        m_buildingXP[index] = value;
}

// PC RVA 0x235935, 30 bytes; reached by named MultiPlayUnitSpeedMult callback.
void MultiPlayMults::setUnitSpeedMult(Int slot, Real value)
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        m_unitSpeed[index] = value;
}

// PC RVA 0x235953, 30 bytes; named MultiPlayBuildingSpeedMult callback identity.
void MultiPlayMults::setBuildingSpeedMult(Int slot, Real value)
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        m_buildingSpeed[index] = value;
}
