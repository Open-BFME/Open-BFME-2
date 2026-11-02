// Target facts (BFME 2 1.06, addresses are RVAs): SphereClass has no virtual functions or base subobject. Constructor 0x0006A52F stores center data at +0/+4/+8 and a float radius at +0xC; constructor 0x000D4A81 stores the same four floats at 0x000D4E78..0x000D4E90. Neither constructor stores a vptr, and no SphereClass destructor is rowed.
// The complete value is 16 bytes: the folded copy/assignment at 0x0004254E copies four dwords at +0/+4/+8/+0xC, including data at +0. RoadSegment's copy constructor calls it at 0x000D513D and its assignment at 0x000D6E20 for the sphere at +0xAC. MeshGeometryClass::Get_Bounding_Sphere (0x00169370) writes the same four output words. W3DPropBuffer constructs 0x18-byte TPropType elements at 0x000EF071; its 0x000EF0AA..0x000EF0B8 loop writes each sphere at element +8..+0x14 and advances by 0x18 at 0x000EF0BD. Rowed Init (0x00069146), Re_Center (0x0006F400), Transform (0x0019AF20), Add_Sphere (0x0019BE00), both constructors and the folded copy/assignment stay out of line.
// Donor facts: Zero Hour's GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h names the public Vector3 Center and float Radius, declares a plain class without bases or virtuals, and supplies the empty default constructor. Its 16-byte layout agrees with retail's complete-value copies and floating-point accesses.

#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "Vector3Data.h"

class Matrix3D;

class SphereClass
{
public:
    SphereClass() {}
    SphereClass(const SphereClass &sphere);
    SphereClass(const Vector3 &center, float radius);
    SphereClass(const Vector3 *positions, int count);
    SphereClass &operator=(const SphereClass &sphere);

    void Init(const Vector3 &position, float radius);
    void Re_Center(const Vector3 &center);
    void Add_Sphere(const SphereClass &sphere);
    void Transform(const Matrix3D &transform);

    Vector3 Center;
    float Radius;
};

#endif // SPHERE_H
