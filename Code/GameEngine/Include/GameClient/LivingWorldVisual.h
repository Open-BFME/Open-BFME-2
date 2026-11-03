// Target facts: retail constructor RVA 0x003FC58C (rowed as Rva003FD14DBase) and destructor 0x003FCE38 (rowed as Rva003FCE38) both store table VA 0x00C37C30 at +0. Neither constructs a parent. Caller 0x003FD849 allocates 0xAC at 0x003FD858, calls the constructor at 0x003FD876, then calls createRenderObject at 0x003FD8A8 on that same object; derived constructor 0x005C4DE0 calls the base at 0x005C4DFC and starts its fields at +0xAC. This is a polymorphic 0xAC-byte class with no evidenced base.
// Target facts: table VA 0x00C37C30 has 14 slots, bounded by the next installed table 0x00C37C68: RVAs 003FD173, 0047A69C, 0047A69C, 003FB7DB, 003FBB99, 003FBD9F, 003FCA58, 003FB6C5, 003FB602, 000B3FD0, 003FBA58, 003FBAE4, 003FCCC9, 0050B5C6. Slot 0 calls the out-of-line destructor 003FCE38; slots 1/2 only prove four-byte argument cleanup, 7 takes the position reference (row 003FB6C5), 8 is setHouseColor, 11/12 take a Boolean (rows 003FBAE4/003FCCC9), and 13 returns true in AL. The other slots take no stack arguments. Nonvirtual row spellings remain separate callable declarations.
// Target facts: constructor 0x003FC58C copies AsciiString at +4 through 0x000365F0 and initializes storage through +0xA8; destructor 0x003FCE38 destroys that string through 0x00036410 and unlinks the +0x1C handle through 0x0004CBC0. Rows 0x003FCEA3/0x003FC6C3 prove primary render object +8, shadow +0x0C and shadow type +0x10; 0x003FC74A creates the pickbox at +0x14; 0x003FCD71 releases objects at +8/+0x14/+0x18. Float stores in 0x003FBC4D/0x003FC291 prove scale +0x7C. Caller 0x00213171 reads the primary pointer directly at 0x00213258/0x00213262, witnessing its existing inline getRenderObject accessor. Other storage stays opaque. Method signatures below follow their LivingWorldVisual ledger rows; the constructor's string reference is witnessed by 0x003FD870 and the copy call 0x003FC5A9.

#pragma once

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

namespace _STL {
template <class T> class allocator;
template <class T, class Allocator> class vector;
}

class Matrix3D;
class RenderObjClass;
class Shadow;
class Vector3;

class LivingWorldVisual
{
public:
    LivingWorldVisual(const AsciiString &name);
    virtual ~LivingWorldVisual();
    virtual void vslot01(unsigned int);
    virtual void vslot02(unsigned int);
    virtual void vslot03();
    virtual void vslot04();
    virtual void vslot05();
    virtual void vslot06();
    virtual void vslot07(const Vector3 &);
    virtual void setHouseColor(const int &color);
    virtual void vslot09();
    virtual void vslot10();
    virtual void vslot11(bool);
    virtual void vslot12(bool);
    virtual bool vslot13();

    RenderObjClass *createRenderObject(const AsciiString &modelName,
        const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &subObjectNames,
        int shadowType, const int *houseColor);
    RenderObjClass *createPickboxObject(const AsciiString *name);
    RenderObjClass *getRenderObject() { return m_primaryRObj; }
    void createShadow();
    void rva003FBC4D(float scale);
    void rva003FBFF3(const Matrix3D &transform);
    void rva003FC291(float scale);
    void rva003FCCC9(bool visible);
    void rva003FCD71();
    void rva003FCDD5(bool enable);

    AsciiString m_04;
    RenderObjClass *m_primaryRObj;
    Shadow *m_shadow;
    int m_shadowType;
    RenderObjClass *m_robj14;
    RenderObjClass *m_robj18;
    unsigned char m_pad1C[0x7C - 0x1C];
    float m_7C;
    unsigned char m_pad80[0xAC - 0x80];
};

typedef char LivingWorldVisualSizeCheck[(sizeof(LivingWorldVisual) == 0xAC) ? 1 : -1];
