// cl: /O1 /DNDEBUG /MD /EHs-c-
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
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Weapon_computeBonus.cpp.
// Target accesses establish the object mask +0x380, global bonus set +0xAD0,
// and template bonus set +0xE0; field meanings follow the donor operation.
typedef unsigned int UnsignedInt;
typedef UnsignedInt WeaponBonusConditionFlags;
typedef float Real;
class Object
{
public:
	char m_pad[0x380];
	UnsignedInt m_weaponBonusCondition;
};
class WeaponBonus
{
public:
	__forceinline void clear()
	{
		for (int i = 0; i < 6; ++i)
			m_fields[i] = 1.0f;
	}
	Real m_fields[6];
};
class WeaponBonusSet
{
public:
	void appendBonuses(UnsignedInt flags, WeaponBonus &bonus) const;
};
class GlobalData
{
public:
	char m_pad[0xAD0];
	WeaponBonusSet *m_weaponBonusSet;
};
extern GlobalData *TheGlobalData;
class WeaponTemplate
{
public:
	char m_pad[0xE0];
	WeaponBonusSet *m_extraBonus;
};
class Weapon
{
protected:
	void computeBonus(const Object *source, WeaponBonusConditionFlags extra, WeaponBonus &bonus) const;
private:
	char m_pad[4];
	WeaponTemplate *m_template;
};

void Weapon::computeBonus(const Object *source, WeaponBonusConditionFlags extra, WeaponBonus &bonus) const
{
	bonus.clear();
	UnsignedInt flags = source->m_weaponBonusCondition | extra;
	WeaponBonusSet *global = TheGlobalData->m_weaponBonusSet;
	if (global)
		global->appendBonuses(flags, bonus);
	WeaponBonusSet *own = m_template->m_extraBonus;
	if (own)
		own->appendBonuses(flags, bonus);
}
