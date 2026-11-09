// Target facts: retail's table at VA 0x00CF1544 has four slots: Delete_This RVA 0x0006CE57, the deleting destructor
// RVA 0x0073F9F4, Install_Materials RVA 0x0073FA10 and UnInstall_Materials RVA 0x0073F9D1. The constructor RVA 0x0073F85D
// writes +0x38, +0x3C, +0x40 and +0x44 and counts instances at VA 0x00E1F290. The class name is the TU's, not retail's.
#pragma once
#ifndef BFME2_W3DGLOWOUTLINEMATERIALPASSCLASS_H
#define BFME2_W3DGLOWOUTLINEMATERIALPASSCLASS_H

#include "../../../Libraries/Source/WWVegas/WW3D2/MaterialPassClass.h"

class W3DGlowOutlineMaterialPassClass : public MaterialPassClass
{
public:
    W3DGlowOutlineMaterialPassClass(int color, float extrusion);
    virtual ~W3DGlowOutlineMaterialPassClass();

    virtual void Install_Materials() const;
    virtual void UnInstall_Materials() const;

    int UpdateFadeState();

    int m_base;           // +0x38
    float m_extrusion;    // +0x3C
    int m_state;          // +0x40
    float m_fade;         // +0x44
};

#endif
