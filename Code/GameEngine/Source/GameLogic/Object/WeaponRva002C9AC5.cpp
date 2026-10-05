// cl: /O1 /DNDEBUG /MD /EHs-c-
// ?rva002C9AC5@Weapon@@QAEHPBVObject@@@Z @0x002C9AC5 57B
// Weapon clip reload with computed bonus: 6x1.0f bonus then computeBonus plus template time.
// Evidence: same Weapon TU neighbours; [ecx+4] template like siblings; callees rowed computeBonus plus getClipReloadTime.
class Object;
class WeaponBonus
{
public:
	float m_fields[6];
};
class WeaponTemplate
{
public:
	int getClipReloadTime(const WeaponBonus &bonus) const;
};
class Weapon
{
public:
	int rva002C9AC5(const Object *source);

protected:
	void computeBonus(const Object *source, unsigned int extra, WeaponBonus &bonus) const;

private:
	char m_pad00[4];
	const WeaponTemplate *m_template;
};
int Weapon::rva002C9AC5(const Object *source)
{
	WeaponBonus bonus;
	for (int i = 0; i < 6; ++i)
		bonus.m_fields[i] = 1.0f;
	computeBonus(source, 0, bonus);
	return m_template->getClipReloadTime(bonus);
}
