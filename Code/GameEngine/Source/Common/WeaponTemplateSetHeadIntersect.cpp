// cl: /DNDEBUG /MD
// ?rva000B3ED3@WeaponTemplateSetHead@@QAEXABV1@@Z retail 0x000B3ED3 25B
// Intersect 19 dwords: this[i] &= src[i] for 76-byte set. Evidence: push 0x13
// pop edx count-down loop with sub eax-ecx delta and and [ecx]-esi; temp at
// ebp-0x4c built by WeaponTemplateSetHead copy ctor 0x00045455 in caller
// 0x003317B0 then AND with member at caller+4 then memcmp 0x4c at 0x00045473;
// sibling NOT loop at 0x000B3EC7 and Equal 0x00045473 share 0x13/0x4c shape.
class WeaponTemplateSetHead
{
public:
	void rva000B3ED3(const WeaponTemplateSetHead &other);
private:
	unsigned int m_data[19];
};
void WeaponTemplateSetHead::rva000B3ED3(const WeaponTemplateSetHead &other)
{
	for (int i = 0; i < 19; ++i)
		m_data[i] &= other.m_data[i];
}
