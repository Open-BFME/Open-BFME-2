// cl: /O1 /DNDEBUG /MD /EHsc
// W3DRopeDraw.cpp: the pool key and tossSegments retail links from this TU
// (tu_map approved), folded from two split units with these exact flags.
//
// stlport
// ?tossSegments@W3DRopeDraw@@AAEXXZ @0x000CA84D 111B: W3DRopeDraw::tossSegments clears m_segments.
// Donor BFME1 Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDraw.cpp tossSegments
// (Remove_Render_Object plus REF_PTR_RELEASE loop plus vector clear). Callers 0x000CA8BC dtor plus
// 0x000CA916 plus 0x000CAC25 call this site. Scene Remove at +0xC and Line Release at slot 0 with
// refcount at +4 per W3DLaserDraw dtor precedent. Vector clear calls rowed BfmePod16 erase 0x002BF70F.
// ?buildSegments@W3DRopeDraw@@AAEXXZ @0x000CA9F1 564B: donor BFME1 W3DRopeDraw.cpp buildSegments; it
// rebuilds the wobbling line pairs. Retail evidence: ceil through the IAT, getPosition 0x002763E6,
// GameClientRandomValueReal 0x00234111 with retail's W3DRopeDraw.cpp path and line 0x4A, Cos/Sin
// 0x2FBC0/0x2FBB0, Line3DClass ctor 0x001673D0 (0x144 bytes), scene Add_Render_Object at +8 and
// push_back through BfmeE16 0x0059D2A3. Vector3 takes its components by reference: by value the
// compiler loads them into other xmm registers than retail does.
#include <vector>
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmePod16 { int a[4]; };
struct BfmeE16 { float x, y, z, w; };


class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class Vector3
{
public:
	Vector3(const float &x, const float &y, const float &z) : X(x), Y(y), Z(z) {}

	float X;
	float Y;
	float Z;
};

class Line3DClass
{
public:
	Line3DClass(const Vector3 &start, const Vector3 &end, float width, float r, float g, float b, float opacity);
	virtual void Release();

private:
	unsigned char m_pad04[0x144 - 4];
};

void *operator new(unsigned int size);

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

float Cos(float value);
float Sin(float value);
float GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

class BfmeScene
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void Add_Render_Object(Line3DClass *obj);
	virtual void Remove_Render_Object(Line3DClass *obj);
};

// W3DDisplay::m_3DScene is an RTS3DScene (W3DLaserDrawDestructor.cpp defines it).
class RTS3DScene : public BfmeScene
{
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class DrawableModule
{
protected:
	virtual ~DrawableModule();
	void *m_moduleData;
	BFMERopeDrawable *m_drawable;
};

class DrawModule : public DrawableModule
{
protected:
	virtual ~DrawModule() {}
};

class RopeDrawInterface
{
public:
	virtual void ropeSlot();
};

struct SegInfo
{
	Line3DClass *line;
	Line3DClass *softLine;
	float wobbleAxisX;
	float wobbleAxisY;
};

class W3DRopeDraw : public DrawModule, public RopeDrawInterface
{
public:
	static NameKeyType rva000CA7F6();

private:
	_STL::vector<BfmePod16> m_segments;
	float m_curLen;
	float m_maxLen;
	float m_width;
	struct RGBColor
	{
		float red;
		float green;
		float blue;
	} m_color;
	float m_curSpeed;
	float m_maxSpeed;
	float m_accel;
	float m_wobbleLen;
	float m_wobbleAmp;
	float m_wobbleRate;
	float m_curWobblePhase;
	float m_curZOffset;

	void buildSegments();
	void tossSegments();
};

void W3DRopeDraw::buildSegments()
{
	m_segments.clear();

	int numSegs = (int)ceil(m_maxLen / m_wobbleLen);
	float eachLen = m_maxLen / (float)numSegs;
	const Coord3D *srcPos = m_drawable->getPosition();
	Coord3D pos;
	pos.x = srcPos->x;
	pos.y = srcPos->y;
	pos.z = srcPos->z;
	for (int i = 0; i < numSegs; ++i, pos.z += eachLen)
	{
		SegInfo info;

		float axis = GetGameClientRandomValueReal(0.0f, 6.283185307179586f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DRopeDraw.cpp", 0x4A);
		info.wobbleAxisX = Cos(axis);
		info.wobbleAxisY = Sin(axis);
		info.line = new Line3DClass(Vector3(pos.x, pos.y, pos.z),
			Vector3(pos.x, pos.y, pos.z + eachLen),
			m_width * 0.5f,
			m_color.red,
			m_color.green,
			m_color.blue,
			1.0f);

		info.softLine = new Line3DClass(Vector3(pos.x, pos.y, pos.z),
			Vector3(pos.x, pos.y, pos.z + eachLen),
			m_width,
			m_color.red,
			m_color.green,
			m_color.blue,
			0.5f);

		W3DDisplay::m_3DScene->Add_Render_Object(info.line);
		W3DDisplay::m_3DScene->Add_Render_Object(info.softLine);
		reinterpret_cast<_STL::vector<BfmeE16> &>(m_segments).push_back(reinterpret_cast<const BfmeE16 &>(info));
	}
}

void W3DRopeDraw::tossSegments()
{
	for (BfmePod16 *it = m_segments.begin(); it != m_segments.end(); ++it)
	{
		SegInfo *si = reinterpret_cast<SegInfo *>(it);
		if (si->line)
		{
			W3DDisplay::m_3DScene->Remove_Render_Object(si->line);
			Line3DClass *line = si->line;
			if (line)
			{
				if (--reinterpret_cast<int *>(line)[1] == 0)
					line->Release();
				si->line = 0;
			}
		}
		if (si->softLine)
		{
			W3DDisplay::m_3DScene->Remove_Render_Object(si->softLine);
			Line3DClass *soft = si->softLine;
			if (soft)
			{
				if (--reinterpret_cast<int *>(soft)[1] == 0)
					soft->Release();
				si->softLine = 0;
			}
		}
	}
	m_segments.clear();
}

// ?rva000CA7F6@W3DRopeDraw@@SA?AW4NameKeyType@@XZ @0xCA7F6
// (68B): cached pool-name key for W3DRopeDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DRopeDraw"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).
// ?rva000CA7F6@W3DRopeDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DRopeDraw::rva000CA7F6()
{
	static NameKeyType TheW3DRopeDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DRopeDraw");
	return TheW3DRopeDrawPoolKey;
}
