// cl: /MD /EHs /Ireference/shims/bfme2_ascii
// Complete floor-element cleanup at 0x000E5033 (104 bytes through RET).
// Semantic guide: Open-BFME-1 6c1e0b51, BaseHeightMapFloorElementDestructor.cpp.
// Native and WB 0x881140 prove the two texture handles at +20/+24, strings
// at +8C/+90, and the leading call to the shared E4567 resource cleanup.
// BFME 1's member offsets differ; retain the target's existing unwind-pin
// name rather than asserting its virtual class identity. The target constructor
// starts with sphere floats, and this nonvirtual destructor writes no vptr.
// The four EH states and their cleanup actions are verified independently.
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
FloorMatrixRow::FloorMatrixRow() {}
struct FloorMatrix {
    FloorMatrixRow rows[3];
    __forceinline FloorMatrix() { rows[0].set(1,0,0,0); rows[1].set(0,1,0,0); rows[2].set(0,0,1,0); }
};
struct FloorSphere {
    float x,y,z,radius;
    FloorSphere() : x(0), y(0), z(0), radius(1) {}
};
class Gen_uw_000e5033 {
public:
    Gen_uw_000e5033();
    ~Gen_uw_000e5033();
private:
    FloorSphere m_sphere00;
    float m_sphere10[4];
    FloorTextureRef m_texture20;
    FloorTextureRef m_texture24;
    void *m_render28;
    void *m_drawable2c;
    struct Position { float x,y,z; Position() : x(0),y(0),z(0) {} } m_position30;
    int m_3c,m_40,m_44,m_48,m_id4c;
    FloorMatrix m_matrix50;
    bool m_active80,m_flag81,m_flag82;
    float m_opacity84,m_speed88;
    AsciiString m_name8c,m_name90;
    int m_94,m_state98;
    bool m_flag9c,m_flag9d;
};
Gen_uw_000e5033::~Gen_uw_000e5033() { reinterpret_cast<Rva000E4567 *>(this)->rva000E4567(); }

typedef char FloorRowStride[(sizeof(FloorMatrixRow)==16)?1:-1];
typedef char FloorElementExtent[(sizeof(Gen_uw_000e5033)==0xa0)?1:-1];
Gen_uw_000e5033::Gen_uw_000e5033() : m_render28(0), m_drawable2c(0), m_3c(0),m_40(0),m_44(0),m_48(0),m_id4c(0), m_active80(false),m_flag81(false),m_flag82(false),m_opacity84(1),m_speed88(0),m_94(0),m_state98(0),m_flag9c(false),m_flag9d(false)
{




}

