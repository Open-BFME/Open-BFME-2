// cl: /Ireference/shims/bfme2renderobj /Ireference/shims/sweep /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
#define Matrix4x4 Matrix4
#include "rendobj.h"
#include "camera.h"
#include "aabox.h"

typedef char RenderObjSizeMatchesRetail[(sizeof(RenderObjClass) == 0xC4) ? 1 : -1];

// Keep the ordinary position helper visible so retail can inline the three
// translation components after virtual transform validation.
// ?Get_Position@RenderObjClass@@QBE?AVVector3@@XZ present-unmatched
inline Vector3 RenderObjClass::Get_Position(void) const
{
    Validate_Transform();
    return Transform.Get_Translation();
}

// Only Camera viewport fields C8..D4 are used here. The complete Camera tail
// layout is not required or asserted by this screen-area calculation.
float RenderObjClass::Get_Screen_Size(CameraClass &camera)
{
	// Currently this works by projecting the bounding sphere to the screen
	// (as if the object was at the center) - in future this may be made more
	// accurate (perhaps by using the object-space bounding-box)
	Vector3 cam = camera.Get_Position();

	ViewportClass viewport = camera.Get_Viewport();
	Vector2 vpr_min, vpr_max;
	camera.Get_View_Plane(vpr_min, vpr_max);
	float width_factor = viewport.Width() / (vpr_max.X - vpr_min.X);
	float height_factor = viewport.Height() / (vpr_max.Y - vpr_min.Y);

	const SphereClass & sphere = Get_Bounding_Sphere();
	float dist = (sphere.Center - cam).Length();
	float radius = 0.0f;
	if (dist) {
		radius = sphere.Radius / dist;
	}

	// Return area in normalized units.
	return WWMATH_PI * radius * radius * width_factor * height_factor;
}
