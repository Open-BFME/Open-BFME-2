// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c-
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
// ?parseWeaponBonusSet@WeaponBonusSet@@QAEXPAVINI@@@Z 0x002C971E 90B
// Donor: ZH/BFME1 Weapon.cpp WeaponBonusSet::parseWeaponBonusSet (scanIndexList+scanPercentToReal).
// BFME2 deltas: INI members via ecx (getNextToken/scanIndexList/dup_002EE10 scanReal*0.01),
// 22 conditions x 6 fields (tables 0x00DBC6C0 TheWeaponBonusNames 22+NULL,
// 0x00DBC71C fields DAMAGE RADIUS RANGE RATE_OF_FIRE PRE_ATTACK FIRING+NULL).
// Callers: static wrappers 0x002CA80E (store) and 0x002CA81C (ptr deref) plus
// WeaponTemplate alloc 0x002CA88B size 0x210 (22*0x18) calling with [esi+0xE0].
// Gap between appendBonuses 0x002C96F7 and 0x002C9778 in WeaponBonusAppend.cpp;
// needs /G7 for imul 6 (plain /O1 emits lea).
typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;
class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, ConstCharPtrArray nameList);
	float dup_002EE10(const char *token);
};
class WeaponBonus
{
public:
	float m_field[6];
};
class WeaponBonusSet
{
public:
	void parseWeaponBonusSet(INI *ini);
	WeaponBonus m_bonus[22];
};
void WeaponBonusSet::parseWeaponBonusSet(INI *ini)
{
	int wb = ini->scanIndexList(ini->getNextToken(0), reinterpret_cast<ConstCharPtrArray>(0x00DBC6C0));
	int wf = ini->scanIndexList(ini->getNextToken(0), reinterpret_cast<ConstCharPtrArray>(0x00DBC71C));
	m_bonus[wb].m_field[wf] = ini->dup_002EE10(ini->getNextToken(0));
}
