// cl: /arch:SSE /Oy- /O1
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
class Vector3 {
public:
    float X, Y, Z;
    __forceinline Vector3(void) {}
    __forceinline Vector3(const Vector3& v) { X=v.X; Y=v.Y; Z=v.Z; }
    __forceinline Vector3(float x, float y, float z) { X=x; Y=y; Z=z; }
    __forceinline Vector3& operator=(const Vector3& v) { X=v.X; Y=v.Y; Z=v.Z; return *this; }
    __forceinline float Length() const { return WWMath::Sqrt(Length2()); }
    __forceinline float Length2() const { return X*X + Y*Y + Z*Z; }
};
__forceinline Vector3 operator-(const Vector3& a, const Vector3& b) {
    return Vector3(a.X-b.X, a.Y-b.Y, a.Z-b.Z);
}
class SphereClass {
public:
    Vector3 Center;
    float Radius;
    void Re_Center(const Vector3& center);
};
void SphereClass::Re_Center(const Vector3& center) {
    float dist = (Center - center).Length();
    Center = center;
    Radius += dist;
}
