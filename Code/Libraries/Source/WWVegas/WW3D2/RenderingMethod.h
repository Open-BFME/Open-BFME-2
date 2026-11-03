// Target facts: retail callers 0x0017446A/0x0017448A/0x00174652/0x0017466B dispatch Begin, Begin_Pass, End_Pass and End through slots 2/3/5/6; Begin takes a pass-count pointer and flags and returns AL. These are the existing consumers' API names, not recovered original declarations. Slot 4 takes one word (forwarder 0x00072A28 and caller 0x000E44BE); its name is unproved. RenderingMethod has virtual functions. RefCountClass ctor/dtor 0x00072882/0x00072892 establish the primary vptr at +0 and int count at +4; the registered parent owns slots 0/1 (Delete_This and deleting destructor), bounded by VA 0x00BC6514.
// Target facts: RenderingMethodDelegate ctor 0x000729F4 stores count 1, VA 0x00BC6540 and its first member at +8; FXShaderSetup ctor 0x001525FB likewise starts its own asset holder at +8 and stores VA 0x00BD3B1C. Their common eight-byte interface prefix supports sizeof(RenderingMethod) == 8 with no additional fields. Neither qualified nor unqualified RenderingMethod has a constructor/destructor ledger row or a proven own table. Delegate dtor 0x00072AED restores VA 0x00BC650C after releasing +8; FXShaderSetup dtor 0x00152411 stores VA 0x00BD3B1C then VA 0x00BC650C. These are distinct derived tables and RefCountClass teardown, not conflicting RenderingMethod tables or a duplicate FXShaderSetup identity (allocation 0x00152C64 is 0x34 bytes).
// Target facts: VA 0x00BC6540 and VA 0x00BD3B1C each contain ten slots. Delegate slots 3/4/5 are rowed Begin_Pass 0x00072A19, UpdateDynamicParameterSet 0x00072A28 and End_Pass 0x00072A37; slot 6 forwards at 0x00072A44. Slots 7/8/9 target 0x00072A51/0x00072AC3/0x00072ADE and 0x001524BE/0x001524CA/0x0047A6A9 respectively: owning four-byte argument, four-byte hidden result, word result. The opaque handle declarations agree with the registered FXShaderSetup interface; slot names remain neutral. No method body is defined here.

#ifndef BFME2_WW3D2_RENDERINGMETHOD_H
#define BFME2_WW3D2_RENDERINGMETHOD_H

#include "../WWLib/RefCountData.h"

class Rva00087A93;
struct TreeHintRef00217D4C;

namespace FXShader {

class RenderingMethod : public RefCountClass
{
public:
    virtual bool Begin(int *passCount, int flags);
    virtual void Begin_Pass(int pass);
    virtual void slot4(int mode);
    virtual void End_Pass();
    virtual void End();
    virtual void slot07(Rva00087A93);
    virtual TreeHintRef00217D4C slot08();
    virtual void *slot09();

protected:
    virtual ~RenderingMethod();
};

}

#endif
