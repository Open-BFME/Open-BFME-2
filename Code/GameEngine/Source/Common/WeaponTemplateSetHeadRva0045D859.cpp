// cl: /MD
//
// ?rva0045D859@WeaponTemplateSetHead@@QAEPAV1@PAV1@@Z retail 0x0045D859 46B.
// Complement 19 dwords: copy *this to temp via rowed copy ctor 0x00045455,
// NOT each dword, placement-copy temp into out via same copy ctor, return out.
// Evidence: frame push ebp/sub 0x4c with two copy-ctor calls and 0x13 NOT loop;
// caller 0x0045E2EE passes global out with ecx=global src; sibling intersect
// ?rva000B3ED3@WeaponTemplateSetHead@@QAEXABV1@@Z shares 19-dword 0x4c shape.
inline void *operator new(unsigned int, void *p)
{
	return p;
}

class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &other);
	WeaponTemplateSetHead *rva0045D859(WeaponTemplateSetHead *out);
private:
	unsigned int m_data[19];
};

WeaponTemplateSetHead *WeaponTemplateSetHead::rva0045D859(WeaponTemplateSetHead *out)
{
	WeaponTemplateSetHead tmp(*this);
	for (unsigned i = 0; i < 19; ++i)
		tmp.m_data[i] = ~tmp.m_data[i];
	__assume(out != 0);
	new (out) WeaponTemplateSetHead(tmp);
	return out;
}
