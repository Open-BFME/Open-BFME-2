// ?renderSubBox@W3DSnowManager@@QAEXAAVRenderInfoClass@@HHHH@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME1 575ba2b04 W3DSnowManagerRenderSubBox.cpp semantic/reference guide.
// Saved cubeOriginXRemainder declaration BEFORE y preserves native ECX/EDX
// initial setup and delayed EDI save; arithmetic/loop semantics are unchanged.
/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Native93507..938C4 RET20 independently gives fields and four cube arguments.
// Target prefix grows4; resource offsets74..90, added offsets98/9C,
// statistics countA0 and brightness gateAC. FastSinTable is already owned.
#define MODPOW2(x,y) ((x) & (y-1))
#define MAXIMUM_CAMERA_DISTANCE 100000
#define SIN_TABLE_SIZE 1024
#define WWMATH_PI 3.14159265358979323846f
#define D3DLOCK_NOOVERWRITE 0x1000
#define D3DLOCK_DISCARD 0x2000
#define D3D_OK 0
#define D3DPT_POINTLIST 1
extern float _FastSinTable[SIN_TABLE_SIZE];
class WWMath {public:static __forceinline int Float_To_Int_Floor(const float&);static __forceinline float Fast_Sin(float);};
struct Vector3 {float X,Y,Z;void Set(float x,float y,float z){X=x;Y=y;Z=z;} Vector3&operator=(const Vector3&r){X=r.X;Y=r.Y;Z=r.Z;return *this;}};
class RenderInfoClass;class TextureBaseClass;
class ShaderClass {public:static ShaderClass _PresetAlphaShader; unsigned int shaderBits;};
namespace Debug_Statistics {void Record_DX8_Polys_And_Vertices(int,int,const ShaderClass&);}
struct IDirect3DDevice8;
class DX8Wrapper {public:static IDirect3DDevice8*D3DDevice;};
float Rva000930C0(float,float);
__forceinline int WWMath::Float_To_Int_Floor (const float& f)
{
	int a			= *reinterpret_cast<const int*>(&f);			// take bit pattern of float into a register
	int sign		= (a>>31);												// sign = 0xFFFFFFFF if original value is negative, 0 if positive
	a&=0x7fffffff;															// we don't need the sign any more

	int exponent	= (a>>23)-127;										// extract the exponent
	int expsign	= ~(exponent>>31);									// 0xFFFFFFFF if exponent is positive, 0 otherwise
	int imask		= ( (1<<(31-(exponent))))-1;					// mask for true integer values
	int mantissa	= (a&((1<<23)-1));								// extract mantissa (without the hidden bit)
	int r			= ((unsigned int)(mantissa|(1<<23))<<8)>>(31-exponent);	// ((1<<exponent)*(mantissa|hidden bit))>>24 -- (we know that mantissa > (1<<24))

	r = ((r & expsign) ^ (sign)) + ((!((mantissa<<8)&imask)&(expsign^((a-1)>>31)))&sign);	// if (fabs(value)<1.0) value = 0; copy sign; if (value < 0 && value==(int)(value)) value++;
	return r;
}

__forceinline float WWMath::Fast_Sin(float val)
{
	val*=float(SIN_TABLE_SIZE) / (2.0f * WWMATH_PI);

	int idx0=Float_To_Int_Floor(val);
	int idx1=idx0+1;
	float frac=val-(float)idx0;

	idx0 = ((unsigned)idx0) & (SIN_TABLE_SIZE-1);
	idx1 = ((unsigned)idx1) & (SIN_TABLE_SIZE-1);
	
	return (1.0f - frac) * _FastSinTable[idx0] + frac * _FastSinTable[idx1];
}

enum { SNOW_NOISE_X = 64, SNOW_NOISE_Y = 64 };

struct POINTVERTEX
{
	Vector3 v;
	unsigned int diffuse;
};

// Retail calls 0x00723C50 on this W3DSnowManager (thunk 0x00038C4E); the
// ledger still names it by its address-derived class.
class Rva000932E1
{
public:
	float rva000932E1();
};

struct Rva00093507VertexBuffer;
struct Rva00093507VertexBufferVtable
{
	void *slots00[11];
	long (__stdcall *Lock)(Rva00093507VertexBuffer *, unsigned, unsigned, void **, unsigned);
	long (__stdcall *Unlock)(Rva00093507VertexBuffer *);
};
struct Rva00093507VertexBuffer { Rva00093507VertexBufferVtable *vtable; };

// BFME binds a D3D9 device: DrawPrimitive is slot 81.
struct Rva00093507Device;
struct Rva00093507DeviceVtable
{
	void *slots00[81];
	long (__stdcall *DrawPrimitive)(Rva00093507Device *, unsigned, unsigned, unsigned);
};
struct Rva00093507Device { Rva00093507DeviceVtable *vtable; };

class W3DSnowManager
{
public:
	void renderSubBox(RenderInfoClass &, int, int, int, int);
private:
	char pad00[12];
	float *m_startingHeights;
	float m_time, m_velocity, m_fullTimePeriod;
	float m_frequencyScaleX, m_frequencyScaleY, m_amplitude;
	float m_pointSize, m_maxPointSize, m_minPointSize, m_quadSize;
	float m_boxDimensions, m_emitterSpacing;
	unsigned char m_isVisible, m_flag3D;
	char pad42[0x74 - 0x42];
	void *m_indexBuffer;
	TextureBaseClass *m_snowTexture;
	Rva00093507VertexBuffer *m_vertexBuffer;
	int m_dwBase, m_dwFlush, m_dwDiscard, m_leafDim;
	float m_snowCeiling, m_heightTraveled,m_offsetX,m_offsetY;
	int m_totalRendered;
	float m_cullOverscan;
	int m_unknownA8;
	int m_brightnessGate;
};

void W3DSnowManager::renderSubBox(RenderInfoClass &rinfo, int originX, int originY, int cubeDimX, int cubeDimY)
{
	int cubeOriginXRemainder = originX;
	int y = originY;
	int totalPart = (cubeDimX - originX) * (cubeDimY - originY);
	int spacing = (int)m_emitterSpacing;
	if (spacing < 1)
		spacing = 1;
	totalPart /= spacing * spacing;
	m_totalRendered += totalPart;

	int gray;
	if (m_brightnessGate)
		gray = (int)(((Rva000932E1 *)this)->rva000932E1() * 255.0f);
	else
		gray = 255;
	unsigned int color = gray * 0x10101 + 0xFF000000;

	while (totalPart)
	{
		int batchSize = totalPart;
		if (batchSize > m_dwFlush)
			batchSize = m_dwFlush;
		if (m_dwBase + batchSize > m_dwDiscard)
			m_dwBase = 0;

		POINTVERTEX *verts;
		if (m_vertexBuffer->vtable->Lock(m_vertexBuffer, m_dwBase * sizeof(POINTVERTEX), batchSize * sizeof(POINTVERTEX),
			(void **)&verts, m_dwBase ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD) != D3D_OK)
			return;

		int numberInBatch = 0;
		for (; y < cubeDimY; y += spacing)
		{
			for (int x = cubeOriginXRemainder; x < cubeDimX; x += spacing)
			{
				if (numberInBatch >= batchSize)
				{
					cubeOriginXRemainder = x;
					goto flush_particles;
				}
				int noiseOffset = MODPOW2(x + MAXIMUM_CAMERA_DISTANCE, SNOW_NOISE_X) +
					MODPOW2(y + MAXIMUM_CAMERA_DISTANCE, SNOW_NOISE_Y) * SNOW_NOISE_X;
				if (noiseOffset > SNOW_NOISE_X * SNOW_NOISE_Y)
					noiseOffset = 0;
				float h0 = m_snowCeiling - Rva000930C0(m_startingHeights[noiseOffset] + m_heightTraveled, m_boxDimensions);
				Vector3 snowCenter;
				snowCenter.Set((float)x, (float)y, h0);
				snowCenter.X += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleX + (float)x);
				snowCenter.Y += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleY + (float)y);
				snowCenter.X += m_offsetX; snowCenter.Y += m_offsetY;
				verts->v = snowCenter;
				verts->diffuse = color;
				verts++;
				numberInBatch++;
			}
			cubeOriginXRemainder = originX;
		}

flush_particles:
		m_vertexBuffer->vtable->Unlock(m_vertexBuffer);
		if (numberInBatch)
		{
			Debug_Statistics::Record_DX8_Polys_And_Vertices(numberInBatch * 2, numberInBatch * 4, ShaderClass::_PresetAlphaShader);
			Rva00093507Device *device = (Rva00093507Device *)DX8Wrapper::D3DDevice;
			device->vtable->DrawPrimitive(device, D3DPT_POINTLIST, m_dwBase, numberInBatch);
			totalPart -= numberInBatch;
			m_dwBase += numberInBatch;
		}
	}
}
