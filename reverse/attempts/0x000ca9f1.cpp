// ?buildSegments@W3DRopeDraw@@AAEXXZ
// partial score=0.9182 date=2026-10-05
// ?buildSegments@W3DRopeDraw@@AAEXXZ
// partial score=0.93 date=2026-09-27
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
// ?buildSegments@W3DRopeDraw@@AAEXXZ @0x000CA9F1 564B: W3DRopeDraw::buildSegments clears m_segments.
// Donor BFME1 Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDraw.cpp buildSegments
// (erase via rowed BfmePod16 0x002BF70F plus ceil/IAT plus ftol2 plus eachLen via divss plus
// getPosition pin 0x002763E6 plus GameClientRandomValueReal rowed 0x00234111 with retail file
// C:\projects\bfme2patch103\bfme2\Code\GameEngineDevice\Source\W3DDevice\GameClient\Drawable\W3DRopeDraw.cpp
// line 0x4A plus Cos/Sin rowed 0x2FBC0/0x2FBB0 plus Line3DClass ctor rowed 0x001673D0 via new rowed
// 0x0002FDA0 plus Add_Render_Object at scene +8 plus push_back via rowed BfmeE16 0x0059D2A3).
// Layout from matched siblings (toss 0xCA84D plus xfer 0xCA916 plus dtor 0xCA8BC plus FriendNew 0x54):
// DrawModule base 0x0C plus RopeDrawInterface vptr at +0x0C giving m_segments at +0x10 plus
// curLen +0x1C maxLen +0x20 width +0x24 color +0x28 curSpeed +0x34 maxSpeed +0x38 accel +0x3C
// wobbleLen +0x40 wobbleAmp +0x44 wobbleRate +0x48 curPhase +0x4C curZOffset +0x50.
#include <vector>

struct BfmePod16 { int a[4]; };
struct BfmeE16 { float x, y, z, w; };

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

class Line3DClass
{
public:
	Line3DClass(const Vector3 &start, const Vector3 &end, float width, float r, float g, float b, float opacity);
private:
	unsigned char m_pad[0x144];
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
};

class W3DDisplay
{
public:
	static BfmeScene *m_3DScene;
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
};

// ?buildSegments@W3DRopeDraw@@AAEXXZ present-unmatched
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
