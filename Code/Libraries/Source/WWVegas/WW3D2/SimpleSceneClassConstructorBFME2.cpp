// ??0SimpleSceneClass@@QAE@XZ
// cl: /arch:SSE /G7 /O2 /Ob2 /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
#include "bittype.h"
#define WWDEBUG_H
#define MEMPOOL_H
template <class T, int N> class AutoPoolClass {};
#define WWDEBUG_SAY(x)
#define WWDEBUG_WARNING(x)
#include "multilist.h"
#include "refcount.h"
#include "vector3.h"
#include "rendobj.h"
typedef RefMultiListClass<RenderObjClass> RefRenderObjListClass;
typedef MultiListClass<RenderObjClass> NonRefRenderObjListClass;

class RenderInfoClass;
class SceneIterator;
class CameraClass;
class ChunkSaveClass;
class ChunkLoadClass;

class SceneClass : public RefCountClass
{
public:
    // ?SceneClass::SceneClass present-unmatched
    SceneClass()
        : AmbientLight(0.5f, 0.5f, 0.5f), PolyRenderMode(2),
          ExtraPassPolyRenderMode(0), FogEnabled(false),
          FogColor(0.0f, 0.0f, 0.0f), FogStart(0.0f), FogEnd(1000.0f)
    {
    }
    virtual ~SceneClass();
    virtual void Add_Render_Object(RenderObjClass *obj);
    virtual void Remove_Render_Object(RenderObjClass *obj);
    virtual SceneIterator *Create_Iterator(bool onlyvisible) = 0;
    virtual void Destroy_Iterator(SceneIterator *it) = 0;
    virtual void Set_Ambient_Light(const Vector3 &color);
    virtual const Vector3 &Get_Ambient_Light();
    virtual void Set_Fog_Enable(bool set);
    virtual bool Get_Fog_Enable();
    virtual void Set_Fog_Color(const Vector3 &color);
    virtual const Vector3 &Get_Fog_Color();
    virtual void Set_Fog_Range(float start, float end);
    // ABI declarations follow donor scene.h; target vtable supplies the extra slots.
    virtual void Get_Fog_Range(float *start, float *end) { *start = FogStart; *end = FogEnd; }
    // scene.h RegType. Only the parameter type reaches the mangled name
    // (W4RegType@SceneClass@@); retail's switch has five cases, upstream three.
    enum RegType
    {
        ON_FRAME_UPDATE = 0,
        LIGHT,
        RELEASE,
    };
    virtual void Register(RenderObjClass *obj, RegType for_what) = 0;
    virtual void Unregister(RenderObjClass *obj, RegType for_what) = 0;
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point) { return 1.0f; }
    // Native base/derived vtables have three additional slots17..19.
    // Target table BD33D0 independently supplies getter6EE1B and
    // bound/level forwarding thunks1428E0/1428F0. Names remain address-derived.
    virtual int rva0006EE1B() const = 0;
    virtual void rva001428E0(const struct Rva00141F90Bounds &) = 0;
    virtual void rva001428F0(unsigned int) = 0;
    virtual void Save(ChunkSaveClass &save);
    virtual void Load(ChunkLoadClass &load);
protected:
    // protected virtual in retail: ?Render@SceneClass@@MAEXAAVRenderInfoClass@@@Z
    virtual void Render(RenderInfoClass &info);
public:
    Vector3 AmbientLight;
    int PolyRenderMode;
    int ExtraPassPolyRenderMode;
    bool FogEnabled;
    Vector3 FogColor;
    float FogStart;
    float FogEnd;
private:
    // Match scene.h: these hooks use private-virtual (EAEX) provider names.
    virtual void Customized_Render(RenderInfoClass &info) = 0;
    virtual void Pre_Render_Processing(RenderInfoClass &info) {}
    virtual void Post_Render_Processing(RenderInfoClass &info) {}
};

struct Rva00141F90Bounds { float m_00,m_04,m_08,m_0C,m_10,m_14; };
struct BfmeSceneVectorElement;
struct Gen_00943CF0_Node;
struct Gen_uw_0002e866;
class BfmeSceneVector
{
public:
    // ?BfmeSceneVector::BfmeSceneVector present-unmatched
    BfmeSceneVector() : vector(0), vector_max(0), level_mask(0) {
        Rva00141F90Bounds initial = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
        rva00141F90(initial);
        Set_Level(0);
    }
    void clear(Gen_uw_0002e866 *objects);
    void process(Gen_00943CF0_Node **objects);
    void Set_Level(unsigned int level);
    void rva00141F90(const Rva00141F90Bounds &bounds);
private:
    Rva00141F90Bounds bounds;
    BfmeSceneVectorElement *vector;
    int vector_max;
    float scale;
    unsigned int level_mask;
};

class SimpleSceneClass : public SceneClass
{
public:
    SimpleSceneClass();
    virtual ~SimpleSceneClass();
    // Native table has28 entries; Get_Scene_ID has no slot.
    int Get_Scene_ID();
    virtual void Add_Render_Object(RenderObjClass *obj);
    virtual void Remove_Render_Object(RenderObjClass *obj);
    virtual void Remove_All_Render_Objects();
    virtual void Register(RenderObjClass *obj, RegType for_what);
    virtual void Unregister(RenderObjClass *obj, RegType for_what);
    virtual SceneIterator *Create_Iterator(bool onlyvisible);
    virtual void Destroy_Iterator(SceneIterator *it);
    virtual void Visibility_Check(CameraClass *camera);
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point);
    // ?SimpleSceneClass::rva0006EE1B present-unmatched
    virtual int rva0006EE1B() const { return m_104; }
    // ?SimpleSceneClass::rva001428E0 present-unmatched
    virtual void rva001428E0(const Rva00141F90Bounds &b) { scene_vector.rva00141F90(b); }
    // ?SimpleSceneClass::rva001428F0 present-unmatched
    virtual void rva001428F0(unsigned int level) { scene_vector.Set_Level(level); }

private:
    BfmeSceneVector scene_vector;
    RefRenderObjListClass list_5c;
    RefRenderObjListClass list_74;
    RefRenderObjListClass list_8c;
    RefRenderObjListClass list_a4;
    NonRefRenderObjListClass list_bc;
    NonRefRenderObjListClass list_d4;
    RefRenderObjListClass list_ec;
    int m_104;
protected:
    // Native slots23/25 are Customized_Render141A30/Post_Render_Processing141BB0.
    virtual void Customized_Render(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);
};

// Target constructor142960 installs BD33D0, and initializes spatial34,
// four owning lists5C/74/8C/A4, nonowning BC/D4, owning EC, stamp104=1.
// BFME1 clean ctor is the structural donor; native independent stores prove
// its base fields and list layout. Existing target spatial ctor142900 proves
// vector18/count1C/level24 initialization and 141F90/142060 call sequence.
typedef char SceneCtorTargetSize[(sizeof(SimpleSceneClass)==0x108)?1:-1];
SimpleSceneClass::SimpleSceneClass() : SceneClass(), m_104(1) {}
