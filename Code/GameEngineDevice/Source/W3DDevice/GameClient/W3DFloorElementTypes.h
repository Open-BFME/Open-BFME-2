#pragma once
// Byte-proven target floor storage helpers; BFME1 6c1e0b51 semantics,
// target E4F20/E5033 and WB880EC0/881140 supply the physical layout.
#include "ascii_string.h"
class TextureBaseClass { public: void Release_Ref(); };
struct FloorTextureRef {
    TextureBaseClass *pointer;
    FloorTextureRef() : pointer(0) {}
    ~FloorTextureRef() { if (pointer) pointer->Release_Ref(); }
};
class Rva000E4567 { public: void rva000E4567(); };
// Native E4F20's array iterator constructs three 16-byte matrix rows at
// +50 using the same empty constructor at 47A6A9 that retail folds with its
// coordinate default constructors. This neutral row type preserves original
// typedef uncertainty. Its complete three-byte body has no relocations.
// WB 880EC0 independently witnesses the three rows and the identity stores.
struct FloorMatrixRow {
    float x,y,z,w;
    __declspec(noinline) FloorMatrixRow();
    void set(float a,float b,float c,float d) { x=a; y=b; z=c; w=d; }
};
struct FloorMatrix {
    FloorMatrixRow rows[3];
    __forceinline FloorMatrix() { rows[0].set(1,0,0,0); rows[1].set(0,1,0,0); rows[2].set(0,0,1,0); }
};
struct FloorSphere {
    float x,y,z,radius;
    FloorSphere() : x(0), y(0), z(0), radius(1) {}
};
