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
// Donor: BFME 1 GameLogic/Object/Weapon.cpp, minimum range query.
// Target callers 0x2C9B05/0x2C9B44 load Weapon::m_template at +4.
// Retail reads the range at +0x18 and subtracts 2.5f (VA 0xBCFB10);
// the quarter-cell interpretation follows the donor.
typedef float Real;
class WeaponTemplate
{
public:
    Real getMinimumAttackRange() const;
private:
    char m_pad00[0x18];
    Real m_minimumAttackRange;
};
#define PATHFIND_CELL_SIZE_F 10.0f
Real WeaponTemplate::getMinimumAttackRange() const
{
    const Real UNDERSIZE = PATHFIND_CELL_SIZE_F * 0.25f;
    Real r = m_minimumAttackRange - UNDERSIZE;
    if (r < 0.0f) r = 0.0f;
    return r;
}
