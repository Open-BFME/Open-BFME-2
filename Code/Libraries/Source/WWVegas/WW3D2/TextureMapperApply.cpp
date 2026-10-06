// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmestages /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// Reference: EA GeneralsMD WW3D2/mapper.cpp, EdgeMapperClass::Apply;
// DX8Wrapper::Set_Transform(Matrix4x4) from the BFME1 reference header.
// Target: game.dat RVA 0x00184FD0, 1288 bytes (discovery batch 5).
// Identity: the already matched EdgeMapperClass constructors at 0x183410
// and 0x1834D0 install vtable 0x7D5738, whose Apply slot (+0x14) points here.
// Their class names are inherited from the ledger's donor identifications.
// Retail independently establishes Stage at +8, UseReflect at +0x18,
// Calculate_Texture_Matrix dispatch at +0x24, and the two texture-state calls.
// Other unused members/virtual declarations below follow donor ABI context;
// the unknown +0x20 virtual is reserved without asserting its signature.
// The transform projection branch writes the same transpose into two globals
// (VA 0xDEDC30 then 0xDEDBF0). Existing cross-TU references bind
// ProjectionMatrix to 0xDEDC30; the upload copy at 0xDEDBF0 is unnamed.
// The established bfmestages shim supplies the 16-texture render-state layout;
// its base is 0xDEE5D8, world +0x1EC and view +0x22C.
// Only ProjectionMatrix carries a donor name;
// the second global is address-labelled, not assigned an invented EA identity.
// GridWSClassicEnvironmentMapperClass::Apply: RVA 0x184AD0, 1266 bytes.
// Matched constructor 0x187410 installs table 0x7D5888; slot+0x14 points here.
// GridWSEnvironmentMapperClass::Apply: RVA 0x185980, 1266 bytes.
// Matched constructor 0x1874E0 installs table 0x7D58B0; slot+0x14 points here.
// Both slots are shared by other mapper tables: these rows claim one body
// per address, not a distinct recovery for each folded source identity.
// ScreenMapperClass::Apply: RVA 0x185E80, 1269 bytes. Matched constructor
// 0x13DA40 and Clone 0x13DA80 install table 0x7D32D0; slot+0x14 points here.
// The retail tail selects passthrough coordinates and COUNT3|PROJECTED.
// Each body is verified individually with /G7 /arch:SSE. No shared headers change.

#include "refcount.h"
#include "matrix4.h"
#include "vector2.h"
#include "vector3.h"
#define VERTEXMAPPER_H

// TU-only mapper ABI. Slot 0x20 is present in the target but is not named here.
class TextureMapperClass : public RefCountClass {
public:
    virtual ~TextureMapperClass();
    virtual int Mapper_ID() const;
    virtual TextureMapperClass *Clone() const;
    virtual bool Is_Time_Variant();
    virtual void Apply(int uv_array_index);
    virtual void Reset();
    virtual bool Needs_Normals();
    virtual void RetailSlot20();
    virtual void Calculate_Texture_Matrix(Matrix4x4 &matrix);
protected:
    unsigned int Stage;
};
class EdgeMapperClass : public TextureMapperClass {
public:
    virtual void Apply(int uv_array_index);
protected:
    unsigned int LastUsedSyncTime;
    float VSpeed, VOffset;
    bool UseReflect;
};
#include "rendobj.h"
#include "ww3d.h"
#include "dx8wrapper.h"

// Only the inherited interface accessed by Apply is declared here; unused
// derived object fields are intentionally not modelled.
class GridTextureMapperClass : public TextureMapperClass {};
class GridWSEnvMapperClass : public GridTextureMapperClass {};
class GridWSClassicEnvironmentMapperClass : public GridWSEnvMapperClass {
public: virtual void Apply(int uv_array_index);
};
class GridWSEnvironmentMapperClass : public GridWSEnvMapperClass {
public: virtual void Apply(int uv_array_index);
};

class ScaleTextureMapperClass : public TextureMapperClass {
public: virtual void Apply(int uv_array_index);
protected:
    Vector2 Scale;
};
class LinearOffsetTextureMapperClass : public ScaleTextureMapperClass {
protected:
    Vector2 CurrentUVOffset;
    Vector2 UVOffsetDeltaPerMS;
    unsigned int LastUsedSyncTime;
    Vector2 StartingUVOffset;
    bool ClampFix;
};
// BumpEnvTextureMapperClass: retail Apply 0x00186A90 reads LastUsedSyncTime,
// CurrentAngle, RadiansPerSecond and ScaleFactor at +0x34/+0x38/+0x3C/+0x40,
// the donor mapper.h layout above.
class BumpEnvTextureMapperClass : public LinearOffsetTextureMapperClass {
public: virtual void Apply(int uv_array_index);
protected:
    unsigned int LastUsedSyncTime;
    float CurrentAngle;
    float RadiansPerSecond;
    float ScaleFactor;
};
class ScreenMapperClass : public LinearOffsetTextureMapperClass {
public: virtual void Apply(int uv_array_index);
};
// Matched Apply DIR32 slots place this 64-byte zero-fill matrix at VA
// 0x00DEDBF0 (tools/find_dir32.py); it is the unnamed upload copy adjacent to
// DX8Wrapper::ProjectionMatrix at 0x00DEDC30.
Matrix4x4 g_mapperProjectionUpload_009EDBF0;
// Access shim only: no runtime instances or claim of a retail derived class.
struct MapperTransformAccess : DX8Wrapper {
    enum { WORLD_CHANGED=1, VIEW_CHANGED=2, WORLD_IDENTITY=1<<18, VIEW_IDENTITY=1<<19 };
    static __forceinline void SetTransform(D3DTRANSFORMSTATETYPE transform, const Matrix4x4 &m) {
        switch ((int)transform) {
        case D3DTS_WORLD:
            render_state.world=m.Transpose();
            render_state_changed=(render_state_changed & ~(unsigned)WORLD_IDENTITY) | (unsigned)WORLD_CHANGED;
            break;
        case D3DTS_VIEW:
            render_state.view=m.Transpose();
            render_state_changed=(render_state_changed & ~(unsigned)VIEW_IDENTITY) | (unsigned)VIEW_CHANGED;
            break;
        case D3DTS_PROJECTION:
            g_mapperProjectionUpload_009EDBF0=ProjectionMatrix=m.Transpose();
            ZFar=0.0f;
            ZNear=0.0f;
            DX8CALL(SetTransform(D3DTS_PROJECTION,(D3DMATRIX*)&g_mapperProjectionUpload_009EDBF0));
            break;
        default:
            DX8_RECORD_MATRIX_CHANGE();
            Matrix4x4 m2=m.Transpose();
            DX8CALL(SetTransform(transform,(D3DMATRIX*)&m2));
            break;
        }
    }
};

// ScaleTextureMapperClass::Apply: RVA 0x1844A0, 1269 bytes. The Scale vtable
// (Clone 0x183F10, Calculate_Texture_Matrix 0x182270) and the Rotate and
// SineLinearOffset tables that inherit it hold it in the Apply slot (+0x14).
void ScaleTextureMapperClass::Apply(int uv_array_index)
{
	// Set up the texture matrix
	Matrix4x4 m;
	Calculate_Texture_Matrix(m);
	MapperTransformAccess::SetTransform((D3DTRANSFORMSTATETYPE) (D3DTS_TEXTURE0+Stage),m);

	// Disable Texgen
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU | uv_array_index);

	// Tell rasterizer to expect 2D texture coordinates
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT2);
}

inline unsigned long F2DW( float f ) { return *((unsigned long*)&f); }

// BumpEnvTextureMapperClass::Apply: RVA 0x186A90, 602 bytes, the Zero Hour
// mapper.cpp body; its first call is the inherited Scale Apply at 0x1844A0.
void BumpEnvTextureMapperClass::Apply(int uv_array_index)
{
	LinearOffsetTextureMapperClass::Apply(uv_array_index);

	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta =  now - LastUsedSyncTime;
	LastUsedSyncTime=now;

	CurrentAngle+=RadiansPerSecond * delta * 0.001f;
	CurrentAngle=fmodf(CurrentAngle,2*WWMATH_PI);

	// Compute the sine and cosine for the bump matrix
	float c,s;
	c=ScaleFactor * WWMath::Fast_Cos(CurrentAngle);
	s=ScaleFactor * WWMath::Fast_Sin(CurrentAngle);

	// Set the Bump Environment Matrix
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_BUMPENVMAT00, F2DW(c));
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_BUMPENVMAT01, F2DW(-s));
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_BUMPENVMAT10, F2DW(s));
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_BUMPENVMAT11, F2DW(c));
}

void EdgeMapperClass::Apply(int uv_array_index)
{
	// Set up the texture matrix
	Matrix4x4 m;
	Calculate_Texture_Matrix(m);
	MapperTransformAccess::SetTransform((D3DTRANSFORMSTATETYPE) (D3DTS_TEXTURE0+Stage),m);

	// Get camera reflection vector
	if (UseReflect)
		DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR);
	else
		DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_CAMERASPACENORMAL);

	// Tell rasterizer to expect 2D matrices
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT2);
	
}

void GridWSClassicEnvironmentMapperClass::Apply(int uv_array_index)
{
	// Set up the texture matrix
	Matrix4x4 m;
	Calculate_Texture_Matrix(m);
	MapperTransformAccess::SetTransform((D3DTRANSFORMSTATETYPE) (D3DTS_TEXTURE0+Stage),m);

	// Get camera normals
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_CAMERASPACENORMAL);

	// Tell rasterizer to expect 2D matrices
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT2);
}

void GridWSEnvironmentMapperClass::Apply(int uv_array_index)
{
	// Set up the texture matrix
	Matrix4x4 m;
	Calculate_Texture_Matrix(m);
	MapperTransformAccess::SetTransform((D3DTRANSFORMSTATETYPE) (D3DTS_TEXTURE0+Stage),m);

	// Get camera space reflection
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR);

	// Tell rasterizer to expect 2D matrices
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT2);
}

void ScreenMapperClass::Apply(int uv_array_index)
{
	// Set up the texture matrix
	Matrix4x4 m;
	Calculate_Texture_Matrix(m);
	MapperTransformAccess::SetTransform((D3DTRANSFORMSTATETYPE) (D3DTS_TEXTURE0+Stage),m);	

	// Get camera space position
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_CAMERASPACEPOSITION);

	// Tell rasterizer what to expect
	DX8Wrapper::Set_DX8_Texture_Stage_State(Stage,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_PROJECTED | D3DTTFF_COUNT3);
}
