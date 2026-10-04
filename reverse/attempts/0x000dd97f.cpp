// ??0W3DBridge@@QAE@XZ
// partial score=0.99 date=2026-10-04
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ??0W3DBridge@@QAE@XZ 0x000DD97F 239B W3DBridge ctor with scale/length 1.0 via g_Va00BBB8D8 plus Matrix rows via Region3D empty ctor
// evidence: LINK BONUS 110B W3DBridgeBufferCtor waits only for this body; retail pushes 0xC8 0x114 with dtor 0x000DDA6E; calls ??_H 0x00001423 thrice with ctor 0x0047A6A9 for 3x0x10 rows at +0x3C +0x80 +0xBC; ZH donor W3DBridgeBuffer.h layout with Matrix3D as 3 Vector4 rows; BFME1 constructor donor for scalar defaults
#include "ascii_string.h"

extern float g_Va00BBB8D8;

class TextureClass
{
public:
	void Release_Ref();
};

class TextureRef
{
public:
	TextureRef() : m_ptr(0) {}
	~TextureRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	TextureClass *m_ptr;
};

class Region3D
{
public:
	Region3D();
	float a;
	float b;
	float c;
	float d;
};

class W3DBridge
{
public:
	W3DBridge();
private:
	float m_start[3];
	float m_end[3];
	float m_scale;
	float m_length;
	int m_bridgeType;
	float m_bounds[4];
	TextureRef m_bridgeTexture;
	void *m_leftMesh;
	Region3D m_leftMtx[3];
	float m_minY;
	float m_maxY;
	float m_leftMinX;
	float m_leftMaxX;
	void *m_sectionMesh;
	Region3D m_sectionMtx[3];
	float m_sectionMinX;
	float m_sectionMaxX;
	void *m_rightMesh;
	Region3D m_rightMtx[3];
	float m_rightMinX;
	float m_rightMaxX;
	int m_firstIndex;
	int m_numVertex;
	int m_firstVertex;
	int m_numPolygons;
	bool m_visible;
	AsciiString m_templateName;
	int m_curDamageState;
	bool m_enabled;
};

W3DBridge::W3DBridge() :
	m_scale(g_Va00BBB8D8),
	m_length(m_scale),
	m_bridgeType(0),
	m_bridgeTexture(),
	m_leftMesh(0),
	m_minY(0.0f),
	m_maxY(0.0f),
	m_leftMinX(0.0f),
	m_leftMaxX(0.0f),
	m_sectionMesh(0),
	m_sectionMinX(0.0f),
	m_sectionMaxX(0.0f),
	m_rightMesh(0),
	m_rightMinX(0.0f),
	m_rightMaxX(0.0f),
	m_firstIndex(0),
	m_numVertex(0),
	m_firstVertex(0),
	m_numPolygons(0),
	m_visible(false),
	m_curDamageState(0),
	m_enabled(false)
{
}
