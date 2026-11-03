// ??0W3DStatusCircle@@QAE@XZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Retail 0x0008E54F, 97 bytes. Identity: W3DStatusCircle (RenderObjClass
// derived; rowed methods updateScreenVB 0x8E335 / updateCircleVB 0x8E623
// use the same +0xC4 triangle count, +0xE4 screen VB). Layout facts from
// target: base ctor RenderObjClass() 0x13BF00, vptrs 0xBC7850/+0 and
// 0xBC784C/+8, -1.0f at +0xCC/+0xD0, shader bits 0x10441B at +0xD8, other
// fields zero. Donor (BF1/ZH W3DStatusCircle ctor) only nulls the four
// buffer pointers; the -1.0f pair and +0xD4 are BFME 2 additions whose
// names are unknown (fieldCC/fieldD0/fieldD4).

#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"

#include "../../../../Libraries/Source/WWVegas/WWLib/MultiListObjectClass.h"

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	RenderObjClass();
	virtual int Class_ID() const;
	virtual ~RenderObjClass();

protected:
	char m_tail[0xB4];
};

struct StatusShaderBits
{
	StatusShaderBits() : bits(0x10441B) {}
	unsigned int bits;
};

class W3DStatusCircle : public RenderObjClass
{
public:
	W3DStatusCircle();
	// Compiler-generated destruction (members, then the rowed base dtor), the
	// body retail's vtable slot 0 reaches.
	virtual ~W3DStatusCircle() {}

private:
	int m_numTriangles;
	void *m_indexBuffer;
	float fieldCC;
	float fieldD0;
	int fieldD4;
	StatusShaderBits m_shaderClass;
	void *m_vertexMaterialClass;
	void *m_vertexBufferCircle;
	void *m_vertexBufferScreen;
};

W3DStatusCircle::W3DStatusCircle() :
	m_numTriangles(0), m_indexBuffer(0), fieldCC(-1.0f), fieldD0(-1.0f), fieldD4(0)
{
	m_vertexMaterialClass = 0;
	m_vertexBufferCircle = 0;
	m_vertexBufferScreen = 0;
}
