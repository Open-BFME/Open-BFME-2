// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Target view for the donor StreakLine setter bodies.
// The target RenderObj Bits field is at +0x10. Its
// base extent C4, and SimpleDynVec fields at D0/E0/F0 follow matched target
// StreakLine ctor/copy ctor. Target RenderObj cache-valid bit is 0x20000.
#include "always.h"
#include "simplevec.h"
#define WWASSERT(x) ((void)0)

class Vector3 { public: float X, Y, Z; };
class Vector4 { public: float X, Y, Z, W; };

class StreakLineClass {
private:
    unsigned char renderObjPrefix[0x10];
    unsigned int RenderObjBits;
    unsigned char renderObjTail[0xB0];
    unsigned int MaxSubdivisionLevels;
    unsigned int *Personalities;
    float NormalizedScreenArea;
    SimpleDynVecClass<Vector3> PointLocations;
    SimpleDynVecClass<Vector4> PointColors;
    SimpleDynVecClass<float> PointWidths;
    void Invalidate_Cached_Bounding_Volumes() { RenderObjBits &= ~0x00020000u; }
protected:
    void Set_Locs(unsigned int num_points, Vector3 *locs);
    void Set_Widths(unsigned int num_points, float *widths);
    void Set_Colors(unsigned int num_points, Vector4 *colors);
public:
    void Set_LocsWidthsColors(unsigned int num_points, Vector3 *locs, float *widths, Vector4 *colors, unsigned int *personalities);
};

void StreakLineClass::Set_Locs(unsigned int num_points, Vector3 *locs)
{
    if (num_points < 2 || !locs) {
        WWASSERT(0);
        return;
    }
    PointLocations.Delete_All();
    for (unsigned int i = 0; i < num_points; i++) {
        PointLocations.Add(locs[i], num_points);
    }
    Invalidate_Cached_Bounding_Volumes();
}

void StreakLineClass::Set_LocsWidthsColors(unsigned int num_points, Vector3 *locs, float *widths, Vector4 *colors, unsigned int *personalities)
{
    Personalities = personalities;
    Set_Locs(num_points, locs);
    if (widths) {
        Set_Widths(num_points, widths);
        int locCount = PointLocations.Count();
        int widCount = PointWidths.Count();
        WWASSERT(locCount == widCount);
    }
    if (colors) {
        Set_Colors(num_points, colors);
        int locCount = PointLocations.Count();
        int colCount = PointColors.Count();
        WWASSERT(locCount == colCount);
    }
    Invalidate_Cached_Bounding_Volumes();
}
