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

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
typedef bool Bool;

//-------------------------------------------------------------------------------------------------
void Drawable::setFullyObscuredByShroud(Bool fullyObscured)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	if (self->fullyObscuredByShroud != fullyObscured)
	{
		for (DrawModule** dm = ((DrawModule **)m_modules[0]); *dm; ++dm)
		{
			(*dm)->setFullyObscuredByShroud(fullyObscured);
		}
		self->fullyObscuredByShroud = fullyObscured;
		if (!fullyObscured)
			onComingOutOfShroud();
	}
}
