// cl: /DNDEBUG /MD /EHsc /Ob2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)

class RenderObjClass;

struct BfmeSceneListNode
{
    void *prev;
    void *next;
    void *next_list;
    void *object_link;
    void *list;
};

class BfmeRefSceneList
{
public:
    virtual ~BfmeRefSceneList();
    BfmeSceneListNode head;

    RenderObjClass *Peek_Head()
    {
        BfmeSceneListNode *node = (BfmeSceneListNode *)head.next;
        if (node == &head || node->object_link == 0)
            return 0;
        return (RenderObjClass *)((char *)node->object_link - 8);
    }
};

class BfmeNonRefSceneList
{
public:
    virtual ~BfmeNonRefSceneList();
    BfmeSceneListNode head;
};

class BfmeSceneVectorElement
{
public:
    ~BfmeSceneVectorElement();
    static void operator delete[](void *ptr);
    unsigned char pad[0x1c];
};

// Retail's cleanup destroys this at +0x34 of the scene, through 0x00141D90, which reads
// the array at +0x18: it is the whole member, not just the part the destructor touches.
class BfmeSceneVector
{
public:
    void release_vector()
    {
        if (vector)
            delete[] vector;
    }

    ~BfmeSceneVector()
    {
        release_vector();
    }

    unsigned char pad_to_unused[0x14];
    void *unused;
    BfmeSceneVectorElement *vector;
    int vector_max;
    int active_count;
};

class SceneIterator;
class Vector3;
class RenderInfoClass;
class CameraClass;
class ChunkSaveClass;
class ChunkLoadClass;
struct Rva00141F90Bounds;

// SceneClass's table as SimpleSceneClassConstructorBFME2.cpp declares it, so
// this unit's ??_7SimpleSceneClass copy is the same 28-slot table (BD33D0).
// Retail's destructor ends with RefCountClass's table: no SceneClass store.
class SceneClass : public RefCountClass
{
public:
    virtual ~SceneClass() {}
    virtual void Add_Render_Object(RenderObjClass *obj);
    virtual void Remove_Render_Object(RenderObjClass *obj);
    virtual SceneIterator *Create_Iterator() = 0;
    virtual void Destroy_Iterator(SceneIterator *it) = 0;
    virtual void Set_Ambient_Light(const Vector3 &color);
    virtual const Vector3 &Get_Ambient_Light();
    virtual void Set_Fog_Enable(bool set);
    virtual bool Get_Fog_Enable();
    virtual void Set_Fog_Color(const Vector3 &color);
    virtual const Vector3 &Get_Fog_Color();
    virtual void Set_Fog_Range(float start, float end);
    virtual void Get_Fog_Range(float *start, float *end);
    enum RegType { ON_FRAME_UPDATE = 0, LIGHT, RELEASE };
    virtual void Register(RenderObjClass *obj, RegType for_what) = 0;
    virtual void Unregister(RenderObjClass *obj, RegType for_what) = 0;
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point);
    virtual int rva0006EE1B() const = 0;
    virtual void rva001428E0(const Rva00141F90Bounds &) = 0;
    virtual void rva001428F0(unsigned int) = 0;
    virtual void Save(ChunkSaveClass &save);
    virtual void Load(ChunkLoadClass &load);
protected:
    virtual void Render(RenderInfoClass &info);
private:
    virtual void Customized_Render(RenderInfoClass &info) = 0;
    virtual void Pre_Render_Processing(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);
};

// The destructor's unwind funclet destroys the base by jumping to 0x00724510,
// where ICF folds SceneClass's empty destructor onto CullableClass's. That
// 7-byte body cannot prove the fold for a ??1SceneClass pin, so the base keeps
// its pinned TU-private name: an empty layer with no slots or data of its own.
class BfmeSceneBase : public SceneClass
{
public:
    virtual ~BfmeSceneBase() {}
};

class SimpleSceneClass : public BfmeSceneBase
{
public:
    virtual ~SimpleSceneClass();
    virtual void Add_Render_Object(RenderObjClass *obj);
    virtual void Remove_Render_Object(RenderObjClass *obj);
    virtual void Remove_All_Render_Objects();
    virtual void Register(RenderObjClass *obj, RegType for_what);
    virtual void Unregister(RenderObjClass *obj, RegType for_what);
    virtual SceneIterator *Create_Iterator();
    virtual void Destroy_Iterator(SceneIterator *it);
    virtual void Visibility_Check(CameraClass *camera);
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point);
    virtual int rva0006EE1B() const;
    virtual void rva001428E0(const Rva00141F90Bounds &b);
    virtual void rva001428F0(unsigned int level);
protected:
    virtual void Customized_Render(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);

private:
    void remove_all_render_objects()
    {
        RenderObjClass *obj;
        while ((obj = render_list.Peek_Head()) != 0)
            Remove_Render_Object(obj);
    }

    unsigned char pad_to_vector[0x40 - 0x14];
    BfmeSceneVector scene_vector;
    unsigned char pad_to_render_list[4];
    BfmeRefSceneList render_list;
    BfmeRefSceneList update_list;
    BfmeRefSceneList light_list;
    BfmeRefSceneList release_list;
    BfmeNonRefSceneList list_bc;
    BfmeNonRefSceneList list_d4;
    BfmeRefSceneList visible_list;
};

SimpleSceneClass::~SimpleSceneClass()
{
    remove_all_render_objects();
}

#pragma comment(linker, "/alternatename:??_VBfmeSceneVectorElement@@SAXPAX@Z=??_V@YAXPAX@Z")

#pragma comment(linker, "/alternatename:??1BfmeSceneVectorElement@@QAE@XZ=??1Rva00141D00@@QAE@XZ")
