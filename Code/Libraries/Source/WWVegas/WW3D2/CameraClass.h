// Target facts (BFME 2 1.06; method addresses are RVAs, tables are VAs): CameraClass constructor 0x00134AB0 calls RenderObjClass constructor 0x0013BF00 at 0x00134AD0, then installs 0x00BD26E0 at +0 and 0x00BD26D8 at +8 (0x00134AE8/0x00134AEE). Copy constructor 0x00134C50 installs the same tables; destructor 0x00133A00 restores both and jumps to RenderObjClass destructor 0x0013BE20, which restores 0x00BD2F68/0x00BD2F60. The secondary table has one slot, the -8 deleting-destructor thunk 0x00133EE0 to 0x00133EF0; the following word is zero. Clone 0x00135330 allocates 0x3FC at 0x00135347 and calls the copy constructor at 0x00135369; the copy reaches +0x3F8. CameraClass is polymorphic, derives from the 0xC4-byte RenderObjClass.
// Target facts: primary slots 0..128 retain the RenderObjClass interface; overrides are destructor (1, 0x00133EF0), Clone (2, 0x00135330), Class_ID (3, 0x0007C3F8), Render (12, 0x0047A69C), Set_Transform (21, 0x00133A90), Set_Position (22, 0x00133AB0), and object-space bounds (0x00133A20/0x00133A50). Slots 129/130 point to Cull_Sphere 0x00135960 and Cull_Box 0x00135990; the next word is 0x3FAAAAAB, not a code pointer. Constructor 0x00134AB0 places Projection +0xC4, viewport +0xC8, view plane +0xD8, aspect +0xE8, near/far +0xEC/+0xF0, depth range +0xF4/+0xF8, validity byte +0xFC, and two frusta +0x100/+0x208. Get_View_Plane 0x00134080, Get_Clip_Planes 0x00133D30, Get_Aspect_Ratio 0x00133D90, Update_Frustum 0x001340B0, and getters 0x00135950/0x00134A60/0x00134A70 independently identify bounds +0x310, projection +0x34C, and inverse view +0x3CC. Setter 0x00133DA0 copies sixteen dwords at +0x38C. Constructors, destructor, copy/assignment 0x00135010 and all rowed accessors remain out of line; the ledger currently spells the two culling bodies as nonvirtual even though the retail table contains them. Rowed nonvirtual API (RVAs): Set_Projection_Type 0x0007B261; Set_Viewport 0x0007E6A6; Get_Viewport 0x004DE9CA; Get_Frustum 0x0004CB06; Get_Frustum_Corners 0x00140C50; Set_View_Plane(float,float) 0x00133AD0 and (Vector2,Vector2) 0x00134020; Set_Aspect_Ratio 0x00133B70; Un_Project 0x00133BC0; Set_Clip_Planes 0x00133D00; Get_Clip_Planes 0x00133D30; horizontal/vertical FOV 0x00133D50/0x00133D70; Get_Aspect_Ratio 0x00133D90; Set_Reflected_Projection_Matrix 0x00133DA0; Convert_Old 0x00133E40; Compute_Projected_Sphere_Radius 0x00133E80; Get_View_Plane 0x00134080; Device_To_View_Space 0x00134650; Device_To_World_Space 0x00134730; Get_Projection_Matrix(Matrix4*) 0x00134820 and () 0x00134A60; Get_D3D_Projection_Matrix 0x001348C0; Get_View_Matrix(Matrix3D*) 0x001349E0 and () 0x00134A70; rva00134A80 0x00134A80; Project 0x00135390; Project_Camera_Space_Point 0x001355E0; Transform_To_View_Space 0x00135770; Rotate_To_View_Space 0x00135870; Get_Near_Clip_Bounding_Box 0x00135950; Apply 0x00135A70.
// Donor facts: Zero Hour GeneralsMD WW3D2/camera.h supplies ViewportClass's Min/Max, the projection enums and the method/parameter names corroborated by those retail bodies. BFME 2's second projection matrix at +0x38C shifts the inverse matrix to +0x3CC; unexpanded aggregate storage retains neutral names. The donor Get_Depth accessor returns ZFar; retail pick-ray 0x001028AA reads that float at +0xF0 at 0x001029B6. The donor camera header is not included.

#pragma once

#ifndef BFME2_WW3D2_CAMERA_CLASS_H
#define BFME2_WW3D2_CAMERA_CLASS_H

#include "rendobj.h"
#include "ViewportClass.h"

class Matrix4;
class FrustumClass;
class PlaneClass;
class OBBoxClass;

class CameraClass : public RenderObjClass
{
public:
    enum ProjectionType { PERSPECTIVE = 0, ORTHO = 1 };
    enum ProjectionResType { INSIDE_FRUSTUM, OUTSIDE_FRUSTUM, OUTSIDE_NEAR_CLIP, OUTSIDE_FAR_CLIP };

    CameraClass();
    CameraClass(const CameraClass &source);
    CameraClass &operator=(const CameraClass &source);
    virtual ~CameraClass();
    virtual RenderObjClass *Clone() const;
    virtual int Class_ID() const;
    virtual void Render(RenderInfoClass &info);
    virtual void Set_Transform(const Matrix3D &transform);
    virtual void Set_Position(const Vector3 &position);
    virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const;
    virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;
    virtual bool Cull_Sphere(const SphereClass &sphere) const;
    virtual bool Cull_Box(const AABoxClass &box) const;

    float Get_Depth() const { return ZFar; }
    void Set_Projection_Type(ProjectionType type);
    void Set_Clip_Planes(float near_clip, float far_clip);
    void Get_Clip_Planes(float &near_clip, float &far_clip) const;
    void Set_View_Plane(const Vector2 &minimum, const Vector2 &maximum);
    void Set_View_Plane(float horizontal_fov, float vertical_fov = -1.0f);
    void Get_View_Plane(Vector2 &minimum, Vector2 &maximum) const;
    void Set_Aspect_Ratio(float aspect);
    float Get_Aspect_Ratio() const;
    float Get_Horizontal_FOV() const;
    float Get_Vertical_FOV() const;
    void Get_Projection_Matrix(Matrix4 *matrix);
    const Matrix4 &Get_Projection_Matrix();
    void Get_D3D_Projection_Matrix(Matrix4 *matrix);
    void rva00134A80(Matrix4 *matrix);
    void Get_View_Matrix(Matrix3D *matrix);
    const Matrix3D &Get_View_Matrix();
    void Set_Reflected_Projection_Matrix(const Matrix4 &matrix);
    ProjectionResType Project(Vector3 &destination, const Vector3 &point) const;
    ProjectionResType Project_Camera_Space_Point(Vector3 &destination, const Vector3 &point) const;
    void Un_Project(Vector3 &destination, const Vector2 &point) const;
    void Transform_To_View_Space(Vector3 &destination, const Vector3 &point) const;
    void Rotate_To_View_Space(Vector3 &destination, const Vector3 &vector) const;
    void Set_Viewport(const Vector2 &minimum, const Vector2 &maximum);
    const ViewportClass &Get_Viewport() const;
    const FrustumClass &Get_Frustum() const;
    const Vector3 *Get_Frustum_Corners() const;
    const OBBoxClass &Get_Near_Clip_Bounding_Box() const;
    void Device_To_View_Space(const Vector2 &device, Vector3 *view);
    void Device_To_World_Space(const Vector2 &device, Vector3 *world);
    float Compute_Projected_Sphere_Radius(float distance, float radius);
    void Apply();
    static void Convert_Old(Vector3 &position);

protected:
    void Update_Frustum() const;

public:
    ProjectionType Projection;
    ViewportClass Viewport;
    ViewportClass ViewPlane;
    float AspectRatio;
    float ZNear;
    float ZFar;
    float ZBufferMin;
    float ZBufferMax;
    mutable bool FrustumValid;
    char field0FD[3];
    mutable char field100[0x108];
    mutable char field208[0x108];
    mutable char field310[0x3C];
    mutable char field34C[0x40];
    mutable char field38C[0x40];
    mutable char field3CC[0x30];
};

#endif
