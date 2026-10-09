#pragma once
// Shared 0xA0 target floor element: layout validated by the complete
// 275-byte constructor, 104-byte destructor and independent EH checks.
// Original class identity remains represented by its existing neutral name.
#include "W3DFloorElementTypes.h"
class Gen_uw_000e5033 {
public:
    Gen_uw_000e5033();
    ~Gen_uw_000e5033();
    bool load();
    friend class W3DFloorBuffer;
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
typedef char FloorElementExtentShared[(sizeof(Gen_uw_000e5033)==0xa0)?1:-1];
