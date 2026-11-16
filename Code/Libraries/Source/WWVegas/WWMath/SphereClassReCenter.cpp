// cl: /Oy-
// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath/
// sphere.h, vector3.h and wwmath.h. Matched target Init/ctor corroborate the
// center/radius offsets; caller 0x72256 uses this operation on a sphere copy.
// Re_Center identity follows donor geometry and the target call context.
// sqrt/sqrtf and intrinsic variants do not match the target x87 shape;
// retain the donor fsqrt helper for this code-generation blocker.
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
class WWMath { public: __forceinline static float Sqrt(float val) {
    float retval;
    __asm { fld val
        fsqrt
        fstp retval }
    return retval;
} };
#include "Vector3Data.h"
static __forceinline float reCenterLength(const Vector3 &v) { return WWMath::Sqrt(v.Length2()); }
__declspec(dllimport) __forceinline Vector3 operator-(const Vector3& a, const Vector3& b) {
    return Vector3(a.X-b.X, a.Y-b.Y, a.Z-b.Z);
}
#include "SphereClass.h"
void SphereClass::Re_Center(const Vector3& center) {
    float dist = reCenterLength(Center - center);
    Center = center;
    Radius += dist;
}
