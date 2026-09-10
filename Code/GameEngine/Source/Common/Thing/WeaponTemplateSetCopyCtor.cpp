// cl: /O1 /DNDEBUG /MD
//
// WeaponTemplateSet copy ctor, retail 0x004AE811, 33 bytes.
// Dedicated TU so WeaponTemplateSetConstruct.cpp cannot see this body.
// Copies a 0x4C-byte head via its copy ctor then two trailing dwords.

class WeaponTemplateSetHead
{
	char _m[0x4C];

public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
};

class WeaponTemplateSet
{
	WeaponTemplateSetHead m_head;
	int m_field4C;
	int m_field50;

public:
	WeaponTemplateSet(const WeaponTemplateSet &that);
};

WeaponTemplateSet::WeaponTemplateSet(const WeaponTemplateSet &that)
	: m_head(that.m_head), m_field4C(that.m_field4C), m_field50(that.m_field50)
{
}
