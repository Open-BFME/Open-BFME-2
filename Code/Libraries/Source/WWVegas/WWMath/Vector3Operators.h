// Vector3Operators.h: Vector3's free operators (+, -, * both ways, /, ==, !=), inline.
//
// Why a separate header: five units that include Vector3Data.h define these operators themselves, in the forms their
// rows need (Rva0007E6F6Rva0007E6F6.cpp, DockUpdateComputeApproachPosition.cpp, BaseHeightMapGetMaximumVisibleBox.cpp,
// W3DDynamicLightSetFrameFade.cpp, W3DTerrainBackgroundDoPartialUpdate.cpp). Defining them in Vector3Data.h would
// collide with those definitions, and dropping them made Rva0007E6F6Rva0007E6F6.cpp emit unreferenced out-of-line
// copies of a-b and a+b that differ from retail's rows (56 bytes against 55), as select-any COMDATs competing with the
// owner's. Include this header only in units that use the operators and define none of their own.
//
// Target facts (BFME 2 1.06, RVAs): retail's out-of-line copies are rowed with their owners, which do not include this
// header: a-b 0x000659E3 and a+b 0x000663B8 (colmathaabox.cpp), a/k 0x0006E051 (meshgeometry.cpp), != 0x0007B38C
// (frustum.cpp), a*k 0x00066382 (vector3.cpp), k*a 0x0007DFB3 (W3DRoadBuffer.cpp). No matched row of the units that
// include Vector3Data.h, or of the units that keep a private Vector3, calls one of them: retail inlines them.
// Donor facts: the bodies are Zero Hour's vector3.h free operators, WWINLINE (__forceinline under MSVC). Retail imports
// none of them (no decorated Vector3 name in game.dat), so they are not dllimport.

#pragma once

#ifndef VECTOR3OPERATORS_H
#define VECTOR3OPERATORS_H

#include "Vector3Data.h"

__forceinline Vector3 operator*(const Vector3 &a, float k) { return Vector3((a.X * k), (a.Y * k), (a.Z * k)); }
__forceinline Vector3 operator*(float k, const Vector3 &a) { return Vector3((a.X * k), (a.Y * k), (a.Z * k)); }
__forceinline Vector3 operator/(const Vector3 &a, float k)
{
    float ook = 1.0f / k;
    return Vector3((a.X * ook), (a.Y * ook), (a.Z * ook));
}
__forceinline Vector3 operator+(const Vector3 &a, const Vector3 &b) { return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z); }
__forceinline Vector3 operator-(const Vector3 &a, const Vector3 &b) { return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z); }
__forceinline bool operator==(const Vector3 &a, const Vector3 &b) { return ((a.X == b.X) && (a.Y == b.Y) && (a.Z == b.Z)); }
__forceinline bool operator!=(const Vector3 &a, const Vector3 &b) { return ((a.X != b.X) || (a.Y != b.Y) || (a.Z != b.Z)); }

#endif // VECTOR3OPERATORS_H
