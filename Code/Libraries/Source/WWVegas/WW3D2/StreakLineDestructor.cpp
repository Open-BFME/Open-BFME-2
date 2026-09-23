// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil
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
class Vector4 { public: Vector4() {} float X, Y, Z, W; };

template<class T> class SimpleVecClass {
public:
    __forceinline virtual ~SimpleVecClass() {
        if (Vector) {
            delete[] Vector;
            Vector = NULL;
            VectorMax = 0;
        }
    }
protected:
    T *Vector;
    int VectorMax;
};

template<class T> class SimpleDynVecClass : public SimpleVecClass<T> {
public:
    __forceinline virtual ~SimpleDynVecClass() {
        if (this->Vector) {
            delete[] this->Vector;
            this->Vector = NULL;
        }
    }
protected:
    int ActiveCount;
};

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
StreakLineClass::~StreakLineClass() {}

template class SimpleDynVecClass<Vector4>;
