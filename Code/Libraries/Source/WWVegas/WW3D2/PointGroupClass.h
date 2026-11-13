// Target facts (BFME 2 1.06; RVAs unless marked VA): constructor 0x00178E50 stores VA 0x00BD4E94 at +0 and initializes fields through float +0x58; allocation 0x0055C8D4 pushes 0x5C before operator new 0x0002FDA0 and constructor call 0x0055C8EA. There is no base-constructor call or inherited table. Destructor 0x00178ED0 restores the same table at 0x00178EEF. Its only slot is scalar deleting destructor 0x00179A20, which calls 0x00178ED0 and conditionally operator delete 0x0002FD60; the following word at VA 0x00BD4E98 is float 0x3F7F0069, not another slot. Caller 0x0055C46E dispatches slot 0 with flag zero.
// Constructor stores and Set_Arrays 0x00179A40 prove six buffer pointers at +4/+8/+0xC/+0x10/+0x14/+0x18, count +0x1C, byte +0x20, texture pointer +0x24, shader word +0x28, mode +0x2C, flags +0x30, size +0x34, color +0x38/+0x3C/+0x40, alpha +0x44, orientation/frame bytes +0x48/+0x49 and viewport floats +0x4C/+0x50/+0x54/+0x58. Destructor 0x00178F70 loads +0x24 and calls TextureClass::Release_Ref 0x0061ED10. Get_Polygon_Count 0x00179160 distinguishes modes 0/1/2. Zero Hour GeneralsMD WW3D2/pointgr.h supplies member, static and enum names; its trailing Billboard byte is absent from the retail 0x5C allocation, so the additional flag uses neutral flag01.
// Rowed methods stay out of line: size 0x00178FA0, color 0x00178FC0/0x00178FF0, alpha 0x00179010, orientation 0x00179020, frame 0x00179040, flags 0x00179060/0x00179090, texture 0x001790A0, shader 0x00665650/0x0013EDB0, mode 0x0066D7A0, frame grid 0x00179130/0x00179140 and prepare_shader 0x00179180. Rowed helpers are 0x00179B50, 0x0017A890, 0x0017D770, 0x0017DDA0, 0x0017F150, 0x0017F1B0, 0x0017F3A0, Render 0x0017F400 and RenderVolumeParticle 0x0017F6E0. Static vector initialization/cleanup at 0x007ACF00/0x007B73C0 binds transformed_loc to VA 0x00DF709C; 0x007B7280/0x007B72C0/0x007B7300/0x007B7340/0x007B7380 bind compressed_loc/diffuse/size/orient/frame to VAs 0x00DF94D0/0x00DF94B0/0x00DB6488/0x00DB6498/0x00DB64A8. All offsets and virtual slots come from retail, independently of donor names.

#ifndef BFME2_WW3D2_POINTGROUPCLASS_H
#define BFME2_WW3D2_POINTGROUPCLASS_H

#include "../WWMath/Vector3Data.h"
#include "ShaderClass.h"

class Vector2;
class Vector4;
class TextureClass;
class RenderInfoClass;
class VertexMaterialClass;
template <class T> class ShareBufferClass;
template <class T> class VectorClass;

class PointGroupClass
{
public:
    enum PointModeEnum { TRIS = 0, QUADS = 1, SCREENSPACE = 2 };
    enum FlagsType { TRANSFORM = 0, flag01 = 1 };

    PointGroupClass();
    virtual ~PointGroupClass();
    PointGroupClass &operator=(const PointGroupClass &);

    void Set_Arrays(ShareBufferClass<Vector3> *,
        ShareBufferClass<Vector4> * = 0,
        ShareBufferClass<unsigned int> * = 0,
        ShareBufferClass<float> * = 0,
        ShareBufferClass<unsigned char> * = 0,
        ShareBufferClass<unsigned char> * = 0,
        int = -1, float = 0.0f, float = 0.0f, float = 0.0f, float = 0.0f);
    void Set_Point_Size(float);
    float Get_Point_Size();
    void Set_Point_Color(Vector3);
    Vector3 Get_Point_Color();
    void Set_Point_Alpha(float);
    float Get_Point_Alpha();
    void Set_Point_Orientation(unsigned char);
    unsigned char Get_Point_Orientation();
    void Set_Point_Frame(unsigned char);
    unsigned char Get_Point_Frame();
    void Set_Point_Mode(PointModeEnum);
    PointModeEnum Get_Point_Mode();
    void Set_Flag(FlagsType, bool);
    int Get_Flag(FlagsType);
    void Set_Texture(TextureClass *);
    TextureClass *Get_Texture();
    TextureClass *Peek_Texture();
    void Set_Shader(ShaderClass);
    ShaderClass Get_Shader();
    unsigned char Get_Frame_Row_Column_Count_Log2();
    void Set_Frame_Row_Column_Count_Log2(unsigned char);
    int Get_Polygon_Count();
    void prepare_shader();
    void Render(RenderInfoClass &, int);
    void RenderVolumeParticle(RenderInfoClass &, unsigned int, void *);
    void rva00913AF0(int, bool);
    void rva009148C0(Vector3 *, float *, unsigned char *, int);
    void rva00912880(Vector4 *, int);
    void rva00916CD0(unsigned char *, int, int);
    void rva00914860(int, int, int *);
    void rva00917920(Vector3 **, Vector4 **, float **, unsigned char **, unsigned char **);
    void rva00917B10(Vector3 *, Vector4 *, float *, unsigned char *, unsigned char *, int, int, int *, int);

    ShareBufferClass<Vector3> *PointLoc;
    ShareBufferClass<Vector4> *PointDiffuse;
    ShareBufferClass<unsigned int> *APT;
    ShareBufferClass<float> *PointSize;
    ShareBufferClass<unsigned char> *PointOrientation;
    ShareBufferClass<unsigned char> *PointFrame;
    int PointCount;
    unsigned char FrameRowColumnCountLog2;
    TextureClass *Texture;
    ShaderClass Shader;
    PointModeEnum PointMode;
    unsigned int Flags;
    float DefaultPointSize;
    Vector3 DefaultPointColor;
    float DefaultPointAlpha;
    unsigned char DefaultPointOrientation;
    unsigned char DefaultPointFrame;
    float VPXMin;
    float VPYMin;
    float VPXMax;
    float VPYMax;

private:
    friend void Rva007B73C0();
    friend void Rva00912CF0();

    static Vector3 _TriVertexLocationOrientationTable[256][3];
    static Vector3 _QuadVertexLocationOrientationTable[256][4];
    static Vector3 _ScreenspaceVertexLocationSizeTable[2][3];
    static Vector2 *_TriVertexUVFrameTable[5];
    static Vector2 *_QuadVertexUVFrameTable[5];
    static VertexMaterialClass *PointMaterial;
    static VectorClass<Vector3> compressed_loc;
    static VectorClass<Vector4> compressed_diffuse;
    static VectorClass<float> compressed_size;
    static VectorClass<unsigned char> compressed_orient;
    static VectorClass<unsigned char> compressed_frame;
    static VectorClass<Vector3> transformed_loc;
};

#endif
