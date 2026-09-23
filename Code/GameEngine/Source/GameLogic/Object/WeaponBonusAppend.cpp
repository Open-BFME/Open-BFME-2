// cl: /O1 /arch:SSE /DNDEBUG /MD /EHs-c-
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
// Donor operations: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp.
// Target code combines six floats per bonus and selects 22 entries at stride 0x18.
// The independently identified Weapon::computeBonus caller applies both sets.
typedef unsigned int WeaponBonusConditionFlags;
class WeaponBonus
{
public:
	void appendBonuses(WeaponBonus &bonus) const;
	float m_field[6];
};
void WeaponBonus::appendBonuses(WeaponBonus &bonus) const
{
	for (int f = 0; f < 6; ++f)
		bonus.m_field[f] += this->m_field[f] - 1.0f;
}
class WeaponBonusSet
{
public:
	void appendBonuses(WeaponBonusConditionFlags flags, WeaponBonus &bonus) const;
	WeaponBonus m_bonus[22];
};
void WeaponBonusSet::appendBonuses(WeaponBonusConditionFlags flags, WeaponBonus &bonus) const
{
	if (flags == 0)
		return;
	for (int i = 0; i < 22; ++i)
	{
		if ((flags & (1 << i)) == 0)
			continue;
		this->m_bonus[i].appendBonuses(bonus);
	}
}
