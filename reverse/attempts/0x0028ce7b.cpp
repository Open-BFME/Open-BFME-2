// ?rva0028CE7B@Object@@QBECXZ
// partial score=0.92 date=2026-10-11
// ?rva0028CE7B@Object@@QBECXZ
// partial score=0.92 date=2026-10-11
// cl: region default
// ?rva0028CE7B@Object@@QBECXZ @0x0028CE7B 84B bank (register-binding near miss)
signed char Object::rva0028CE7B() const
{
	const ObjectCrushLevelsView *tpl = getTemplate();
	float bonus;
	signed char add = 0;
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool && pool->rva00403382(0x19, &bonus, 0))
		add = (signed char)(int)bonus;
	signed char level = tpl->alternateCrushable;
	if (level != -1 && ((unsigned char)(mountedFlags >> 22) & 1) == 0)
		level = tpl->crushable;
	return level + add;
}
