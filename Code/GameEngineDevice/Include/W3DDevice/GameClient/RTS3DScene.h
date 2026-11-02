// Target facts (BFME 2 1.06; addresses are RVAs unless marked VA):
// Constructor 0x0006F470 calls SimpleSceneClass 0x00142960 at +0 and
// SubsystemInterface 0x001B4E63 at +0x108, then stores VA 0x00BC63C8 at
// +0 and VA 0x00BC6390 at +0x108 (0x0006F4A2/0x0006F4A8). Destructor
// 0x0006F7BD restores the identical pair at 0x0006F7D1/0x0006F7D7;
// it subsequently calls the base destructors 0x001B4E74 and 0x00141DF0.
// The base tables VA 0x00BD77A0/0x00BD33D0 belong to those base lifetimes.
// VA 0x00BC63C8 has 28 virtual slots: 0 Delete_This (0x0006CE57),
// 1 deleting destructor (0x0006FB2F), 2 Add_Render_Object (0x001413A0),
// 3 Remove_Render_Object (0x00141860), 4 Create_Iterator (0x00141CD0),
// 5 Destroy_Iterator (0x006132A0), 6 Set_Ambient_Light (0x0006E265),
// 7 Get_Ambient_Light (0x005C4AD5), 8/9 fog enable (0x0006EDE3/0x004C54EC),
// 10/11 fog color (0x00049F0F/0x004F5FA3), 12/13 fog range
// (0x0006EDED/0x0006EE06), 14/15 Register/Unregister
// (0x00141400/0x001414D0), 16 Compute_Point_Visibility (0x001418F0),
// 17 getter (0x0006EE1B), 18/19 forwarders (0x001428E0/0x001428F0),
// 20/21 Save/Load (0x00140CF0/0x00140DC0), 22 Render (0x00071E40),
// 23 Customized_Render (0x0007054F), 24 empty RET4 (0x0047A69C),
// 25 Post_Render_Processing (0x00141BB0), 26 Remove_All_Render_Objects
// (0x00141370), 27 Visibility_Check (0x00071245). Zero Hour scene.h
// names the shared operations; the extra slots 17-19 retain neutral names.
// VA 0x00BC6390 has 14 slots, ending exactly at VA 0x00BC63C8.
// Slot 0 is 0x0006F796 (subtract 0x108, jump 0x0006FB2F); slot 12
// is 0x0006ED55 (read secondary-this+0x70C, render primary-this).
// 0x0006ED36 stores the camera at +0x814, dispatches secondary slot 12,
// then clears +0x814. Allocation 0x00046B38 pushes 0x818 before new
// 0x0002FDA0 and constructor call 0x00046B53: sizeof 0x818.
// SceneClass ctor 0x00140C60 establishes +8 ambient, +0x14/+0x18 modes,
// +0x1C fog byte, +0x20 fog color and +0x2C/+0x30 fog range. SimpleScene
// ctor 0x00142960 establishes spatial +0x34 (0x28 bytes), seven 0x18-byte
// lists at +0x5C/+0x74/+0x8C/+0xA4/+0xBC/+0xD4/+0xEC and token +0x104.
// Scene ctor 0x0006F470 constructs a list at +0x114 (table VA 0x00BC6260)
// and three 0x228-byte LightEnvironmentClass members at +0x164/+0x38C/+0x5B4.
// Its writes establish byte +0x12C, four pointers +0x130, scratch +0x140,
// three floats +0x144, four pointers +0x150, count +0x160, byte +0x7DC,
// pointers +0x7E0/+0x7E4/+0x7E8, mode +0x7EC, counts +0x7F0/+0x7F8,
// buffers +0x7F4/+0x7FC/+0x800/+0x804, counts +0x808/+0x80C/+0x810.
// GenericMultiList ctor 0x00065815 establishes a vptr and five-dword node;
// createLightsIterator 0x0006F927 takes the +0x8C list, reads its +8 head,
// and returns an eight-byte iterator. Dynamic light body 0x0006F94A instead
// traverses the +0x114 list (sentinel +0x118, next +0x11C).
// LightEnvironment Set_Output_Ambient 0x0006E136 copies the three dwords
// at +0x164/+0x168/+0x16C; Zero Hour lightenvironment.h names OutputAmbient.
// Its assignment 0x0014A230 is out of line, as are Add_Light 0x00140770
// and Pre_Render_Update 0x00140A20. Zero Hour multilist.h names the five
// node fields and MultiListNodeClass; 0x0006F94A reads Next+4 and Object+0xC.
// Rowed nonvirtual methods: Flush 0x00071606, getADynamicLight 0x0006F94A,
// doRender 0x0006ED36, rva0006E5A0/5C8/605 at their named RVAs,
// rva00070F80/710D6/72109 at their named RVAs, renderOneObject 0x0006FB59,
// updateFixedLightEnvironments 0x0006E716, flushOccludedObjectsIntoStencil
// 0x00070841. The row named getCustomPassMode at 0x0026FF4F reads +0x58C;
// it remains a declaration and supplies no evidence for the +0x7EC field.
// Donor facts: Zero Hour W3DScene.h supplies the shared member and accessor
// names. The third light environment and unknown bytes retain neutral names.

#pragma once
#ifndef BFME2_RTS3DSCENE_H
#define BFME2_RTS3DSCENE_H

#define BFME_SUBSYSTEM_SLOTS
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

class CameraClass;
class ChunkLoadClass;
class ChunkSaveClass;
class LightClass;
class MaterialPassClass;
class RayCollisionTestClass;
class RenderInfoClass;
class RenderObjClass;
class SceneIterator;
class W3DDynamicLight;
class W3DShroudMaterialPassClass;
class Matrix3D;
class MultiListObjectClass;
class GenericMultiListClass;
enum CustomScenePassModes;

class MultiListNodeClass
{
public:
    MultiListNodeClass *Prev;
    MultiListNodeClass *Next;
    MultiListNodeClass *NextList;
    MultiListObjectClass *Object;
    GenericMultiListClass *List;
};

class GenericMultiListClass
{
public:
    GenericMultiListClass() throw();
    virtual ~GenericMultiListClass();
    MultiListNodeClass Head;
};

template<class T> class RefMultiListClass : public GenericMultiListClass
{
public:
    bool Add(T *object, bool onlyOnce = false);
    bool Remove(T *object);
    bool Release_Head();
};

template<class T> class RefMultiListIterator
{
public:
    RefMultiListIterator(RefMultiListClass<T> *list) : m_list(list), m_current(list->Head.Next) {}
    RefMultiListClass<T> *m_list;
    MultiListNodeClass *m_current;
};

class BfmeRefSceneList : public GenericMultiListClass
{
public:
    BfmeRefSceneList() {}
    virtual ~BfmeRefSceneList();
};

class LightEnvironmentClass
{
public:
    LightEnvironmentClass();
    ~LightEnvironmentClass();
    LightEnvironmentClass &operator=(const LightEnvironmentClass &other);
    void Add_Light(const LightClass &light);
    void Pre_Render_Update(const Matrix3D &camera);
    void Set_Output_Ambient(Vector3 &ambient);
    char m_field000[0x164];
    Vector3 OutputAmbient;
    char m_field170[0x228 - 0x170];
};

class SceneClass : public RefCountClass
{
public:
    SceneClass();
    virtual ~SceneClass();
    virtual void Add_Render_Object(RenderObjClass *object);
    virtual void Remove_Render_Object(RenderObjClass *object);
    virtual SceneIterator *Create_Iterator() = 0;
    virtual void Destroy_Iterator(SceneIterator *iterator) = 0;
    virtual void Set_Ambient_Light(const Vector3 &color);
    virtual const Vector3 &Get_Ambient_Light();
    virtual void Set_Fog_Enable(bool enable);
    virtual bool Get_Fog_Enable();
    virtual void Set_Fog_Color(const Vector3 &color);
    virtual const Vector3 &Get_Fog_Color();
    virtual void Set_Fog_Range(float start, float end);
    virtual void Get_Fog_Range(float *start, float *end);
    enum RegType { ON_FRAME_UPDATE = 0, LIGHT, RELEASE };
    virtual void Register(RenderObjClass *object, RegType reason) = 0;
    virtual void Unregister(RenderObjClass *object, RegType reason) = 0;
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point);
    virtual int slot17() const = 0;
    virtual void slot18(const void *bounds) = 0;
    virtual void slot19(unsigned int level) = 0;
    virtual void Save(ChunkSaveClass &save);
    virtual void Load(ChunkLoadClass &load);
    virtual void Render(RenderInfoClass &info);
    virtual void Customized_Render(RenderInfoClass &info) = 0;
    virtual void slot24(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);

    Vector3 AmbientLight;
    int PolyRenderMode;
    int ExtraPassPolyRenderMode;
    bool FogEnabled;
    Vector3 FogColor;
    float FogStart;
    float FogEnd;
};

class SimpleSceneClass : public SceneClass
{
public:
    SimpleSceneClass();
    virtual ~SimpleSceneClass();
    virtual void Add_Render_Object(RenderObjClass *object);
    virtual void Remove_Render_Object(RenderObjClass *object);
    virtual SceneIterator *Create_Iterator();
    virtual void Destroy_Iterator(SceneIterator *iterator);
    virtual void Register(RenderObjClass *object, RegType reason);
    virtual void Unregister(RenderObjClass *object, RegType reason);
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point);
    virtual int slot17() const;
    virtual void slot18(const void *bounds);
    virtual void slot19(unsigned int level);
    virtual void Customized_Render(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);
    virtual void Remove_All_Render_Objects();
    virtual void Visibility_Check(CameraClass *camera);

    char m_field034[0x28];
    RefMultiListClass<RenderObjClass> RenderList;
    RefMultiListClass<RenderObjClass> UpdateList;
    RefMultiListClass<RenderObjClass> LightList;
    RefMultiListClass<RenderObjClass> ReleaseList;
    GenericMultiListClass m_field0BC;
    GenericMultiListClass m_field0D4;
    RefMultiListClass<RenderObjClass> m_field0EC;
    int m_field104;
};

struct TreeOpaqueMapped00372FF4;
namespace _STL {
template<class T> struct less;
template<class T> class allocator;
template<class A, class B> struct pair;
template<class Key, class Value, class Compare, class Allocator> class multimap;
}

class RTS3DScene : public SimpleSceneClass, public SubsystemInterface
{
public:
    RTS3DScene();
    virtual ~RTS3DScene();
    virtual void Customized_Render(RenderInfoClass &info);
    virtual void Visibility_Check(CameraClass *camera);
    virtual void Render(RenderInfoClass &info);
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void vslot12();

    RefMultiListIterator<RenderObjClass> *createLightsIterator();
    void destroyLightsIterator(RefMultiListIterator<RenderObjClass> *iterator);
    W3DDynamicLight *getADynamicLight();
    CustomScenePassModes getCustomPassMode();
    void setCustomPassMode(CustomScenePassModes mode) { m_customPassMode = mode; }
    void drawTerrainOnly(bool draw) { m_drawTerrainOnly = draw; }
    RefMultiListClass<RenderObjClass> *getDynamicLights() { return reinterpret_cast<RefMultiListClass<RenderObjClass> *>(&m_dynamicLightList); }
    LightEnvironmentClass &getDefaultLightEnv() { return m_defaultLightEnv; }
    void Flush(RenderInfoClass &info);
    void doRender(CameraClass *camera);
    void rva0006E5A0(Vector3 *destination);
    void rva0006E5C8(Vector3 *source);
    void rva0006E605(Vector3 *source, bool remove);
    void rva00070F80(RenderInfoClass &info);
    void rva000710D6(RenderInfoClass &info);
    void rva00072109(RayCollisionTestClass &ray, int collisionType,
        _STL::multimap<float, TreeOpaqueMapped00372FF4, _STL::less<float>,
        _STL::allocator<_STL::pair<const float, TreeOpaqueMapped00372FF4> > > &hits);
protected:
    void renderOneObject(RenderInfoClass &info, RenderObjClass *object, int localPlayerIndex, int flag);
    void updateFixedLightEnvironments(RenderInfoClass &info);
    void flushOccludedObjectsIntoStencil(RenderInfoClass &info);
public:
    BfmeRefSceneList m_dynamicLightList;
    bool m_drawTerrainOnly;
    LightClass *m_globalLight[4];
    LightClass *m_scratchLight;
    Vector3 m_infantryAmbient;
    LightClass *m_infantryLight[4];
    int m_numGlobalLights;
    LightEnvironmentClass m_defaultLightEnv;
    LightEnvironmentClass m_foggedLightEnv;
    LightEnvironmentClass m_field5B4;
    bool m_field7DC;
    W3DShroudMaterialPassClass *m_shroudMaterialPass;
    MaterialPassClass *m_heatVisionMaterialPass;
    MaterialPassClass *m_heatVisionOnlyPass;
    CustomScenePassModes m_customPassMode;
    int m_translucentObjectsCount;
    RenderObjClass **m_translucentObjectsBuffer;
    int m_occludedObjectsCount;
    RenderObjClass **m_potentialOccluders;
    RenderObjClass **m_potentialOccludees;
    RenderObjClass **m_nonOccludersOrOccludees;
    int m_numPotentialOccluders;
    int m_numPotentialOccludees;
    int m_numNonOccluderOrOccludee;
    CameraClass *m_camera;
};

typedef char RTS3DSceneSizeCheck[sizeof(RTS3DScene) == 0x818 ? 1 : -1];
typedef char RTS3DSceneBaseSizeCheck[sizeof(SimpleSceneClass) == 0x108 ? 1 : -1];

#endif
