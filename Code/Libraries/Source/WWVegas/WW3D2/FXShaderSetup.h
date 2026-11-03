// Target facts: FXShaderSetup has virtual functions and sizeof 0x34: RVA 0x00152C64 allocates 0x34 before ctor 0x001525FB; RVA 0x0015B129 does likewise before copy ctor 0x00152DE9. Both ctors store VA 0x00BD3B1C at +0 and count 1 at +4. Dtor 0x00152411 stores that same table at 0x00152423, then restores RefCountClass's VA 0x00BC650C at 0x001524AE; these are derived and base teardown states, not conflicting class tables.
// Target facts: VA 0x00BD3B1C has ten code pointers before the non-code word at VA 0x00BD3B44: slots 0/1 are Delete_This 0x0006CE57 and deleting dtor 0x0015263D; slots 2..6 are Begin_Rendering 0x00151EE2, Begin_Pass 0x00151CEE, UpdateDynamicParameterSet 0x00151D1A, End_Pass 0x00151D5F and End_Rendering 0x00151D85. Slots 7/8/9 target 0x001524BE (four-byte by-value handle cleanup), 0x001524CA (zeroed four-byte hidden result), and 0x0047A6A9 (returns this); their names are unproved.
// Target facts: ctor 0x001525FB and dtor 0x00152411 prove a four-byte asset holder at +8, a three-pointer parameter vector at +0x0C (ctor 0x001F81BF, dtor 0x0007C5D5), an AsciiString at +0x18 (release 0x00036410), LOD int at +0x1C, technique and parameter-block handles at +0x20/+0x24, and a three-pointer texture vector at +0x28 (ctor 0x00211E58, dtor 0x00152118). Pointer arrays expose only those vectors' storage. Copy ctor 0x00152DE9 calls assignment 0x00152CDA; assignment calls InitializeShader 0x0015288F. Other rowed methods are UpdateParameterList 0x0015265E, Load_W3D 0x00152E4D and the UpdateDynamicParameterSet spelling apply at 0x00151D1A.

#ifndef BFME2_WW3D2_FXSHADERSETUP_H
#define BFME2_WW3D2_FXSHADERSETUP_H

#include "../WWLib/RefCountData.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

namespace _STL {
template <class T> class allocator;
template <class T, class Allocator> class vector;
}

struct Rva0007BB16Record;
class Rva00087A93;
struct TreeHintRef00217D4C;
class ChunkLoadClass;

class FXShaderSetup : public RefCountClass
{
public:
    FXShaderSetup();
    FXShaderSetup(const FXShaderSetup &);
    FXShaderSetup &operator=(const FXShaderSetup &);

    virtual bool Begin_Rendering(unsigned int *, int);
    virtual void Begin_Pass(unsigned int);
    virtual void UpdateDynamicParameterSet(unsigned int);
    virtual void End_Pass();
    virtual void End_Rendering();
    virtual void slot07(Rva00087A93);
    virtual TreeHintRef00217D4C slot08();
    virtual void *slot09();

    bool InitializeShader(const char *, const char *,
        const _STL::vector<Rva0007BB16Record, _STL::allocator<Rva0007BB16Record> > *, int);
    bool UpdateParameterList(
        const _STL::vector<Rva0007BB16Record, _STL::allocator<Rva0007BB16Record> > &);
    bool Load_W3D(ChunkLoadClass &);
    void apply(unsigned int);

protected:
    virtual ~FXShaderSetup();

public:
    void *field08;
    void *field0c[3];
    AsciiString field18;
    int field1c;
    const char *field20;
    const char *field24;
    void *field28[3];
};

#endif
