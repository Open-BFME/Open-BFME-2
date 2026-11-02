// Target facts: W3DShadowManager has no virtual functions or base subobject.
// Retail constructor RVA 0x0009A710 stores no vptr: 0x0009A733 clears +8,
// 0x0009A73A sets +4 to 0x7FA0A0A0, and 0x0009A741 clears byte +0.
// The allocation at 0x00091B7C requests 0x18 bytes; 0x00091B91 constructs
// that object and 0x00091B9F publishes it as TheW3DShadowManager (VA 0xDE5DFC).
// 0x0009A72A places one 12-byte light element at +0x0C; 0x0009A7EB through
// 0x0009A7F4 write its three floats. 0x0009A497 returns this+12+index*12.
// Its array-constructor callback is the rowed Rva0009A710LightPosition
// constructor at RVA 0x0047A6A9; its original type name is unknown.
// 0x0009A59C, 0x0009A5A6 and 0x0009A5B0 store light coordinates at +0xC/10/14.
// Destructor RVA 0x0009A500 stores no table and discards its incoming this;
// its virtual call at 0x0009A54D uses the submanager from VA 0xDEC2D8.
// The deleting wrapper at 0x00091ACE calls that destructor directly.
// Rowed methods: ReAcquireResources 0x0009A383, rva0009A254 0x0009A254,
// rva0009A348 0x0009A348, invalidateCachedLightPositions 0x0009A478,
// getLightPosWorld 0x0009A497. The constructor calls setLightPosition
// 0x0009A587, currently rowed as W3DGameClientShadowShim::setLightPosition.
// reset at 0x00091CC8 calls 0x0009A2CD with this = TheW3DShadowManager;
// the ledger spells that body Rva0009A2CDRun and retains the member pin.
// 0x0009A354 tests byte +0; 0x000F08E7 reads color +4; 0x000F0896 reads
// mask +8. Zero Hour W3DShadow.h supplies the scene, color and mask names
// and their inline accessors. The light element inherits registered Coord3D.
// addShadow at RVA 0x0009A8D3 requires Shadow::ShadowTypeInfo; a shared
// Shadow definition is needed before that nested-type declaration can be added.
#pragma once

#ifndef BFME2_W3D_SHADOW_MANAGER_H
#define BFME2_W3D_SHADOW_MANAGER_H

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class RenderInfoClass;
class Vector3;

struct Rva0009A710LightPosition : Coord3D
{
    __declspec(noinline) Rva0009A710LightPosition();
};

class W3DShadowManager
{
public:
    W3DShadowManager();
    ~W3DShadowManager();
    bool ReAcquireResources();
    bool rva0009A254();
    void rva0009A2CD();
    void rva0009A348(RenderInfoClass &rinfo);
    void invalidateCachedLightPositions();
    Vector3 &getLightPosWorld(int lightIndex);
    void setLightPosition(int lightIndex, float x, float y, float z);

    void queueShadows(bool state) { m_isShadowScene = state; }
    bool isShadowScene() { return m_isShadowScene; }
    void setShadowColor(unsigned int color) { m_shadowColor = color; }
    unsigned int getShadowColor() { return m_shadowColor; }
    void setStencilShadowMask(int mask) { m_stencilShadowMask = mask; }
    int getStencilShadowMask() { return m_stencilShadowMask; }
    int getStencilShadowMask() const { return m_stencilShadowMask; }

    bool m_isShadowScene;
    unsigned int m_shadowColor;
    int m_stencilShadowMask;
    Rva0009A710LightPosition m_lightPos[1];
};

extern W3DShadowManager *TheW3DShadowManager;

#endif
