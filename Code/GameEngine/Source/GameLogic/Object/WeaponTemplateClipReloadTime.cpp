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
// Donor: BFME 1 GameEngine/Source/GameLogic/Object/Weapon.cpp.
// Target reloadWithBonus calls this with its WeaponTemplate receiver and bonus.
// Retail reads min/max at E8/EC and rate-of-fire bonus at 0C; its random-call
// diagnostic fixes the donor file and line. The full ret4 ends at RVA 2C93DF.
#include <math.h>
typedef int Int;
typedef float Real;
class WeaponBonus
{
public:
	enum Field { DAMAGE = 0, RADIUS, RANGE, RATE_OF_FIRE };
	Real getField(Field field) const { return m_field[field]; }
	Real m_field[6];
};
class WeaponTemplate
{
public:
	Int getClipReloadTime(const WeaponBonus &bonus) const;
private:
	char m_pad00[0xE8];
	Int m_minClipReloadTime;
	Int m_maxClipReloadTime;
};
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
// Upstream basetype.h x87 conversion. Cast/floor, roundf, and SSE intrinsic
// trials differed; the target uses this fld/fistp sequence after floor.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
Int WeaponTemplate::getClipReloadTime(const WeaponBonus &bonus) const
{
	Int reloadTime;
	if (m_minClipReloadTime == m_maxClipReloadTime)
		reloadTime = m_minClipReloadTime;
	else
		reloadTime = GetGameLogicRandomValue(m_minClipReloadTime, m_maxClipReloadTime,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp", 1006);
	reloadTime -= reloadTime % 3;
	return fast_float2long_round((Real)floor((double)((Real)reloadTime / bonus.getField(WeaponBonus::RATE_OF_FIRE))));
}
