// LivingWorldManager doom-ray and doom-cloud setup.
// Native 0x006133E0..0x0061376B: 907 bytes, thiscall, RET 0.
// WB 0x00B60F40 corroborates the two loops and doomRays/doomCloud names.
// Native member accesses establish the model, scale, count, bounds and vector
// offsets below. The function and visual subclass identities remain opaque.
// Reconstructed from target evidence; no engine donor source.
//
// FuncInfo 0x00D138E4 has four unwind states, all parent -1: allocation
// cleanup at EBP-10, vector<AsciiString> at -34, allocation at -20, vector at
// -58. The 12-byte coordinate locals have no native unwind actions.
//
// Keep STLport's real push_back definition visible, even though it compiles
// out of line. A declaration-only specialization changes the caller's stack
// coloring. Natural count/range locals then reproduce every native slot.
// Paired volatile accesses to primary+8 and the f30/f88 stores preserve the
// two observed store-before-load schedules; this is a compiler adapter, not
// evidence that the original fields were volatile.
// ?rva002133E0@LivingWorldManager@@QAEXXZ
// cl: /D_CRTIMP= /D_STLP_USE_STATIC_LIB /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Match the allocator and helper policy of SiegeDockingBehaviorInitializeBones:
// the real growth helper stays visible and compiles to its retail body.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned &max(const unsigned &a,const unsigned &b) { return a<b?b:a; }
}
#include <vector>
#include "ascii_string.h"
// Use the existing destructor provider, avoiding a conflicting COMDAT copy.
namespace _STL { template<> vector<AsciiString>::~vector(); }
#include "../../../../Libraries/Source/WWVegas/WWMath/WWMathClass.h"
class Coord3D;
class RenderObjClass;
class BfmeAnimationReceiver;
class Rva003FD14DBase {public:
    virtual void vbfunc();
    AsciiString name;
    BfmeAnimationReceiver *volatile m_primary;
    char pad0c[0x30-0x0c];
    int f30;
    char pad34[0x88-0x34];
    bool f88;
    char pad89[0x98-0x89];
    float f98;
    float f9c,fA0,fA4,fA8;
};
class Rva003FDAAE : public Rva003FD14DBase {public:
    Rva003FDAAE(AsciiString name);
    virtual void vfunc();
};
class Rva003FDBD1 : public Rva003FD14DBase {public:
    Rva003FDBD1(AsciiString name);
    virtual void vfuncDBD1();
    char positionAC[12];
};
#include "../../../Include/GameClient/LivingWorldVisual.h"
class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;
class BfmeRenderSceneView {public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();

    virtual void insertObject(RenderObjClass*);
};
class BfmeVisualPositionView {public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();

    virtual void setPosition(const Coord3D*);
};
extern "C" __declspec(dllimport) int __cdecl sprintf(char *,const char *,...);
template <int N> class DoomVSlots : public DoomVSlots<N - 1> { public: virtual void gap(char (*)[N]) = 0; };
template <> class DoomVSlots<0> { };
class DoomPrimaryView : public DoomVSlots<101> { public: virtual void setHidden(int); };
class Rva003FBA0E { public: void rva003FBA0E(int,int,int,int,int,float); };
struct Rva002BFFD4Template;
class Rva002BFF5A { public: void rva002BFFD4(Rva002BFFD4Template *,int,unsigned int); };
struct Rva00459E05Entry;
struct DoomVec12 { float x,y,z; };
struct DoomVec3 { __forceinline DoomVec3() {} __forceinline DoomVec3(const DoomVec3 &o) { x=o.x; y=o.y; z=o.z; } float x,y,z; };
static __forceinline void doomSetOpacity(Rva003FD14DBase *visual,float opacity) { visual->f98=opacity; }
static __forceinline RenderObjClass *doomPrimary(Rva003FD14DBase *visual) { return reinterpret_cast<RenderObjClass *>(visual->m_primary); }

void rva0010E4F6(void *,bool);
bool Rva0010E676_SetEmissive(RenderObjClass *,float,float,float);

class LivingWorldManager { public:
    void rva002133E0();
    char pad00[0x44];
    float m_cloudZ;                     // +44
    char pad48[0x12C-0x48];
    AsciiString m_rayModel;             // +12C
    char pad130[0x140-0x130];
    DoomVec12 m_rayScale;               // +140
    float m_rayOpacity;                 // +14C
    int m_rayLevels;                    // +150
    char pad154[0x168-0x154];
    AsciiString m_cloudModel;           // +168
    char pad16C[4];
    int m_cloudCount;                   // +170
    DoomVec3 m_cloudMin;                // +174
    DoomVec3 m_cloudMax;                // +180
    int m_cloudSpread;                  // +18C
    char pad190[0x1B8-0x190];
    float m_cloudScale;                 // +1B8
    char pad1BC[0x234-0x1BC];
    char padVectors[0x240-0x234+12];
    _STL::vector<Rva00459E05Entry*> &cloudList() { return *reinterpret_cast<_STL::vector<Rva00459E05Entry*> *>(reinterpret_cast<char *>(this)+0x234); }
    _STL::vector<Rva00459E05Entry*> &rayList() { return *reinterpret_cast<_STL::vector<Rva00459E05Entry*> *>(reinterpret_cast<char *>(this)+0x240); }
};

void LivingWorldManager::rva002133E0()
{
    int count;
    float range;
    int index;
    int base;
    Rva003FDBD1 *visual;

    count=1;
    int level;
    for (level=m_rayLevels; level>0; --level) {
        for (index=0; index<count; ++index) {
            char name[64];
            sprintf(name,"doomRays%02d",index);
            visual=new Rva003FDBD1(AsciiString(name));
            Rva00459E05Entry *entry=reinterpret_cast<Rva00459E05Entry *>(visual);
            RenderObjClass *created;
            {
                _STL::vector<AsciiString> subObjects;
                created=reinterpret_cast<LivingWorldVisual *>(visual)->createRenderObject(m_rayModel,subObjects,0,0);
            }
            if (created) {
                rva0010E4F6(doomPrimary(visual),false);
                const_cast<volatile int&>(visual->f30)=1;
                Rva0010E676_SetEmissive(doomPrimary(visual),0.0f,0.0f,0.0f);
                reinterpret_cast<DoomPrimaryView *>(doomPrimary(visual))->setHidden(true);
                *reinterpret_cast<DoomVec12 *>(&visual->fA0)=m_rayScale;
                doomSetOpacity(visual,m_rayOpacity);
                reinterpret_cast<BfmeRenderSceneView *>(((Rva002D3627Host *)TheLivingWorld))->insertObject(doomPrimary(visual));
                rayList().push_back(entry);
            }
        }
        count*=2;
    }
    DoomVec3 lo=m_cloudMin;
    DoomVec3 hi=m_cloudMax;
    int spread=m_cloudSpread;
    for (int j=0; j<m_cloudCount; ++j) {
        char name[64];
        sprintf(name,"doomCloud%02d",j);
        Rva003FDAAE *visual=new Rva003FDAAE(AsciiString(name));
        Rva00459E05Entry *entry=reinterpret_cast<Rva00459E05Entry *>(visual);
        RenderObjClass *created;
        {
            _STL::vector<AsciiString> subObjects;
            created=reinterpret_cast<LivingWorldVisual *>(visual)->createRenderObject(m_cloudModel,subObjects,0,0);
        }
        if (created) {
            rva0010E4F6(visual->m_primary,false);
            DoomVec12 position;
            position.x=WWMath::Random_Float()*(hi.x-lo.x)+lo.x;
            position.y=WWMath::Random_Float()*(hi.y-lo.y)+lo.y;
            position.z=m_cloudZ;
            range=(float)spread;
            base=(int)(WWMath::Random_Float()*range*0.3f);
            reinterpret_cast<BfmeVisualPositionView *>(visual)->setPosition(reinterpret_cast<const Coord3D *>(&position));
            const_cast<volatile bool&>(visual->f88)=true;
            reinterpret_cast<DoomPrimaryView *>(visual->m_primary)->setHidden(false);
            int a=(int)((WWMath::Random_Float()*(0.35f-0.2f)+0.2f)*range)+base;
            int b=(int)((WWMath::Random_Float()*(0.6f-0.4f)+0.4f)*range)+base;
            int c=(int)((WWMath::Random_Float()*(0.9f-0.75f)+0.75f)*range)+base;
            reinterpret_cast<Rva003FBA0E *>(visual)->rva003FBA0E(base,a,b,c,1,0.0f);
            reinterpret_cast<LivingWorldVisual *>(visual)->rva003FC291(m_cloudScale);
            reinterpret_cast<BfmeRenderSceneView *>(((Rva002D3627Host *)TheLivingWorld))->insertObject(reinterpret_cast<RenderObjClass *>(visual->m_primary));
            cloudList().push_back(entry);
            reinterpret_cast<Rva002BFF5A *>(((Rva002D3627Host *)TheLivingWorld))->rva002BFFD4(reinterpret_cast<Rva002BFFD4Template *>(visual),3,0);
        }
    }
}
