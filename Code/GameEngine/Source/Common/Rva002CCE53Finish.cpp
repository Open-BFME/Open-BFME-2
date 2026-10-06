// ?rva002CCE53@Weapon@@QBEMXZ
// cl: /O1 /DNDEBUG /MD
// ?rva002CCE53@Weapon@@QBEMXZ @0x002CCE53 128B evidence: Weapon neighbours prev
// deleting dtor next getStatus plus computeStatus row; float div via
// BfmeZeroRange and 1.0 plus 2pow32 fixup; Rva000B2EB5 precedent flags.
enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK,
	WEAPON_STATUS_5
};
class ObjectFilter
{
public:
	bool isValid() const;
};
class WeaponTemplate
{
public:
	char m_pad00[0x78];
	int m_flag78;
	char m_pad7C[0x120 - 0x78 - 4];
	ObjectFilter m_ammo;
};
class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;
class Weapon
{
public:
	float rva002CCE53() const;
	WeaponStatus computeStatus(bool *cacheable) const;
private:
	char m_pad00[4];
	WeaponTemplate *m_template;
	char m_pad08[8];
	WeaponStatus m_status;
	int m_pad14;
	unsigned int m_frame18;
	unsigned int m_frame1C;
	unsigned int m_frame20;
	unsigned int m_frame24;
	unsigned int m_frame28;
};

float Weapon::rva002CCE53() const
{
	WeaponStatus s = computeStatus(0);
	switch (s)
	{
	case READY_TO_FIRE:
		return 1.0f;
	case OUT_OF_AMMO:
		return 0.0f;
	case PRE_ATTACK:
		return 0.0f;
	case BETWEEN_FIRING_SHOTS:
	case RELOADING_CLIP:
	case WEAPON_STATUS_5:
		break;
	default:
		return 0.0f;
	}
	unsigned int cur = TheGameLogic->m_frame;
	if (cur >= m_frame18)
		return 1.0f;
	unsigned int total = m_frame18 - m_frame28;
	if (total == 0)
		return 1.0f;
	unsigned int done = total - m_frame18 + cur;
	if (done >= total)
		return 1.0f;
	return (float)done / (float)total;
}
