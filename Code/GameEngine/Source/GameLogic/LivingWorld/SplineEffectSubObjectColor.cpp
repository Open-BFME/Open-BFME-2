// cl: /O1 /G7 /EHsc /MD /Ireference/shims/bfme2_ascii /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// WB128E4D0 names SplineEffect::SetSubObjectColor in LivingWorldCampaignObjects.cpp.
// Native4E34B1..4E35A3 proves 32-byte geometry records, name0/render4,
// color-vector14 with 12-byte float triples, sub-object query VT80 and refcount4/VT0.
// The original color type is not established: preserve its accessed three floats in
// an address-derived record instead of assigning a donor color identity.
// String-node ABI views below are reused from the byte-verified geometry
// wrappers in WW3D2/Rva002BF4F3.cpp. Their zero-offset base views describe
// the passed records, not the original template hierarchy. Both builders,
// the conversion wrapper, and all cleanup calls resolve to rowed bodies.
// ZH refcount.h establishes Delete_This/Release_Ref semantics; native and WB
// independently confirm the accessed count and virtual slot. Full bytes/EH match.
#include <vector>
#include <set>
#include "ascii_string.h"
struct Rva004E34B1Color { float red,green,blue; };
template<int N> class SplineSlots:public SplineSlots<N-1>{public:virtual void gap(char(*)[N])=0;};
template<> class SplineSlots<0>{public:virtual void Delete_This()=0;};
class RenderObjClass:public SplineSlots<29>
{
public:
    virtual RenderObjClass *Get_Sub_Object(int);
    virtual void unused31();
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
    _STL::set<int> subobjects;
    _STL::vector<Rva004E34B1Color> colors;
};

struct Rva002BE7DBValue { float x,y,z; };
class Rva002BE7DB {public:
    Rva002BE7DBValue &rva002BE7DB(Rva002BE7DBValue &) const;
};
class Rva00064390 {public:
    Rva00064390();
    float x,y,z,w,control0,control1;
    unsigned frame;
};
class Rva00064880Tree {public:
    bool atEnd(unsigned);
    bool rva005042F2(unsigned,Rva00064390 *);
    void *header;
    unsigned count,unknown08;
};
bool Rva0010E676_SetEmissive(RenderObjClass *,float,float,float);

class SplineEffect
{
    virtual void unused0()=0;
    virtual void unused1()=0;
    virtual void rvaSlot2(int)=0;
    Rva00064880Tree curve;
    unsigned frame;
    _STL::vector<SplineGeometry> geometry;
public:
    void Execute();
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



// WB128E8C0 names Execute. Native4E1E35..4E1F62 supplies curve+4,
// frame10, set<int> at record8 and Get_Sub_Object slot78. The unnamed
// curve evaluator5042F2 has its own independently checked binding.
// Its control-point prefix is copied through the existing rowed23B getter.
// Native MULSS operands prove the float color fields; keep their original
// type name unresolved. Geometry and curve data, not donor names, establish
// this complete accessed prefix. Both this301B body and color242B verify.
void SplineEffect::Execute()
{
    if(curve.atEnd(frame))
        rvaSlot2(0);
    else
    {
        Rva00064390 point;
        curve.rva005042F2(++frame,&point);
        Rva002BE7DBValue scale;
        reinterpret_cast<Rva002BE7DB *>(&point)->rva002BE7DB(scale);
        for(unsigned i=0;i<geometry.size();++i)
        {
            for(_STL::set<int>::iterator it=geometry[i].subobjects.begin();
                it!=geometry[i].subobjects.end();++it)
            {
                int index=*it;
                RenderObjClass *object=geometry[i].render->Get_Sub_Object(index);
                if(object)
                {
                    Rva004E34B1Color color=geometry[i].colors[index];
                    Rva0010E676_SetEmissive(object,scale.x*color.red,scale.y*color.green,scale.z*color.blue);
                    if(--object->refs==0)object->Delete_This();
                }
            }
        }
    }
}
