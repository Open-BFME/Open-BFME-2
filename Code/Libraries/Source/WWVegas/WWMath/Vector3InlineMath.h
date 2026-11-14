// Vector3InlineMath.h: the inline Vector3 members whose bodies Vector3Data.h cannot carry.
//
// Why a separate header: Normalize needs WWMath::Inv_Sqrt (WWMathClass.h). Including it, or <math.h> for
// Rotate_Z(angle)'s sinf/cosf, in Vector3Data.h broke 25 of its 260 dependents, which keep private WWMath views
// or math declarations (C2011, C2375, C2084). The const subscript is here too: Matrix3D_Set_Matrix3_Vector3.cpp,
// which includes Vector3Data.h, owns its rowed out-of-line copy 0x004047D9 and emits it from its own `inline`
// definition, so Vector3Data.h keeps it a declaration. Include this header only in units that call these members.
// It includes nothing but Vector3Data.h: the including unit must already declare a WWMath with Inv_Sqrt
// (WWMathClass.h or its own view of it). Including that here would collide with the private views the units that
// need Normalize keep, as W3DBridgeBuffer.cpp's does (C2011). Rotate_Z(angle) is not here yet: its body needs
// sinf/cosf in every includer, and its one caller among the units that keep a private Vector3
// (MineshaftPortalBehaviour.cpp) has not adopted Vector3Data.h; it comes with that adoption.
//
// Target facts (BFME 2 1.06, RVAs): retail inlines all three at their call sites. W3DBridge::getBridgeInfo
// 0x000DDB94 calls WWMath::Inv_Sqrt 0x0004233A and scales X, Y and Z in place (Normalize). The const subscript
// returns the float (FLD), as the rowed copy 0x004047D9 does. No matched row of the units that include
// Vector3Data.h, or of the units that keep a private Vector3, calls the rowed out-of-line copies (Normalize
// 0x0006924F, const subscript 0x004047D9).
// Donor facts: the bodies are Zero Hour's vector3.h (WWINLINE, __forceinline under MSVC); the const subscript is
// the one its owner already uses.

#pragma once

#ifndef VECTOR3INLINEMATH_H
#define VECTOR3INLINEMATH_H

#include "Vector3Data.h"

__forceinline void Vector3::Normalize()
{
    float len2 = Length2();
    if (len2 != 0.0f) {
        float oolen = WWMath::Inv_Sqrt(len2);
        X *= oolen;
        Y *= oolen;
        Z *= oolen;
    }
}

inline float Vector3::operator[](int index) const
{
    return (&X)[index];
}

#endif // VECTOR3INLINEMATH_H
