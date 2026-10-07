// BFME1 donor: 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_setMaxHealth.cpp.
// Identity: ActiveBody ctor 0x4BF6A1 installs its secondary body-interface
// table 0xC5B5B0. Slot +0x58 names native 0x4BDB85, shared by its derived bodies.
// This local view starts at that interface (complete ActiveBody +0x10).
// Native health accesses +8/+0x10/+0x1C correspond to full-object
// +0x18/+0x20/+0x2C, also established by ActiveBodyConstructor.cpp.
// Slot +0x80 changes health with the BFME2 DamageInfo pointer argument.
// The donor guides the ratio/addition/clamp semantics and change-type names.
// cl: -O1 -arch:SSE -G7 -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Body -DNDEBUG -MD -EHsc

class DamageInfo;
typedef bool Bool;
typedef float Real;

enum MaxHealthChangeType
{
	SAME_CURRENTHEALTH,
	PRESERVE_RATIO,
	ADD_CURRENT_HEALTH_TOO,
	FULLY_HEAL,
};

class BodyModuleInterface
{
public:
	virtual void pad00(); virtual void pad04(); virtual void pad08(); virtual void pad0C();
	virtual void pad10(); virtual void pad14(); virtual void pad18(); virtual void pad1C();
	virtual void pad20(); virtual void pad24(); virtual void pad28(); virtual void pad2C();
	virtual void pad30(); virtual void pad34(); virtual void pad38(); virtual void pad3C();
	virtual void pad40(); virtual void pad44(); virtual void pad48(); virtual void pad4C();
	virtual void pad50(); virtual void pad54();
	virtual void setMaxHealth( Real maxHealth, MaxHealthChangeType healthChangeType );
	virtual void pad5C();
	virtual void pad60(); virtual void pad64(); virtual void pad68(); virtual void pad6C();
	virtual void pad70(); virtual void pad74(); virtual void pad78(); virtual void pad7C();
	virtual void internalChangeHealth( Real delta, DamageInfo *damageInfo );
};

class ActiveBody : public BodyModuleInterface
{
public:
	virtual void setMaxHealth( Real maxHealth, MaxHealthChangeType healthChangeType );

private:
	unsigned char m_pad04[4];
	Real m_currentHealth;      // +0x08
	unsigned char m_pad0C[4];
	Real m_maxHealth;          // +0x10
	unsigned char m_pad14[8];
	Real m_initialHealth;      // +0x1C
};

// ?setMaxHealth@ActiveBody@@UAEXMW4MaxHealthChangeType@@@Z
void ActiveBody::setMaxHealth( Real maxHealth, MaxHealthChangeType healthChangeType )
{
	Real prevMaxHealth = m_maxHealth;
	m_maxHealth = maxHealth;
	m_initialHealth = maxHealth;

	switch( healthChangeType )
	{
		case PRESERVE_RATIO:
		{
			Real ratio = m_currentHealth / prevMaxHealth;
			Real newHealth = maxHealth * ratio;
			internalChangeHealth( newHealth - m_currentHealth, 0 );
			break;
		}
		case ADD_CURRENT_HEALTH_TOO:
		{
			internalChangeHealth( maxHealth - prevMaxHealth, 0 );
			break;
		}
		default:
			break;
	}

	if( m_currentHealth > maxHealth )
	{
		internalChangeHealth( maxHealth - m_currentHealth, 0 );
	}
}
