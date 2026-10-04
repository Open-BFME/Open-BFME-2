// ?rva0028CE7B@Object@@QAEHXZ
// partial score=0.91 date=2026-10-04
// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0028CE7B@Object@@QAEHXZ @ 0x0028CE7B (84B).
// Object armor-ish getter: pool attribute 0x19 bonus (pinned 0x00403382)
// converted to int, added to template byte 0x5FC (or 0x5FA when 0xFF or
// when bit 22 of +0x124 is clear). Evidence: LINK unlock (9 fns wait);
// callers at 0x00264197, 0x00266962 and 9 more; neighbours share /O1.

typedef float Real;
typedef bool Bool;
typedef int Int;

class AttributeModifierPoolUpdate
{
public:
	Bool rva00403382(Int attribute, Real *value, Int arg);
};

struct ThingTemplate0028CE7B
{
	unsigned char m_pad000[0x5FA];
	unsigned char m_5FA;
	unsigned char m_5FB;
	unsigned char m_5FC;
};

class Object
{
public:
	Int rva0028CE7B();

private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;

	unsigned char m_pad000[4];
	const ThingTemplate0028CE7B *m_template;
	unsigned char m_pad008[0x124 - 0x08];
	unsigned int m_124;
};

// ?rva0028CE7B@Object@@QAEHXZ present-unmatched
Int Object::rva0028CE7B()
{
	Int bonusInt = 0;
	const ThingTemplate0028CE7B *tpl = m_template;
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool)
	{
		Real bonus;
		if (pool->rva00403382(0x19, &bonus, 0))
			bonusInt = (Int)bonus;
	}
	unsigned char base = tpl->m_5FC;
	if (base == 0xFF || (((m_124 >> 0x16) & 1) == 0))
		base = tpl->m_5FA;
	return base + bonusInt;
}
