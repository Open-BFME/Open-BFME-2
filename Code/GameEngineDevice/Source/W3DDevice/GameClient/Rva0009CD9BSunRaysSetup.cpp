// LM_SunRays customized-render setup at 0x0009CD9B (1984B).
// Decoded from the retail body: two Create_Render_Obj calls (the host's +0xD4
// and "LM_SunRays" +0x188), the +0x18C/+0x190/+0x194 sub-object bindings via
// rva0009C0EB, the mesh texture assignment, two sun-ray matrix builds with
// sin/cos, the livingworld.txt atof pass into the DE5E00 globals and the
// SegmentedLineClass setup. Unrowed 0x9C18A/0x9B28C keep Rva-named methods.
// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /arch:SSE /G7 /MD /EHsc
// The two-entry livingworld arrays below own their retail zero-filled storage.

// Retail corrections: guarded resources, complete light colors/transforms and unchecked file reads.
// Texture ownership and line allocation follow retail; original class identity remains unresolved.
#include <new>
#include <stdio.h>
#include <stdlib.h>
#define inline static inline
#include <math.h>
#undef inline
#include "ascii_string.h"
#include "Lib/Coord2D.h"

class Vector3 {
public:
    float X, Y, Z;
    Vector3 &operator=(const Vector3 &o) { X=o.X; Y=o.Y; Z=o.Z; return *this; }

    void set(float x,float y,float z) { X=x; Y=y; Z=z; }
};
struct Matrix3D { float Row[3][4]; };
class TextureClass {
public:
    virtual void slot0();
    unsigned short m_refCount, m_pad06;
    void Release_Ref();
};
template<class T> class RefCountPtr {
public:
    T *Ptr;
    RefCountPtr() : Ptr(0) {}
    RefCountPtr(const RefCountPtr &refCountPtr) : Ptr(refCountPtr.Ptr) { if (Ptr) ++Ptr->m_refCount; }
    ~RefCountPtr() { if (Ptr) Ptr->Release_Ref(); }
    const RefCountPtr &operator=(const RefCountPtr &);
};
class BFME2ParticleTextureHandle {
public:
    TextureClass *Ptr;
    ~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
};
class TextureAsset {
public:
    static BFME2ParticleTextureHandle Get(const char *,int,int);
    void rva00132FE9(bool);
};
class Rva0009B266 {
public:
    virtual void Release();
    int m_ref;					// +4
    RefCountPtr<TextureClass> rva0009B266(int,int,int) const;
};
class MeshModelClass;
class MeshClass { public: MeshModelClass *Get_Model(); };
struct Rva0009C0EBRef;
class Rva0009C0EB {
public:
    void rva0009C0EB(Rva0009C0EBRef **out,const AsciiString *name);
};
class ShaderClass {
public:
    unsigned m_value;
    __declspec(dllimport) __forceinline ShaderClass(const ShaderClass &shader) : m_value(shader.m_value) {}
    static ShaderClass _PresetAdditiveShader;
};
class SegLineRendererClass {
public:
    enum TextureMapMode { MAP_NONE=0,MAP_LINEAR=1,MAP_PERSPECTIVE=2 };
};
class SegmentedLineClass {
    char m_data[0x12c];
public:
    SegmentedLineClass();
    // Existing row 0x15E250 uses this spelling; retail consumes a texture-slot address.
    void Set_Texture(TextureClass *);
    void Set_Shader(ShaderClass);
    void Set_Width(float);
    void Set_Color(const Vector3 &);
    void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode);
    void Set_Disable_Sorting(int);
};
class Rva0009C134C4 {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void ReleaseChild(void *child);
};
#define SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define SLOTS16(p) SLOTS4(p##0) SLOTS4(p##1) SLOTS4(p##2) SLOTS4(p##3)
class Rva0009C134MatrixView {
public:
    SLOTS16(s0) SLOTS4(s1) virtual void s20();
    virtual void Set_Transform(const Matrix3D &);
    char pad04[0xd4-4];
    Vector3 ambient,diffuse,specular;
};
// Retail spills each light angle twice: X reads one copy, Y snapshots the
// other through memory and Z reads it again. A volatile read of an aliased
// copy reproduces that home/snapshot pair.
#define SNAP(x) (*(volatile float *)&(x))

class RenderObjClass;
RenderObjClass *Create_Render_Obj(const char *);
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
extern bool ShaderOverbrightEnabled;
class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern float g_Va00DE5E38[3],g_Va00DE5E2C[3];
float g_rva00DE5E24[2],g_rva00DE5E1C[2],g_rva00DE5E14[2],g_rva00DE5E0C[2];
extern float g_00DE5E08,g_00DE5E04,g_00DE5E00;
extern float g_00DE5E44,g_00DB4AA8,BfmeCameraPanRotationLimit,BfmeCameraPanRotationRate;
class Rva0009D55BProduct {
public:
    void rva0009C18A();
    void rva0009B28C(const Coord2D *);
};
class Rva0009C134Host
{
public:
    void rva0009CD9B();

private:
    unsigned char m_pad0[0xc4];
    Rva0009C134C4 *m_c4;			// +0xc4
    void *m_c8;					// +0xc8
    Rva0009C134MatrixView *m_cc;		// +0xcc
    Rva0009C134MatrixView *m_d0;		// +0xd0
    RenderObjClass *m_d4;			// +0xd4
    float m_d8;					// +0xd8
    float m_dc;					// +0xdc
    Vector3 m_e0;				// +0xe0
    unsigned char m_padE4[0x13c - 0xec];
    float m_13c;					// +0x13c
    unsigned char m_pad140[0x188 - 0x140];
    RenderObjClass *m_188;			// +0x188
    Rva0009C0EBRef *m_18c;			// +0x18c
    Rva0009C0EBRef *m_190;			// +0x190
    Rva0009C0EBRef *m_194;			// +0x194
    unsigned char m_pad198[0x1cc - 0x198];
    SegmentedLineClass *m_1cc;			// +0x1cc
    RefCountPtr<TextureClass> m_1d0;		// +0x1d0
};

void Rva0009C134Host::rva0009CD9B()
{
    char *src=(char *)TheLivingWorldManager+0x14;
    ShaderOverbrightEnabled=false;
    m_d4=Create_Render_Obj(((AsciiString *)src)->str());
    m_188=Create_Render_Obj("LM_SunRays");
    if (m_d4) {
        m_c4->ReleaseChild(m_d4);
        ((Rva0009D55BProduct *)this)->rva0009C18A();
        Rva0009C0EB *binder=(Rva0009C0EB *)this;
        binder->rva0009C0EB(&m_18c,(const AsciiString *)(src+0x180));
        binder->rva0009C0EB(&m_190,(const AsciiString *)(src+0x184));
        { AsciiString tmp("plane03"); binder->rva0009C0EB(&m_194,&tmp); }
        if (m_190) {
            Rva0009B266 *model=(Rva0009B266 *)((MeshClass *)m_190)->Get_Model();
            if (model) {
                RefCountPtr<TextureClass> tex=model->rva0009B266(0,0,0);
                ((TextureAsset *)&tex)->rva00132FE9(true);
                if (--model->m_ref==0) model->Release();
            }
        }
    }
    if (m_188) m_c4->ReleaseChild(m_188);
    m_e0.set(*(float *)(src+0x38),*(float *)(src+0x3c),*(float *)(src+0x40));
    ((Rva0009D55BProduct *)this)->rva0009B28C((const Coord2D *)(src+0x44));
    if (m_c8) m_c4->ReleaseChild(m_c8);
    if (m_cc) {
        Vector3 color=*(const Vector3 *)(src+0x60);
        float theta2=*(float *)(src+0x58)*0.017453292f+1.5707964f;
        float phi=*(float *)(src+0x5c)*0.017453292f;
        float theta=*(float *)(src+0x58)*0.017453292f+1.5707964f;
        float phi2=phi;
        Vector3 direction;
        direction.X=sin(theta)*cos(phi);
        direction.Y=sin(SNAP(theta2))*sin(SNAP(phi2));
        direction.Z=cos(SNAP(theta2));
        m_cc->ambient.set(0.0f,0.0f,0.0f);
        m_cc->specular.set(0.0f,0.0f,0.0f);
        m_cc->diffuse=color;
        Matrix3D tm;
        tm.Row[0][0]=1.0f; tm.Row[0][1]=0.0f; tm.Row[0][2]=direction.X; tm.Row[0][3]=0.0f;
        tm.Row[1][0]=0.0f; tm.Row[1][1]=1.0f; tm.Row[1][2]=direction.Y; tm.Row[1][3]=0.0f;
        tm.Row[2][0]=0.0f; tm.Row[2][1]=0.0f; tm.Row[2][2]=direction.Z; tm.Row[2][3]=0.0f;
        m_cc->Set_Transform(tm);
        m_c4->ReleaseChild(m_cc);
    }
    if (m_d0) {
        Vector3 color=*(const Vector3 *)(src+0x74);
        float theta2=*(float *)(src+0x6c)*0.017453292f+1.5707964f;
        float phi=*(float *)(src+0x70)*0.017453292f;
        float theta=*(float *)(src+0x6c)*0.017453292f+1.5707964f;
        float phi2=phi;
        Vector3 direction;
        direction.X=sin(theta)*cos(phi);
        direction.Y=sin(SNAP(theta2))*sin(SNAP(phi2));
        direction.Z=cos(SNAP(theta2));
        m_d0->ambient.set(0.0f,0.0f,0.0f);
        m_d0->specular.set(0.0f,0.0f,0.0f);
        m_d0->diffuse=color;
        Matrix3D tm;
        tm.Row[0][0]=1.0f; tm.Row[0][1]=0.0f; tm.Row[0][2]=direction.X; tm.Row[0][3]=0.0f;
        tm.Row[1][0]=0.0f; tm.Row[1][1]=1.0f; tm.Row[1][2]=direction.Y; tm.Row[1][3]=0.0f;
        tm.Row[2][0]=0.0f; tm.Row[2][1]=0.0f; tm.Row[2][2]=direction.Z; tm.Row[2][3]=0.0f;
        m_d0->Set_Transform(tm);
        m_c4->ReleaseChild(m_d0);
    }
    ((int *)TheW3DShadowManager)[1]=*(int *)(src+0x1d0);
    FILE *fp=fopen("livingworld.txt","rt");
    if (fp) {
        char line[100];
        for (int i=0;i<3;++i) {
            fgets(line,100,fp);
            g_Va00DE5E38[i]=(float)(atof(line)*0.017453293005625408);
            fgets(line,100,fp);
            double dist=atof(line)*m_dc;
            g_Va00DE5E2C[i]=(float)dist;
            if (i==2) break;
            fgets(line,100,fp); g_rva00DE5E24[i]=(float)atof(line);
            fgets(line,100,fp); g_rva00DE5E1C[i]=(float)atof(line);
            fgets(line,100,fp); g_rva00DE5E14[i]=(float)atof(line);
            fgets(line,100,fp); g_rva00DE5E0C[i]=(float)atof(line);
        }
        fgets(line,100,fp); g_00DE5E08=(float)atof(line);
        fgets(line,100,fp); g_00DE5E04=(float)atof(line);
        fgets(line,100,fp); g_00DE5E00=(float)atof(line);
        fclose(fp);
    }
    int index=0;
    if (TheWritableGlobalData && *((char *)TheWritableGlobalData+0xd2e)) index=1;
    m_13c=g_Va00DE5E38[index];
    m_d8=g_Va00DE5E2C[index];
    g_00DE5E44=g_rva00DE5E24[index];
    g_00DB4AA8=g_rva00DE5E1C[index];
    BfmeCameraPanRotationLimit=g_rva00DE5E14[index];
    BfmeCameraPanRotationRate=g_rva00DE5E0C[index];
    m_1cc=new SegmentedLineClass;
    m_1d0=(const RefCountPtr<TextureClass> &)TextureAsset::Get(((AsciiString *)(src+0x114))->str(),0,0);
    // 0x15E250 forwards to 0x1911E0, which dereferences this slot before Add_Ref.
    m_1cc->Set_Texture((TextureClass *)&m_1d0);
    m_1cc->Set_Shader(ShaderClass::_PresetAdditiveShader);
    m_1cc->Set_Disable_Sorting(1);
    m_1cc->Set_Width(*(float *)(src+0xec));
    {
        Vector3 color;
        color.X=*(float *)(src+0xf0);
        color.Y=*(float *)(src+0xf4);
        color.Z=*(float *)(src+0xf8);
        m_1cc->Set_Color(color);
    }
    m_1cc->Set_Texture_Mapping_Mode(SegLineRendererClass::MAP_PERSPECTIVE);
}
