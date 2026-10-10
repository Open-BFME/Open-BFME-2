// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc
// stlport
//
// ?drawRiverWater@WaterRenderObjClass@@IAEXAAVRenderInfoClass@@PAVRenderableRiverArea@@@Z
// retail 0x00100A0B..0x001011CA (1983 bytes) EH thiscall ret 8.
// BFME 2's river draw (WorldBuilder twin 0x00765E80, W3DWaterDraw.cpp lines
// 686..937). Zero Hour/BFME 1 W3DWater.cpp drawRiverWater is the donor: the
// skip above the water LOD (the river's +0x40 holder value through the rowed
// getter 0x002A98AB against TheGameLODManager +0x1784), the rowed
// Invalidate_Cached_Render_States, two indexed triangles per river section
// into a dynamic index buffer, the standing water colour (here the holder's
// +0x50 colour through the rowed 0x0007E0EA) with the legacy terrain
// lighting and the time-of-day water diffuse (+0x158 stride 0x30, index
// +0x258), the wobbling V coordinate from WWMath::Fast_Sin and the vertex
// pairs walked outward from the start of the boundary (the river's
// Coord3D vector at +0x14 and V origin at +0x10). BFME 2 then draws through
// the river's FX rendering method (rowed 0x00083A50, the same stack calls as
// W3DRoadBufferDrawRoads.cpp) and resets the vertex and pixel shaders.
// Codegen notes: the boundary is an STLport vector (its size is re-read after
// every vertex store); the pushed method is an explicit temporary copied into
// the by-value argument; the pass count lives in a block opened before the
// push, which lets it share the diffuse slot as retail's frame does.
#include <vector>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

extern "C" double __cdecl sqrt(double);

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	~RefCountPtr(void)
	{
		if (Referent)
			Referent->Release_Ref();
	}
	T *Peek(void) const { return Referent; }
	T *operator->(void) const { return Referent; }

private:
	T *Referent;
};

namespace FXShader {
class RenderingMethod : public RefCountClass
{
public:
	virtual void slot1();
	virtual bool Begin(Int *passCount, Int flags);	// slot 2
	virtual void Begin_Pass(Int pass);	// slot 3
	virtual void slot4();
	virtual void End_Pass(void);	// slot 5
	virtual void End(void);	// slot 6
};
}

typedef _STL::vector<RefCountPtr<FXShader::RenderingMethod>, _STL::allocator<RefCountPtr<FXShader::RenderingMethod> > > RenderingMethodStackType;

class RenderInfoClass
{
public:
	void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod> method);
	void Pop_Rendering_Method(void);
	const RenderingMethodStackType &Get_Rendering_Method_Stack(void) const;
};

void Rva001688FF(const RefCountPtr<FXShader::RenderingMethod> *methods, Int count);
void Rva00168952(const RefCountPtr<FXShader::RenderingMethod> *methods, Int count);

#define PAD_STDCALL10(p) \
	virtual void __stdcall p##0() = 0; virtual void __stdcall p##1() = 0; virtual void __stdcall p##2() = 0; \
	virtual void __stdcall p##3() = 0; virtual void __stdcall p##4() = 0; virtual void __stdcall p##5() = 0; \
	virtual void __stdcall p##6() = 0; virtual void __stdcall p##7() = 0; virtual void __stdcall p##8() = 0; \
	virtual void __stdcall p##9() = 0;

struct IDirect3DDevice8
{
	PAD_STDCALL10(d0) PAD_STDCALL10(d1) PAD_STDCALL10(d2) PAD_STDCALL10(d3) PAD_STDCALL10(d4)
	PAD_STDCALL10(d5) PAD_STDCALL10(d6) PAD_STDCALL10(d7) PAD_STDCALL10(d8)
	virtual void __stdcall d90() = 0; virtual void __stdcall d91() = 0;
	virtual long __stdcall SetVertexShader(void *shader) = 0;	// slot 92
	PAD_STDCALL10(e0)
	virtual void __stdcall f103() = 0; virtual void __stdcall f104() = 0;
	virtual void __stdcall f105() = 0; virtual void __stdcall f106() = 0;
	virtual long __stdcall SetPixelShader(void *shader) = 0;	// slot 107
};

extern unsigned number_of_DX8_calls;

struct Matrix3D
{
	Real Row[3][4];
	Matrix3D(bool identity)
	{
		if (identity) {
			Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
			Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
			Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
		}
	}
};

class Matrix4
{
public:
	__forceinline Matrix4 &operator=(const Matrix3D &m)
	{
		Row[0][0] = m.Row[0][0]; Row[0][1] = m.Row[0][1]; Row[0][2] = m.Row[0][2]; Row[0][3] = m.Row[0][3];
		Row[1][0] = m.Row[1][0]; Row[1][1] = m.Row[1][1]; Row[1][2] = m.Row[1][2]; Row[1][3] = m.Row[1][3];
		Row[2][0] = m.Row[2][0]; Row[2][1] = m.Row[2][1]; Row[2][2] = m.Row[2][2]; Row[2][3] = m.Row[2][3];
		Row[3][0] = 0.0f; Row[3][1] = 0.0f; Row[3][2] = 0.0f; Row[3][3] = 1.0f;
		return *this;
	}
	Real Row[4][4];
};

// DX8Wrapper::render_state (VA 0x00DEE5D8, dx8wrapper.cpp): Zero Hour's
// RenderStateStruct (bfmestages/dx8wrapper.h) -- shader, material,
// Textures[16], Lights[4] and LightEnable[4] (0x1EC bytes), then world at
// +0x1EC (0x00DEE7C4).
struct RenderStateStruct
{
	unsigned char m_pad00[0x1EC];
	Matrix4 world;
};

class DynamicIBAccessClass
{
public:
	DynamicIBAccessClass(UnsignedShort type, UnsignedShort index_count);
	~DynamicIBAccessClass();

	class WriteLockClass
	{
	public:
		WriteLockClass(DynamicIBAccessClass *ib_access);
		~WriteLockClass();
		UnsignedShort *Get_Index_Array() { return Indices; }
	private:
		DynamicIBAccessClass *DynamicIBAccess;
		UnsignedShort *Indices;
		int m_guard;
	};

private:
	unsigned char m_data[0xC];
};

struct VertexFormatXYZNDUV2
{
	Real x, y, z;
	Real nx, ny, nz;
	UnsignedInt diffuse;
	Real u1, v1;
	Real u2, v2;
};

class DynamicVBAccessClass
{
public:
	DynamicVBAccessClass(unsigned type, unsigned format_index, UnsignedShort vertex_count, unsigned declaration);
	~DynamicVBAccessClass();

	class WriteLock
	{
	public:
		WriteLock(DynamicVBAccessClass *vb_access);
		~WriteLock();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	private:
		DynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;
		int m_guard;
	};

private:
	unsigned char m_data[0x18];
};

class DX8Wrapper
{
public:
	static void Invalidate_Cached_Render_States(void);
	static void Set_Index_Buffer(const DynamicIBAccessClass &ib_access, UnsignedShort index_base_offset);
	static void Set_Vertex_Buffer(const DynamicVBAccessClass &vb_access);
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count, unsigned min_vertex_index, unsigned vertex_count);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

	static __forceinline void Set_World(const Matrix3D &m)
	{
		render_state.world = m;
		render_state_changed |= 0x1;
		render_state_changed &= ~0x40000;
	}
	static __forceinline void Set_Vertex_Shader(void *shader)
	{
		_Get_D3D_Device8()->SetVertexShader(shader);
		number_of_DX8_calls++;
	}
	static __forceinline void Set_Pixel_Shader(void *shader)
	{
		_Get_D3D_Device8()->SetPixelShader(shader);
		number_of_DX8_calls++;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned int render_state_changed;
	static RenderStateStruct render_state;
};

#define SIN_TABLE_SIZE 1024
extern float _FastSinTable[];

struct WWMathView
{
	static __forceinline int Float_To_Int_Floor(const float &f)
	{
		int a = *reinterpret_cast<const int *>(&f);
		int sign = (a >> 31);
		a &= 0x7fffffff;

		int exponent = (a >> 23) - 127;
		int expsign = ~(exponent >> 31);
		int imask = ((1 << (31 - (exponent)))) - 1;
		int mantissa = (a & ((1 << 23) - 1));
		int r = ((unsigned int)(mantissa | (1 << 23)) << 8) >> (31 - exponent);

		r = ((r & expsign) ^ (sign)) + ((!((mantissa << 8) & imask) & (expsign ^ ((a - 1) >> 31))) & sign);
		return r;
	}

	static __forceinline float Fast_Sin(float val)
	{
		val *= float(SIN_TABLE_SIZE) / (2.0f * 3.141592654f);

		int idx0 = Float_To_Int_Floor(val);
		int idx1 = idx0 + 1;
		float frac = val - (float)idx0;

		idx0 = ((unsigned)idx0) & (SIN_TABLE_SIZE - 1);
		idx1 = ((unsigned)idx1) & (SIN_TABLE_SIZE - 1);

		return (1.0f - frac) * _FastSinTable[idx0] + frac * _FastSinTable[idx1];
	}
};

#define PI 3.14159265359f

struct RGBColor
{
	Real red, green, blue;
};

class GlobalData
{
public:
	unsigned char m_pad000[0x8D8];
	RGBColor m_terrainAmbient[3];	// +0x8D8
	RGBColor m_terrainDiffuse[3];	// +0x8FC
	Coord3D m_terrainLightPos[3];	// +0x920
	unsigned char m_pad944[0x988 - 0x944];
	Int m_numGlobalLights;	// +0x988
};
extern GlobalData *TheWritableGlobalData;

class GameLODManager
{
public:
	unsigned char m_pad0[0x1784];
	Int m_waterLOD;	// +0x1784
};
extern GameLODManager *TheGameLODManager;

// The river's +0x40 holder: its LOD word through the rowed 4-byte getter.
class Rva002A98ABDwordField
{
public:
	int get() const;
};

// The rowed 0x0007E0EA: the address of the holder's +0x50 colour.
class Rva0007E0EA
{
public:
	int rva0007E0EA();
};

class RenderableRiverArea
{
public:
	RefCountPtr<FXShader::RenderingMethod> rva00083A50();

	Int getNumPoints() const { return m_points.size(); }
	const Coord3D *getPoint(Int i) const { return &m_points[i]; }
	Rva002A98ABDwordField *getHolder() const { return m_holder; }
	const RGBColor *getColor() { return (const RGBColor *)reinterpret_cast<Rva0007E0EA *>(this)->rva0007E0EA(); }
	Real getRiverVOrigin() const { return m_riverVOrigin; }

private:
	unsigned char m_pad00[0x10];
	Real m_riverVOrigin;	// +0x10
	_STL::vector<Coord3D> m_points;	// +0x14
	unsigned char m_pad20[0x40 - 0x20];
	Rva002A98ABDwordField *m_holder;	// +0x40
};

struct WaterSettingView
{
	UnsignedInt waterDiffuse;
	unsigned char m_pad04[0x30 - 0x04];
};

class WaterRenderObjClass
{
protected:
	void drawRiverWater(RenderInfoClass &rinfo, RenderableRiverArea *pRiver);

	unsigned char m_pad000[0x134];
	Bool m_drawingRiver;	// +0x134
	Bool m_disableRiver;	// +0x135
	unsigned char m_pad136[0x158 - 0x136];
	WaterSettingView m_settings[5];	// +0x158
	unsigned char m_pad248[0x258 - 0x248];
	Int m_tod;	// +0x258
};

void WaterRenderObjClass::drawRiverWater(RenderInfoClass &rinfo, RenderableRiverArea *pRiver)
{
	Int waterLOD = TheGameLODManager->m_waterLOD;
	if (pRiver->getHolder()->get() > waterLOD)
		return;

	DX8Wrapper::Invalidate_Cached_Render_States();

	Int rectangleCount = pRiver->getNumPoints() / 2;
	rectangleCount--;

	if (m_disableRiver)
		return;
	m_drawingRiver = true;

	DynamicIBAccessClass ib_access(2, (rectangleCount + 1) * 2 * 3);
	{
		DynamicIBAccessClass::WriteLockClass lockib(&ib_access);
		UnsignedShort *curIb = lockib.Get_Index_Array();
		for (Int i = 0; i < rectangleCount; i++)
		{
			curIb[0] = i * 2;
			curIb[1] = i * 2 + 1;
			curIb[2] = i * 2 + 3;

			curIb[3] = i * 2;
			curIb[4] = i * 2 + 3;
			curIb[5] = i * 2 + 2;

			curIb += 6;
		}
	}

	Real shadeR = pRiver->getColor()->red;
	Real shadeG = pRiver->getColor()->green;
	Real shadeB = pRiver->getColor()->blue;

	if (shadeR == 1.0f && shadeG == 1.0f && shadeB == 1.0f)
	{
		shadeR = TheWritableGlobalData->m_terrainAmbient[0].red;
		shadeG = TheWritableGlobalData->m_terrainAmbient[0].green;
		shadeB = TheWritableGlobalData->m_terrainAmbient[0].blue;

		for (Int lightIndex = 0; lightIndex < TheWritableGlobalData->m_numGlobalLights; lightIndex++)
		{
			if (-TheWritableGlobalData->m_terrainLightPos[lightIndex].z > 0)
			{
				shadeR += -TheWritableGlobalData->m_terrainLightPos[lightIndex].z * TheWritableGlobalData->m_terrainDiffuse[lightIndex].red;
				shadeG += -TheWritableGlobalData->m_terrainLightPos[lightIndex].z * TheWritableGlobalData->m_terrainDiffuse[lightIndex].green;
				shadeB += -TheWritableGlobalData->m_terrainLightPos[lightIndex].z * TheWritableGlobalData->m_terrainDiffuse[lightIndex].blue;
			}
		}

		Real waterShadeR = (m_settings[m_tod].waterDiffuse & 0xff) / 255.0f;
		Real waterShadeG = ((m_settings[m_tod].waterDiffuse >> 8) & 0xff) / 255.0f;
		Real waterShadeB = ((m_settings[m_tod].waterDiffuse >> 16) & 0xff) / 255.0f;

		shadeR = shadeR * waterShadeR * 255.0f;
		shadeG = shadeG * waterShadeG * 255.0f;
		shadeB = shadeB * waterShadeB * 255.0f;
	}
	else
	{
		shadeR = shadeR * 255.0f;
		shadeG = shadeG * 255.0f;
		shadeB = shadeB * 255.0f;

		if (shadeR == 0 && shadeG == 0 && shadeB == 0)
		{
			shadeR = 255;
			shadeG = 255;
			shadeB = 255;
		}
	}

	Int diffuse = (Int)shadeB | ((Int)shadeG << 8) | ((Int)shadeR << 16);
	diffuse |= m_settings[m_tod].waterDiffuse & 0xff000000;

	Int innerNdx = 0;
	Int outerNdx = innerNdx + 1;

	Real endLen = 0;
	Real totalLen = 0;
	Int i;
	for (i = 0; i < pRiver->getNumPoints() - 1; i++)
	{
		Real dx = pRiver->getPoint(i)->x - pRiver->getPoint(i + 1)->x;
		Real dy = pRiver->getPoint(i)->y - pRiver->getPoint(i + 1)->y;
		Real curLen = sqrt(dx * dx + dy * dy);
		totalLen += curLen;
		if (i == innerNdx)
			endLen = curLen;
	}

	Real lengthOfRiver = (totalLen / 2) - endLen;
	Real repeatCount = lengthOfRiver / (endLen);

	Real vScale = (Real)repeatCount / (Real)rectangleCount;

	if (innerNdx >= pRiver->getNumPoints() - 1)
		return;

	DynamicVBAccessClass vb_access(2, 5, (rectangleCount + 1) * 2, 0);
	{
		DynamicVBAccessClass::WriteLock lock(&vb_access);
		VertexFormatXYZNDUV2 *vb = lock.Get_Formatted_Vertex_Array();

		Real constA = 3 * pRiver->getRiverVOrigin();

		for (i = 0; i < (pRiver->getNumPoints() / 2); i++)
		{
			const Coord3D *innerPt = pRiver->getPoint(outerNdx);
			const Coord3D *outerPt = pRiver->getPoint(innerNdx);
			outerNdx++;
			innerNdx--;
			if (innerNdx < 0) {
				innerNdx = pRiver->getNumPoints() - 1;
			}
			if (outerNdx >= pRiver->getNumPoints()) {
				outerNdx = 0;
			}

			vb->x = innerPt->x;
			vb->y = innerPt->y;
			vb->z = innerPt->z;
			vb->diffuse = diffuse;

			Real wobbleConst = vScale * (Real)i + WWMathView::Fast_Sin(2 * PI * (vScale * (Real)i) - constA) / 22.0f - pRiver->getRiverVOrigin();
			vb->v1 = wobbleConst;
			vb->u1 = 0.5f;
			vb->v2 = wobbleConst;
			vb->u2 = 1.0f;
			vb->nx = 0;
			vb->ny = 0;
			vb->nz = 1.0f;
			vb++;

			vb->x = outerPt->x;
			vb->y = outerPt->y;
			vb->z = outerPt->z;
			vb->diffuse = diffuse;
			vb->v1 = wobbleConst;
			vb->u1 = 0;
			vb->v2 = wobbleConst;
			vb->u2 = 0;
			vb->nx = 0;
			vb->ny = 0;
			vb->nz = 1.0f;
			vb++;
		}
	}

	Matrix3D tm(true);
	DX8Wrapper::Set_World(tm);
	DX8Wrapper::Set_Index_Buffer(ib_access, 0);
	DX8Wrapper::Set_Vertex_Buffer(vb_access);

	if (!pRiver->rva00083A50().Peek())
		return;

	{
		Int passes;
		rinfo.Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod>(pRiver->rva00083A50()));
		Rva001688FF(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
		RefCountPtr<FXShader::RenderingMethod> current = rinfo.Get_Rendering_Method_Stack()[0];
		if (current->Begin(&passes, 0xffff))
		{
			for (Int pass = 0; pass < passes; pass++)
			{
				current->Begin_Pass(pass);
				DX8Wrapper::Draw_Triangles(0, rectangleCount * 2, 0, (rectangleCount + 1) * 2);
				current->End_Pass();
			}
			current->End();
		}
		Rva00168952(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
		rinfo.Pop_Rendering_Method();
		DX8Wrapper::Set_Vertex_Shader(0);
		DX8Wrapper::Set_Pixel_Shader(0);
	}
}
