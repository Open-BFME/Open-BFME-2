// Target facts (BFME 2 1.06, addresses are RVAs unless marked VA):
// Vector3 has no virtual functions or base subobject: operator= 0x00169FB0
// copies the complete value as three dwords at +0/+4/+8, including +0 as data;
// Length2 0x00711C40 reads those offsets as floats. initFromMesh 0x000F1018
// advances vertex pointers by 12 at 0x000F1143 and 0x000F1155, proving sizeof 12.
// No Vector3 constructor or destructor is rowed, and retail_layout finds no
// constructor/destructor vtable stores or virtual slots for this value class.
// Rowed members: Dot_Product 0x000663EF, Length2 0x00711C40,
// Cross_Product_Z 0x000D46CE, Add 0x0006E090, Subtract 0x0006E0C7,
// Scale(Vector3) 0x0006E0FE, Update_Min 0x000E0E71, Update_Max 0x000E0EA7,
// Normalize 0x0006924F, Length 0x000692B3,
// Normalized_Cross_Product 0x0006A965, Quick_Length 0x0026FDD4,
// Quick_Distance 0x0026FE70, Rotate_Z(float) 0x0008E48C,
// Rotate_Z(float,float) 0x0008E11F, Lerp 0x0009AA48, Distance 0x000CFF7F,
// Find_X_At_Z 0x000852F7 and Find_Y_At_Z 0x00085317. These stay declarations
// so consumers call the rowed bodies without emitting their own copies, except
// Length2, Dot_Product and Rotate_Z(sine, cosine): retail inlines them at their
// call sites. RTS3DScene::rva00072109 0x00072109 computes Dot_Product and
// Length2 inline; MineshaftPortalBehaviour::createWaypoint 0x003738F6 rotates
// inline after calling msvcr71's sin and cos. No matched row of the units that
// include this header calls one of the rowed out-of-line copies. They are
// defined inline here with the bodies of Zero Hour's vector3.h (WWINLINE,
// __forceinline under MSVC); their rowed copies stay with their owners.
// Normalize and Rotate_Z(angle) are inline in retail too, but need
// WWMath::Inv_Sqrt and sinf/cosf, whose headers collide with private views in
// units that include this one; they stay declared here.
// operator= is the exception: its rowed body 0x00169FB0 is a compiler COMDAT
// of Zero Hour's inline assignment (owner matrix3d_inverse.cpp) that nothing in
// retail calls or references, while consumers such as renderSubBox 0x00093507
// copy the three dwords inline, so it is defined inline here.
// CreateBeaconObject 0x00213171 initializes a Vector3 inline at 0x002132CB,
// 0x002132D0 and 0x002132D5, with no constructor call or vptr store.
// updateScorches 0x000678BB copies the scorch location inline; Zero Hour
// supplies the empty default and component-copy/value constructor bodies.
// Unary minus is rowed at 0x0007DF87. The non-const subscript 0x007173D0
// returns the address this+4*index (LEA); the const subscript 0x004047D9
// returns its float value (FLD), unlike Zero Hour's reference-returning const
// overload. Set has no ledger row; its component stores use the same proven
// +0/+4/+8 fields and the body and name in Zero Hour's vector3.h.
// Zero Hour also names the unrowed compound operators; retail's component
// arithmetic in SlaughterHordeContain 0x00463AD3 corroborates scalar scaling.
// Donor facts: Zero Hour's WWMath/vector3.h names public float X/Y/Z and the
// remaining nonvirtual constructors, accessors, operators and math methods;
// its three-float layout agrees with the retail field accesses and stride.

#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
    float X;
    float Y;
    float Z;

    __forceinline Vector3() {}
    __forceinline Vector3(const Vector3 &value) : X(value.X), Y(value.Y), Z(value.Z) {}
    __forceinline Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
    __forceinline Vector3(const float value[3]) : X(value[0]), Y(value[1]), Z(value[2]) {}
    __forceinline Vector3 &operator=(const Vector3 &value) { X = value.X; Y = value.Y; Z = value.Z; return *this; }
    __forceinline void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
    __forceinline void Set(const Vector3 &value) { X = value.X; Y = value.Y; Z = value.Z; }
    float &operator[](int index);
    float operator[](int index) const;

    void Normalize();
    float Length() const;
    __forceinline float Length2() const { return X * X + Y * Y + Z * Z; }
    float Quick_Length() const;
    void Scale(const Vector3 &scale);
    void Rotate_X(float angle);
    void Rotate_X(float sine, float cosine);
    void Rotate_Y(float angle);
    void Rotate_Y(float sine, float cosine);
    void Rotate_Z(float angle);
    __forceinline void Rotate_Z(float sine, float cosine)
    {
        float x = X;
        float y = Y;
        X = cosine * x - sine * y;
        Y = sine * x + cosine * y;
    }

    Vector3 operator-() const;
    Vector3 operator+() const;
    __forceinline Vector3 &operator+=(const Vector3 &value) { X += value.X; Y += value.Y; Z += value.Z; return *this; }
    __forceinline Vector3 &operator-=(const Vector3 &value) { X -= value.X; Y -= value.Y; Z -= value.Z; return *this; }
    __forceinline Vector3 &operator*=(float scale) { X *= scale; Y *= scale; Z *= scale; return *this; }
    __forceinline Vector3 &operator/=(float scale) { float inverse = 1.0f / scale; X *= inverse; Y *= inverse; Z *= inverse; return *this; }

    static __forceinline float Dot_Product(const Vector3 &a, const Vector3 &b)
    {
        return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
    }
    static void Cross_Product(const Vector3 &a, const Vector3 &b, Vector3 *result);
    static void Normalized_Cross_Product(const Vector3 &a, const Vector3 &b, Vector3 *result);
    static float Cross_Product_X(const Vector3 &a, const Vector3 &b);
    static float Cross_Product_Y(const Vector3 &a, const Vector3 &b);
    static float Cross_Product_Z(const Vector3 &a, const Vector3 &b);
    static void Add(const Vector3 &a, const Vector3 &b, Vector3 *result);
    static void Subtract(const Vector3 &a, const Vector3 &b, Vector3 *result);
    static float Find_X_At_Y(float y, const Vector3 &a, const Vector3 &b);
    static float Find_X_At_Z(float z, const Vector3 &a, const Vector3 &b);
    static float Find_Y_At_X(float x, const Vector3 &a, const Vector3 &b);
    static float Find_Y_At_Z(float z, const Vector3 &a, const Vector3 &b);
    static float Find_Z_At_X(float x, const Vector3 &a, const Vector3 &b);
    static float Find_Z_At_Y(float y, const Vector3 &a, const Vector3 &b);
    void Update_Min(const Vector3 &value);
    void Update_Max(const Vector3 &value);
    void Cap_Absolute_To(const Vector3 &value);
    bool Is_Valid() const;
    static float Quick_Distance(const Vector3 &a, const Vector3 &b);
    static float Distance(const Vector3 &a, const Vector3 &b);
    static void Lerp(const Vector3 &a, const Vector3 &b, float alpha, Vector3 *result);
    unsigned long Convert_To_ABGR() const;
    unsigned long Convert_To_ARGB() const;
};

#endif // VECTOR3_H
