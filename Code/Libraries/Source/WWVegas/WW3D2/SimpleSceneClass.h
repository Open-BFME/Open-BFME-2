// Target facts (BFME2 1.06; code addresses are RVAs, tables are VAs): constructor 0x00142960 stores 0x00BD33D0 at +0 (0x001429D5); destructor 0x00141DF0 restores it at 0x00141E0F, then restores RefCountClass's 0x00BC650C at 0x00141ED7 after member teardown. The latter is the base lifetime, not a second SimpleSceneClass table. SceneClass constructor 0x00140C60 stores 0x00BD3350 and initializes the same prefix through +0x30: count +4, ambient +8, modes +0x14/+0x18, fog byte +0x1C, color +0x20 and range +0x2C/+0x30. The inlined prefix in 0x00142960 and spatial member construction at +0x34 establish SceneClass at +0 with size 0x34; the registered RefCountClass header owns its eight-byte base.
// Target facts: table 0x00BD33D0 has 28 code words and ends at non-code 0x00BD3440. Slots 0/1 are Delete_This 0x0006CE57/deleting destructor 0x001426B0; 2/3 Add/Remove_Render_Object 0x001413A0/0x00141860; 4/5 Create/Destroy_Iterator 0x00141CD0/0x006132A0; 6-13 ambient and fog 0x0006E265/0x005C4AD5/0x0006EDE3/0x004C54EC/0x00049F0F/0x004F5FA3/0x0006EDED/0x0006EE06; 14/15 Register/Unregister 0x00141400/0x001414D0; 16 Compute_Point_Visibility 0x001418F0; 17 getter 0x0006EE1B reads +0x104; 18/19 0x001428E0/0x001428F0 forward this+0x34 to 0x00141F90/0x00142060; 20/21 Save/Load 0x00140CF0/0x00140DC0; 22 Render 0x00141170; 23 Customized_Render 0x00141A30; 24 empty ret4 0x0047A69C; 25 Post_Render_Processing 0x00141BB0; 26 Remove_All_Render_Objects 0x00141370; 27 Visibility_Check 0x001426D0. There is no Get_Scene_ID slot. Rowed virtual destructors and methods stay out of line.
// Target facts: 0x00142960 initializes spatial +0x34 (0x28 bytes), owning lists +0x5C/+0x74/+0x8C/+0xA4/+0xEC (table 0x00BC6260), nonowning lists +0xBC/+0xD4 (0x00BD33B8) and int +0x104 = 1 at 0x00142B7A. Destructor calls 0x0006F29B on the five owning lists and 0x00141780 on the two others; 0x00141EA9 reads the spatial array at +0x4C. Spatial constructor 0x00142900, rescale 0x00141F90 and Set_Level 0x00142060 establish six floats, array +0x18, count +0x1C, float +0x20 and level +0x24 within that member. Create_Iterator 0x00141CD0 takes +0x5C without a bool parameter; Post_Render_Processing 0x00141BB0 uses +0xA4. SimpleSceneClass's extent is 0x108; RTS3DScene constructor 0x0006F470 places its next base at +0x108. Donor facts: Zero Hour GeneralsMD WW3D2/scene.h names the shared scene methods, ambient/fog fields and RenderList/UpdateList/LightList/ReleaseList; WWLib/multilist.h names RefMultiListClass and its operations. Additional fields and slots retain neutral names.
#pragma once
#ifndef BFME2_SIMPLE_SCENE_CLASS_H
#define BFME2_SIMPLE_SCENE_CLASS_H

#include "../WWLib/RefCountData.h"
#include "../WWLib/GenericMultiListClass.h"
#include "../WWMath/Vector3Data.h"

class CameraClass;
class ChunkLoadClass;
class ChunkSaveClass;
class RenderInfoClass;
class RenderObjClass;
class SceneIterator;
class Rva00141D00;

struct Rva00141F90Bounds
{
    float m_00, m_04, m_08, m_0C, m_10, m_14;
};

class BfmeSceneVector
{
public:
    BfmeSceneVector();
    void rva00141F90(const Rva00141F90Bounds &bounds);
    void Set_Level(unsigned int level);

    Rva00141F90Bounds m_field000;
    Rva00141D00 *m_field018;
    int m_field01C;
    float m_field020;
    unsigned int m_field024;
};

template <class T> class RefMultiListClass : public GenericMultiListClass
{
public:
    virtual ~RefMultiListClass();
    bool Add(T *object, bool onlyonce = true);
    bool Add_Tail(T *object, bool onlyonce = true);
    bool Remove(T *object);
    T *Remove_Head();
    T *Peek_Head();
    bool Release_Head();
    void Reset_List();
};

class BfmeNonRefSceneList : public GenericMultiListClass
{
public:
    BfmeNonRefSceneList();
    virtual ~BfmeNonRefSceneList();
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
    virtual void slot18(const Rva00141F90Bounds &bounds) = 0;
    virtual void slot19(unsigned int level) = 0;
    virtual void Save(ChunkSaveClass &save);
    virtual void Load(ChunkLoadClass &load);

protected:
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
    virtual void Customized_Render(RenderInfoClass &info) = 0;
    virtual void Pre_Render_Processing(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);
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
    virtual int slot17() const { return m_field104; }
    virtual void slot18(const Rva00141F90Bounds &bounds) { m_field034.rva00141F90(bounds); }
    virtual void slot19(unsigned int level) { m_field034.Set_Level(level); }
    virtual void Remove_All_Render_Objects();
    virtual void Visibility_Check(CameraClass *camera);

    BfmeSceneVector m_field034;
    RefMultiListClass<RenderObjClass> RenderList;
    RefMultiListClass<RenderObjClass> UpdateList;
    RefMultiListClass<RenderObjClass> LightList;
    RefMultiListClass<RenderObjClass> ReleaseList;
    BfmeNonRefSceneList m_field0BC;
    BfmeNonRefSceneList m_field0D4;
    RefMultiListClass<RenderObjClass> m_field0EC;
    int m_field104;

protected:
    virtual void Customized_Render(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);
};

typedef char SimpleSceneClassSizeCheck[sizeof(SimpleSceneClass) == 0x108 ? 1 : -1];

#endif
