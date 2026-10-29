// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Target layout follows the matched StreakLine constructors and assignment.
// Vtable 0xCF1688 selects deleting destructor 0x742570, which calls 0x742590.
// SimpleVec cleanup follows the donor; delete[] is nonthrowing as in the
// matched constructor and renderer units. Personalities is not freed here.
#include "always.h"
void __cdecl operator delete[](void *) throw();

class Vector3 { public: Vector3() {} float X, Y, Z; };
#include "../WWMath/Vector4Data.h"

#include "simplevec.h"

// Bind virtual growth operations to their owned template bodies.
template <> bool SimpleVecClass<Vector3>::Resize(int);
template <> bool SimpleVecClass<Vector3>::Uninitialised_Grow(int);
template <> bool SimpleDynVecClass<Vector3>::Resize(int);
template <> bool SimpleVecClass<Vector4>::Resize(int);
template <> bool SimpleVecClass<Vector4>::Uninitialised_Grow(int);
template <> bool SimpleDynVecClass<Vector4>::Resize(int);
template <> bool SimpleVecClass<float>::Resize(int);
template <> bool SimpleVecClass<float>::Uninitialised_Grow(int);
template <> bool SimpleDynVecClass<float>::Resize(int);

// Inline member cleanup while the shared template supplies all virtual slots.
template <> __declspec(dllimport) __forceinline SimpleVecClass<Vector3>::~SimpleVecClass()
{
    if (Vector) {
        delete[] Vector;
        Vector = NULL;
        VectorMax = 0;
    }
}

template <> __declspec(dllimport) __forceinline SimpleVecClass<Vector4>::~SimpleVecClass()
{
    if (Vector) {
        delete[] Vector;
        Vector = NULL;
        VectorMax = 0;
    }
}

template <> __declspec(dllimport) __forceinline SimpleVecClass<float>::~SimpleVecClass()
{
    if (Vector) {
        delete[] Vector;
        Vector = NULL;
        VectorMax = 0;
    }
}

template <> __forceinline SimpleDynVecClass<Vector3>::~SimpleDynVecClass()
{
    if (Vector) {
        delete[] Vector;
        Vector = NULL;
    }
}

template <> __forceinline SimpleDynVecClass<float>::~SimpleDynVecClass()
{
    if (Vector) {
        delete[] Vector;
        Vector = NULL;
    }
}

class RenderObjClass {
public:
    virtual void Delete_This();
    virtual ~RenderObjClass();
protected:
    unsigned char base_storage[0xC0];
};
class SegLineRendererClass {
public:
    ~SegLineRendererClass();
private:
    unsigned char storage[0x50];
};
class StreakRendererClass {
public:
    ~StreakRendererClass();
private:
    unsigned char storage[0x4C];
};
// The target destructor omits a store of the derived vptr before member cleanup.
class __declspec(novtable) StreakLineClass : public RenderObjClass {
public:
    virtual ~StreakLineClass();
private:
    unsigned int MaxSubdivisionLevels;
    unsigned int *Personalities;
    float NormalizedScreenArea;
    SimpleDynVecClass<Vector3> PointLocations;
    SimpleDynVecClass<Vector4> PointColors;
    SimpleDynVecClass<float> PointWidths;
    SegLineRendererClass LineRenderer;
    StreakRendererClass StreakRenderer;
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline StreakLineClass::~StreakLineClass() {}

// ?bfmeAnchorStreakLineClassDtor absent-from-retail
void bfmeAnchorStreakLineClassDtor(StreakLineClass *streakLine)
{
	streakLine->StreakLineClass::~StreakLineClass();
}

// Emit the owned Vector4 deleting wrapper without unrelated template members.
template SimpleDynVecClass<Vector4>::~SimpleDynVecClass();
