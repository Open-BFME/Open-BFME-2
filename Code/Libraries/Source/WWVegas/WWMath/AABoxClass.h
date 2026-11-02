// Target facts (BFME 2 1.06, addresses are RVAs):
// AABoxClass has no virtual functions or base subobject. Constructors
// 0x00108B65 and 0x0019BF20 write floats at +0/+4/+8 and +0xC/+0x10/+0x14,
// including data at +0, without vtable stores or base-constructor calls.
// Assignment 0x001492E0 and the copy body 0x0009AC04 copy those six words;
// Geometry::setBoundingBox 0x000F0FBD tail-calls 0x0009AC04 at this+0x1C.
// The copy-constructor spelling is pinned to that folded Region3D body.
// Geometry::setBoundingSphere 0x000F0FC5 addresses the next member at +0x34;
// the box spans +0x1C..+0x33, agreeing with sizeof 0x18 and two Vector3s.
// Contains(Vector3) 0x0071AFA0 subtracts +0/+4/+8 from the point and compares
// absolute distances with +0xC/+0x10/+0x14. Project_To_Axis 0x007236F0 reads
// the latter triple as floats. Zero Hour's WWMath/aabox.h names these public
// Vector3 members Center and Extent and declares no bases or virtual methods.
// Rowed methods remain out of line: Init(center,extent) 0x0007E535,
// Init(points,count) 0x00068E76, Init(MinMaxAABoxClass) 0x00068F68,
// Init_Min_Max 0x0007E561, Init_Random 0x00719730,
// Transform(Matrix3D) 0x0013B0F0 and static Transform 0x007197B0,
// plus the constructors, assignment and predicates above.
// Donor facts: Zero Hour's WWMath/aabox.h supplies the empty default
// constructor and the remaining nonvirtual method names and declarations.
// Vector3's registered header supplies the two 12-byte member values.

#pragma once

#ifndef BFME2_AABOXCLASS_H
#define BFME2_AABOXCLASS_H

#include "Vector3Data.h"

class LineSegClass;
class Matrix3D;
class MinMaxAABoxClass;

class AABoxClass
{
public:
    __forceinline AABoxClass() {}
    AABoxClass(const AABoxClass &box);
    AABoxClass(const Vector3 &center, const Vector3 &extent);
    AABoxClass(const MinMaxAABoxClass &box);
    AABoxClass(Vector3 *points, int count);
    AABoxClass &operator=(const AABoxClass &box);
    bool operator==(const AABoxClass &box);
    bool operator!=(const AABoxClass &box);

    void Init(const Vector3 &center, const Vector3 &extent);
    void Init(Vector3 *points, int count);
    void Init(const MinMaxAABoxClass &box);
    void Init(const LineSegClass &line);
    void Init_Min_Max(const Vector3 &minimum, const Vector3 &maximum);
    void Init_Random(float min_center = -1.0f, float max_center = 1.0f,
                     float min_extent = 0.5f, float max_extent = 1.0f);
    void Add_Point(const Vector3 &point);
    void Add_Box(const AABoxClass &box);
    void Add_Box(const MinMaxAABoxClass &box);
    float Project_To_Axis(const Vector3 &axis) const;
    void Transform(const Matrix3D &transform);
    void Translate(const Vector3 &translation);
    float Volume() const;
    bool Contains(const Vector3 &point) const;
    bool Contains(const AABoxClass &box) const;
    bool Contains(const MinMaxAABoxClass &box) const;
    static void Transform(const Matrix3D &transform, const AABoxClass &in, AABoxClass *out);

    Vector3 Center;
    Vector3 Extent;
};

#endif
