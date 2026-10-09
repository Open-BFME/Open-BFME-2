// cl: /O1 /DNDEBUG /MD
//
// ?rva0028F44C@Object@@QBE_NPBV1@@Z @0x0028F44C 112B (ret 4):
// Resolves this object and the argument to the object carrying template
// KindOf bit 0x2000 (template +0x114) - itself, or else its +0x274 owner when
// that owner carries the bit (this side recurses through owners; the tail
// call is the native loop back to the bit test) - and asks this side's horde contain (rowed
// 0x0028C197: +0x250 contain, slot 31) through its slot 147 (+0x24C) about the
// other side. Null argument, an unresolved side or no horde contain: false.
// Callers: 0x00508120 (DamageNugget::generateDamageInfo per WorldBuilder)
// tests target->(source) and source->(target) for its bonus/scale block.
// Bit, offsets and slots from the native body; the meaning is not proven.
class Object;
class Rva0028F44CTemplateView
{
public:
	unsigned char pad00[0x114];
	unsigned int kindOf114;
};
class Rva0028F44CHordeView
{
public:
#define RVA0028F44C_SLOT(n) virtual void slot##n();
#define RVA0028F44C_SLOT10(n) RVA0028F44C_SLOT(n##0) RVA0028F44C_SLOT(n##1) RVA0028F44C_SLOT(n##2) RVA0028F44C_SLOT(n##3) RVA0028F44C_SLOT(n##4) RVA0028F44C_SLOT(n##5) RVA0028F44C_SLOT(n##6) RVA0028F44C_SLOT(n##7) RVA0028F44C_SLOT(n##8) RVA0028F44C_SLOT(n##9)
	RVA0028F44C_SLOT(0) RVA0028F44C_SLOT(1) RVA0028F44C_SLOT(2) RVA0028F44C_SLOT(3) RVA0028F44C_SLOT(4)
	RVA0028F44C_SLOT(5) RVA0028F44C_SLOT(6) RVA0028F44C_SLOT(7) RVA0028F44C_SLOT(8) RVA0028F44C_SLOT(9)
	RVA0028F44C_SLOT10(1) RVA0028F44C_SLOT10(2) RVA0028F44C_SLOT10(3) RVA0028F44C_SLOT10(4)
	RVA0028F44C_SLOT10(5) RVA0028F44C_SLOT10(6) RVA0028F44C_SLOT10(7) RVA0028F44C_SLOT10(8)
	RVA0028F44C_SLOT10(9) RVA0028F44C_SLOT10(10) RVA0028F44C_SLOT10(11) RVA0028F44C_SLOT10(12)
	RVA0028F44C_SLOT10(13)
	RVA0028F44C_SLOT(140) RVA0028F44C_SLOT(141) RVA0028F44C_SLOT(142) RVA0028F44C_SLOT(143)
	RVA0028F44C_SLOT(144) RVA0028F44C_SLOT(145) RVA0028F44C_SLOT(146)
	virtual bool slot147(const Object *other);
};
class Object
{
public:
	bool rva0028F44C(const Object *other) const;
	void *rva0028C197() const;
private:
	unsigned char pad00[4];
	Rva0028F44CTemplateView *m_template;
	unsigned char pad08[0x274 - 8];
	Object *m_owner274;
};
bool Object::rva0028F44C(const Object *other) const
{
	if (!other)
		return false;
	if (!(m_template->kindOf114 & 0x2000))
	{
		const Object *owner = m_owner274;
		if (owner && (owner->m_template->kindOf114 & 0x2000))
			return owner->rva0028F44C(other);
		return false;
	}
	if (!(other->m_template->kindOf114 & 0x2000))
	{
		const Object *owner = other->m_owner274;
		if (!owner || !(owner->m_template->kindOf114 & 0x2000))
			return false;
		other = owner;
	}
	Rva0028F44CHordeView *horde = (Rva0028F44CHordeView *)rva0028C197();
	if (!horde)
		return false;
	return horde->slot147(other);
}
