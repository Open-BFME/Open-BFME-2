// Target facts (game.dat, RVAs unless marked VA): factory 0x00064DF7 pushes sizeof 0x20 at 0x00064E02 and calls ctor 0x000CF91D at 0x00064E1E. The ctor calls DrawModule 0x000B19A1 at 0x000CF938 and installs VA 0x00BCD728 at 0x000CF944. Dtor 0x000CFA42 restores that table at 0x000CFA53, then VA 0x00BC9690 at 0x000CFA81 before calling 0x0049B47C at 0x000CFA87: the latter table belongs to base teardown. Deleting dtor 0x000CFBF0 calls 0x000CFA42. This is a polymorphic DrawModule, whose inherited storage ends at +0x0C.
// Target facts: VA 0x00BCD728 has 62 slots, ending at the ModuleData table VA 0x00BCD820. It differs from DrawModule VA 0x00BC9690 only at slots 0/1/2/3/4/11/12/13/14/16/35/38/39: 0x000CFBF0/0x0058B03E/0x000CFA3C/0x000CFAB1/0x000CFAF9/0x000CFC0C/0x0047A69C/0x000B3FD0/0x000B3FD0/0x000CFA99/0x0047A69C/0x000CFDFB/0x000B3FD0. The parent supplies the slot names; the ledger names the draw, transform, transfer, key and destructor bodies. Getter 0x000CFA3C and key 0x000CFAF9 reference VA 0x00BC5B78, "W3DLightDraw". The getter's ledger spelling is nonvirtual name(); slot 16's ledger spelling rva000CFA99 would append a virtual slot and is not the inherited setHidden spelling.
// Target facts: ctor stores a dynamic-light pointer at +0x0C at 0x000CF974 after calling 0x0006F94A, and four-byte floats at +0x10/+0x14/+0x18/+0x1C at 0x000CF964/0x000CF94A/0x000CF94F/0x000CF954. Transfer 0x000CFAB1 passes those four float addresses to Xfer slot +0x70. Original field names are unproved. Static factories are ledger rows 0x00064DF7 and 0x00064E2F; the latter constructs separate 0x48-byte W3DLightDrawModuleData storage, not this class.
#pragma once

#ifndef __BFME2_W3DLIGHTDRAW_H_
#define __BFME2_W3DLIGHTDRAW_H_

#include "../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"

class INI;
class W3DDynamicLight;

class W3DLightDraw : public DrawModule
{
public:
    W3DLightDraw(Thing *thing, const ModuleData *moduleData);
    virtual ~W3DLightDraw();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    static ModuleData *friend_newModuleData(INI *ini);

    virtual NameKeyType getModuleNameKey() const;
    virtual void doDrawModule(const Matrix3D *transformMtx);
    virtual void setShadowsEnabled(bool enable);
    virtual void releaseShadows();
    virtual void allocateShadows();
    virtual void setHidden(bool hidden);
    virtual void setFullyObscuredByShroud(bool fullyObscured);
    virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle);
    virtual void reactToGeometryChange();

protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);

private:
    W3DDynamicLight *m_0C;
    float m_10;
    float m_14;
    float m_18;
    float m_1C;
};

typedef char BFME2W3DLightDrawSizeCheck[sizeof(W3DLightDraw) == 0x20 ? 1 : -1];

#endif
