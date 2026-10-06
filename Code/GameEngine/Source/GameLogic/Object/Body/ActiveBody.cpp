// cl: /O1 /EHsc /MD /arch:SSE
// ActiveBody.cpp -- ActiveBody members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function (vtable
// pairing); retail supplies the bytes. Zero Hour's setDamageState
// (GameLogic/Object/Body/ActiveBody.cpp) as a switch over the state with the
// thresholds held in the body itself.
//
// Layout (target evidence, matching Body/ActiveBodyDamageState.cpp): the body
// module interface is the second base at +0x10, so this body runs with ecx at
// +0x10; health +0x18, max health +0x20, damaged and really-damaged ratios
// +0x24/+0x28. The health change is interface slot 32 (+0x80); the final
// call is slot 21 (+0x54) of the primary vtable with a zero argument.

typedef float Real;
typedef int Int;

enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };

class ActiveBodyModuleBase
{
public:
	virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
	virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
	virtual void m20();
	virtual void rvaSlot21(Int arg);			// +0x54

private:
	unsigned char m_pad04[0xc];
};

class BodyModuleInterface
{
public:
	virtual void i00(); virtual void i01(); virtual void i02(); virtual void i03();
	virtual void i04(); virtual void i05(); virtual void i06(); virtual void i07();
	virtual void i08(); virtual void i09(); virtual void i10(); virtual void i11();
	virtual void i12(); virtual void i13(); virtual void i14(); virtual void i15();
	virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
	virtual void i20(); virtual void i21(); virtual void i22(); virtual void i23();
	virtual void i24(); virtual void i25(); virtual void i26(); virtual void i27();
	virtual void i28(); virtual void i29(); virtual void i30(); virtual void i31();
	virtual void internalChangeHealth(Real delta, Int flag);	// +0x80
	virtual void setDamageState(BodyDamageType newState);
};

class ActiveBody : public ActiveBodyModuleBase, public BodyModuleInterface
{
public:
	virtual void setDamageState(BodyDamageType newState);

private:
	unsigned char m_pad14[4];
	Real m_currentHealth;			// +0x18
	unsigned char m_pad1C[4];
	Real m_maxHealth;			// +0x20
	Real m_damagedRatio;			// +0x24
	Real m_reallyDamagedRatio;		// +0x28
};

// ActiveBody::setDamageState, retail 0x004BDAA9.
void ActiveBody::setDamageState(BodyDamageType newState)
{
	switch (newState)
	{
	case BODY_PRISTINE:
		internalChangeHealth(m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_DAMAGED:
		internalChangeHealth(m_damagedRatio * m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_REALLYDAMAGED:
		internalChangeHealth(m_reallyDamagedRatio * m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_RUBBLE:
		internalChangeHealth(0.0f - m_currentHealth, 0);
		break;
	}
	rvaSlot21(0);
}
