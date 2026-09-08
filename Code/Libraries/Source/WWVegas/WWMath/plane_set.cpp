// cl: /Ireference/shims/bfmefrustum /Ireference/shims/bfmerendobj /G7 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /O1
/*
**	Command & Conquer Generals(tm)
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

#include "../../../../../reference/shims/bfmefrustum/plane.h"
void PlaneClass::Set(const Vector3 & point1, const Vector3 & point2, const Vector3 & point3) 
{
#ifdef ALLOW_TEMPORARIES
	N = Vector3::Cross_Product((point2 - point1), (point3 - point1));
#else
	Vector3::Cross_Product((point2 - point1), (point3 - point1), &N);
#endif
	if (N != Vector3(0.0f, 0.0f, 0.0f)) {
		// Points are not colinear. Normalize N and calculate D.
		N.Normalize();
		D = Vector3::Dot_Product(N, point1);
	} else {
		// They are colinear - return default plane (constructors can't fail).
		N = Vector3(0.0f, 0.0f, 1.0f);
		D = 0.0f;
	}
}
