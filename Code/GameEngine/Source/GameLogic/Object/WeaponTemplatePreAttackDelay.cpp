// cl: /DNDEBUG /MD /EHs-c-
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Donor: ZH GeneralsMD Weapon.h / Weapon.cpp getPreAttackDelay.
// The original method name is unproved; retain an address-derived name.
// Native bonus-name table VA0xDBC71C independently proves PRE_ATTACK index4.
// Retail interval RVA0x002C93DF/24B ends at the next getter0x002C93F7.
// Retail FieldParse table proves m_preAttackDelay at +0x138 (entry at
// VA 0x00C00F38: name PreAttackDelay, parse INI::parseDurationUnsignedInt,
// offset 0x138; twins validate table method via 0x002C9055/0x002C9136).
// Bonus PRE_ATTACK is field 4 (+0x10); RATE_OF_FIRE at +0x0C proven by
// landed clip/delay siblings in same family. Direct donor reuse first.
typedef int Int;
typedef float Real;
class WeaponBonus
{
public:
	enum Field { DAMAGE = 0, RADIUS, RANGE, RATE_OF_FIRE, PRE_ATTACK };
	Real getField(Field field) const { return m_field[field]; }
	Real m_field[6];
};
class Weapon;
class WeaponTemplate
{
	friend class Weapon;
public:
	Int rva002C93DF(const WeaponBonus &bonus) const;
private:
	char m_pad00[0x138];
	Int m_preAttackDelay;
	char m_pad13C[0x144 - 0x13C];
	Int m_firingDuration; // +0x144: FieldParse FiringDuration at RVA0x00800E98
};
Int WeaponTemplate::rva002C93DF(const WeaponBonus &bonus) const
{
	return m_preAttackDelay * bonus.getField(WeaponBonus::PRE_ATTACK);
}

// Native RVA0x002C9D3B..0x002C9D47 (12 bytes, RET8). The independently
// decoded adjustAnimation caller at RVA0x000BF725 obtains this receiver
// from Object::getCurrentWeapon, pushes the source Object and a zero word,
// and adds the integer result to Weapon::getPreAttackDelay. The native
// FieldParse entry at RVA0x00800E98 names template offset0x144 FiringDuration
// and uses INI::parseDurationUnsignedInt. Original method spelling and the
// second argument's semantic type remain unknown; retain an address name
// and a raw32 unused slot. Weapon::m_template at+4 is independently proven
// by the already matched WeaponGetPreAttackDelay and reload consumers.
class Object;
class Weapon
{
public:
	Int rva002C9D3B(const Object *source, unsigned rawUnused) const;
private:
	char m_pad00[4];
	const WeaponTemplate *m_template;
};
Int Weapon::rva002C9D3B(const Object *, unsigned) const
{
	return m_template->m_firingDuration;
}
