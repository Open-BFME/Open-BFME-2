// cl: /O1 /arch:SSE /G7 /MD /EHs /DNDEBUG /DWIN32 /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// Complete floor-element cleanup at 0x000E5033 (104 bytes through RET).
// Semantic guide: Open-BFME-1 6c1e0b51, BaseHeightMapFloorElementDestructor.cpp.
// Native and WB 0x881140 prove the two texture handles at +20/+24, strings
// at +8C/+90, and the leading call to the shared E4567 resource cleanup.
// BFME 1's member offsets differ; retain the target's existing unwind-pin
// name rather than asserting its virtual class identity. The target constructor
// starts with sphere floats, and this nonvirtual destructor writes no vptr.
// The four EH states and their cleanup actions are verified independently.
#include "W3DFloorElement.h"

FloorMatrixRow::FloorMatrixRow() {}
Gen_uw_000e5033::~Gen_uw_000e5033() { reinterpret_cast<Rva000E4567 *>(this)->rva000E4567(); }

typedef char FloorRowStride[(sizeof(FloorMatrixRow)==16)?1:-1];
typedef char FloorElementExtent[(sizeof(Gen_uw_000e5033)==0xa0)?1:-1];
Gen_uw_000e5033::Gen_uw_000e5033() : m_render28(0), m_drawable2c(0), m_3c(0),m_40(0),m_44(0),m_48(0),m_id4c(0), m_active80(false),m_flag81(false),m_flag82(false),m_opacity84(1),m_speed88(0),m_94(0),m_state98(0),m_flag9c(false),m_flag9d(false)
{
}


#include "BFME2ParticleTextureHandles.h"
#include "sphere.h"

template<class T> inline RefCountPtr<T>::~RefCountPtr() { if (Ptr) Ptr->Release_Ref(); }
class FloorTextureNameDispatch { public: virtual const char *name(); };
class RenderObjClass;
RenderObjClass *Create_Render_Obj(const char *);
bool Render_Obj_Exists(const char *);
AsciiString makeNrmTextureName(const AsciiString &);
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *,int,int);
struct BfmeResetTextureRef { void clear(); };
struct CursorTextureSlot { void operator=(const BFME2ParticleTextureHandle &); };
class FloorMaterialDispatch;
class FloorRenderDispatch {
public:
    virtual void destroy();
    virtual void slot01();
    virtual void slot02();
    virtual int classId();
    virtual void slot04();
    virtual FloorRenderDispatch *asMesh();
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
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual FloorRenderDispatch *subObject(int);
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual Matrix3D boneTransform(int);
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual FloorMaterialDispatch *material();
    int refs;
    __forceinline void release() { if (--refs==0) destroy(); }
};
#include "../../../../Libraries/Source/WWVegas/WW3D2/MaterialTextureGetterView.h"
class FloorMaterialDispatch { public: virtual void destroy(); int refs; char rest[0x28]; int textures; __forceinline void release() { if (--refs==0) destroy(); } };
class FloorDisplayDispatch { public:
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
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual AsciiString resolveName(const AsciiString &);
};
class Display;
class GlobalData;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
struct FloorModelView { char prefix[0x28]; int count; int pad; struct Vertices { char prefix[0xc]; Vector3 *data; } *vertices; };
struct FloorMeshView { char prefix[0xc4]; FloorModelView *model; };
// Complete 875B E509B..E5406; WB8819A0 W3DFloor::load.
// Semantic guide: clean BFME1 0bef414b BaseHeightMapFloorElementInit006F8A60.
// Target differs at mesh28, matrix50, name8C/90 and normal-map lookup.
// Dispatch views describe only directly witnessed call slots, not class identity.
// Globals use the data ledger owners: TheDisplay and TheWritableGlobalData.
// Material texture getter returns the shared owning handle by value; its
// four-byte texture pointer is consumed through the existing holder assignment.
bool Gen_uw_000e5033::load()
{
    reinterpret_cast<BfmeResetTextureRef *>(&m_texture20)->clear();
    reinterpret_cast<BfmeResetTextureRef *>(&m_texture24)->clear();
    if (m_render28) { static_cast<FloorRenderDispatch *>(m_render28)->release(); m_render28=0; }
    AsciiString filename=reinterpret_cast<FloorDisplayDispatch *>(TheDisplay)->resolveName(m_name8c);
    FloorRenderDispatch *obj=reinterpret_cast<FloorRenderDispatch *>(Create_Render_Obj(filename.str()));
    if (!obj) return false;
    Vector3 offset(0,0,0);
    if (obj->classId()==25) {
        FloorRenderDispatch *parent=obj;
        obj=obj->subObject(0);
        Matrix3D matrix=obj->boneTransform(0);
        offset=matrix.Get_Translation();
        parent->release();
    }
    m_position30.x=offset.X; m_position30.y=offset.Y; m_position30.z=offset.Z;
    if (obj->classId()==0) m_render28=obj->asMesh();
    if (!m_render28) { obj->release(); return false; }
    FloorModelView *model=static_cast<FloorMeshView *>(m_render28)->model;
    int count=model->count;
    Vector3 *vertices=model->vertices->data;
    SphereClass sphere(vertices,count);
    sphere.Center+=offset;
    *reinterpret_cast<SphereClass *>(&m_sphere00)=sphere;
    *reinterpret_cast<SphereClass *>(m_sphere10)=sphere;
    Matrix3D &matrix=*reinterpret_cast<Matrix3D *>(&m_matrix50);
    matrix.Make_Identity();
    matrix.Set_Translation(offset);
    *reinterpret_cast<Vector3 *>(&m_position30)=offset;
    if (m_name90.isEmpty()) {
        FloorMaterialDispatch *info=static_cast<FloorRenderDispatch *>(m_render28)->material();
        if (info) {
            if (info->textures>0) {
                reinterpret_cast<CursorTextureSlot *>(&m_texture20)->operator=(reinterpret_cast<const BFME2ParticleTextureHandle &>(reinterpret_cast<Rva00016EE40 *>(info)->getTexture(0)));
            }
            info->release();
        }
    } else reinterpret_cast<CursorTextureSlot *>(&m_texture20)->operator=(BFME2LoadParticleTexture(m_name90.str(),3,0));
    if (*(bool *)((char *)TheWritableGlobalData+0x49)) {
        AsciiString normal=makeNrmTextureName(AsciiString(m_texture20.pointer ? reinterpret_cast<FloorTextureNameDispatch *>(m_texture20.pointer)->name() : (const char *)0));
        if (Render_Obj_Exists(normal.str())) reinterpret_cast<CursorTextureSlot *>(&m_texture24)->operator=(BFME2LoadParticleTexture(normal.str(),3,0));
    }
    return true;
}
