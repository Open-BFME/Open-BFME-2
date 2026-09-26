// cl: /O2 /MD /arch:SSE
// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath/
// sphere.h, vector3.h and wwmath.h. Matched target Init/ctor corroborate the
// center/radius offsets; caller 0x19E2A3 (HLodClass::Update_Obj_Space_Bounding_Volumes)
// uses this operation to enclose each sub-object sphere.
// sqrt/sqrtf and intrinsic variants do not match the target x87 shape;
// retain the donor fsqrt helper for this code-generation blocker (same as
// SphereClassReCenter.cpp).
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
    __forceinline friend Vector3 operator-(const Vector3& a, const Vector3& b) {
        return Vector3(a.X-b.X, a.Y-b.Y, a.Z-b.Z);
    }
    __forceinline friend Vector3 operator*(const Vector3& a, float k) {
        return Vector3(a.X*k, a.Y*k, a.Z*k);
    }
    __forceinline friend Vector3 operator+(const Vector3& a, const Vector3& b) {
        return Vector3(a.X+b.X, a.Y+b.Y, a.Z+b.Z);
    }
};
class SphereClass {
public:
    Vector3 Center;
    float Radius;
    __forceinline void Init(const Vector3& pos, float radius) {
        Center = pos;
        Radius = radius;
    }
    void Add_Sphere(const SphereClass& s);
};
void SphereClass::Add_Sphere(const SphereClass& s)
{
    if (s.Radius == 0.0f) return;

    Vector3 diff = s.Center - Center;
    float dist = diff.Length();
    if (dist == 0.0f) {
        Radius = (Radius > s.Radius) ? Radius : s.Radius;
        return;
    }

    float rnew = (dist + Radius + s.Radius) / 2.0f;

    // If rnew is smaller than either of the two sphere radii (it can't be
    // smaller than both of them), this means that the smaller sphere is
    // completely inside the larger, and the result of adding the two is
    // simply the larger sphere. If rnew isn't less than either of them, it is
    // the new radius - calculate the new center.
    if (rnew < Radius) {
        // The existing sphere is the result - do nothing.
    } else {
        if (rnew < s.Radius) {
            // The new sphere is the result:
            Init(s.Center, s.Radius);
        } else {
            // Neither sphere is completely inside the other, so rnew is the new
            // radius - calculate the new center
            float lerp = (rnew - Radius) / dist;
            Vector3 center = diff * lerp + Center;
            Init(center, rnew);
        }
    }
}
