/* Target facts (code addresses are RVAs; table addresses are VAs):
 * 0x0006DD6F calls LightClass(POINT), 0x00130AC0, then stores 0x00BC6038
 * at +0 and 0x00BC6034 at +8. The destructor at 0x0006DD51 (rowed as
 * Rva006DD51) stores these same tables and tail-calls ~LightClass, 0x00130E80,
 * which restores 0x00BD23C0/0x00BD23BC before ~RenderObjClass, 0x0013BE20.
 * 0x0006DE21 calls 0x0006DD51; 0x0006DD67 adjusts this by -8 to 0x0006DE21.
 * 0x0006F94A allocates 0x174 bytes and calls 0x0006DD6F. LightClass's Clone,
 * 0x00130EA0, allocates 0x120 bytes; its constructor's fields start at +0xC4.
 * The leaf table has 130 code entries: slot 1 is 0x0006DE21 and slot 13 is
 * On_Frame_Update, 0x0006DE3D. Only these differ from LightClass's table.
 * RenderObjClass supplies slots 0..128; LightClass adds Is_Vertex_Processor
 * at 129 (0x0050B5C6). LightClass's slots 2/26/27/67/68 are its rowed Clone,
 * Notify_Added/Removed and object-space bounds. Both classes are polymorphic.
 * 0x0006DD6F writes priorEnable +0x120, bounds +0x124..0x140, enabled +0x144,
 * decay flags +0x145/146, counters +0x148..0x154, range +0x158 and colors
 * +0x15C/+0x168; it leaves +0x121..0x123 untouched. 0x0006DF81 copies
 * Ambient +0xD4, Diffuse +0xE0 and range
 * +0x104 into those targets; 0x0006DE3D reads and updates the same fields.
 * setEnabled/isEnabled are rowed at 0x00042F30/0x0006E298 and stay out of line.
 * LightClass's Set_Ambient/Set_Diffuse/Set_Far_Attenuation_Range are rowed at
 * 0x00042EBD/0x00042EDA/0x00042F14; 0x000CF91D uses those same field offsets.
 * Donor names: Zero Hour W3DDynamicLight.h and WW3D2/light.h. Its member order
 * agrees after the retail RenderObjClass's 0xC4 bytes; its extra Persist base
 * and Get_Factory/Save/Load virtual slots are absent from these retail tables.
 */
#pragma once

#ifndef BFME2_W3DDYNAMICLIGHTCLASS_H
#define BFME2_W3DDYNAMICLIGHTCLASS_H

#include "../../../../Libraries/Source/WWVegas/WW3D2/LightClass.h"

class W3DDynamicLight : public LightClass
{
public:
    W3DDynamicLight();
    virtual ~W3DDynamicLight();
    virtual void On_Frame_Update();
    void setEnabled(bool enabled);
    bool isEnabled();
    void setFrameFade(unsigned int frameIncreaseTime, unsigned int decayFrameTime);

    bool m_priorEnable;
    int m_prevMinX;
    int m_prevMinY;
    int m_prevMaxX;
    int m_prevMaxY;
    int m_minX;
    int m_minY;
    int m_maxX;
    int m_maxY;
    bool m_enabled;
    bool m_decayRange;
    bool m_decayColor;
    unsigned int m_curDecayFrameCount;
    unsigned int m_curIncreaseFrameCount;
    unsigned int m_decayFrameCount;
    unsigned int m_increaseFrameCount;
    float m_targetRange;
    Vector3 m_targetAmbient;
    Vector3 m_targetDiffuse;
};

typedef char BFME2LightClassSizeCheck[sizeof(LightClass) == 0x120 ? 1 : -1];
typedef char BFME2W3DDynamicLightSizeCheck[sizeof(W3DDynamicLight) == 0x174 ? 1 : -1];

#endif
