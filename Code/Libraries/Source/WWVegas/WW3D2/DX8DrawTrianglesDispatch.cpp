// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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
// BFME1 DX8Wrapper::Draw_Triangles donor, adapted to target 1205B0.
// Buffer types 1/3 use sorting; other types draw indexed triangle lists.
#include "TargetCenter3.h"
// Address-derived local ABI name: retail 0x12FE00 consumes center xyz and four
// DWORD ranges. The donor SphereClass spelling is not asserted for this target.
#include "BfmeSortingDispatchAt0012FE00.h"
#include "DX8WrapperClass.h"
void DX8Wrapper::Draw_Triangles(unsigned buffer_type, unsigned start,
    unsigned polygons, unsigned minimum, unsigned vertices)
{
    if (buffer_type == 1 || buffer_type == 3) {
        TargetCenter3 center(0.0f, 0.0f, 0.0f);
        BfmeSortingDispatchAt0012FE00::Insert(center, start, polygons, minimum, vertices);
    } else {
        Draw(4, start, polygons, minimum, vertices, true);
    }
}
