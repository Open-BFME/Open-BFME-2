// cl: /O1 /G7 /arch:SSE2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Retail 0x0010E87A..0x0010EA49 (463 bytes); WB 0x00963540 names
// W3DUtility::_SetOpacity and this source path (assert lines 128..164).
// The native cdecl bool ABI is proven; whether W3DUtility is a namespace or
// a class is not, so the exported recovery retains an address-qualified name.
// Native access proves RenderObj class-id slot 3, child-count slot 28,
// child slot 30 and material-info slot 85; only class-id zero reads model +C4.
// The model's shader holder is +94, shader setup +B8, parameter vector +C,
// record stride 36, value +C and floating-parameter tag 2. These are local ABI
// views, not a reconstructed declaration of the engine classes.
// All nonrecursive callees have independent matched providers. The existing
// 0x00199FCC search only compares keys and does not allocate or throw; its
// nothrow declaration reproduces retail's temporary-string cleanup state.
// The 0x0010E482 provider returns exactly 0 or 1; retail tests its low byte.
// Setup changes are scoped by the native DX8 lock; material and child references
// are released through the retail refcount +4 / Delete_This slot zero protocol.
#include <vector>
#include "ascii_string.h"
class RenderObjClass;
struct Rva0007BB16Record {
    unsigned char storage[36];
    Rva0007BB16Record(const Rva0007BB16Record &);
    ~Rva0007BB16Record();
};
namespace _STL {
template<> vector<Rva0007BB16Record>::vector(const vector<Rva0007BB16Record> &);
template<> vector<Rva0007BB16Record>::~vector();
}
struct BfmeAssignRecord36 {
    BfmeAssignRecord36(const char *,int);
    unsigned char prefix[12];
    float value;
    unsigned char rest[20];
};
// Keep the native 36-byte object's lifetime local. Other historical size views
// emit an incomplete BfmeAssignRecord36 destructor, so this wrapper delegates
// complete destruction to the independently verified two-string record owner.
struct OpacityOwnedParameter {
    BfmeAssignRecord36 record;
    OpacityOwnedParameter(const char *key,int type): record(key,type) {}
    ~OpacityOwnedParameter() { reinterpret_cast<Rva0007BB16Record *>(&record)->~Rva0007BB16Record(); }
};
struct Rva00082EB8Rec;
class Rva00082EB8 { public: void rva00082EB8(const Rva00082EB8Rec &); };
class Rva00199FCC { public: void *rva00199FCC(const AsciiString &) throw(); };
class Rva0010E482 { public: int rva0010E482(int); };
class FXShaderSetup {
public: bool UpdateParameterList(const _STL::vector<Rva0007BB16Record> &);
};
struct OpacityParameterView { int word0,type; };
struct OpacitySetupView {
    unsigned char pad0[12];
    _STL::vector<Rva0007BB16Record> parameters;
    __forceinline bool hasFloat(const AsciiString &name) {
        OpacityParameterView *p=reinterpret_cast<OpacityParameterView *>(reinterpret_cast<Rva00199FCC *>(&parameters)->rva00199FCC(name));
        return p && p->type==2;
    }
};
struct OpacityShaderView { unsigned char pad0[0xb8]; OpacitySetupView *setup; };
struct OpacityMeshModelView { unsigned char pad0[0x94]; OpacityShaderView *shader; };
class VertexMaterialClass { public: void Set_Opacity(float); };
class MaterialInfoClass { public: VertexMaterialClass *Get_Vertex_Material(int); };
class OpacityReferenceView {
public:
    virtual void destroy();
    int references;
    void release() { if (--references==0) destroy(); }
};
class OpacityRenderView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual int classId();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual int childCount(); // slot 28: +0x70
    virtual void s29();
    virtual RenderObjClass *child(int); // slot 30: +0x78
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual void s66();
    virtual void s67();
    virtual void s68();
    virtual void s69();
    virtual void s70();
    virtual void s71();
    virtual void s72();
    virtual void s73();
    virtual void s74();
    virtual void s75();
    virtual void s76();
    virtual void s77();
    virtual void s78();
    virtual void s79();
    virtual void s80();
    virtual void s81();
    virtual void s82();
    virtual void s83();
    virtual void s84();
    virtual MaterialInfoClass *materials(); // slot 85: +0x154
    unsigned char unknown04[0xc4-4];
    OpacityMeshModelView *model;
};
void BFME_DX8_Thread_Lock(); bool BFME_DX8_Thread_Assert();
class OpacityDeviceLock {
public: OpacityDeviceLock() { BFME_DX8_Thread_Lock(); }
    ~OpacityDeviceLock() { BFME_DX8_Thread_Assert(); }
};
bool Rva0010E87A_SetOpacity(RenderObjClass *object,float opacity)
{
    if (!object) return false;
    bool changed=false;
    OpacityRenderView *render=reinterpret_cast<OpacityRenderView *>(object);
    MaterialInfoClass *materials=render->materials();
    if (materials) {
        if (render->classId()==0 && render->model) {
            OpacityShaderView **shader=&render->model->shader;
            if (static_cast<unsigned char>(reinterpret_cast<Rva0010E482 *>(*shader)->rva0010E482(0))) {
                OpacityDeviceLock lock;
                OpacitySetupView *setup=(*shader)->setup;
                if (setup && setup->hasFloat(AsciiString("Opacity"))) {
                    _STL::vector<Rva0007BB16Record> parameters(setup->parameters);
                    OpacityOwnedParameter parameter("Opacity",2);
                    parameter.record.value=opacity;
                    reinterpret_cast<Rva00082EB8 *>(&parameters)->rva00082EB8(*reinterpret_cast<const Rva00082EB8Rec *>(&parameter));
                    reinterpret_cast<FXShaderSetup *>(setup)->UpdateParameterList(parameters);
                }
            }
        }
        for (int i=0;i<reinterpret_cast<const int *>(materials)[6];++i) {
            VertexMaterialClass *vertex=materials->Get_Vertex_Material(i);
            if (vertex) {
                vertex->Set_Opacity(opacity);
                reinterpret_cast<OpacityReferenceView *>(vertex)->release();
                changed=true;
            }
        }
        reinterpret_cast<OpacityReferenceView *>(materials)->release();
    } else {
        int count=render->childCount();
        for (int i=0;i<count;++i) {
            RenderObjClass *child=render->child(i);
            bool childChanged=Rva0010E87A_SetOpacity(child,opacity);
            changed=changed || childChanged;
            if (child) reinterpret_cast<OpacityReferenceView *>(child)->release();
        }
    }
    return changed;
}
