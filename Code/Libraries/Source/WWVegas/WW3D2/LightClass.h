// Target facts (RVAs; tables are VAs): ctor 0x00130AC0 builds on RenderObjClass (0xC4 bytes) and its fields start at +0xC4; ~LightClass 0x00130E80 restores 0x00BD23C0/0x00BD23BC before ~RenderObjClass 0x0013BE20; Clone 0x00130EA0 allocates 0x120 bytes.
// The table keeps RenderObjClass slots 0..128 and adds Is_Vertex_Processor at 129 (0x0050B5C6); slots 2/26/27/67/68 are the rowed Clone, Notify_Added/Removed and object-space bounds. Set_Ambient/Set_Diffuse/Set_Far_Attenuation_Range are rowed at 0x00042EBD/0x00042EDA/0x00042F14.
// Donor names: Zero Hour WW3D2/light.h; its Persist base and Get_Factory/Save/Load slots are absent from these retail tables.
#pragma once

#ifndef BFME2_WW3D2_LIGHTCLASS_H
#define BFME2_WW3D2_LIGHTCLASS_H

#include "rendobj.h"

class LightClass : public RenderObjClass
{
public:
    enum LightType { POINT = 0, DIRECTIONAL, SPOT };
    enum FlagsType { NEAR_ATTENUATION = 0, FAR_ATTENUATION };

    LightClass(LightType type = POINT);
    LightClass(const LightClass &source);
    LightClass &operator=(const LightClass &source);
    virtual ~LightClass();
    virtual RenderObjClass *Clone() const;
    virtual int Class_ID() const;
    virtual void Render(RenderInfoClass &info);
    virtual void Notify_Added(SceneClass *scene);
    virtual void Notify_Removed(SceneClass *scene);
    virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const;
    virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;
    virtual bool Is_Vertex_Processor();

    void Set_Ambient(const Vector3 &color);
    void Set_Diffuse(const Vector3 &color);
    void Set_Far_Attenuation_Range(double start, double end);

    LightType Type;
    unsigned int Flags;
    bool CastShadows;
    float Intensity;
    Vector3 Ambient;
    Vector3 Diffuse;
    Vector3 Specular;
    float NearAttenStart;
    float NearAttenEnd;
    float FarAttenStart;
    float FarAttenEnd;
    float SpotAngle;
    float SpotAngleCos;
    float SpotExponent;
    Vector3 SpotDirection;
};

typedef char Bfme2LightClassExtent[(sizeof(LightClass) == 0x120) ? 1 : -1];

#endif
