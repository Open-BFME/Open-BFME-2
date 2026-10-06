// cl: /DNDEBUG /MD
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

// Drawable::setFullyObscuredByShroud, ported from Zero Hour's
// GameEngine/Source/GameClient/Drawable.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference) onto the BFME 2 layout: the draw
// module array at +0x14C (read inline, as Drawable.cpp's own getDrawModules
// is) and m_drawableFullyObscuredByShroud at +0x440. Each module's override
// is DrawModule vslot 35. When a drawable comes out of the shroud BFME 2
// also runs a Drawable member at 0x0027893E (747B, identity open; it walks
// the controlling player's objects and castle modules).

typedef bool Bool;

class DrawModule
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34();
	virtual void setFullyObscuredByShroud( Bool fullyObscured );								///< slot 35
};

class Drawable
{
public:
	void setFullyObscuredByShroud( Bool fullyObscured );
	DrawModule **getDrawModules( void ) { return m_drawModules; }
private:
	void onComingOutOfShroud( void );

	char m_unrecovered000[ 0x14C ];
	DrawModule **m_drawModules;																								///< 0x14C
	char m_unrecovered150[ 0x440 - 0x150 ];
	Bool m_drawableFullyObscuredByShroud;																			///< 0x440
};

//-------------------------------------------------------------------------------------------------
void Drawable::setFullyObscuredByShroud(Bool fullyObscured)
{
	if (m_drawableFullyObscuredByShroud != fullyObscured)
	{
		for (DrawModule** dm = getDrawModules(); *dm; ++dm)
		{
			(*dm)->setFullyObscuredByShroud(fullyObscured);
		}
		m_drawableFullyObscuredByShroud = fullyObscured;
		if (!fullyObscured)
			onComingOutOfShroud();
	}
}
