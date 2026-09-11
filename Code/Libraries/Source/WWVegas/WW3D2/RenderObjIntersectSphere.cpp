// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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

// RenderObjClass::Intersect_Sphere at 0x0013BD20, on the bfme2renderobj
// model.  Zero Hour's body: the bounding sphere comes back through the
// virtual accessor and is copied to a local, and the ray test is
// IntersectionClass::Intersect_Sphere, which retail keeps out of line at
// 0x0013B260.

#include "rendobj.h"
#include "intersec.h"

// ?Intersect_Sphere@RenderObjClass@@UAE_NPAVIntersectionClass@@PAVIntersectionResultClass@@@Z present-unmatched
bool RenderObjClass::Intersect_Sphere(IntersectionClass *Intersection, IntersectionResultClass *Final_Result)
{
	SphereClass sphere = Get_Bounding_Sphere();
	return Intersection->Intersect_Sphere(sphere, Final_Result);
}
