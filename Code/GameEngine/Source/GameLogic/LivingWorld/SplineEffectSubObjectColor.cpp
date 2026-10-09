// cl: /O1 /G7 /EHsc /MD /Ireference/shims/bfme2_ascii /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// WB128E4D0 names SplineEffect::SetSubObjectColor in LivingWorldCampaignObjects.cpp.
// Native4E34B1..4E35A3 proves 32-byte geometry records, name0/render4,
// color-vector14 with 12-byte entries, sub-object query VT80 and refcount4/VT0.
// The original color type is not established: preserve its three words in
// an address-derived record instead of assigning a donor color identity.
// String-node ABI views below are reused from the byte-verified geometry
// wrappers in WW3D2/Rva002BF4F3.cpp. Their zero-offset base views describe
// the passed records, not the original template hierarchy. Both builders,
// the conversion wrapper, and all cleanup calls resolve to rowed bodies.
// ZH refcount.h establishes Delete_This/Release_Ref semantics; native and WB
// independently confirm the accessed count and virtual slot. Full bytes/EH match.
#include <vector>
#include "ascii_string.h"
struct Rva004E34B1Color { unsigned int words[3]; };
template<int N> class SplineSlots:public SplineSlots<N-1>{public:virtual void gap(char(*)[N])=0;};
template<> class SplineSlots<0>{public:virtual void Delete_This()=0;};
class RenderObjClass:public SplineSlots<31>
{
public:
    virtual RenderObjClass *Get_Sub_Object_By_Name(const char *,int *)=0;
    int refs;
};
struct Rva005F17C6S12 { int m0,m1,m2; };
struct AsciiStringPlusText: Rva005F17C6S12 {};
AsciiStringPlusText operator+(const AsciiString &,const char *);
struct Rva0020F58E { int storage[4]; operator AsciiString(); };
struct Rva005F17C6S16: Rva0020F58E {};
Rva005F17C6S16 Rva005F17C6Build(const Rva005F17C6S12 &,int);
AsciiString Rva004E2ED9Construct(Rva0020F58E &);
struct SplineGeometry
{
    AsciiString name;
    RenderObjClass *render;
    int unknown08,unknown0C,unknown10;
    _STL::vector<Rva004E34B1Color> colors;
};
class SplineEffect
{
    char initial[0x14];
    _STL::vector<SplineGeometry> geometry;
public:
    void SetSubObjectColor(const AsciiString &,const Rva004E34B1Color &);
};
void SplineEffect::SetSubObjectColor(const AsciiString &name,const Rva004E34B1Color &color)
{
    for(unsigned i=0;i<geometry.size();++i)
    {
        if(geometry[i].render)
        {
            int index;
            RenderObjClass *object=geometry[i].render->Get_Sub_Object_By_Name(
                Rva004E2ED9Construct(Rva005F17C6Build(geometry[i].name+".",reinterpret_cast<int>(&name))).str(),&index);
            if(object)
            {
                geometry[i].colors[index]=color;
                if(--object->refs==0) object->Delete_This();
            }
        }
    }
}


