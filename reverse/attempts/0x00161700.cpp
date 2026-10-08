// ?Simple_Evaluate_Pivot@HTreeClass@@QBE_NPAVHAnimClass@@HMABVMatrix3D@@PAV3@@Z
// partial score=0.65 date=2026-10-08
// cl: /O2 /Ireference/shims/bfme2htree /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
#include "htree.h"
// Retail animation vtable: Get_Transform occupies offset 0x28.
class HAnimClass {
public:
    virtual ~HAnimClass();
    virtual const char *Get_Name() const=0;
    virtual int Get_Key() const=0;
    virtual const char *Get_HName() const=0;
    virtual int Get_Num_Frames() const=0;
    virtual float Get_Frame_Rate() const=0;
    virtual float Get_Total_Time() const=0;
    virtual void RvaSlot1C() const=0;
    virtual void Get_Translation(Vector3&,int,float) const=0;
    virtual bool Get_Orientation(Quaternion&,int,float) const=0;
    virtual void Get_Transform(Matrix3D&,int,float) const=0;
};

// ZH HTreeClass::Simple_Evaluate_Pivot is the semantic guide. BFME2's
// Get_Transform virtual returns a quaternion at +0 and translation at +0x10
// (landed HCompressedAnimTransform.cpp). Retail 161700..162022 uses compact
// 0x58-byte pivots, +0x10 Parent, +0x14 Base and +0x4c Index.
struct HTreeCompactTransform {
    Quaternion Rotation;
    Vector3 Translation;
};
struct HTreeCompactPivot {
    char Name[16];
    HTreeCompactPivot *Parent;
    HTreeCompactTransform Base;
    HTreeCompactTransform Current;
    int Index;
    bool Visible;
    char Tail[7];
};
typedef char HTreeCompactPivotStride[sizeof(HTreeCompactPivot)==0x58 ? 1 : -1];
static __forceinline Quaternion compactProduct(const Quaternion &a,const Quaternion &b) {
    return Quaternion(
        (b.Z*a.Y-b.Y*a.Z)+a.X*b.W+b.X*a.W,
        (b.Y*a.W+b.W*a.Y)-(a.X*b.Z-b.X*a.Z),
        (a.X*b.Y-b.X*a.Y)+b.Z*a.W+b.W*a.Z,
        a.W*b.W-(a.X*b.X+a.Y*b.Y+a.Z*b.Z));
}
static __forceinline Vector3 compactRotate(const Quaternion &q,const Vector3 &v) {
    float x=(v.Z*q.Y-v.Y*q.Z)+v.X*q.W;
    float y=q.W*v.Y-(q.X*v.Z-v.X*q.Z);
    float z=(v.Y*q.X-v.X*q.Y)+v.Z*q.W;
    float w=-(q.X*v.X+q.Y*v.Y+q.Z*v.Z);
    return Vector3((q.Y*z-y*q.Z)+(x*q.W-w*q.X),
        (y*q.W-w*q.Y)-(q.X*z-x*q.Z),
        (y*q.X-x*q.Y)+(z*q.W-w*q.Z));
}
static __forceinline void compactMultiply(const HTreeCompactTransform &a,
    const HTreeCompactTransform &b,HTreeCompactTransform &out) {
    out.Translation=compactRotate(a.Rotation,b.Translation)+a.Translation;
    out.Rotation=compactProduct(a.Rotation,b.Rotation);
}
static __forceinline void compactMatrix(const HTreeCompactTransform &t,Matrix3D &m) {
    const Quaternion &q=t.Rotation;
    float xx=q.X*q.X*2.0f,xy=q.X*q.Y*2.0f,xz=q.Z*q.X*2.0f;
    float wx=q.W*q.X*2.0f,yy=q.Y*q.Y*2.0f,yz=q.Z*q.Y*2.0f;
    float wy=q.W*q.Y*2.0f,zz=q.Z*q.Z*2.0f,wz=q.W*q.Z*2.0f;
    m[0][0]=1.0f-yy-zz;m[0][1]=xy-wz;m[0][2]=xz+wy;
    m[1][0]=xy+wz;m[1][1]=1.0f-zz-xx;m[1][2]=yz-wx;
    m[2][0]=xz-wy;m[2][1]=yz+wx;m[2][2]=1.0f-yy-xx;
    m[0][3]=t.Translation.X;m[1][3]=t.Translation.Y;m[2][3]=t.Translation.Z;
}
// ?Simple_Evaluate_Pivot@HTreeClass@@QBE_NPAVHAnimClass@@HMABVMatrix3D@@PAV3@@Z present-unmatched
bool HTreeClass::Simple_Evaluate_Pivot(HAnimClass *motion,int pivot_index,
    float frame,const Matrix3D &obj_tm,Matrix3D *end_tm) const {
    if (!end_tm) return false;
    end_tm->Make_Identity();
    if(motion && pivot_index>=0 && pivot_index<NumPivots) {
        HTreeCompactTransform result;
        result.Rotation.Make_Identity();result.Translation.Set(0,0,0);
        for(HTreeCompactPivot *pivot=&reinterpret_cast<HTreeCompactPivot *>(Pivot)[pivot_index];
            pivot && pivot->Parent;pivot=pivot->Parent) {
            HTreeCompactTransform anim,current;
            motion->Get_Transform(reinterpret_cast<Matrix3D &>(anim),pivot->Index,frame);
            anim.Translation*=ScaleFactor;
            compactMultiply(pivot->Base,anim,current);
            compactMultiply(current,result,result);
        }
        compactMatrix(result,*end_tm);
        end_tm->preMul(obj_tm);
        return true;
    }
    return false;
}
