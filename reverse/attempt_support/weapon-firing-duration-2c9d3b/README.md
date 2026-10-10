# Weapon firing-duration leaf

Retail RVA 0x002C9D3B..0x002C9D47 is a complete 12-byte body: load the
WeaponTemplate pointer at Weapon+4, load its integer at+0x144, RET8.
The preceding body ends RET8 at 0x002C9D38..0x002C9D3B; the next body begins
at 0x002C9D47. There are no relocations in this leaf.

Independent owner/caller evidence: the sole direct call is at0x000BF725 in
W3DScriptedModelDraw::adjustAnimation (whole0x000BEE25..0x000BF7E8). It obtains
its receiver through the actual Object::getCurrentWeapon provider0x0028AEBD,
pushes source Object and zero, invokes this leaf, and adds the returned EAX
integer to Weapon::getPreAttackDelay0x002CCFF0 before signed integer-to-float
conversion for animation timing. No absolute address references were found.

Independent field evidence: retail FieldParse entry0x00800E98 contains the
FiringDuration string at0x00801840, parser0x00338B30
(INI::parseDurationUnsignedInt), null context, and offset0x144. The neighboring
PreAttackDelay entry0x00800F38 names offset0x138, retained by this existing
WeaponTemplate getter home. Established Weapon consumers prove m_template+4.

Unknown original method spelling and the unused second argument's meaning
remain explicit. The method uses an address-derived name, const Object* for
the independently witnessed source pointer, and an unused raw32 argument
slot. No original enum/bool meaning, full Weapon layout, new pin, alias,
synthetic caller, or global name is asserted. The original template getter
and the new method each match their complete native extents (24 and12).

Reference guide: committed BFME1 575ba2b04743f190f069805fbdc59936123c45da
and the ZH Weapon pre-attack getter in the existing source. FiringDuration
is a target-specific addition, established by the retail table and caller.
