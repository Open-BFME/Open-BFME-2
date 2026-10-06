// cl: /MD
// ?rva003317B0@Rva003317B0@@QAE_NPBVWeaponTemplateSetHead@@@Z retail 0x003317B0 73B
// Subset check over 76-byte sets: if overlap at +0x50 return false; copy arg
// to temp ebp-0x4c via rowed copy ctor 0x00045455; temp intersect member at
// +4 via rowed 0x000B3ED3; return Equal(member temp) via rowed 0x00045473.
// Evidence: sub esp-0x4c push esi lea ecx esi+0x50 call overlap 0x00263546
// then copy-intersect-equal chain; unblocks 0x00335FE1; chain from 0xB3ED3.
typedef bool Bool;
class WeaponTemplateSetHead
{
	char _m[0x4C];
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
	void rva000B3ED3(const WeaponTemplateSetHead &other);
};
class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
private:
	int m_mask[19];
};
Bool Rva00045473Equal(const void *a, const void *b);
class Rva003317B0
{
public:
	bool rva003317B0(const WeaponTemplateSetHead *arg);
private:
	int m_00;
	WeaponTemplateSetHead m_04;
	Rva00263546 m_50;
};
bool Rva003317B0::rva003317B0(const WeaponTemplateSetHead *arg)
{
	if (m_50.rva00263546((const Rva00263546 *)arg))
		return false;
	WeaponTemplateSetHead tmp(*arg);
	tmp.rva000B3ED3(m_04);
	unsigned char eq = Rva00045473Equal(&m_04, &tmp);
	return eq;
}
