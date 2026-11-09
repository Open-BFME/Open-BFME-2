// cl: /MD
// ??0W3DGlowOutlineMaterialPassClass@@QAE@HM@Z @0x0073F85D 56B.
// Ctor of W3DGlowOutlineMaterialPassClass: base ctor row 0x0013EDD0
// then int +0x38, float +0x3C, zero +0x40/+0x44, inc g_bfmeCountAtE1F290.
// Evidence: unlock lane packet; vtable 0x008F1544; callers 0x00362C1E/0x00362C75.
#include "../../Include/Common/W3DGlowOutlineMaterialPassClass.h"
extern int g_bfmeCountAtE1F290;
W3DGlowOutlineMaterialPassClass::W3DGlowOutlineMaterialPassClass(int color, float extrusion)
{
    m_base = color;
    m_extrusion = extrusion;
    m_state = 0;
    m_fade = 0.0f;
    ++g_bfmeCountAtE1F290;
}
