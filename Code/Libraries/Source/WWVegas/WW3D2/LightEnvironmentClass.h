// Target facts (BFME 2 1.06, addresses are RVAs): constructor 0x0013F410
// clears byte +0 and int +4 (0x0013F418/0x0013F41A), then initializes data
// through +0x224 (0x0013F611). It has no calls or vtable stores. Assignment
// 0x0014A230 copies +0 as a byte, +4 as a dword, and +8/+0xC/+0x10 as the
// object center; its final dword copy is +0x224 at 0x0014A3D0/0x0014A3D7.
// MeshClass::~MeshClass calls the destructor at 0x0014A60B on its +0xCC
// member; the target 0x0069E440 is a single RET. This class has no virtual
// functions, vtable slots or base subobject. The MeshClass constructor uses
// +0x2F4 for the following member, and RTS3DScene's three environments start
// at +0x164/+0x38C/+0x5B4 (constructor 0x0006F470): sizeof is 0x228.
// Constructor 0x0013F41D/0x0013F433/0x0013F4A8 initializes four input lights
// at +0x14, stride 0x54. Output ambient is +0x164 (0x0013F4B3); four output
// lights occupy +0x170..+0x1CF, stride 0x18 (0x0013F4CB..0x0013F55C).
// FillLight begins at +0x1D0 (0x0013F561); FillIntensity is +0x224.
// Input assignment 0x0013F660 copies vectors at +0/+0xC/+0x18, bytes
// +0x24/+0x25, vector +0x28, floats +0x34/+0x38 and vectors +0x3C/+0x48.
// Its copy constructor is called out of line by Calculate_Fill_Light
// 0x00140010 and folds onto that same 0x0013F660 body (symbols.csv).
// Rowed methods: Add_Light 0x00140770, Pre_Render_Update 0x00140A20,
// Add_Fill_Light 0x0013F7E0, Calculate_Fill_Light 0x00140010,
// Set_Output_Ambient(Vector3&) 0x0006E136, lighting LOD setter/getter
// 0x0013F7B0/0x0013F7D0; input accessors 0x0011C320..0x0011C400 (step 0x20).
// Input methods Init/point-or-spot/directional/Contribution are rowed at
// 0x00140730/0x0013FB60/0x0013F250/0x0013F2E0; output Init is 0x0013F300.
// Reset is named by Zero Hour; retail body 0x0013F620 currently has the
// ledger spelling Gen_0094AC70::bfmeSetPair, not LightEnvironmentClass::Reset.
// Donor facts: Zero Hour WW3D2/lightenvironment.h supplies the nested type,
// field and method names. BFME 2 adds the unnamed leading byte, shifting
// those fields by four. The donor has no base or virtual functions either.

#pragma once

#ifndef BFME2_LIGHTENVIRONMENTCLASS_H
#define BFME2_LIGHTENVIRONMENTCLASS_H

#include "../WWMath/Vector3Data.h"

class Matrix3D;
class LightClass;

class LightEnvironmentClass
{
public:
    LightEnvironmentClass();
    ~LightEnvironmentClass();
    LightEnvironmentClass &operator=(const LightEnvironmentClass &that);

    void Reset(const Vector3 &object_center, const Vector3 &scene_ambient);
    void Add_Light(const LightClass &light);
    void Pre_Render_Update(const Matrix3D &camera_tm);
    void Add_Fill_Light();
    void Calculate_Fill_Light();
    void Set_Output_Ambient(Vector3 &ambient);
    void Set_Fill_Intensity(float intensity) { FillIntensity = intensity; }
    const Vector3 &Get_Equivalent_Ambient() const { return OutputAmbient; }
    int Get_Light_Count() const { return LightCount; }
    const Vector3 &Get_Light_Direction(int index) const;
    const Vector3 &Get_Light_Diffuse(int index) const;
    bool isPointLight(int index) const;
    float getPointIrad(int index) const;
    float getPointOrad(int index) const;
    const Vector3 &getPointDiffuse(int index) const;
    const Vector3 &getPointAmbient(int index) const;
    const Vector3 &getPointCenter(int index) const;
    static void Set_Lighting_LOD_Cutoff(float intensity);
    static float Get_Lighting_LOD_Cutoff();
    enum { MAX_LIGHTS = 4 };
    static int Get_Max_Lights() { return MAX_LIGHTS; }

    struct InputLightStruct
    {
        InputLightStruct()
            : Direction(0.0f, 0.0f, 0.0f), Ambient(0.0f, 0.0f, 0.0f),
              Diffuse(0.0f, 0.0f, 0.0f), DiffuseRejected(false), m_point(false),
              m_center(0.0f, 0.0f, 0.0f), m_innerRadius(0.0f), m_outerRadius(0.0f),
              m_ambient(0.0f, 0.0f, 0.0f), m_diffuse(0.0f, 0.0f, 0.0f) {}
        InputLightStruct(const InputLightStruct &that);
        InputLightStruct &operator=(const InputLightStruct &that);
        void Init(const LightClass &light, const Vector3 &object_center);
        void Init_From_Point_Or_Spot_Light(const LightClass &light, const Vector3 &object_center);
        void Init_From_Directional_Light(const LightClass &light, const Vector3 &object_center);
        float Contribution();

        Vector3 Direction;
        Vector3 Ambient;
        Vector3 Diffuse;
        bool DiffuseRejected;
        bool m_point;
        Vector3 m_center;
        float m_innerRadius;
        float m_outerRadius;
        Vector3 m_ambient;
        Vector3 m_diffuse;
    };

    struct OutputLightStruct
    {
        void Init(const InputLightStruct &input, const Matrix3D &camera_tm);
        Vector3 Direction;
        Vector3 Diffuse;
    };

    unsigned char field00;
    int LightCount;
    Vector3 ObjectCenter;
    InputLightStruct InputLights[MAX_LIGHTS];
    Vector3 OutputAmbient;
    OutputLightStruct OutputLights[MAX_LIGHTS];
    InputLightStruct FillLight;
    float FillIntensity;
};

#endif // BFME2_LIGHTENVIRONMENTCLASS_H
