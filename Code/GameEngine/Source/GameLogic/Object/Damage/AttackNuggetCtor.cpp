// cl: /O1 /MD /DNDEBUG /EHsc /arch:SSE
//
// ??0AttackNugget@@QAE@XZ, retail 0x001F05C1 (69 bytes). EH nugget ctor over
// a trivially-constructed base with a declared virtual dtor (its unwind
// state 0 covers the member-constructing call): the compiler installs vtable
// 0x00BE0FF4 between the state store plus member lea and the +0x04 member
// construction through the pinned RadiusDecalTemplate ctor at 0x00330E5D,
// then the body zeroes the +0x40 word and the +0x38 float slot and sets the
// +0x3C word. Donor: BFME1 RadiusDecal.h (member class with AsciiString
// members per the callee pin; the pin spelling resolves the call). Identity
// is the Attack OCL keyword parse at 0x001F0D96 calling this out-of-line
// ctor (superseded pin note). The base is ObjectCreationNugget, as in ZH:
// retail's unwind funclet 0x0076AFD7 runs its rowed destructor 0x001F0409.

class ObjectCreationNugget
{
public:
	// Rowed out of line at 0x001F0102; inlined here, so never emitted.
	__declspec(dllimport) __forceinline ObjectCreationNugget() {}
	virtual ~ObjectCreationNugget();
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();

private:
	unsigned char m_opaque[0x34];
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class AttackNugget : public ObjectCreationNugget
{
public:
	AttackNugget();
	virtual ~AttackNugget();

private:
	RadiusDecalTemplate m_deliveryDecalTemplate;	// +0x04
	float m_deliveryDecalRadius;	// +0x38
	int m_numberOfShots;	// +0x3C
	WeaponSlotType m_weaponSlot;	// +0x40
};

inline AttackNugget::AttackNugget()
{
	m_deliveryDecalRadius = 0.0f;
	m_numberOfShots = 1;
	m_weaponSlot = PRIMARY_WEAPON;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeAttackNuggetInlineAnchor@@YAXPAVAttackNugget@@@Z absent-from-retail
void _bfmeAttackNuggetInlineAnchor(AttackNugget *attackNugget)
{
    attackNugget->AttackNugget::AttackNugget();
}
#pragma inline_depth()
